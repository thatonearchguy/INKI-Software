/*
 * Copyright (c) 2021 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 */


#if defined(NRF52840_XXAA)
    #include <nrf52840.h>
#elif defined(CONFIG_SOC_SERIES_NRF53X)
    #include <nrf5340_application.h>
#endif

#include <zephyr/types.h>
#include <sys/types.h>
#include <errno.h>
#include <hal/nrf_qspi.h>
#include <nrfx_qspi.h>
#include "../xipa_dev.h"

#define mod_name nrf_xip_qspi_xipa_drv
#define drv_name xipa_nrf_qspi

NRF_QSPI_Type nrf_qspi_reg;

static int nrf_qspi_xip_setoffset(const struct xipa_dev* dev, off_t xip_offset)
{
    //default offset is zero in the zephyr flash drivers, so as long as our storage partition
    //is stored at 0x0 offset we should be fine. 
    nrf_qspi_xip_offset_set(&nrf_qspi_reg, (uint32_t)xip_offset); 
    return 1;
}

static int nrf_qspi_xip_fs_set(const struct xip_dev* dev, bool en)
{
    int rc = 1;
    if(nrfx_qspi_mem_busy_check()==NRFX_SUCCESS)
    {
        #if defined(CONFIG_SOC_SERIES_NRF53X)
            nrf_qspi_xip_set(&qspi_reg, en);
        #endif

    }
    return rc;
}

static int nrf_qspi_xip_enable(const struct xip_dev* dev)
{
    return nrf_qspi_xip_fs_set(dev, true);
}

static int nrf_qspi_xip_disable(const struct xip_dev* dev)
{
    nrf_qspi_xip_fs_set(dev, false);
}

static const struct xipa_dev_api nrf_qspi_xip_api = {
    .di = nrf_qspi_xip_disable,
    .en = nrf_qspi_xip_enable,
    .setoffset = nrf_qspi_xip_setoffset,
};

static int xip_init(struct xipa_dev* dev)
{
    dev->api = &nrf_qspi_xip_api;
    return 1;
}