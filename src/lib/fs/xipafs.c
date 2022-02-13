/*
 * Copyright (c) 2021 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 */

/*
   _  __ ________  ___         ___________
  | |/ //  _/ __ \/   |       / ____/ ___/
  |   / / // /_/ / /| |      / /_   \__ \ 
 /   |_/ // ____/ ___ |     / __/  ___/ / 
/_/|_/___/_/   /_/  |_|____/_/    /____/  
                     /_____/              

𝗲𝗫𝗲𝗰𝘂𝘁𝗲 𝗜𝗻 𝗣𝗹𝗮𝗰𝗲 𝗔𝗵𝗲𝗮𝗱 𝗼𝗳 𝘁𝗶𝗺𝗲 𝗙𝗶𝗹𝗲 𝗦𝘆𝘀𝘁𝗲𝗺

*/

#include "xipafs.h"
#include "xipa_dev.h"
/*

What do we need:
- A vector that can hold the struct pointers that contain the details for each file
- The aforementioned struct, which should contain a SHA-256 hash to check binary integrity, a version code,
an interpreter name/code (in this case solely WASM, but this is to build compatibility for other frameworks)
a file name which can be used to lookup using a linear search.
(because we only have a few records, sorting by filename and binary searching will be unnecessary (but cool!))

Scenario - what happens if write interrupted by power loss?
Solution - we check every entry's SHA256 hash (stored in internal LittleFS/FAT32 partition) and compare it to the hash of the binary. 
If there is a mismatch, the binary data is invalid and will be discarded/freed.
We can provide error messages for this sort of scenario. 

We will also need some kind of standardised error declaration system.
By this I mean a standard, but separate set of codes that the zephyr implementation/shim
will adapt to the zephyr specific error codes. 

We will use an atomic file operation system - kind of like how GParted works, but we make
adding, removing files a composition of granular processes that 

*/

LOG_LEVEL_SET(LOG_LEVEL_INF);

#define XIPA_ERR_CHECK(logger, message, rc) \
if(rc < 0) \
{ \
    LOG_INST_ERR(logger, message); \
    return rc; \
}

/*

[||||||||||[(  app 1   )(    app 2     )(     app 3      )     free space     ]|||||||||]
     ^                                          
     |
64KB superblock
*/


int populate_record(struct xipafs *x, volatile unsigned int *offset);
int xipa_fs_align(struct xipafs *x);
int xipa_fs_verifyparams(struct xipafs_params *ptr);


struct privatefs_ptr
{
    //struct vector filerecord_list; //now unnecessary as we are not loading the entire table into memory.
    bool init;
    uint32_t num_files;
    const struct flash_area *pfa;
    struct xipafs_params *param;
    struct xipa_dev *xip;
    struct vector operations; //stores pointers to functions in order of atomic operations.
    struct stack superblock_locations;
    struct filerecord f; 
    size_t offset;
};

struct xipa_superblock_loc
{
    volatile unsigned int record;
    volatile uint8_t* superblock_start; //with respect to processor address space!
};

//Good - after reading nrfxlib documentation, it seems apparently possible to hash
//items of arbitrary length. This will come in very handy for hashing the large binaries.

//XIPA-FS filesystems, to minimise unnecessary aligns and wearing down the flash, will have a fixed
//starting block of 64 KiloBytes. This will contain all the required information about the binary files.
//The file system keep some information stored

//TODO - Change offsets to ENDING OFFSETS -> Done!! YAY!!

int arr_contains_int(uint8_t array[], uint8_t value, int len)
{
    for(int i = 0; i < len; i++)
    {
        if(array[i]==value)
        {
            return i;
        }
    }
    return -1;
}

int arr_contains_string(char* array[], char* value, int len)
{
    for(int i = 0; i < len; i++)
    {
        if(strcmp(array[i], value))
        {
            return i;
        }
    }
    return -1;
}

const char* xipa_file_extensions[] =
{
    "ext", //superblock pointer
    "pdf", //pdf
    "wsm", //wasm binary
    "bin", //misc binary file
    DEL_NAME, //deleted file for overwriting
    "ttf", //font file
    "txt", //text file
    "zip", //zip file
    "png", //PNG image
    "jpg", //JPG image
    "svg", //SVG image (vector)
    "bmp", //Bitmap image
    "prt", //Part download
    "jso", //JSON
    "xml", //XML
    "htm", //HTML
    "mp3", //MP3 - but like is this actually going to be used?
    "wav", //WAV - really?!    
};

