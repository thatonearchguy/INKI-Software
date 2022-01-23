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
#include <stdio.h>
#include <string.h>
#include "lib/disk/disk.h"
#include <usb/usb_device.h>	


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
	//TODO - TEST AND DEBUG DISK API -> DONE YAY!
	//TODO - MCUBOOT INTEGRATION -> DONE YAY!
	//TODO - FIGURE OUT WHY MCUBOOT WON'T LOG TO RTT -> I GIVE UP -> Moving to uart, that'll probably fix it! -> still didn't work -> I give up
	//TODO - REDUCE BINARY SIZE SO I CAN ACTUALLY WRITE CODE -> DONE YAY!
	//TODO - USB DFU BRUH -> DONE AND TESTED YAY!!
	//TODO - Figure out why USB MASS STORAGE CONFLICTS WITH USB DFU?? -> I am blind and can't read docs - can't act as both at the same time!
	//TODO - Get USB MASS WORKING AND MOUNTED ON LINUX

	//TODO NEXT - WAMR INTEGRATION
	LOG_INF("Initialising USB Mass Storage");

	if((int)usb_enable(NULL) < 0)
	{
		LOG_ERR("FAIL: USB not initialised");
		return;
	}
	LOG_INF("Initialising WAMR Runtime");
	
	static char global_heap_buf[128 * 1024]; //TODO - TAILOR RAM USAGE ONCE WE GET SOME APPS GOING.
    char *buffer, error_buf[128];
    int opt;
    char *wasm_path = NULL;

    wasm_module_t module = NULL;
    wasm_module_inst_t module_inst = NULL;
    wasm_exec_env_t exec_env = NULL;
    uint32_t buf_size, stack_size = 8092, heap_size = 8092;
    wasm_function_inst_t func = NULL;
    wasm_function_inst_t func2 = NULL;
    char *native_buffer = NULL;
    uint32_t wasm_buffer = 0;

	RuntimeInitArgs init_args;
	memset(&init_args, 0, sizeof(RuntimeInitArgs)); //Native Zephyr libc
	init_args.mem_alloc_type = Alloc_With_Pool;
	init_args.mem_alloc_option.pool.heap_buf = global_heap_buf;
	init_args.mem_alloc_option.pool.heap_size = sizeof(global_heap_buf);
	if(!wasm_runtime_full_init(&init_args))
	{
		LOG_ERR("Could not initialise WAMR runtime!");
		return;
	}
	//wasm_runtime_init();
	//lv_init();


}