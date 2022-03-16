/*
 * Copyright (c) 2021 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <sys/types.h>
#include <device.h>

struct lp_uarte_dev {
    const struct lp_uarte_dev_api* api;
    struct lp_uarte_dev_params p;
    bool init;
};


typedef int (*_lp_uarte_dev_init)(struct lp_uarte_dev*);
typedef int (*_lp_uarte_ft_dev_start)(struct lp_uarte_dev*);
typedef int (*_lp_uarte_dev_deinit)(struct lp_uarte_dev*);
typedef int (*_lp_uarte_dev_pkt_tx)(struct lp_uarte_dev*, void* tx_pkt_buf, size_t pkt_len);
typedef int (*_lp_uarte_dev_pkt_rx)(struct lp_uarte_dev*, void* rx_pkt_buf, size_t pkt_len);
typedef int (*_lp_uarte_ft_dev_end)(struct lp_uarte_dev*);


//May add more funcions to api, but this is enough for now!
__subsystem struct lp_uarte_dev_api
{
    _lp_uarte_dev_pkt_tx tx;
    _lp_uarte_dev_pkt_rx rx;
    _lp_uarte_dev_init init;
    _lp_uarte_dev_deinit deinit;
    _lp_uarte_ft_dev_start ft_start;
    _lp_uarte_ft_dev_end ft_end;
};


struct lp_uarte_dev_params {
    unsigned long baud;
    bool flow_control;
    bool even_parity;
    bool odd_parity;
    char start_byte;
    char end_byte;
    uint32_t tx_pin;
    uint32_t rx_pin;
    uint32_t cts_pin;
    uint32_t rts_pin;
    uint32_t s0_pin;
    uint32_t s1_pin;
    uint32_t s2_pin;

};

//technically inheritance again? fairly similar but we don't also have 
//inherited data fields, only exposing a set of common methods -> an interface!

static inline int lp_uarte_ft_start(const struct lp_uarte_dev* dev)
{
    return dev->api->ft_start(dev);
}

static inline int lp_uarte_pkt_ft_end(const struct lp_uarte_dev* dev)
{
    return dev->api->ft_end(dev);
}

static inline int lp_uarte_init(const struct lp_uarte_dev* dev)
{
    return dev->api->init(dev);
}

static inline int lp_uarte_deinit(const struct lp_uarte_dev* dev)
{
    return dev->api->deinit(dev);
}

static inline int lp_uarte_pkt_tx(const struct lp_uarte_dev* dev, void* tx_pkt_buf, size_t pkt_len)
{
    return dev->api->tx(dev, tx_pkt_buf, pkt_len);
}

static inline int lp_uarte_pkt_rx(const struct lp_uarte_dev* dev, void* rx_pkt_buf, size_t pkt_len)
{
    return dev->api->rx(dev, rx_pkt_buf, pkt_len);
}