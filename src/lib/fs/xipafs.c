/*
 * Copyright (c) 2022 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 * 
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


int xipa_fs_populate_record(struct xipafs *x, struct filerecord* f, unsigned int record, volatile uint8_t* tableStart);
int xipa_fs_align(struct xipafs *x, struct filerecord f_del);
int xipa_fs_verifyparams(struct xipafs_params *ptr);
int arr_contains_int(uint8_t array[], uint8_t value, int len);
int arr_contains_string(char* array[], char* value, int len);
int xipa_fs_check_sizes(uint8_t offsets[6], uint8_t sizes[6], int len);
int xipa_fs_traverse_flash_api(struct xipafs *x, struct filerecord* f, struct xipafs_dir_t* dir);


static char xipa_fs_start_block[8] = {'X', 'I', 'P', 'A', '\0', '\0', '\0', '\0'}; //get rid of null terminator messing up byte sizes. 

/**
 * @brief Main container for XIPA_FS implementation. 
 * 
 * 
 */
struct privatefs_ptr
{
     /** Current number of files in the filesystem - including superblock records */
    uint32_t num_files;
    //struct vector filerecord_list; //now unnecessary as we are not loading the entire table into memory.
    /** Current number of superblocks in the filesystem - populated at mount time */
    uint32_t num_superblocks;
    /** Zephyr struct representing current flash area */
    const struct flash_area *pfa;
    /** XIPA_FS parameter struct, containing offsets, XIP region address, and desired XIP offset */
    struct xipafs_params *param;
    /** XIPA_FS device struct, exposes APIs for HW specific operations */
    struct xipa_dev *xip;
    /** List/vector containing function pointers - TODO: add mutex/lock functionality to lock file system for writes, but reads should still be allowed. for thread safety */
    struct vector operations; 
    /** Storing superblock locations during traverse operation to ensure no files are left after a superblock traversal */
    struct stack superblock_locations;
    /** Storing superblock locations during traverse operation with FLASH API to ensure no files are left after a superblock traversal */
    struct stack superblock_flash_dev_locations;
    /** Internal filerecord */
    struct filerecord f; 
    /** Pointer represented as integer pointing to end of the file-system. Subtract from start offset of flash area to get space used. */
    unsigned int last_file_end;
    /** Starting offset */
    size_t offset;
    bool init;
    int64_t storing;
};

struct __attribute__((__packed__)) xipa_superblock_loc //packed to shove into stack safely. is a multiple of 4 bytes so we should be ok.
{
    volatile unsigned int record;
    volatile uint8_t* superblock_start; //with respect to processor address space!
};

//Good - after reading nrfxlib documentation, it seems apparently possible to hash
//items of arbitrary length. This will come in very handy for hashing the large binaries.

//XIPA-FS filesystems, to minimise unnecessary aligns and wearing down the flash, will have a fixed
//starting block of 64 KiloBytes. This will contain all the required information about the binary files.

/**
 * @brief Helper funcion to return the index of a number stored in an array
 * 
 * @param array Input array
 * @param value Desired integer to find
 * @param len Length of array
 * @return Index of element if found, else -1.
 */
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

/**
 * @brief Helper funcion to return the index of a string stored in an array
 * 
 * @param array Input array
 * @param value Desired string to find
 * @param len Length of array
 * @return Index of element if found, else -1.
 */
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
    "ext", /** superblock pointer */
    "pdf", /** pdf */
    "bin", /** misc binary file */
    "wsm", /** wasm binary */
    DEL_NAME, /** file marked for deletion */
    FREE_NAME, /** freed file after align operation */
    "ttf", /** font file */
    "txt", /** text file */
    "zip", /** zip file */
    "png", /** PNG image */
    "jpg", /** JPG image */
    "svg", /** SVG image (vector) */
    "bmp", /** Bitmap image */
    "prt", /** Part download */
    "jso", /** JSON */
    "xml", /** XML */
    "htm", /** HTML */
    "mp3", /** MP3 - but like is this actually going to be used? */
    "wav", /** WAV - really?!   */  
};

//In XIPA_FS, the sizes for the individual fields that make up the 64 bytes are totally fixed.
//You have control over the location of each field within the filesystem, so this function
//will check if the offsets you've put in correspond to valid sizes!
/**
 * @brief Helper function to help verify user-specified offsets
 * 
 * @param offsets Array populated with offsets
 * @param sizes Expected sizes
 * @param len Length of 
 * @return int 
 */
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

/**
 * @brief Function to check if user specified parameters make sense or not. These are basic sanity checks only! 
 * 
 * @param ptr Pointer to populated parameter struct.
 * @return 1 if parameters valid, negative err code otherwise. 
 */
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
/**
 * @brief Mount a XIPA partition with specified offset parameters.
 * 
 * @param x xipafs disk object
 * @param params struct containing offset parameters for file parsing and XIP handling.
 * @return 1 on success, negative err code otherwise. 
 */