//In XIPA_FS, the sizes for the individual fields that make up the 64 bytes are totally fixed.
//You have control over the location of each field within the filesystem, so this function
//will check if the offsets you've put in correspond to valid sizes!
int xipa_fs_check_sizes(uint8_t offsets[6], uint8_t sizes[6], int len)
{
    //finding which offset is first - i.e whichever one subtracted by it's size ends up with zero. if we can't find 
    //one then the offsets are invalid!
    uint8_t zero_offset = -1;
    for(int i = 0; i < len; i ++)
    {
        if((offsets[i]-sizes[i])==0)
        {
            zero_offset = i;
            break;
        }         
    }
    if(zero_offset == -1)
    {
        return -EINVAL;
    }
    for (int i = 0; i < len; i ++)
    {
        if(i==zero_offset)
        {
            i++;
        }
        else
        {
            int hyp_index = arr_contains_int(offsets, (offsets[i]-sizes[i]), len); //hypothesized index
            if(hyp_index == -1 || hyp_index == zero_offset)
            {
                return -1;
            }
            /*
            This code works off the idea that every offset, when subtracted from its corresponding size, 
            should end up with another offset that exists within the array, apart from the very first offset which will end up 
            at zero. This is why whenever we reach the offset that we computed earlier, we increment i to skip over it. 
            */
        }
    }
    if(arr_contains_int(offsets, XIPA_JOURNAL_SIZE, len))
    {
        return 1; //theoretically the above check should have checked for this condition, but just to be extra safe
        //i have explicitly expressed the same check here. 
    }
    return -1;
}


int xipa_fs_verifyparams(struct xipafs_params *ptr)
{
    int rc = 1;
    //we want to perform lots of very similar checks, so it makes sense to serialise the struct
    //into an array temporarily and perform our checks.
    uint8_t serialisecheck[7] = { 0 }; //8 bit array makes sense because are you really, really going to have a record size larger than 255 bytes? what kind of hash are u using lmfao
    serialisecheck[0] = ptr->name_end_offset;
    serialisecheck[1] = ptr->hash_end_offset;
    serialisecheck[2] = ptr->loc_end_offset;
    serialisecheck[3] = ptr->size_end_offset;
    serialisecheck[4] = ptr->vers_end_offset;
    serialisecheck[5] = ptr->run_end_offset;
    uint8_t sizes[6] = {NAME_SIZE, HASH_SIZE, LOC_SIZE, SIZE_SIZE, VER_STR_SIZE, RUN_SIZE};


    for (int i = 0; i < ARRAY_SIZE(serialisecheck); i++)
    {
            //All offsets must be word aligned   //Offsets cannot be greater than final journal size       //None of the offests can be zero otherwise these fields do not exist.       
        if (serialisecheck[i] % 4 != 0 || serialisecheck[i] > serialisecheck[ARRAY_SIZE(serialisecheck)-1] || serialisecheck[i] == 0)
        {
            rc = -EINVAL;
            return rc;
        }
    }
    if(xipa_fs_check_sizes(serialisecheck, sizes, ARRAY_SIZE(serialisecheck)) == -1)
    {
        rc = -EINVAL;
        return rc;
    }
    if(ptr->flash_area_id < 0)
    {
        rc = -EINVAL;
        return rc;
    }
    if(ptr->path == NULL)
    {
        rc = -EINVAL;
        return rc;
    }
    return rc;
}

