/*
 * Copyright (c) 2022 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 * 
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <sys/types.h>
#include <device.h>
#include <logging/log.h>
#include "lp_uarte_cfg.h"

struct lp_uarte_dev {
    const struct lp_uarte_dev_api* api;
    struct lp_uarte_dev_params p;
    bool init;
};


typedef int (*_lp_uarte_dev_init)(const struct lp_uarte_dev*);
typedef int (*_lp_uarte_ft_dev_start)(const struct lp_uarte_dev*);
typedef int (*_lp_uarte_dev_deinit)(const struct lp_uarte_dev*);
typedef int (*_lp_uarte_dev_pkt_tx)(const struct lp_uarte_dev*);
typedef int (*_lp_uarte_dev_pkt_rx)(const struct lp_uarte_dev*);
typedef int (*_lp_uarte_get_ft)();
typedef int (*_lp_uarte_tx_fin)(const struct lp_uarte_dev*);


//May add more funcions to api, but this is enough for now!
__subsystem struct lp_uarte_dev_api
{
    _lp_uarte_dev_pkt_tx tx;
    _lp_uarte_dev_pkt_rx rx;
    _lp_uarte_dev_init init;
    _lp_uarte_dev_deinit deinit;
    _lp_uarte_ft_dev_start ft_start;
    _lp_uarte_get_ft ft_status;
    _lp_uarte_tx_fin tx_fin;
};


//technically inheritance again? fairly similar but we don't also have 
//inherited data fields, only exposing a set of common methods -> an interface!

static inline int lp_uarte_dev_ft_start(const struct lp_uarte_dev* dev)
{
    return dev->api->ft_start(dev);
}

static inline int lp_uarte_dev_ft_status(const struct lp_uarte_dev* dev)
{
    return dev->api->ft_status(dev);
}

static inline int lp_uarte_dev_init(const struct lp_uarte_dev* dev)
{
    return dev->api->init(dev);
}

static inline int lp_uarte_dev_deinit(const struct lp_uarte_dev* dev)
{
    return dev->api->deinit(dev);
}

static inline int lp_uarte_dev_pkt_tx_rdy(const struct lp_uarte_dev* dev)
{
    return dev->api->tx(dev);
}

static inline int lp_uarte_dev_pkt_rx_rdy(const struct lp_uarte_dev* dev)
{
    return dev->api->rx(dev);
}

static inline int lp_uarte_dev_tx_fin(const struct lp_uarte_dev* dev)
{
    return dev->api->tx_fin(dev);
}


int lp_uarte_drv_init(struct lp_uarte_dev* dev);