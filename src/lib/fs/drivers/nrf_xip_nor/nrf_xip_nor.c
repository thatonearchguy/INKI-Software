/*
 * Copyright (c) 2022 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 * 
 */


#ifdef CONFIG_SOC_SERIES_NRF52X
    #include <nrf52840.h>
#endif
#ifdef CONFIG_SOC_SERIES_NRF53X
    #include <nrf5340_application.h>
#endif

#include <zephyr/types.h>
#include <sys/types.h>
#include <errno.h>
#include <hal/nrf_qspi.h>
#include <nrfx_qspi.h>
#include <psa/crypto.h>
#include <psa/crypto_extra.h>
#include "../../xipa_dev.h"

#define mod_name nrf_xip_qspi_xipa_drv
#define drv_name xipa_nrf_qspi

NRF_QSPI_Type nrf_qspi_reg;
off_t xipo;

struct crypto_ctx 
{
    int initialised;
    int64_t bytes_checked;  
    psa_hash_operation_t operation;
    psa_status_t status;
};


struct crypto_ctx sha_operation = {.bytes_checked = -1, .initialised = -1};

static int nrf_qspi_xip_init(const struct xipa_dev* dev, off_t xip_offset)
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
            nrf_qspi_xip_set(&nrf_qspi_reg, en);
        #endif

    }
    if(nrf_qspi_reg.XIPOFFSET!=xipo)
    {
        nrf_qspi_xip_offset_set(&nrf_qspi_reg, (uint32_t)xipo); 
    }
    return rc;
}

static int nrf_qspi_enable_xip(const struct xipa_dev* dev)
{
    return nrf_qspi_xip_fs_set(dev, true);
}

static int nrf_qspi_disable_xip(const struct xipa_dev* dev)
{
    return nrf_qspi_xip_fs_set(dev, false);
}

static int nrf_qspi_sha256_verif(const struct xipa_dev* dev, void* frag_buf, size_t frag_len)
{
    psa_status_t err_code;
    if(sha_operation.initialised == -1)
    {
        if(psa_crypto_init() != PSA_SUCCESS)
        {
            return -1;
        }
        //NRF_CRYPTOCELL->ENABLE = 1;
        sha_operation.operation = psa_hash_operation_init();

        err_code = psa_hash_setup(&sha_operation.operation, PSA_ALG_SHA_256);
        if(err_code != PSA_SUCCESS) return -1;

        sha_operation.initialised = 1;
        sha_operation.bytes_checked = 0;
    }
    err_code = psa_hash_update(&sha_operation.operation, (const uint8_t*)frag_buf, (uint32_t)frag_len);
    if(err_code == PSA_SUCCESS)
    {
        sha_operation.bytes_checked += frag_len;
        return 1;
    }
    else return -1;
}

static int nrf_qspi_sha256_verif_fin(const struct xipa_dev* dev, void* hash_buf)
{
    size_t length = 0;
    psa_status_t err_code = psa_hash_finish(&sha_operation.operation, hash_buf, 32, &length);

    if(err_code == PSA_SUCCESS && length == PSA_HASH_LENGTH(PSA_ALG_SHA_256))
    {
        sha_operation.initialised = -1;
        sha_operation.bytes_checked = 0;
        NRF_CRYPTOCELL->ENABLE = 0;
        return 1;
    }
    return err_code;
}



static const struct xipa_dev_api nrf_qspi_xip_api = {
    .di = nrf_qspi_disable_xip,
    .en = nrf_qspi_enable_xip,
    .setoffset = nrf_qspi_xip_init,
    .verif = nrf_qspi_sha256_verif,
    .fin = nrf_qspi_sha256_verif_fin,
};

int xip_init(struct xipa_dev* dev)
{
    dev->api = &nrf_qspi_xip_api;
    return 1;
}