//Ensure filesystem is formatted to XIPA_FS before mounting. Returns ENOENT if superblock not found
int xipa_fs_mount(struct xipafs* x, struct xipafs_params* params)
{
    int rc;
    char buf[4]; //We are looking for XIPA at the start of the filesystem, effectively a permanent superblock marking a particular
    //storage medium as XIPA_FS.
    int fs_param_ret_code = xipa_fs_verifyparams(params);
    XIPA_ERR_CHECK(x->log, "Invalid parameters, check and remount!", fs_param_ret_code);

    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    //ptr->f = k_malloc(sizeof(struct filerecord)); //allocating memory from kernel heap to ensure files can still be traversed in low memory conditions
    ptr->param = params;
    x->mountpoint = ptr->param->path;
    rc = flash_area_open(ptr->param->flash_area_id, &ptr->pfa);
    if (rc < 0)
    {
        flash_area_close(ptr->pfa);
        return rc;
    }
    //const struct device* fdev = flash_area_get_device((const struct flash_area*)ptr->param->flash_area_id);
    
    rc = flash_area_read(ptr->pfa, 0, buf, sizeof(buf)); //we can safely use single word read writes according to nordic product specification, so this is fine.
    if (rc < 0)
    {
        if (rc == -EIO)
        {
            LOG_INST_INF(x->log, "I/O Error - could not read device");
        }
    }
    if (strcmp(buf, xipa_fs_start_block) != 0)
    {
        LOG_INST_INF(x->log, "Superblock not found! Is filesystem formatted to XIPA?");
        return -ENOENT;
    }
    ptr->offset = ptr->pfa->fa_off;
    char numfiles[4];
    rc = flash_area_read(ptr->pfa, 4, numfiles, 4); //getting number of files on filesystem.
    if (rc < 0)
    {
        return rc;
    }
    ptr->num_files = (uint32_t) numfiles;
    LOG_INST_INF(x->log, "Number of files - %d", ptr->num_files);
    flash_area_close(ptr->pfa); //NOP right now, but for future compatibility this is fine.
    ptr->xip = k_malloc(sizeof(struct xipa_dev));
    rc = xip_init(ptr->xip);
    XIPA_ERR_CHECK(x->log, "Could not init XIP!", rc);

    rc = xip_setoffset(ptr->xip, ptr->offset);
    XIPA_ERR_CHECK(x->log, "Could not set XIP offset!", rc);

    rc = xip_enable(ptr->xip);
    XIPA_ERR_CHECK(x->log, "Could not enable XIP!", rc);

    /*
    We want to use the stack to keep track of where we've gotten up to in the superblock traversal. 
    If we end up at a record with file extension "ext", we will store the current value of "record" in the stack
    and start traversing the new superblock at the given location, and so on so forth. 
    When the function finishes traversing this level of superblock, it will pop a new record off the stack and 
    resume where it left off. 
    */
    stack_init(&ptr->superblock_locations, 4, sizeof(struct xipa_superblock_loc));

    ptr->init = true;

    return 1;
}

int xipa_fs_unmount(struct xipafs *x)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    if (!ptr->init)
        return -EINVAL;
    //k_free(ptr->f); //free filerecord to prevent further transactions.
    xip_disable(ptr->xip);
    k_free(ptr->xip); //free xip to prevent further manipulation
    //this should leave QSPI peripheral in a state where standard flash manipulation commands should work perfectly
    //with no XIPA_FS manipulation. 
    ptr->init = false;
    return 1;
}

int xipa_fs_dir_init(struct xipafs* x, struct xipafs_dir_t* dir)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    dir = malloc(sizeof(struct xipafs_dir_t));
    if(dir!=NULL)
    {
        dir->current_record = 1;
        dir->current_records_to_traverse = ptr->num_files;
        return 1;
    }
    return -ENOMEM; 
}

int xipa_fs_dir_deinit(struct xipafs* x, struct xipafs_dir_t* dir)
{
    free(dir);
    return 1;
}
//https://stackoverflow.com/questions/54964154/is-memcpyvoid-dest-src-n-with-a-volatile-array-safe
//This function is a volatile safe memcpy for XIP region reads and validation. 
volatile void *xipa_vol_memcpy(volatile void *restrict dest,
            const volatile void *restrict src, size_t n) {
    const volatile unsigned char *src_c = src;
    volatile unsigned char *dest_c      = dest;

    while (n > 0) {
        n--;
        dest_c[n] = src_c[n];
    }
    return  dest;
}

