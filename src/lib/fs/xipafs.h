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

#ifndef INKI_XIPA_FS
#define INKI_XIPA_FS

#include <stdlib.h>
#include <stdio.h>
#include <fs/fs.h> 
#include <storage/flash_map.h>
#include "lib/d_vector/vector.h"
#include "lib/d_stack/stack.h"
#include <logging/log_instance.h>
#include <nrfx_qspi.h>
#include <logging/log.h>
#include <drivers/flash.h>


/*

Q: WHY DOES THIS EXIST?
A: Most, if not all of Zephyr's file systems operate in a "RAM-backed manner". What I mean by this, is that interacting with files is
done by copying it into RAM, making changes to that copy, and then writing it back to the disk. 
This is great for things like logging, storing configuration files etc.., but very impractical for storing large application binaries.

External memory connected via QSPI (or in the future, any sort of connection!) provides a great and vital way to extend the
capabilities of a low powered MCU like the nRF52 or nRF53 series. 128MB of fast, accessible storage is a huge amount for this
sort of chip, the possibilities are effectively endless!

There are some major issues - The fastest protocol available is usually QSPI, which does not support concurrent reading and writing 
operations. Then, these MCUs do not have MMUs, meaning direct code execution from a distributed-sector file system like 
LittleFS, FAT32, or EXT4 is extremely difficult as the application binary information is strewn across the storage medium.

This leaves no option but to copy the entire application into working memory, which in nearly all cases is a fraction of the
permanent storage available. For instance, the nRF52840 has 256KB of RAM. That is nowhere near enough to fit in a fat 2-4MB
binary that could do lots of very useful things, let alone catering for its heap and stack requirements. 

Now, many MCUs have a facility called XiP (eXecute in Place) - this can integrate with peripherals like QSPI and bring external storage mediums
into memory addressable range. This allows the processing core to access the external storage directly as if it were RAM!
It can therefore be leveraged to satisfy the requirement of a contiguous buffer in working memory that we can begin executing an application from. 

But here, we hit another hurdle - Many XiP regions are READ-ONLY, because QSPI does not support concurrent reads and writes.
This means we have to restart the QSPI peripheral into user-accessible DMA mode every time we want to make a change to the 
contents of the external flash. Evidently this is something that the MCU cannot handle on its own - it becomes a very sticky
and risky ground! If there are applications running from the QSPI flash, we must terminate or suspend them otherwise they will
crash when they try to access memory space that no longer exists!!

This file system aims to bridge this gap - providing a clean interface for files to be stored in contiguous memory buffers, 
to be provided to runtimes or native code execution within the main application domain. 
There will be no folders, symlinks, or permissions, just an interface to look up file names as strings, and have a memory pointer
returned to you with the size of your file! Simple as that! 

---------------------------------------------------------------------------------------------------------------------------------------------

Q: HOW IS IT IMPLEMENTED?
A: Have a wander through these files and find out! Joking, I will update this section when I actually implement this (TODO)

---------------------------------------------------------------------------------------------------------------------------------------------

*/

#define XIPA_FS_NAME XiPAFS
#define NRF_QSPI_XIP_START_ADDR      0x12000000
#define XIPA_JOURNAL_SIZE 0x40
//TODO - Add this to mount function to allow for multiple XIPA_FS instances.
#define XIPA_NAME_OFFSET 0x0
#define XIPA_HASH_OFFSET 0x12
#define XIPA_LOC_OFFSET 0x2A
#define XIPA_SIZE_OFFSET 0x2E
#define XIPA_VERS_OFFSET 0x32
#define XIPA_RUN_OFFSET 0x37

struct xipafs
{
    LOG_INSTANCE_PTR_DECLARE(log);
    void* private_ptr;
    char* name;
    char* mountpoint;
    uint16_t* id;
};

struct xipafs_params
{
    uint8_t name_end_offset;
    uint8_t hash_end_offset;
    uint8_t loc_end_offset;
    uint8_t size_end_offset;
    uint8_t vers_end_offset;
    uint8_t run_end_offset;
    uint8_t journal_size;
    uintptr_t flash_area_id;
    uint32_t xip_device_offset;
    uint32_t xip_dev_location;
    char* path;
};

#define XIPAFS_INIT(_name)  \
LOG_INSTANCE_REGISTER(XIPA_FS_NAME, _name, CONFIG_XIPAFS_LOG_LEVEL);  \
struct vector _name = {  \
            LOG_INSTANCE_PTR_INIT(log, XIPA_FS_NAME, _name)  \
}


int xipa_fs_mount(struct xipafs* x, struct xipafs_params* params); //Path may be unnecesary, I do not think this will integrate into Zephyr's VFS yet..
int xipa_fs_get_file(struct xipafs* x, char* filename, char* start, uint32_t size);
int xipa_fs_store(struct xipafs* x, char* filename);
int xipa_fs_delete(struct xipafs* x, char* filename);
int xipa_fs_unmount(struct xipafs* x);
int xipa_fs_format(struct xipafs* x);
int xipa_fs_verify(struct xipafs* x);


#endif