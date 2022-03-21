/*
 * Copyright (c) 2022 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 * 
 */



#ifndef INKI_LP_PARAMS
#define INKI_LP_PARAMS


#include <logging/log.h>

/**
 * @brief Configuration struct for LP-UARTE, containing TX, RX & HWFC pins, callback function pointers, 
 * 
 */
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
    void* tx_buf_ptr;
    void* rx_buf0_ptr;
    void* rx_buf1_ptr;
    void (*tx_cb)();
    void (*rx_cb)(size_t len, void* data_ptr, void(*self)());
};

#endif