/*
 * Copyright (c) 2021 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 */

#include "disk.h"

#define INT_FSTAB_PARTITION_NODE DT_NODELABEL(lfs1)
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
	if(DT_NODE_EXISTS(INT_FSTAB_PARTITION_NODE)==1)
	{
		FS_FSTAB_DECLARE_ENTRY(INT_FSTAB_PARTITION_NODE);
		i->super.mnt_p = &FS_FSTAB_ENTRY(INT_FSTAB_PARTITION_NODE);
		LOG_INST_INF(i->super.log, "Internal flash FSTAB reference found");
		i->super.id = (uintptr_t)i->super.mnt_p->storage_dev;
		rc = flash_area_open(i->super.id, &i->pfa);
		if(rc < 0)
		{
			LOG_INST_ERR(i->super.log, "FAILED: Could not find flash area %u: %d\n", i->super.id, rc);
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
		const char* mountpoint = (char*) k_malloc(10);
		rc = fs_readmount((int*)i->super.mnt_p->mnt_point, &mountpoint);
		if(mountpoint==NULL || rc == ENOENT)
		{
			LOG_INST_ERR(i->super.log, "id %u at %s: %d not registered", (unsigned int)i->super.mnt_p->storage_dev, i->super.mnt_p->mnt_point, rc);
		}
		LOG_INST_INF(i->super.log, "%s automount probably successful!", i->super.mnt_p->mnt_point);
		k_free((char*)mountpoint);
	}
	else
	{
		return -1; /* //internal flash MUST be in FSTAB!! NO EXCEPTIONS!!
			Thinking ahead to newer models and revisions, possibly even
			different architectures and eventual end products, everything
			must be extensified using devicetree tables to keep consistency.
			Hacks in code and measures to counteract negligence on DST 
			will result in significant issues while debugging later revisions
			with the same library!
		*/
	}
	return 0;
}

struct baseDisk_vtable intFlash_vtable = 
{
	(int (*)(void *, char *))&intFlash_init,
	(int (*)(void *))&intFlash_deinit,
};

void intFlash_setup(struct intFlash *i)
{
	i->super.vtable = &intFlash_vtable;
}

int intQSPIFlash_init(struct intQSPIFlash *q, char* label)
{
	int rc;
	LOG_INST_INF(q->super.log, "Initialising lfs QSPI internal flash");
	if(DT_NODE_EXISTS(EXT_FSTAB_PARTITION_NODE)==1)
	{
		FS_FSTAB_DECLARE_ENTRY(EXT_FSTAB_PARTITION_NODE);
		q->super.mnt_p = &FS_FSTAB_ENTRY(EXT_FSTAB_PARTITION_NODE);
		LOG_INST_INF(q->super.log, "Internal QSPI flash FSTAB reference found");
		q->super.id = (uintptr_t)q->super.mnt_p->storage_dev;
		rc = flash_area_open(q->super.id, &q->pfa);
		if(rc < 0)
		{
			LOG_INST_ERR(q->super.log, "FAILED: Could not find flash area %u: %d\n", q->super.id, rc);
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
		const char* mountpoint = (char*) k_malloc(10);
		rc = fs_readmount((int*)q->super.mnt_p->mnt_point, &mountpoint);
		if(mountpoint==NULL || rc == ENOENT)
		{
			LOG_INST_WRN(q->super.log, "id %u at %s: %d not registered", (unsigned int)q->super.mnt_p->storage_dev, q->super.mnt_p->mnt_point, rc);
		}
		LOG_INST_INF(q->super.log, "%s automount probably successful!", q->super.mnt_p->mnt_point);
		k_free((char*)mountpoint);
	}
	else
	{
		return -1; /* //internal flash MUST be in FSTAB!! NO EXCEPTIONS!!
			Thinking ahead to newer models and revisions, possibly even
			different architectures and eventual end products, everything
			must be extensified using devicetree tables to keep consistency.
			Hacks in code and measures to counteract negligence on DST 
			will result in significant issues while debugging later revisions
			with the same library!
		*/
	}
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
};

void intQSPIFlash_setup(struct intQSPIFlash *q)
{
	q->super.vtable = &intQSPIFlash_vtable;
}

//https://stackoverflow.com/questions/25661925/quickly-find-whether-a-value-is-present-in-a-c-array 
//One-branch instruction optimised linear search (modified)
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
};

void extSPIFlash_setup(struct extSPIFlash *e)
{
	e->super.vtable = &extSPIFlash_vtable;
}