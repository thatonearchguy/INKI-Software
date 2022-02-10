/*
 * Copyright (c) 2021 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 */

#include "disk.h"

//HORRIBLE HACK, I HATE PARTITION MANAGER!!!!!!!!! WON'T LET ME DEFINE MY PARTITIONS HOW I WANT THEM IN MY OWN 
//FREAKING DTS AAAAAAAAAAAAAAAAAAAAAAAAAAA
FS_LITTLEFS_DECLARE_DEFAULT_CONFIG(littlefs_storage);
static struct fs_mount_t int_storage_mnt = {
	.type = FS_LITTLEFS,
	.fs_data = &littlefs_storage,
	.storage_dev = (void *)FLASH_AREA_ID(littlefs_storage),
	.mnt_point = "/int",
};

FS_LITTLEFS_DECLARE_DEFAULT_CONFIG(ext_storage);
static struct fs_mount_t ext_storage_mnt = {
	.type = FS_LITTLEFS,
	.fs_data = &ext_storage,
	.storage_dev = (void *)FLASH_AREA_ID(ext_storage),
	.mnt_point = "/ext",
};

//This method is better as I have more direct control over the hardware, while automounting is cool and convenient it works
//terribly with a custom defined pm_static.yml file!! All the addresses and partitions are swapped and messed up!!

#define EXT_FSTAB_PARTITION_NODE DT_NODELABEL(lfs2)

LOG_LEVEL_SET(LOG_LEVEL_INF);

int base_init(struct baseDisk *b, char* label)
{
	int retcode = b->vtable->init(b, label);
	LOG_INST_INF(b->log, "Initialised."); //ignore Z_FOR_LOOP_1 - Intellisense is confused
	return retcode;
}
int base_deinit(struct baseDisk *b)
{
	int retcode = b->vtable->deinit(b);
	LOG_INST_WRN(b->log, "Deinitialised.");
	return retcode;
}

int base_get_file_path(struct baseDisk *b, const char* filename)
{
	LOG_INST_INF(b->log, "Finding file path");
	int retcode = b->vtable->get_file_path(b, filename);
	return retcode;
}

//TODO - Add this to disk api -> Yes shall do. Great idea. Should take an extension as well
//so we can just do straight up strcmp without any strtok_r invocations.
//Place the starting path inside the struct's fname, this function will set fname to the path if found, otherwise NULL. 
//Function not defined in header, therefore technically encapsulated away!
int base_find_file_from_path(struct baseDisk* b, const char* filename)
{
    struct fs_dir_t* dir;
	fs_dir_t_init(dir);

    static struct fs_dirent dirent;

    if (fs_opendir(dir, b->fname) < 0)
	{
		return -ENOTDIR;
	}
    while (&dirent.name[0] != 0) {
		if(fs_readdir(dir, &dirent) < 0)
			break;
		//This is safe because there can never be directories inside files on LittleFS.
		//Would be unnecessary to set filepath back to original as this function is purely looking for FILES, not searching inside a zip for instance.
		if(dirent.type == FS_DIR_ENTRY_FILE)
		{
			if(strcmp(&dirent.name[0], filename) == 0)
			{
				snprintf(b->fname, sizeof(b->fname), "%s/%s", b->fname, dirent.name);
				LOG_INST_INF(b->log, "Found at %s, joe!", b->fname);
				fs_closedir(dir);
				return 1;
			}
		}
		if(dirent.type == FS_DIR_ENTRY_DIR)
		{
			snprintf(b->fname, sizeof(b->fname), "%s/%s", b->fname, dirent.name);
			LOG_INST_INF(b->log, "Going to %s", b->fname);
			return base_find_file_from_path(b, filename);
			fs_closedir(dir);
		}
    }
	return 0;
	//free((void*)dir); //might be dodgy, want to prevent a bunch of dir pointers being left on the stack. 
}

int general_get_file_path(struct baseDisk *b, const char* filename)
{
	memset(b->fname, 0, MAX_FS_PATH_LENGTH);
	snprintf(b->fname, sizeof(b->fname), "%s", b->mnt_p->mnt_point);
	if(base_find_file_from_path(b, filename) == 1) return 1;
	else return -ENFILE;
}

int intFlash_deinit(struct intFlash *i)
{
	int rc = 1;
	LOG_INST_INF(i->super.log, "Unmounting...");
	rc = fs_unmount(i->super.mnt_p);
	if (rc < 0) {
		LOG_INST_ERR(i->super.log, "Could not unmount, error code %d\n", rc);
	}
	else if (rc == EINVAL)
	{
		LOG_INST_WRN(i->super.log, "Already unmounted!");
	}
	rc = fs_unregister(i->super.mnt_p->type, i->super.mnt_p->fs);
	return rc;
}

