/*
 * Copyright (c) 2021 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 */


#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <logging/log.h>
#include <lvgl.h>
#include "wasm_export.h"
#include <drivers/flash.h>
#include <stdio.h>
#include <string.h>
#include "lib/disk/disk.h"


LOG_MODULE_REGISTER(main, CONFIG_LOG_DEFAULT_LEVEL);
INT_FLASH_DEFINE(inki_flash);
INT_QSPIFLASH_DEFINE(inki_qflash);

static struct baseDisk* inki_flash_ptr = (struct baseDisk *)&inki_flash;
static struct baseDisk* inki_qflash_ptr = (struct baseDisk *)&inki_qflash;


void main(void)
{
	LOG_INF("Reached main.c");
	LOG_INF("Initialising internal flash");
	intFlash_setup(&inki_flash);
	intQSPIFlash_setup(&inki_qflash);

	base_init(inki_flash_ptr, NULL);	
	base_init(inki_qflash_ptr, NULL);	

	//TODO NEXT - TEST AND DEBUG DISK API.



}