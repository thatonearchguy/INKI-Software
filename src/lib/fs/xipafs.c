#include "xipafs.h"
#include "drivers/xipa_dev.h"
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
    //Constant RAM usage - 10+32+8+8+5+1 = 64 bytes
    char name[16];
    char hash[32];
    uint32_t location;
    uint32_t size;
    char ver_str[4];
    char run[4];
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
    serialisecheck[6] = ptr->journal_size;
    if(serialisecheck[6] == 0)
    {
        rc = -EINVAL;
        return rc;
    }
    for (int i = 0; i < sizeof(serialisecheck) - 2; i++)
    {
            //All offsets must be word aligned   //Offsets cannot be greater than final journal size       //None of the offests can be zero otherwise these fields do not exist.       
        if (serialisecheck[i] % 4 != 0 || serialisecheck[i] > serialisecheck[sizeof(serialisecheck)-1] || serialisecheck[i] == 0)
        {
            rc = -EINVAL;
            return rc;
        }
        if(serialisecheck[i] == ptr->journal_size)
        {
            offeqsize += 1; //if this is greater than one, multiple values are equal and thus is invalid.
        }
    }
    if(offeqsize != 1)
    {
        rc = -EINVAL;
    }
    if(ptr->flash_area_id < 0)
    {
        rc = -EINVAL;
    }
    if(ptr->path == NULL)
    {
        rc = -EINVAL;
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
    const struct device* fdev = flash_area_get_device(ptr->param->flash_area_id);
    
    rc = flash_area_read(ptr->pfa, 0, buf, sizeof(buf)); //we can safely use single word read writes according to nordic product specification, so this is fine.
    if (rc < 0)
    {
        if (rc == -EIO)
        {
            LOG_INST_INF(x->log, "I/O Error - could not read device");
        }
    }
    if (strcmp(buf, "XIPA") != 0)
    {
        LOG_INST_INF(x->log, "Superblock not found! Is filesystem formatted to XIPA?");
        return -ENOENT;
    }
    ptr->offset = ptr->pfa->fa_off;
    rc = flash_area_read(ptr->pfa, 4, (uint32_t)ptr->num_files, 4); //getting number of files on filesystem.
    if (rc < 0)
    {
        return rc;
    }
    LOG_INST_INF(x->log, "Number of files - %d", ptr->num_files);
    flash_area_close(ptr->pfa); //NOP right now, but for future compatibility this is fine.
    ptr->xip = k_malloc(sizeof(struct xipa_dev));
    rc = xip_init(ptr->xip);
    if(rc < 0)
    {
        LOG_INST_ERR(x->log, "Could not init XIP!");
        return rc;
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
    return 1;
}

//PLEASE ENSURE DEVICE IS ACTIVELY IN XIP MODE!! OTHERWISE MCU WILL CRASH!! YOU MUST REINIT QSPI WHEN SWITCHING FROM DMA-BASED MOUNT TO XIP BASED EXECUTE ON NRF52840
//PLEASE MOUNT BEFORE YOU TRY TO GET FILE, OR YOU WILL HAVE -ENODEV.
int xipa_fs_get_file(struct xipafs *x, char *filename, char *start, uint32_t size)
{
    char *fname;
    char *ext;
    char *context = NULL;
    struct privatefs_ptr *ptr = (struct privatefs_ptr *)x->private_ptr;
    if (!ptr->init)
        return -ENODEV;
    volatile unsigned int *tableStart = (volatile unsigned int *)ptr->param->xip_dev_location + 8; //first 4 bytes (machine word) is the identifier superblock, next 4 bytes is the number of files.
    fname = strtok_r(fname, ".", &context);
    ext = strtok_r(NULL, ".", &context);
    if (fname == NULL || ext == NULL)
    {
        return -EIO;
    }
    //each journal entry is 64 bytes (#wordaligned gang) so we will iterate through until we find our entry!
    //We maintain the number of files to avoid needessly iterating over the entire 64KB superblock region.
    //This means that there must be no gaps within the entries!!
    for (volatile unsigned int jso = 0; jso < (volatile unsigned int)ptr->num_files * ptr->param->journal_size; jso += 0x40) //journal starting offset (jso)
    {
        memcpy(ptr->f->name, tableStart + jso, sizeof(ptr->f->name));
        if (strcmp(ptr->f->name, fname) == 0)
        {
            //populate_record(x);
            return 1;
        }
    }
    return -ENFILE;
}
