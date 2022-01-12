/*
 * Copyright (c) 2021 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 */

#include <fs/fs.h>
#include <fs/littlefs.h>
#include <ff.h>
#include <storage/disk_access.h>
#include <storage/flash_map.h> //TODO - Find out whether this is required
#include <logging/log_instance.h>
#include <stdio.h>
#include <kernel.h>

#ifndef INKI_DISK_API
#define INKI_DISK_API

#define MAX_FS_PATH_LENGTH 255
#define TYPE_INTERNAL_FLASH 1
#define TYPE_INTERNAL_QSPI_FLASH 2
#define TYPE_EXTERNAL_SPI_FLASH 3
#define TYPE_EXTERNAL_USB_FAT 4 //LONG TERM TODO
#define TYPE_EXTERNAL_USB_NTFS 5 //LONG TERM TODO (after production probably!!)

//*************************************************************************************************************************************************
//Straight C POLYMORPHISM GO BRRRRRRRRR (no access protection though without opaque pointers, which are pointless 
//because I want to allow 3rd party devs and myself to manipulate the Zephyr FileSystem (FS) structs directly for full access over the hardware.)
//Protection will most likely be implemented on the WASM sandbox side to prevent apps misbehaving, but I will definitely need TOTAL access.
//Currently supported types - SPI external (SD card), QSPI internal, FLASH internal
//*************************************************************************************************************************************************

//******************************************************************************************************
//*   LONG TERM TO-DOs:                                                                          
//*     - Add method(s) for intQSPIFlash device that streamline XIP/Data lookups to the same flash chip  
//*     - RAMDisk? Feels like a solution in search of a problem tho 
//*     - Integrate USB Host chip, and use FATFS driver to add support for USB Mass Storage devices

#define BASEDISK_NAME bDisk
#define INTFLASH_NAME iDisk
#define INTQSPIFLASH_NAME qDisk
#define EXTSPIFLASH_NAME eDisk

struct baseDisk_vtable
{
    int (*init)(void *self, char* label);
    int (*deinit)(void *self);
};

struct baseDisk
{
    LOG_INSTANCE_PTR_DECLARE(log);
    struct baseDisk_vtable* vtable;
    struct fs_mount_t* mnt_p;
    unsigned int id;
    char fname[MAX_FS_PATH_LENGTH];
    struct fs_statvfs vol_stats;
};


#define BASE_DISK_DEFINE(_name)  \
LOG_INSTANCE_REGISTER(BASEDISK_NAME, _name, CONFIG_LOG_DEFAULT_LEVEL);  \
struct baseDisk _name = {  \
            LOG_INSTANCE_PTR_INIT(log, BASEDISK_NAME, _name)  \
}   
                                                            

int base_init(struct baseDisk *b, char* label);
int base_deinit(struct baseDisk *b);


struct intFlash
{
    struct baseDisk super;
    const struct flash_area* pfa;
};

#define INT_FLASH_DEFINE(_name) \
LOG_INSTANCE_REGISTER(INTFLASH_NAME, _name, CONFIG_IFLASH_LOG_LEVEL);   \
struct intFlash _name = { \
    .super LOG_INSTANCE_PTR_INIT(log, INTFLASH_NAME, _name)    \
};

int intFlash_init(struct intFlash *i, char* label);
int intFlash_deinit(struct intFlash *i);
void intFlash_setup(struct intFlash *i);


struct intQSPIFlash
{
    struct baseDisk super;
    const struct flash_area* pfa;
};


#define INT_QSPIFLASH_DEFINE(_name)  \
LOG_INSTANCE_REGISTER(INTQSPIFLASH_NAME, _name, CONFIG_QFLASH_LOG_LEVEL);  \
struct intQSPIFlash _name = {  \
        .super LOG_INSTANCE_PTR_INIT(log, INTQSPIFLASH_NAME, _name)  \
}; 
                                                             


int intQSPIFlash_init(struct intQSPIFlash *q, char* label);
int intQSPIFlash_deinit(struct intQSPIFlash *q);
void intQSPIFlash_setup(struct intQSPIFlash *q);


struct extSPIFlash
{
    struct baseDisk super;
    struct fs_mount_t mnt;
    FATFS fat_fs;
    const char *disk_mount_pt;

};


#define EXT_SPIFLASH_DEFINE(_name)  \
LOG_INSTANCE_REGISTER(EXTSPIFLASH_NAME, _name, CONFIG_EFLASH_LOG_LEVEL);  \
struct extSPIFlash _name = {  \
        .super LOG_INSTANCE_PTR_INIT(log, EXTSPIFLASH_NAME, _name)  \
};  


int extSPIFlash_init(struct extSPIFlash *e, char* label);
int extSPIFlash_deinit(struct extSPIFlash *e);
void extSPIFlash_setup(struct extSPIFlash *e);


#endif