int xipa_fs_populate_record(struct xipafs *x, struct filerecord* f, unsigned int record, volatile uint8_t* tableStart)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    if (!ptr->init)
        return -EINVAL;
    xipa_vol_memcpy(ptr->f.run, (volatile uint8_t*)(tableStart + ((record-1)<<6) + ptr->param->run_end_offset - RUN_SIZE), RUN_SIZE);
    if(ptr->f.run != NULL)
    {
        xipa_vol_memcpy(ptr->f.name, (volatile uint8_t*)(tableStart + ((record-1)<<6) + ptr->param->name_end_offset - NAME_SIZE), NAME_SIZE);
        ptr->f.file_loc = *(volatile uint8_t*)(tableStart + ((record-1)<<6) + ptr->param->loc_end_offset - LOC_SIZE);
        ptr->f.size =  *(volatile uint8_t*)(tableStart + ((record-1)<<6) + ptr->param->size_end_offset - SIZE_SIZE);
        if(ptr->f.file_loc != (volatile uint8_t*)0x0 || ptr->f.size != (size_t)0x0)
        {
            xipa_vol_memcpy(ptr->f.hash, (volatile uint8_t*)(tableStart + ((record-1)<<6) + ptr->param->hash_end_offset - HASH_SIZE), HASH_SIZE);
            xipa_vol_memcpy(ptr->f.ver_str, (volatile uint8_t*)(tableStart + ((record-1)<<6) + ptr->param->vers_end_offset - VER_STR_SIZE), VER_STR_SIZE);
            ptr->f.record_loc = *(volatile uint8_t*)(tableStart + ((record - 1)<<6));
            f = &ptr->f;
            return 1;
        }
        else {
            f = NULL;
            return -EINVAL;
        }
    }
    else
    {
        f = NULL;
        return -EINVAL;
    }
    return -EIO;
}


int xipa_fs_traverse(struct xipafs *x, struct filerecord* f, struct xipafs_dir_t* dir) //every call to this function will update the filerecord with details of the next file, until the end of directory is reached.
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    if (!ptr->init)
        return -EINVAL;
    volatile uint8_t *tableStart = (volatile uint8_t*)(ptr->param->xip_dev_location + sizeof(ptr->num_files) + sizeof(xipa_fs_start_block)); //first 4 bytes (machine word) is the identifier superblock, next 4 bytes is the number of files.
    if(dir->current_records_to_traverse > 1)
    {
        xipa_vol_memcpy(ptr->f.run, (volatile uint8_t*)(tableStart + ((dir->current_record-1)<<6) + ptr->param->run_end_offset - RUN_SIZE), RUN_SIZE);
        if(strcmp(ptr->f.run, "ext") == 0)
        {
            volatile struct xipa_superblock_loc yeet = {.record = dir->current_record, .superblock_start = tableStart};
            //This should be ok, stack_push carries out malloc and copies manually internally rather than just storing pointers.
            stack_push(&ptr->superblock_locations, (struct xipa_superblock_loc*)&yeet);
            //No memcpy required here as we are reading a known datatype.
            volatile uint8_t* new_tablestart = *(volatile uint8_t*)(tableStart + ((dir->current_record-1)<<6) + ptr->param->loc_end_offset - LOC_SIZE);
            tableStart = new_tablestart;
            dir->current_record = (volatile unsigned int)1;
        }
        else if(arr_contains_string((char**)xipa_file_extensions, ptr->f.run, ARRAY_SIZE(xipa_file_extensions))==-1) //Checking if file extension is null or garbage, meaning a valid record does not exist (i.e we have moved into the null area) and we need to stop traversing.
        {
            if(stack_length(&ptr->superblock_locations)>0)
            {
                volatile struct xipa_superblock_loc back = *(volatile struct xipa_superblock_loc*)stack_pop(&ptr->superblock_locations);
                volatile unsigned int records_left = dir->current_records_to_traverse - (dir->current_record - back.record);
                tableStart = back.superblock_start;
                dir->current_record = back.record;
                dir->current_records_to_traverse = dir->current_record + records_left;
                if(dir->current_records_to_traverse > ptr->num_files)
                {
                    LOG_INST_ERR(x->log, "IO Error - rtt %i > num_files %i", dir->current_records_to_traverse, ptr->num_files);
                    return -EIO;
                }
            }
            else
            {
                dir->current_records_to_traverse = 1;
            }
        }
        else
        {
            if(ptr->f.run[RUN_SIZE-1]=='\0')
            {
                int rc = xipa_fs_populate_record(x, f, dir->current_record, tableStart); //this is sorta shitty as we're passing the filerecord pointer down three levels...
                XIPA_ERR_CHECK(x->log, "Could not populate record", rc);
                return rc;
            }
        }
        dir->current_record++;
    }
    else 
    {
        return -ENOTDIR;
        LOG_INST_WRN(x->log, "Reached end of directory, reset dir structure");
    }
    return -EIO;
}

//Mount before calling this function - TODO add nice documentation to all the XIPA functions.

