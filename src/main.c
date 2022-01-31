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
#include <stdlib.h>
#include <string.h>
#include "lib/disk/disk.h"
#include "lib/vector/vector.h"
#include <usb/usb_device.h>	
#include <drivers/display.h>


typedef struct AppThread {
    wasm_exec_env_t exec_env;
    int start;
    int length;
} AppThread;

LOG_MODULE_REGISTER(main, CONFIG_LOG_DEFAULT_LEVEL);
INT_FLASH_DEFINE(inki_flash);
INT_QSPIFLASH_DEFINE(inki_qflash);

static struct baseDisk* inki_flash_ptr = (struct baseDisk *)&inki_flash;
static struct baseDisk* inki_qflash_ptr = (struct baseDisk *)&inki_qflash;

VECTOR_INIT(disk_vector);

#if DT_NODE_HAS_STATUS(DT_INST(0, inki_ssd16xxfb), okay)
#define DISPLAY_DEV_NAME DT_LABEL(DT_INST(0, inki_ssd16xxfb))
#endif

static lv_disp_draw_buf_t disp_buf;

#ifdef MARK_ONE
static uint8_t LV_TICK_INCREMENT_MS = 4;
static lv_color_t buf_1[ DT_PROP(DT_PATH(soc, spi_40023000, inki_ssd16xxfb_0), width) * DT_PROP(DT_PATH(soc, spi_40023000, inki_ssd16xxfb_0), height) / 10 ]; //Above 1/10th sized buffer, there is no performance gain
static lv_color_t buf_2[ DT_PROP(DT_PATH(soc, spi_40023000, inki_ssd16xxfb_0), width) * DT_PROP(DT_PATH(soc, spi_40023000, inki_ssd16xxfb_0), height) / 10 ]; //Second buffer for DMA (background) transfer to the display
#endif

//Recursive exponentiation by squaring algorithm
int exp(int x, int n)
{
	if(n < 0)
	{
		return exp(1 / x, -n);
	}
	else if (n == 0)
	{
		return 1;
	}
	else if (n == 1)
	{
		return x;
	}
	else if (n % 2 == 0)
	{
		return exp(x*x, n/2);
	}
	else if (n % 2 == 1)
	{
		return x * exp(x*x, (n-1)/2);
	}
	return 0;
}

static char sandboxed_memory[128 * 1000] = { 0 };

//For now, code execution and storage only possible from external or internal flash
static bool module_reader_cb(const char* module_name, uint8_t **p_buffer, uint32_t *p_size)
{
	const char filename[MAX_FS_PATH_LENGTH];
}

void main(void)
{
	LOG_INF("Reached main.c");
	/*
	const struct device *display_dev;
	struct display_capabilities capabilities;
	display_dev = device_get_binding(DISPLAY_DEV_NAME);
	if (display_dev == NULL) {
		LOG_ERR("Display %s not found!",
			DISPLAY_DEV_NAME);
	}
	for (int i = 0; i < sizeof(MARK1_BOOT_IMG_map); i++)
	{
		display_write(display_dev, 0, 0
	}
	*/

	LOG_INF("Initialising internal flash");
	intFlash_setup(&inki_flash);
	intQSPIFlash_setup(&inki_qflash);

	base_init(inki_flash_ptr, NULL);	
	base_init(inki_qflash_ptr, NULL);


	//Soon(TM) -> autodiscover and add more disks to array. Maximum disks shall be 5 for now. 

	//TODO - TEST AND DEBUG DISK API -> DONE YAY!
	//TODO - MCUBOOT INTEGRATION -> DONE YAY!
	//TODO - FIGURE OUT WHY MCUBOOT WON'T LOG TO RTT -> I GIVE UP -> Moving to uart, that'll probably fix it! -> still didn't work -> I give up
	//TODO - REDUCE BINARY SIZE SO I CAN ACTUALLY WRITE CODE -> DONE YAY!
	//TODO - USB DFU TESTING -> DONE AND TESTED YAY!!
	//TODO - Figure out why USB MASS STORAGE CONFLICTS WITH USB DFU?? -> I am blind and can't read docs - can't act as both at the same time!
	//TODO - Get USB MASS WORKING AND MOUNTED ON LINUX -> DONE YAY!!
	//TODO - WAMR INTEGRATION -> DONEISH YAY!!
	//TODO NEXT - PORT LVGL TO WAMR (EXPOSE METHODS SOMEHOW) AND PORT MENU & WATCHFACE CODE -> Sorta know how, time to do it!

	LOG_INF("Initialising USB Mass Storage");

	if((int)usb_enable(NULL) < 0)
	{
		LOG_ERR("FAIL: USB not initialised");
		return;
	}
	LOG_INF("Initialising WAMR Runtime");
	
	bool ret = false;
    /* 8K */
    const uint32_t stack_size = 8 * 1024;
    const uint32_t heap_size = 16 * 1024;

    RuntimeInitArgs init_args = { 0 };
    char error_buf[128] = { 0 };
    /* parameters and return values */
    char *args[1] = { 0 };

    uint8_t *file_buf = NULL;
    uint32_t file_buf_size = 0;
    wasm_module_t module = NULL;
    wasm_module_inst_t module_inst = NULL;

	init_args.mem_alloc_type = Alloc_With_Pool;
    init_args.mem_alloc_option.pool.heap_buf = sandboxed_memory;
    init_args.mem_alloc_option.pool.heap_size = sizeof(sandboxed_memory);


	if(!wasm_runtime_full_init(&init_args))
	{
		LOG_ERR("Could not initialise WAMR runtime!");
		return;
	}
	
	//wasm_runtime_init();
	lv_init();


}