int xipa_fs_mount(struct xipafs* x, struct xipafs_params* params)
{
    int rc;
    char buf[4]; //We are looking for XIPA at the start of the filesystem, effectively a permanent superblock marking a particular
    //storage medium as XIPA_FS.
    char check[4] = "XIPA";
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
    if (strcmp(buf, check) != 0)
    {
        LOG_INST_INF(x->log, "Superblock not found! Is filesystem formatted to XIPA?");
        return -ENOENT;
    }
    //char numsuperblocks[4];
    rc = flash_area_read(ptr->pfa, 4, buf, sizeof(buf)); //getting number of superblocks on filesystem.
    if (rc < 0)
    {
        return rc;
    }
    ptr->num_superblocks = (uint32_t) buf;   //we must add the device offset now, because we have gone down a layer of abstraction.
    ptr->offset = ptr->pfa->fa_off;
    char numfiles[4];
    rc = flash_area_read(ptr->pfa, sizeof(xipa_fs_start_block), numfiles, 4); //getting number of files on filesystem.
    if (rc < 0)
    {
        return rc;
    }
    ptr->num_files = (uint32_t) numfiles;
    LOG_INST_INF(x->log, "Number of files - %d", ptr->num_files);
    flash_area_close(ptr->pfa); //NOP right now, but for future compatibility this is fine.
    ptr->init = true;
    /*
    We want to use the stack to keep track of where we've gotten up to in the superblock traversal. 
    If we end up at a record with file extension "ext", we will store the current value of "record" in the stack
    and start traversing the new superblock at the given location, and so on so forth. 
    When the function finishes traversing this level of superblock, it will pop a new record off the stack and 
    resume where it left off. 
    */
    stack_init(&ptr->superblock_locations, ptr->num_superblocks, sizeof(struct xipa_superblock_loc));
    stack_init(&ptr->superblock_flash_dev_locations, ptr->num_superblocks, sizeof(struct xipa_superblock_loc));
    struct xipafs_dir_t temp_dir;
    struct filerecord tempfr;
    xipa_fs_dir_init(x, &temp_dir); //ignore uninitialised warning
    do {
        rc = xipa_fs_traverse_flash_api(x, &tempfr, &temp_dir);
        if(rc < 0)
        {
            if(rc == -ENOTDIR)
            {
                ptr->last_file_end = (unsigned int)(tempfr.file_loc + tempfr.size);
                break;
            }
            else return -EIO;
        }
    }
    while(arr_contains_string((char**)xipa_file_extensions, tempfr.run, SIZE_SIZE) && tempfr.name[sizeof(tempfr.name)-1] == '\0');
    xipa_fs_dir_deinit(x, &temp_dir);

    ptr->xip = k_malloc(sizeof(struct xipa_dev));
    rc = xip_init(ptr->xip);
    XIPA_ERR_CHECK(x->log, "Could not init XIP!", rc);

    rc = xip_setoffset(ptr->xip, ptr->offset);
    XIPA_ERR_CHECK(x->log, "Could not set XIP offset!", rc);

    rc = xip_enable(ptr->xip);
    XIPA_ERR_CHECK(x->log, "Could not enable XIP!", rc);


    ptr->storing = -1;

    return 1;
}

/**
 * @brief Unmount XIPA file system. Ensure all pending operations have been completed.
 * 
 * @param x xipafs disk pointer
 * @return 1 on success, -EBUSY if operations pending, else negative err code.
 */
int xipa_fs_unmount(struct xipafs *x)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    if (!ptr->init)
        return -EINVAL;
    if(vector_length(&ptr->operations) == 0)
    {
        //k_free(ptr->f); //free filerecord to prevent further transactions.
        xip_disable(ptr->xip);
        k_free(ptr->xip); //free xip to prevent further manipulation
        //this should leave QSPI peripheral in a state where standard flash manipulation commands should work perfectly
        //with no XIPA_FS manipulation. 
        stack_destroy(&ptr->superblock_flash_dev_locations);
        stack_destroy(&ptr->superblock_locations);
        vector_deinit(&ptr->operations);
        ptr->init = false;
        return 1;
    }
    else return -EBUSY;
}

/**
 * @brief Initialises directory context object from heap for file traversal.
 * 
 * @param x xipafs disk object
 * @param dir xipafs directory pointer
 * @return 1 on success, else negative err code.
 */
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

/**
 * @brief Frees resources allocated for a directory context object.
 * 
 * @param x xipafs disk object
 * @param dir xipafs directory pointer
 * @return 1 on success
 */
int xipa_fs_dir_deinit(struct xipafs* x, struct xipafs_dir_t* dir)
{
    free(dir);
    return 1;
}
//https://stackoverflow.com/questions/54964154/is-memcpyvoid-dest-src-n-with-a-volatile-array-safe
//This function is a volatile safe memcpy for XIP region reads and validation. 
volatile void *xipa_vol_memcpy(volatile void *restrict dest,
                               const volatile void *restrict src, size_t n) 
{
    const volatile unsigned char *src_c = src;
    volatile unsigned char *dest_c = dest;

    while (n > 0)
    {
        n--;
        dest_c[n] = src_c[n];
    }
    return  dest;
}
/**
 * @brief Helper function to translate a filerecord to a buffer of memory, ready to write to filesystem.
 * 
 * @param x xipafs disk object
 * @param f pointer to filerecord
 * @param record record number to update
 * @param tableStart pointer to start of memory location.
 * @return 1 on success, negative err code otherwise.
 * @exception You must ensure the record and tablestart values make sense - buffer overflow is not checked! 
 */
