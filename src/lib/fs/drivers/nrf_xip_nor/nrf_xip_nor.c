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
#include <../../nrf_cc310_bl/include/nrf_cc310_bl_init.h>
#include <../../nrf_cc310_bl/include/nrf_cc310_bl_hash_sha256.h>
#include "../../xipa_dev.h"

#define mod_name nrf_xip_qspi_xipa_drv
#define drv_name xipa_nrf_qspi

NRF_QSPI_Type nrf_qspi_reg;
off_t xipo;
static struct crypto_ctx 
{
    int initialised;
    int64_t bytes_checked;  
    nrf_cc310_bl_hash_context_sha256_t *const p_hash_context;  
};

struct crypto_ctx sha_operation = {.bytes_checked = -1, .initialised = -1};

static int nrf_lp_uarte_init(const struct xipa_dev* dev, off_t xip_offset)
{
    //default offset is zero in the zephyr flash drivers, so as long as our storage partition
    //is stored at 0x0 offset we should be fine. 
    xipo = xip_offset;
    return 1;
}

static int nrf_qspi_xip_fs_set(const struct xipa_dev* dev, bool en)
{
    int rc = 1;
    if(nrfx_qspi_mem_busy_check()==NRFX_SUCCESS)
    {
        #if defined(CONFIG_SOC_SERIES_NRF53X)
            nrf_qspi_xip_set(&qspi_reg, en);
        #endif

    }
    if(nrf_qspi_reg.XIPOFFSET!=xipo)
    {
        nrf_qspi_xip_offset_set(&nrf_qspi_reg, (uint32_t)xipo); 
    }
    return rc;
}

static int nrf_lp_uarte_ft_start(const struct xipa_dev* dev)
{
    return nrf_qspi_xip_fs_set(dev, true);
}

static int nrf_lp_uarte_deinit(const struct xipa_dev* dev)
{
    return nrf_qspi_xip_fs_set(dev, false);
}

static int nrf_qspi_sha256_verif(const struct xipa_dev* dev, void* frag_buf, size_t frag_len)
{
    CRYSError_t err_code;
    if(sha_operation.initialised == -1)
    {
        if(nrf_cc310_bl_init() != 0)
        {
            return -1;
        }
        NRF_CRYPTOCELL->ENABLE = 1;

        err_code = nrf_cc310_bl_hash_sha256_init(sha_operation.p_hash_context);
        if(err_code != CRYS_OK) return err_code;
        sha_operation.initialised = 1;
        sha_operation.bytes_checked = 0;
    }
    err_code = nrf_cc310_bl_hash_sha256_update(sha_operation.p_hash_context, (const uint8_t*)frag_buf, (uint32_t)frag_len);
    return err_code;
}

static int nrf_lp_uarte_rx(const struct xipa_dev* dev, void* hash_buf)
{
    CRYSError_t err_code = nrf_cc310_bl_hash_sha256_finalize(sha_operation.p_hash_context, (uint8_t*)hash_buf);
    if(err_code = CRYS_OK)
    {
        sha_operation.initialised = -1;
        sha_operation.bytes_checked = 0;
        NRF_CRYPTOCELL->ENABLE = 0;
        return 1;
    }
    return err_code;
}



static const struct xipa_dev_api nrf_qspi_xip_api = {
    .di = nrf_lp_uarte_deinit,
    .en = nrf_lp_uarte_ft_start,
    .setoffset = nrf_lp_uarte_init,
    .verif = nrf_lp_uarte_rx,
    .fin = nrf_lp_uarte_rx,
};

int xip_init(struct xipa_dev* dev)
{
    dev->api = &nrf_qspi_xip_api;
    return 1;
}