int xipa_fs_get_file(struct xipafs *x, char *filename, struct filerecord* f)
{
    char *fname;
    char *ext;
    char *context = NULL;
    int rc;
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    if (!ptr->init)
        return -EINVAL;
    fname = strtok_r(filename, ".", &context);
    ext = strtok_r(NULL, ".", &context);
    if (fname == NULL || ext == NULL)
    {
        return -EINVAL;
    }
    struct xipafs_dir_t dir;
    xipa_fs_dir_init(x, &dir);
    //each journal entry is 64 bytes (#wordaligned gang) so we will iterate through until we find our entry!
    //We maintain the number of files to avoid needessly iterating over the entire 64KB superblock region.
    //This means that there must be no gaps within the entries!!

    while((strcmp(ptr->f.name, fname) == 0) && (strcmp(ptr->f.run, ext)==0))
    {
        if(rc = xipa_fs_traverse(x, f, &dir) < 0)
        {
            return rc;
        }
    }
    return 1;
}

//Ensure XIP threads are disabled before calling this!
int xipa_fs_format(struct xipafs* x)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    if(!ptr->init)
    {
        LOG_INST_ERR(x->log, "XIPA not initialised!");
        return -EINVAL;
    }
    int rc = flash_area_open(ptr->pfa->fa_id, &ptr->pfa);
    XIPA_ERR_CHECK(x->log, "Could not open flash area", rc);

    LOG_INST_WRN(x->log, "Formatting filesystem to XIPA!");
	rc = flash_area_erase(ptr->pfa, 0, ptr->pfa->fa_size);
    XIPA_ERR_CHECK(x->log, "Format failed", rc);

    rc = flash_area_write(ptr->pfa, 0, xipa_fs_start_block, sizeof(xipa_fs_start_block)); //writing identifier block
    XIPA_ERR_CHECK(x->log, "Could not write identifier block", rc);

    rc = flash_area_write(ptr->pfa, (off_t)sizeof(xipa_fs_start_block), 0, sizeof(int)); //writing file number block
    XIPA_ERR_CHECK(x->log, "Could not write file number block", rc);

    flash_area_close(ptr->pfa);
    return 1;
} 


int xipa_fs_verify(struct xipafs* x)
{
    return -EOPNOTSUPP;
}
int xipa_fs_store(struct xipafs* x, char* filename)
{
    return -EOPNOTSUPP;
}

//Pause XIP apps before calling this unless you love chaos and death.
int xipa_fs_delete(struct xipafs* x, char* filename)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    volatile uint8_t* deletion_offset = 0;
    volatile uint8_t* record_offset = 0;
    size_t size = 0;
    int rc = xipa_fs_get_file(x, filename, NULL); //we don't need an accessible pointer, we will manipulate directly from within. 
    XIPA_ERR_CHECK(x->log, "Could not get file name!", rc);
    if(ptr->f.record_loc==(volatile uint8_t*)0 || ptr->f.file_loc==(volatile uint8_t*)0 || ptr->f.size==0)
    {
        LOG_INST_ERR(x->log, "Offsets zero!");
        return -EINVAL;
    }

    //switching to xip disable mode and using flash driver to delete the file.
    xip_disable(ptr->xip);
    rc = flash_area_open(ptr->pfa->fa_id, &ptr->pfa);
    XIPA_ERR_CHECK(x->log, "Could not open flash area!", rc);

    rc = flash_area_erase(ptr->pfa, (off_t)ptr->f.file_loc-(off_t)ptr->param->xip_dev_location, size);
    XIPA_ERR_CHECK(x->log, "Could not erase file!", rc);
    LOG_INST_INF(x->log, "Erased %i byte file data at %i (0-based offset)", size, (off_t)deletion_offset-(off_t)ptr->param->xip_dev_location);

    rc = flash_area_write(ptr->pfa, (off_t)ptr->f.record_loc-(off_t)ptr->param->xip_dev_location+(off_t)ptr->param->run_end_offset-(off_t)RUN_SIZE, &DEL_NAME, RUN_SIZE);
    XIPA_ERR_CHECK(x->log, "Could not erase file record!", rc);
    LOG_INST_INF(x->log, "Marked %i byte file record at %i (0-based offset) as erased", XIPA_JOURNAL_SIZE, (off_t)record_offset-(off_t)ptr->param->xip_dev_location);

    rc = xipa_fs_align(x); //this function will align the main memory blocks 
    return rc;
}