int xipa_fs_write_temp_record(struct xipafs *x, struct filerecord* f, unsigned int record, volatile uint8_t* tableStart)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    if(!ptr->init)
        return -EINVAL;
    if(f->file_loc != NULL && f->hash != NULL && f->name != NULL && f->run != NULL && f->size != 0 && f->ver_str != NULL)
    {
        if(ptr->f.file_loc != (volatile uint8_t*)0x0 || ptr->f.size != (size_t)0x0)
        {
            volatile uint8_t* journal_loc = (tableStart + ((record-1)<<6));
            xipa_vol_memcpy((volatile uint8_t*)(journal_loc + ptr->param->run_end_offset - RUN_SIZE), f->run, RUN_SIZE);
            xipa_vol_memcpy((volatile uint8_t*)(journal_loc + ptr->param->name_end_offset - NAME_SIZE), f->name, NAME_SIZE);
            xipa_vol_memcpy((volatile uint8_t*)(journal_loc + ptr->param->loc_end_offset - LOC_SIZE), f->file_loc, LOC_SIZE);
            xipa_vol_memcpy((volatile uint8_t*)(journal_loc + ptr->param->size_end_offset - SIZE_SIZE), &f->size, SIZE_SIZE);
            xipa_vol_memcpy((volatile uint8_t*)(journal_loc + ptr->param->hash_end_offset - HASH_SIZE), f->hash, HASH_SIZE);
            xipa_vol_memcpy((volatile uint8_t*)(journal_loc + ptr->param->vers_end_offset - VER_STR_SIZE), f->ver_str, VER_STR_SIZE);
            return 1;
        }
        else return -EINVAL;
    }
    else return -EINVAL;
    return -EIO;
}

/**
 * @brief Helper function to translate a record stored in memory into a filerecord for manipulation.
 * 
 * @param x xipafs disk object
 * @param f pointer to filerecord
 * @param record record number inside memory region
 * @param tableStart pointer to memory region.
 * @return 1 on success, negative err code otherwise
 * @exception Bounds are not checked! Please ensure your offsets are correct!
 */