int intFlash_init(struct intFlash *i, char* label)
{
	int rc;
	LOG_INST_INF(i->super.log, "Initialising lfs internal flash");
	i->super.mnt_p = &int_storage_mnt;
	i->super.id = (uintptr_t)i->super.mnt_p->storage_dev;
	rc = flash_area_open(i->super.id, &i->pfa);
	if(rc < 0)
	{
		LOG_INST_ERR(i->super.log, "FAILED: Could not find flash area %u: %d", i->super.id, rc);
		return rc;
	}
	else
	{
		LOG_INST_INF(i->super.log, "Area %u at 0x%x on %s for %u bytes", i->super.id, (unsigned int)i->pfa->fa_off, i->pfa->fa_dev_name, (unsigned int)i->pfa->fa_size);
		if (IS_ENABLED(CONFIG_APP_INT_WIPE_STORAGE))
		{
			LOG_INST_WRN(i->super.log, "Erasing flash area ...");
			rc = flash_area_erase(i->pfa, 0, i->pfa->fa_size);
			LOG_INST_WRN(i->super.log, "Code: %d", rc);
		}
		flash_area_close(i->pfa);
	}
	LOG_INST_INF(i->super.log, "Attempting to mount id %u at %s", (unsigned int)i->super.mnt_p->storage_dev, i->super.mnt_p->mnt_point);
	rc = fs_mount(i->super.mnt_p);
	if (rc < 0) {
		LOG_INST_ERR(i->super.log, "FAIL: mount id %u at %s: %d",
		       (unsigned int)i->super.mnt_p->storage_dev, i->super.mnt_p->mnt_point,
		       rc);
		return rc;
	}
	LOG_INST_INF(i->super.log, "%s mounted: %d!", i->super.mnt_p->mnt_point, rc);
	rc = fs_register(FS_LITTLEFS, i->super.mnt_p->fs);
	if (rc < 0) {
		LOG_INST_ERR(i->super.log, "FAIL: register id %u at %s: %d",
		       (unsigned int)i->super.mnt_p->storage_dev, i->super.mnt_p->mnt_point,
		       rc);
		return rc;
	}
	/* //internal flash MUST be in FSTAB!! NO EXCEPTIONS!!
			Thinking ahead to newer models and revisions, possibly even
			different architectures and eventual end products, everything
			must be extensified using devicetree tables to keep consistency.
			Hacks in code and measures to counteract negligence on DST 
			will result in significant issues while debugging later revisions
			with the same library!
		*/
	return 0;
}

struct baseDisk_vtable intFlash_vtable = 
{
	(int (*)(void *, char *))&intFlash_init,
	(int (*)(void *))&intFlash_deinit,
	(int (*)(void *, const char *))&general_get_file_path,
};

void intFlash_setup(struct intFlash *i)
{
	i->super.vtable = &intFlash_vtable;
}

int intQSPIFlash_init(struct intQSPIFlash *q, char* label)
{
	int rc;
	LOG_INST_INF(q->super.log, "Initialising lfs internal flash");
	q->super.mnt_p = &ext_storage_mnt;
	q->super.id = (uintptr_t)q->super.mnt_p->storage_dev;
	rc = flash_area_open(q->super.id, &q->pfa);
	if(rc < 0)
	{
		LOG_INST_ERR(q->super.log, "FAILED: Could not find flash area %u: %d", q->super.id, rc);
		return rc;
	}
	else
	{
		LOG_INST_INF(q->super.log, "Area %u at 0x%x on %s for %u bytes", q->super.id, (unsigned int)q->pfa->fa_off, q->pfa->fa_dev_name, (unsigned int)q->pfa->fa_size);
		if (IS_ENABLED(CONFIG_APP_EXT_WIPE_STORAGE))
		{
			LOG_INST_WRN(q->super.log, "Erasing flash area ...");
			rc = flash_area_erase(q->pfa, 0, q->pfa->fa_size);
			LOG_INST_WRN(q->super.log, "Code: %d", rc);
		}
		flash_area_close(q->pfa);
	}
	LOG_INST_INF(q->super.log, "Attempting to mount id %u at %s", (unsigned int)q->super.mnt_p->storage_dev, q->super.mnt_p->mnt_point);
	rc = fs_mount(q->super.mnt_p);
	if (rc < 0) {
		LOG_INST_ERR(q->super.log, "FAIL: mount id %u at %s: %d",
		       (unsigned int)q->super.mnt_p->storage_dev, q->super.mnt_p->mnt_point,
		       rc);
		return rc;
	}
	LOG_INST_INF(q->super.log, "%s mounted: %d!", q->super.mnt_p->mnt_point, rc);
	rc = fs_register(FS_LITTLEFS, q->super.mnt_p->fs);
	if (rc < 0) {
		LOG_INST_ERR(q->super.log, "FAIL: register id %u at %s: %d",
		       (unsigned int)q->super.mnt_p->storage_dev, q->super.mnt_p->mnt_point,
		       rc);
		return rc;
	}
	/* //internal flash MUST be in FSTAB!! NO EXCEPTIONS!!
			Thinking ahead to newer models and revisions, possibly even
			different architectures and eventual end products, everything
			must be extensified using devicetree tables to keep consistency.
			Hacks in code and measures to counteract negligence on DST 
			will result in significant issues while debugging later revisions
			with the same library!
		*/
	return 0;

}
int intQSPIFlash_deinit(struct intQSPIFlash *q)
{
	int rc = 1;
	LOG_INST_INF(q->super.log, "Unmounting...");
	rc = fs_unmount(q->super.mnt_p);
	if (rc < 0) {
		LOG_INST_ERR(q->super.log, "Could not unmount, error code %d\n", rc);
	}
	else if (rc == EINVAL)
	{
		LOG_INST_WRN(q->super.log, "Already unmounted!");
	}
	rc = fs_unregister(q->super.mnt_p->type, q->super.mnt_p->fs);
	return rc;
}


