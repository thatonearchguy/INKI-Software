/*
 * Copyright (c) 2021 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <sys/types.h>
#include <device.h>

struct xipa_dev {
    const struct xipa_dev_api* api;
    bool mounted;
};


typedef int (*xipa_xip_setoffset)(const struct xipa_dev*, off_t xip_offset);
typedef int (*xipa_xip_enable)(const struct xipa_dev*);
typedef int (*xipa_xip_disable)(const struct xipa_dev*);


//May add more funcions to api, but this is enough for now!
__subsystem struct xipa_dev_api
{
    xipa_xip_setoffset setoffset;
    xipa_xip_enable en;
    xipa_xip_disable di;

};

//technically inheritance again? fairly similar but we don't also have 
//inherited data fields, only exposing a set of common methods -> an interface!

static inline int xip_enable(const struct xipa_dev* dev)
{
    return dev->api->en(dev);
}

static inline int xip_disable(const struct xipa_dev* dev)
{
    return dev->api->di(dev);
}

static inline int xip_setoffset(const struct xipa_dev* dev, off_t offset)
{
    return dev->api->setoffset(dev, offset);
}

int xip_init(struct xipa_dev* dev);