int xipa_fs_populate_record(struct xipafs *x, struct filerecord* f, unsigned int record, volatile uint8_t* tableStart)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    if (!ptr->init)
        return -EINVAL;
    //refactored the journal arithmetic to make it more readable.
    volatile uint8_t* journal_location = (volatile uint8_t*)(tableStart + ((record-1)<<6));
    xipa_vol_memcpy(ptr->f.run, journal_location + ptr->param->run_end_offset - RUN_SIZE, RUN_SIZE);
    if(ptr->f.run != NULL)
    {
        xipa_vol_memcpy(ptr->f.name, journal_location + ptr->param->name_end_offset - NAME_SIZE, NAME_SIZE);
        ptr->f.file_loc = __LOC(journal_location + ptr->param->loc_end_offset - LOC_SIZE);
        ptr->f.size = (size_t)*journal_location + ptr->param->size_end_offset - SIZE_SIZE;
        if(ptr->f.file_loc != (volatile uint8_t*)0x0 || ptr->f.size != (size_t)0x0)
        {
            xipa_vol_memcpy(ptr->f.hash, journal_location + ptr->param->hash_end_offset - HASH_SIZE, HASH_SIZE);
            xipa_vol_memcpy(ptr->f.ver_str, journal_location + ptr->param->vers_end_offset - VER_STR_SIZE, VER_STR_SIZE);
            ptr->f.record_loc = journal_location;
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

/**
 * @brief Traverse through the flash - but using the flash driver in XIP disable mode.
 * 
 * @param x xipafs disk object
 * @param f pointer to filerecord to fill with file details (including superblock!)
 * @param dir directory context object
 * @return 1 on success, -ENOTDIR at end of filesystem, negative err code otherwise.
 */
int xipa_fs_traverse_flash_api(struct xipafs *x, struct filerecord* f, struct xipafs_dir_t* dir)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    if (!ptr->init)
        return -EINVAL;
    const struct device* flash_dev = flash_area_get_device((const struct flash_area*)&ptr->pfa);
    volatile uint8_t* tableStart = (volatile uint8_t*)(ptr->offset + sizeof(ptr->num_files) + sizeof(xipa_fs_start_block)); //first 4 bytes (machine word) is the identifier superblock, next 4 bytes is the number of files.
    if(dir->current_records_to_traverse > 1)
    {
        char journal[XIPA_JOURNAL_SIZE];
        flash_read(flash_dev, (off_t)tableStart+(dir->current_record*XIPA_JOURNAL_SIZE), journal, XIPA_JOURNAL_SIZE);
        struct filerecord temp_fr;
        xipa_fs_populate_record(x, &temp_fr, 1, journal);
        if(strcmp(temp_fr.run, "ext") == 0)
        {
            if(ptr->num_superblocks < 2) return -EIO;
            xipa_fs_populate_record(x, f, 1, journal);
            volatile struct xipa_superblock_loc yeet = {.record = dir->current_record, .superblock_start = tableStart};
            //This should be ok, stack_push carries out malloc and copies manually internally rather than just storing pointers.
            stack_push(&ptr->superblock_flash_dev_locations, (struct xipa_superblock_loc*)&yeet);
            //No memcpy required here as we are reading a known datatype.
            volatile uint8_t* new_tablestart = temp_fr.file_loc + ptr->offset;
            tableStart = new_tablestart;
            dir->current_record = (volatile unsigned int)1;
        }
        else if(arr_contains_string((char**)xipa_file_extensions, ptr->f.run, ARRAY_SIZE(xipa_file_extensions))==-1) //Checking if file extension is null or garbage, meaning a valid record does not exist (i.e we have moved into the null area) and we need to stop traversing.
        {
            if(stack_length(&ptr->superblock_flash_dev_locations)>0)
            {
                if(ptr->num_superblocks < 2) return -EIO;
                volatile struct xipa_superblock_loc* back_ptr = (volatile struct xipa_superblock_loc*)stack_pop(&ptr->superblock_locations);
                volatile struct xipa_superblock_loc back = *back_ptr;
                free(back_ptr);
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
                int rc = xipa_fs_populate_record(x, f, 1, journal); //this is a bit crap as we're passing the filerecord pointer down three levels...
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


/**
 * @brief Traverse through the flash in XIP enable mode.
 * 
 * @param x xipafs disk object
 * @param f pointer to filerecord to fill with file details (including superblock!)
 * @param dir directory context object
 * @return 1 on success, -ENOTDIR at end of filesystem, negative err code otherwise.
 */
int xipa_fs_traverse(struct xipafs *x, struct filerecord* f, struct xipafs_dir_t* dir) //every call to this function will update the filerecord with details of the next file, until the end of directory is reached.
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    if (!ptr->init)
        return -EINVAL;
    volatile uint8_t *tableStart = (volatile uint8_t*)(ptr->param->xip_dev_location + sizeof(ptr->num_files) + sizeof(xipa_fs_start_block) + sizeof(ptr->num_superblocks)); //first 4 bytes (machine word) is the identifier superblock, next 4 bytes is the number of files.
    if(dir->current_records_to_traverse > 1)
    {
        xipa_vol_memcpy(ptr->f.run, (volatile uint8_t*)(tableStart + ((dir->current_record-1)<<6) + ptr->param->run_end_offset - RUN_SIZE), RUN_SIZE);
        if(strcmp(ptr->f.run, "ext") == 0)
        {
            if(ptr->num_superblocks < 2) return -EIO;
            volatile struct xipa_superblock_loc yeet = {.record = dir->current_record, .superblock_start = tableStart};
            //This should be ok, stack_push carries out malloc and copies manually internally rather than just storing pointers.
            stack_push(&ptr->superblock_locations, (struct xipa_superblock_loc*)&yeet);
            //No memcpy required here as we are reading a known datatype.
            //Additionally, since the location offsets are done with respect to the start of the flash, we need to add the xip dev location
            //and subtract the xip offset to jump to the correct place in XIP memory space.
            volatile uint8_t* new_tablestart = __LOC(tableStart + ((dir->current_record-1)<<6) + ptr->param->loc_end_offset - LOC_SIZE) + (unsigned int)ptr->param->xip_dev_location - (unsigned int)ptr->param->xip_device_offset;
            tableStart = new_tablestart;
            dir->current_record = (volatile unsigned int)1;
        }
        else if(arr_contains_string((char**)xipa_file_extensions, ptr->f.run, ARRAY_SIZE(xipa_file_extensions))==-1) //Checking if file extension is null or garbage, meaning a valid record does not exist (i.e we have moved into the null area) and we need to stop traversing.
        {
            if(stack_length(&ptr->superblock_locations)>0)
            {
                if(ptr->num_superblocks < 2) return -EIO;
                volatile struct xipa_superblock_loc* back_ptr = (volatile struct xipa_superblock_loc*)stack_pop(&ptr->superblock_locations);
                volatile struct xipa_superblock_loc back = *back_ptr;
                free(back_ptr);
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
                int rc = xipa_fs_populate_record(x, f, dir->current_record, tableStart); //eek we're passing the filerecord pointer down three levels...
                XIPA_ERR_CHECK(x->log, "Could not populate record", rc);
                f->file_loc = f->file_loc + (unsigned int)(ptr->param->xip_dev_location - ptr->param->xip_device_offset);
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

//Mount before calling this function - TODO add nice documentation to all the XIPA functions ->TODO DONE YAAYY!!

/**
 * @brief Returns the first instance of a file designated by filename in a filerecord f. 
 * 
 * @param x xipafs disk object
 * @param filename Desired filename with extension
 * @param f Pointer to filerecord to populate with information about the file if found.
 * @return f -> NULL if file not found, 1 on success, -ENFILE if file not found, negative err code otherwise.
 */
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
    stack_clear(&ptr->superblock_locations);
    struct xipafs_dir_t dir;
    xipa_fs_dir_init(x, &dir);
    //each journal entry is 64 bytes (#wordaligned gang) so we will iterate through until we find our entry!
    //We maintain the number of files to avoid needessly iterating over the entire 64KB superblock region.
    //This means that there must be no gaps within the entries!!
    //*.* is just nonsense so we will return EINVAL.
    if((strcmp(fname, "*")==0) && (strcmp(ext, "*")==0))
    {
        return -EINVAL;
    }
    else if((strcmp(fname, "*")==0)) //strtok is null terminated
    //if the file name is *.extension, this will give the first instance of that extension. 
    {
        for(int i = 0; i < ptr->num_files; i ++)
        {
            rc = xipa_fs_traverse(x, f, &dir);
            if(rc < 0)
            {
                LOG_INST_WRN(x->log, "Code: %i", rc);
                return rc;
            }
            if(strcmp(ptr->f.run, ext)==0)
            {
                return 1;
            }
        }
    }
    else if(strcmp(ext, "*")==0) //strtok is null terminated
    //if the file name is name.*, this will give the first instance of that name. 
    {
        for(int i = 0; i < ptr->num_files; i ++)
        {
            rc = xipa_fs_traverse(x, f, &dir);
            if(rc < 0)
            {
                LOG_INST_WRN(x->log, "Code: %i", rc);
                return rc;
            }
            if(strcmp(ptr->f.name, fname)==0)
            {
                return 1;
            }
        }
    }
    else
    {
        for(int i = 0; i < ptr->num_files; i ++)
        {
            rc = xipa_fs_traverse(x, f, &dir);
            if(rc < 0)
            {
                LOG_INST_WRN(x->log, "Code: %i", rc);
                return rc;
            }
            if((strcmp(ptr->f.name, fname) == 0) && (strcmp(ptr->f.run, ext)==0))
            {
                return 1;
            }
        }
    }
    return -ENFILE;
    //stack is not cleared until next read operation, should traverse be a private method?
}

/**
 * @brief Format the filesystem - hard delete all files and records.
 * @exception 1) WARNING - FORMAT OPERATION IS IRREVERSIBLE! 
 * @exception 2) Stop all XIP utilising threads to prevent crashes.
 * 
 * @param x xipafs disk object
 * @return 1 on success, else negative err code. 
 */
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
     //Bounding erase logic not required as we are erasing entirety of flash, which is a multiple of 4096 as it's all the sectors.
	rc = flash_area_erase(ptr->pfa, 0, ptr->pfa->fa_size);
    XIPA_ERR_CHECK(x->log, "Format failed", rc);

    rc = flash_area_write(ptr->pfa, 0, xipa_fs_start_block, sizeof(xipa_fs_start_block)); //writing identifier block
    XIPA_ERR_CHECK(x->log, "Could not write identifier block", rc);

    rc = flash_area_write(ptr->pfa, (off_t)sizeof(xipa_fs_start_block), 0, sizeof(int)); //writing file number block
    XIPA_ERR_CHECK(x->log, "Could not write file number block", rc);

    flash_area_close(ptr->pfa);
    return 1;
} 

/**
 * @brief This function will use your hardware crypto acceleration (if present) to verify the integrity of a particular file by calculating a SHA-256 hash, and comparing it to the known hash. Ensure the correct drivers and Kconfig directives are selected!  
 * 
 * @param x xipafs disk object
 * @param f_verify filerecord of the desired file to verify
 * @return 1 on success, -1 if file is corrupt.
 */
int xipa_fs_verify(struct xipafs* x, struct filerecord* f_verify)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    xip_enable(ptr->xip);
    uint32_t passes = 0;
    //we are hardcoding a 1024 byte pass here, not really any need for more.
    volatile uint8_t* start_addr = f_verify->file_loc + (unsigned int)(ptr->param->xip_dev_location);// - (unsigned int)(ptr->param->xip_device_offset);
    while(start_addr + (passes * 1024) < f_verify->file_loc + f_verify->size)
    {
        xipa_frag_sha256_verif(ptr->xip, start_addr + (passes++ * 1024), 1024);
    }
    xipa_frag_sha256_verif(ptr->xip, start_addr+(passes * 1024), f_verify->size-(passes * 1024));
    char hash[32];
    xipa_frag_sha256_fin(ptr->xip, hash);
    if(strcmp(f_verify->hash, hash) == 0) return 1;
    return -1;
}


//Pause XIP apps before calling this unless you love chaos and death.
/**
 * @brief Delete the first instance of a particular file with specified name.
 * @exception 1) IMPORTANT! You must pause any activity on the XIP region to prevent reads to undefined memory locations while deletion takes place.
 * @exception 2) You must include the extension in the filename.
 * @exception 3) This will only delete the FIRST instance of a file.
 * 
 * @param x xipafs disk object
 * @param filename char array of length 16 containing name and extension 
 * @return -EINVAL if there are no files, or if file could not be found. negative err code otherwise. 
 */
int xipa_fs_delete(struct xipafs* x, char* filename)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    if(ptr->num_files == 0) return -EINVAL;
    volatile uint8_t* record_offset = 0;
    struct filerecord tempfr;
    int rc = xipa_fs_get_file(x, filename, &tempfr); 
    XIPA_ERR_CHECK(x->log, "Could not get file name!", rc);
    if(tempfr.record_loc==(volatile uint8_t*)0 || tempfr.file_loc==(volatile uint8_t*)0 || tempfr.size==0)
    {
        LOG_INST_ERR(x->log, "Offsets zero!");
        return -EINVAL;
    }

    //switching to xip disable mode and using flash driver to delete the file.
    xip_disable(ptr->xip);
    rc = flash_area_open(ptr->pfa->fa_id, &ptr->pfa);
    XIPA_ERR_CHECK(x->log, "Could not open flash area!", rc);

    /* We are already erasing the flash sector by sector during align operation, no point doing it again!
    rc = flash_area_erase(ptr->pfa, (off_t)(tempfr.file_loc-ptr->param->xip_dev_location), size);
    XIPA_ERR_CHECK(x->log, "Could not erase file!", rc);
    LOG_INST_INF(x->log, "Erased %i byte file data at %i (0-based offset)", size, (off_t)(deletion_offset-ptr->param->xip_dev_location));
    */
    rc = flash_area_write(ptr->pfa, (off_t)(tempfr.record_loc-ptr->param->xip_dev_location+ptr->param->run_end_offset-RUN_SIZE), DEL_NAME, RUN_SIZE);
    XIPA_ERR_CHECK(x->log, "Could not erase file record!", rc);
    LOG_INST_INF(x->log, "Marked %i byte file record at %i (0-based offset) as erased", XIPA_JOURNAL_SIZE, (off_t)(record_offset-ptr->param->xip_dev_location));
    flash_area_close(ptr->pfa);
    if(ptr->num_files > 0) rc = xipa_fs_align(x, tempfr); //this function will align the main memory blocks 
    if(rc < 0) return rc;
    xip_enable(ptr->xip);
    return 1;
}


int arr_subset(uint8_t* d, uint8_t* s, uint32_t start, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        d[i] = s[start+i];
    }
    return 1;
}

/**
 * @brief Internal function to align physical memory after a delete operation. ONLY ACCESS VIA xipa_fs_delete() !
 * 
 * @param x xipafs disk object
 * @param f_del filerecord of deleted file
 * @return 1 on success, negative err code otherwise. 
 */
int xipa_fs_align(struct xipafs *x, struct filerecord f_del)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    struct filerecord tempfr;
    struct xipafs_dir_t dir;
    int rc;
    volatile uint8_t* deletion_offset = f_del.file_loc - (uint32_t)ptr->param->xip_dev_location + ptr->offset;
    volatile uint8_t* record_offset = f_del.record_loc - (uint32_t)ptr->param->xip_dev_location + (uint32_t)ptr->offset;
    if(ptr->num_files == 0) return -EINVAL;
           
    int flash_init_rc = flash_area_open(ptr->pfa->fa_id, &ptr->pfa);
    /*
        user might have TONNES of files, so we are going to trade RAM for CPU cycles and make the CPU traverse the entire filesystem block to find 
        the next record to update. It should be okay for just a few dozen files which is the general intended use case, but 
        things might get sticky in the hundreds of thousands of files!!
        (but then again this filesystem is NOT intended for processors which can access something large enough to warrant having hundreds of thousands of read only files lmao)
    */

    XIPA_ERR_CHECK(x->log, "Could not open flash area during align", flash_init_rc);
    //xip_enable(ptr->xip);
    
    xipa_fs_dir_init(x, &dir);
    
    //also we want to store the superblock offsets:
    struct vector superblocks;
    vector_init(&superblocks, ptr->num_superblocks, sizeof(unsigned int)); //there should ideally only be one superblock added here, otherwise
    //we have quite a cursed situation going on potentially. 
    struct xipafs_dir_t temp_dir;
    //check first superblock (i.e start of flash)
    unsigned int end_of_first_superblock = sizeof(ptr->num_files) + sizeof(ptr->num_superblocks) + sizeof(xipa_fs_start_block) + ptr->offset + (XIPA_JOURNAL_SIZE * 1000);
    if((unsigned int)record_offset < end_of_first_superblock)
    {
        unsigned int sb_ptr = end_of_first_superblock - (XIPA_JOURNAL_SIZE * 1000);
        vector_push_back(&superblocks, &sb_ptr); //this is fine, sb_ptr can go out of scope because it's safely stored in our vector.
    }
    xipa_fs_dir_init(x, &temp_dir); //ignore uninitialised warning
    do {
        rc = xipa_fs_traverse_flash_api(x, &tempfr, &temp_dir);
        if(rc < 0)
        {
            if(rc == -ENOTDIR)
            {
                ptr->last_file_end = (unsigned int)(tempfr.file_loc + tempfr.size);
                break;
            }
            else return -EIO;
        }
        //because of how the adding logic will work, superblocks added to the vector must be in logical order,
        //that is they will appear in order on the physical storage medium. 
        if(tempfr.run == xipa_file_extensions[0] && //superblock entry
        (tempfr.file_loc > deletion_offset || //superblock is located beyond the starting offset of the file we are deleting
        (tempfr.file_loc < deletion_offset && (tempfr.file_loc + 0x10000) > deletion_offset))) //superblock entry located inside the current superblock entry.
        {
            unsigned int sb_ptr_sec = (unsigned int)tempfr.file_loc;
            vector_push_back(&superblocks, &sb_ptr_sec); //safe as it will be copied into the vector memory.
        }
    }
    while(arr_contains_string((char**)xipa_file_extensions, tempfr.run, SIZE_SIZE) && tempfr.name[sizeof(tempfr.name)-1] == '\0');

    //we need to do low level block access so we need to get the underlying device.
    const struct device* flash_dev = flash_area_get_device((const struct flash_area*)&ptr->pfa);
    struct flash_pages_info* flash_bound_info;
    //we must add the device offset now, because we have gone down a layer of abstraction.
    //off_t prepared_del_off = (off_t)(deletion_offset-ptr->param->xip_dev_location+ptr->param->xip_device_offset);
    rc = flash_get_page_info_by_offs(flash_dev, (unsigned int)deletion_offset, flash_bound_info);
    XIPA_ERR_CHECK(x->log, "IO Error - deletion offset outside bounds", rc);
    size_t size_of_erasearea = flash_bound_info->size+XIPA_JOURNAL_SIZE;
    char* eraseArea = malloc(size_of_erasearea);
    //Now we have the actual flash page data.
    if(eraseArea == NULL)
    XIPA_ERR_CHECK(x->log, "OOM!!? - could not allocate enough memory to perform deletion operation!", rc);

    //Now, we will calculate how far away we are from the start of the superblock, and divide by XIPA_JOURNAL_SIZE to get
    //the number of records we are away from the start. 

    int buffer_shift_count = 0;
    int current_superblock = 0;
    rc = flash_read(flash_dev, flash_bound_info->start_offset, eraseArea, size_of_erasearea);
    XIPA_ERR_CHECK(x->log, "Could not read data into memory", rc);

    while(current_superblock < vector_length(&superblocks) - 1)
    {
        unsigned int* current_superblock_loc_ptr = (unsigned int*)vector_get(&superblocks, current_superblock);
        unsigned int current_superblock_loc = *current_superblock_loc_ptr;
        free(current_superblock_loc_ptr);
        rc = flash_get_page_info_by_offs(flash_dev, current_superblock_loc, flash_bound_info);
        XIPA_ERR_CHECK(x->log, "Could not get containing bounds for non-primary superblock", rc);
        int temp_computed_record = (flash_bound_info->start_offset - current_superblock_loc)/XIPA_JOURNAL_SIZE;
        int intra_buffer_index = ((off_t)record_offset - flash_bound_info->start_offset)/XIPA_JOURNAL_SIZE;
        do 
        {
            xipa_fs_populate_record(x, &tempfr, intra_buffer_index, eraseArea);
            tempfr.file_loc -= f_del.size;
            xipa_fs_write_temp_record(x, &tempfr, intra_buffer_index, eraseArea);
            if(++intra_buffer_index > flash_bound_info->size / XIPA_JOURNAL_SIZE)
            {
                //erase the block of flash in question
                rc = flash_erase(flash_dev, flash_bound_info->start_offset + ((buffer_shift_count) * flash_bound_info->size), flash_bound_info->size); 
                XIPA_ERR_CHECK(x->log, "Erase failed", rc);
                //now, we are sneaky and we've managed to shift all the data we need into position with one memmove, so let's write it!
                rc = flash_write(flash_dev, flash_bound_info->start_offset + ((buffer_shift_count) * flash_bound_info->size), eraseArea, flash_bound_info->size);
                XIPA_ERR_CHECK(x->log, "Write failed", rc);

                //now, let's read the next block of memory.
                                                                        //eeeeehhh, this could be more elegant by directly updating start_offset, but this makes more sense
                                                                        //and will hopefully be easier to debug. 
                rc = flash_read(flash_dev, flash_bound_info->start_offset + ((++buffer_shift_count) * flash_bound_info->size), eraseArea, size_of_erasearea);
                if(current_superblock == 0) // we are only shifting memory in the first superblock as we've deleted a record. 
                {
                    memmove((eraseArea+(intra_buffer_index*XIPA_JOURNAL_SIZE)), 
                    (eraseArea+(intra_buffer_index+1*XIPA_JOURNAL_SIZE)), 
                    (size_of_erasearea-((intra_buffer_index)*XIPA_JOURNAL_SIZE)));
                }
                XIPA_ERR_CHECK(x->log, "Read failed", rc);
                intra_buffer_index = 0;
                buffer_shift_count++;
            }
        }
        while(arr_contains_string((char**)xipa_file_extensions, tempfr.run, RUN_SIZE) && 
            tempfr.name[sizeof(tempfr.name)-1] == '\0' &&
            (temp_computed_record + (buffer_shift_count * (flash_bound_info->size / XIPA_JOURNAL_SIZE))) > 1000);
        current_superblock ++;
    }


/*
    first superblock has now been completely modified. 
    Time to go through the rest of the files, starting from the end offset, and copy everything right until the end.
    One limitation here, is that Nordic QSPI is capable of 64KB erase, but Zephyr will generally only expose the ability to erase 4KB at a time.
    A future TODO might be to add another parameter that defines a user defined erase size, but this is dangerous!! It would be much safer
    to rely on pre-built drivers. We will see.
*/   
    //We have location of last file from first traversal, so now we copy 4096 bytes from end of deleted file, erase starting 4096 bytes, and write the 4096 until our pointer is greater than or equal to the 
    //ending offset of the filesystem.
    unsigned int main_align_ptr = (unsigned int)f_del.file_loc;
    rc = flash_get_page_info_by_offs(flash_dev, main_align_ptr, flash_bound_info); //first we need to get the initial overlap as the files may not be 4096 byte aligned.
    size_t bytes_to_read_left = main_align_ptr - flash_bound_info->start_offset;
    size_t bytes_to_read_right = (unsigned int)(flash_bound_info->size - bytes_to_read_left);
    //we can assume all files will be 4 byte aligned though, sub-word alignment will be hell. Adding function will pad anything up to a multiple of 4.
    rc = flash_read(flash_dev, main_align_ptr-bytes_to_read_left, eraseArea, bytes_to_read_left);
    XIPA_ERR_CHECK(x->log, "Read failed", rc);

    rc = flash_read(flash_dev, main_align_ptr+f_del.size, eraseArea, bytes_to_read_right);
    XIPA_ERR_CHECK(x->log, "Read failed", rc);

    rc = flash_erase(flash_dev, flash_bound_info->start_offset, flash_bound_info->size);
    XIPA_ERR_CHECK(x->log, "Erase failed", rc);

    rc = flash_write(flash_dev, flash_bound_info->start_offset, eraseArea, flash_bound_info->size);
    XIPA_ERR_CHECK(x->log, "Write failed", rc);

    unsigned int reach_ptr = (unsigned int)(f_del.file_loc + f_del.size + bytes_to_read_right);
    unsigned int current_ptr = flash_bound_info->start_offset + flash_bound_info->size;
    while(reach_ptr < (unsigned int)(ptr->last_file_end + flash_bound_info->size)) //if last bit of last file is in between another sector, we need to copy that sector too. 
    {
        rc = flash_read(flash_dev, reach_ptr, eraseArea, flash_bound_info->size);
        XIPA_ERR_CHECK(x->log, "Read failed", rc);

        rc = flash_erase(flash_dev, current_ptr, flash_bound_info->size);
        XIPA_ERR_CHECK(x->log, "Erase failed", rc);

        rc = flash_write(flash_dev, current_ptr, eraseArea, flash_bound_info->size);
        XIPA_ERR_CHECK(x->log, "Write failed", rc);

        reach_ptr += flash_bound_info->size; //moving to next sector in flash
        current_ptr += flash_bound_info->size;
    }
    ptr->last_file_end -= f_del.size;
    vector_deinit(&superblocks);
    free(eraseArea);
    xipa_fs_dir_deinit(x, &temp_dir);
    return 1;
}

/**
 * @brief Initiate write of a new file to the filesystem. Once write is initialised, call xipa_fs_data_store_cb() with your incremental buffer writes. 
 * 
 * @param x xipafs disk object
 * @param filename Desired filename, should not exceed 12 characters (i.e should fit inside a char[12] with null termination)
 * @param extension Desired extension, should fit inside a char[4] with null terminator, and must be one of the defined extensions in xipa_file_extensions.
 * @param size Size of new file - MUST BE WORD ALIGNED! (i.e rounded up to nearest multiple of 4 for 32-bit systems)
 * @param hash SHA-256 hash of new file
 * @param ver_str Version string of file or app.
 * @return 1 on success, negative err_code otherwise. 
 */
int xipa_fs_store(struct xipafs* x, char* filename, char* extension, size_t size, char* hash, char* ver_str)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    if(ptr->storing > 0) return -EINVAL;
    if(strlen(filename) > NAME_SIZE) return -EINVAL;
    if(strlen(extension) > RUN_SIZE) return -EINVAL;
    if(strlen(hash) != HASH_SIZE) return -EINVAL;
    if(strlen(ver_str) > VER_STR_SIZE) return -EINVAL;
    int extension_index = arr_contains_string((char**)xipa_file_extensions, extension, RUN_SIZE);
    if(extension_index == -1) return -EINVAL;
    if(size % 4 != 0) return -EINVAL;
    if(ptr->last_file_end + size > ptr->param->dev_size) return -EINVAL;
    //we want to get location of file record for very last file. we will append our new data onto the end of the corresponding superblock. 
    struct xipafs_dir_t tempdir;
    xipa_fs_dir_init(x, &tempdir);
    struct filerecord tempfr;
    int traverse_rc = 0;
    int rc = 0;
    while(traverse_rc != -ENOTDIR)
    {
        xipa_fs_traverse_flash_api(x, &tempfr, &tempdir);
        XIPA_ERR_CHECK(x->log, "IO Error - filesystem corrupted?", traverse_rc);
    }
    if((unsigned int)(tempfr.file_loc + tempfr.size) != ptr->last_file_end) return -EIO;
    char newJournalEntry[XIPA_JOURNAL_SIZE];
    tempfr.file_loc = (volatile uint8_t*)ptr->last_file_end;
    memcpy(tempfr.name, filename, NAME_SIZE);
    memcpy(tempfr.run, extension, RUN_SIZE);
    memcpy(tempfr.hash, hash, HASH_SIZE);
    memcpy(tempfr.ver_str, ver_str, VER_STR_SIZE);
    tempfr.size = size;
    //we need to do low level block access so we need to get the underlying device.
    const struct device* flash_dev = flash_area_get_device((const struct flash_area*)&ptr->pfa);
    unsigned int new_record_loc = (unsigned int)(tempfr.record_loc + XIPA_JOURNAL_SIZE);
    XIPA_ERR_CHECK(x->log, "IO Error - temporary record construction failed", rc);
    if(tempdir.current_record == 999)
    {
        struct filerecord new_superblock;
        new_superblock.file_loc = (volatile uint8_t*)ptr->last_file_end;
        memcpy(new_superblock.run, xipa_file_extensions[0], RUN_SIZE);
        snprintf(new_superblock.name, NAME_SIZE, "superblock%d", ++ptr->num_superblocks);
        memset(new_superblock.hash, 1, HASH_SIZE);
        new_superblock.size = XIPA_JOURNAL_SIZE * 1000;
        memcpy(new_superblock.ver_str, "1.0", VER_STR_SIZE);
        char new_superblock_entry[XIPA_JOURNAL_SIZE];
        xipa_fs_write_temp_record(x, &new_superblock, 1, new_superblock_entry);
        flash_write(flash_dev, ptr->last_file_end, new_superblock_entry, XIPA_JOURNAL_SIZE);
        ptr->last_file_end += new_superblock.size;
        new_record_loc = ptr->last_file_end;
    }
    
    rc = xipa_fs_write_temp_record(x, &tempfr, 0, newJournalEntry);
    XIPA_ERR_CHECK(x->log, "IO Error - new record creation failed", rc);
    rc = flash_write(flash_dev, new_record_loc, newJournalEntry, XIPA_JOURNAL_SIZE);
    XIPA_ERR_CHECK(x->log, "IO Error - new record write failed", rc);
    ptr->last_file_end += size;
    xipa_fs_dir_deinit(x, &tempdir);
    ptr->storing = 0;
    ptr->f = tempfr;
    return 1;
}

/**
 * @brief Callback function to write contents of file bit by bit. You can use arbitrarily sized buffers and call this function as you receive the data, just please keep them word aligned. You must initialise a write operation first with store().
 * 
 * @param x xipafs disk object
 * @param buf pointer to buffer containing file data
 * @param buf_size size of data to copy - MUST BE WORD ALIGNED (multiple of 4 on 32-bit systems)!
 * @return 0 on incremental write success, 1 when all data written successfully, -EINVAL when called uninitialised or if end buffer too large.
 */
int xipa_fs_data_store_cb(struct xipafs* x, void* buf, size_t buf_size)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    if(ptr->storing == -1) return -EINVAL;
    const struct device* flash_dev = flash_area_get_device((const struct flash_area*)&ptr->pfa);
    flash_write(flash_dev, (unsigned int)(ptr->f.file_loc + ptr->storing), buf, buf_size);
    ptr->storing += buf_size;
    if(ptr->storing == ptr->f.size)
    {
        ptr->storing = -1;
        return 1;
    }
    if(ptr->storing > ptr->f.size) return -EINVAL;
    return 0;
}