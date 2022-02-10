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

#define NAME_SIZE 16
#define HASH_SIZE 32
#define LOC_SIZE 4
#define SIZE_SIZE 4
#define VER_STR_SIZE 4
#define RUN_SIZE 4

/*

[||||||||||[(  app 1   )(    app 2     )(     app 3      )     free space     ]|||||||||]
     ^                                          
     |
64KB superblock
*/


int populate_record(struct xipafs *x, volatile unsigned int *offset);
int align(struct xipafs *x);
int xipa_fs_verifyparams(struct xipafs_params *ptr);


struct filerecord
{
    //Constant RAM usage - 16+32+4+4+4+4 = 64 bytes
    char name[NAME_SIZE];
    char hash[HASH_SIZE];
    uint32_t location;
    uint32_t size;
    char ver_str[VER_STR_SIZE];
    char run[RUN_SIZE];
};

struct privatefs_ptr
{
    //struct vector filerecord_list; //now unnecessary as we are not loading the entire table into memory.
    bool init;
    uint32_t num_files;
    const struct flash_area *pfa;
    struct xipafs_params *param;
    struct xipa_dev *xip;
    struct vector operations; //stores pointers to functions in order of atomic operations.
    struct filerecord *f;
    size_t offset;
};

//Good - after reading nrfxlib documentation, it seems apparently possible to hash
//items of arbitrary length. This will come in very handy for hashing the large binaries.

//XIPA-FS filesystems, to minimise unnecessary aligns and wearing down the flash, will have a fixed
//starting block of 64 KiloBytes. This will contain all the required information about the binary files.
//The file system keep some information stored

//TODO - Change offsets to ENDING OFFSETS.

/* Just to get the project to build -> project builds. Good.
int populate_record_table(struct xipafs *x, volatile unsigned int offset)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    ptr->f->hash = memcpy(ptr->f->name, offset, sizeof(ptr->param->))
}
*/
//Call function after verifying params, will take params struct directly from xipafs object.

int arr_contains_int(uint8_t array[], uint8_t value)
{
    for(int i = 0; i < sizeof(array); i++)
    {
        if(array[i]==value)
        {
            return i;
        }
    }
    return -1;
}