struct baseDisk_vtable intQSPIFlash_vtable = 
{
	(int (*)(void *, char *))&intQSPIFlash_init,
	(int (*)(void *))&intQSPIFlash_deinit,
	(int (*)(void *, const char *))&general_get_file_path,
};

void intQSPIFlash_setup(struct intQSPIFlash *q)
{
	q->super.vtable = &intQSPIFlash_vtable;
}

//https://stackoverflow.com/questions/25661925/quickly-find-whether-a-value-is-present-in-a-c-array 
//One-branch instruction optimised linear search (modified)
//Again technically encapsulated away as not exposed in header file.
bool check(char* arr[], char* val)
{
    uint16_t i;
	uint16_t count = sizeof(&arr)/sizeof(arr[0]);
    char* x = arr[count-1];
    if (strcmp(x,val)==0)
        return true;
    arr[count-1] = val;
    for (i = 0; strcmp(arr[i], val) != 0; i++);
    arr[count-1] = x;
    return i != count-1;
}

//Must use drive-names specified in _VOLUME_STRS, otherwise 
//function will return ENOTDIR (20)
int extSPIFlash_init(struct extSPIFlash *e, char* label)
{
	int rc;
	char* mountpath;
	e->mnt.type = FS_FATFS;
	e->mnt.fs_data = &e->fat_fs;
	char* vols [] = {_VOLUME_STRS};
	if(!(check(vols, label)))
	{
		LOG_INST_INF(e->super.log, "Invalid mount point!");
		return ENOTDIR;
	}
	e->disk_mount_pt = label;
	rc = disk_access_init(e->disk_mount_pt);
	if(rc != 0)
	{
		LOG_INST_ERR(e->super.log, "FAILED: Could not init id %u at %s: %d", (unsigned int)e->super.mnt_p->storage_dev, e->super.mnt_p->mnt_point, rc);
		return rc;
	}
	if((mountpath = k_malloc(strlen(label)+2)) != NULL)
	{
		mountpath[0] = '\0';
		strcat(mountpath, "/");
		strcat(mountpath, label);
		strcat(mountpath, ":");
	}
	else
	{
		LOG_INST_ERR(e->super.log, "Label malloc failed! Check memory usage");
		return ENOMEM;
	}
	e->mnt.mnt_point = mountpath;
	rc = fs_mount(&e->mnt);
	k_free(mountpath);
	if(rc != FR_OK)
	{
		LOG_INST_ERR(e->super.log, "FAIL: Could not mount id %u at %s: %d", (unsigned int)e->super.mnt_p->storage_dev, e->super.mnt_p->mnt_point, rc);
	}
	LOG_INST_INF(e->super.log, "SUCCESS: Could mounted id %u at %s: %d", (unsigned int)e->super.mnt_p->storage_dev, e->super.mnt_p->mnt_point, rc);
	if(disk_access_status(e->disk_mount_pt)==DISK_STATUS_WR_PROTECT)
	{
		LOG_INST_WRN(e->super.log, "Disk in Write-Protect Mode!!");
	}
	return 1;
}

//Zero on success
int extSPIFlash_deinit(struct extSPIFlash *e)
{
	int rc = 1;
	LOG_INST_INF(e->super.log, "Unmounting...");
	rc = fs_unmount(e->super.mnt_p);
	if (rc < 0) {
		LOG_INST_ERR(e->super.log, "Could not unmount, error code %d\n", rc);
		return rc;
	}
	else if (rc == EINVAL)
	{
		LOG_INST_WRN(e->super.log, "Already unmounted!");
	}
	rc = fs_unregister(e->super.mnt_p->type, e->super.mnt_p->fs);
	if (rc < 0)
	{
		LOG_INST_ERR(e->super.log, "Could not unregister filesystem");
		return rc;
	}
	return 1;
}

struct baseDisk_vtable extSPIFlash_vtable = 
{
	(int (*)(void *, char *))&intQSPIFlash_init,
	(int (*)(void *))&intQSPIFlash_deinit,
	(int (*)(void *, const char *))&general_get_file_path,
};

void extSPIFlash_setup(struct extSPIFlash *e)
{
	e->super.vtable = &extSPIFlash_vtable;
}