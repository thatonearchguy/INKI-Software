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
INT_FLASH_DEFINE(inki_int);
EXT_FLASH_DEFINE(inki_ext);

void main(void)
{
	LOG_INF("Reached main.c");
	LOG_INF("Initialising internal flash");
	//INKI.vtable->init(&INKI, "/int", 3);
	
	
}