//In XIPA_FS, the sizes for the individual fields that make up the 64 bytes are totally fixed.
//You have control over the location of each field within the filesystem, so this function
//will check if the offsets you've put in correspond to valid sizes!
int xipa_fs_check_sizes(uint8_t offsets[6], uint8_t sizes[6])
{
    //finding which offset is first - i.e whichever one subtracted by it's size ends up with zero. if we can't find 
    //one then the offsets are invalid!
    uint8_t zero_offset = -1;
    uint8_t inval_size_flag = 0;
    for(int i = 0; i < sizeof(offsets); i ++)
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
    for (int i = 0; i < sizeof(offsets); i ++)
    {
        if(i==zero_offset)
        {
            i++;
        }
        else
        {
            int hyp_index = arr_contains_int(offsets, (offsets[i]-sizes[i])); //hypothesized index
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
    if(arr_contains_int(offsets, XIPA_JOURNAL_SIZE))
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
    int offeqsize = 0; //check if one of the ending offsets is equal to the file size.
    uint8_t serialisecheck[7]; //8 bit array makes sense because are you really, really going to have a record size larger than 255 bytes? what kind of hash are u using lmfao
    serialisecheck[0] = ptr->name_end_offset;
    serialisecheck[1] = ptr->hash_end_offset;
    serialisecheck[2] = ptr->loc_end_offset;
    serialisecheck[3] = ptr->size_end_offset;
    serialisecheck[4] = ptr->vers_end_offset;
    serialisecheck[5] = ptr->run_end_offset;
    uint8_t sizes[6] = {NAME_SIZE, HASH_SIZE, LOC_SIZE, SIZE_SIZE, VER_STR_SIZE, RUN_SIZE};


    for (int i = 0; i < sizeof(serialisecheck) - 2; i++)
    {
            //All offsets must be word aligned   //Offsets cannot be greater than final journal size       //None of the offests can be zero otherwise these fields do not exist.       
        if (serialisecheck[i] % 4 != 0 || serialisecheck[i] > serialisecheck[sizeof(serialisecheck)-1] || serialisecheck[i] == 0)
        {
            rc = -EINVAL;
            return rc;
        }
    }
    if(xipa_fs_check_sizes(serialisecheck, sizes) == -1)
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

    if(fs_param_ret_code < 0)
    {
        LOG_INST_ERR(x->log, "Invalid parameters! Check and remount");
        return fs_param_ret_code;
    }

    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    ptr->f = k_malloc(sizeof(struct filerecord)); //allocating memory from kernel heap to ensure files can still be traversed in low memory conditions
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
    if (strcmp(buf, start) != 0)
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
    if(rc < 0)
    {
        LOG_INST_ERR(x->log, "Could not init XIP!");
        return rc;
    }
    rc = xip_setoffset(ptr->xip, ptr->offset);
    if(rc < 0)
    {
        LOG_INST_ERR(x->log, "Could not set offset!");
    }
    rc = xip_enable(ptr->xip);
    if(rc < 0)
    {
        LOG_INST_ERR(x->log, "Could not enable XIP!");
    }

    ptr->init = true;

    return 1;
}

int xipa_fs_unmount(struct xipafs *x)
{
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    k_free(ptr->f); //free filerecord to prevent further transactions.
    xip_disable(ptr->xip);
    k_free(ptr->xip); //free xip to prevent further manipulation
    //this should leave QSPI peripheral in a state where standard flash manipulation commands should work perfectly
    //with no XIPA_FS manipulation. 
    ptr->init = false;
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


//Mount before calling this function - TODO add nice documentation to all the XIPA functions.
int xipa_fs_get_file(struct xipafs *x, char *filename, char *start, uint32_t size)
{
    char *fname;
    char *ext;
    char *context = NULL;
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    if (!ptr->init)
        return -EINVAL;
    volatile uint8_t *tableStart = (volatile uint8_t*)(ptr->param->xip_dev_location + sizeof(ptr->num_files) + sizeof(start)); //first 4 bytes (machine word) is the identifier superblock, next 4 bytes is the number of files.
    fname = strtok_r(filename, ".", &context);
    ext = strtok_r(NULL, ".", &context);
    if (fname == NULL || ext == NULL)
    {
        return -EINVAL;
    }
    struct stack superblock_locations;
    volatile struct xipa_superblock_loc
    {
        volatile unsigned int record;
        volatile uint8_t* superblock_start; //with respect to processor address space!
    };
    /*
    We want to use the stack to keep track of where we've gotten up to in the superblock traversal. 
    If we end up at a record with file extension "ext", we will store the current value of "record" in the stack
    and start traversing the new superblock at the given location, and so on so forth. 
    When the function finishes traversing this level of superblock, it will pop a new record off the stack and 
    resume where it left off. 
    */
    stack_init(&superblock_locations, 4, sizeof(struct xipa_superblock_loc*));
    //each journal entry is 64 bytes (#wordaligned gang) so we will iterate through until we find our entry!
    //We maintain the number of files to avoid needessly iterating over the entire 64KB superblock region.
    //This means that there must be no gaps within the entries!!
    char iter_fname[NAME_SIZE];
    char iter_ext[RUN_SIZE];
    for (volatile unsigned int record = 0; record < (volatile unsigned int)ptr->num_files * XIPA_JOURNAL_SIZE; record += 0x40) 
    {
        xipa_vol_memcpy(iter_ext, (volatile uint8_t*)(tableStart + record + ptr->param->run_end_offset - RUN_SIZE), RUN_SIZE);
        if(strcmp(iter_ext, "ext") == 0)
        {
            volatile struct xipa_superblock_loc yeet = {.record = record, .superblock_start = tableStart};
            stack_push(&superblock_locations, &yeet);
            uint32_t new_tablestart;
            xipa_vol_memcpy(new_tablestart, (volatile uint8_t*)(tableStart + record + ptr->param->run_end_offset - RUN_SIZE), RUN_SIZE);

        }
        if (strcmp(ptr->f->name, fname) == 0)
        {
            //populate_record(x);
            return 1;
        }
    }
    return -ENFILE;
}
