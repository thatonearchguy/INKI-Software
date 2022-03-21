/*
 * Copyright (c) 2022 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 * 
 */

/*
 _      ____  __ __   ____  ____  ______    ___ 
| |    |    \|  |  | /    ||    \|      |  /  _]
| |    |  o  )  |  ||  o  ||  D  )      | /  [_ 
| |___ |   _/|  |  ||     ||    /|_|  |_||    _]
|     ||  |  |  :  ||  _  ||    \  |  |  |   [_ 
|     ||  |  |     ||  |  ||  .  \ |  |  |     |
|_____||__|   \__,_||__|__||__|\_| |__|  |_____|

𝙇𝙤𝙬-𝙋𝙤𝙬𝙚𝙧 𝙐𝙣𝙞𝙫𝙚𝙧𝙨𝙖𝙡 𝘼𝙨𝙮𝙣𝙘𝙝𝙧𝙤𝙣𝙤𝙪𝙨 𝙍𝙚𝙘𝙚𝙞𝙫𝙚𝙧-𝙏𝙧𝙖𝙣𝙨𝙢𝙞𝙩𝙩𝙚𝙧

*/

#ifndef INKI_LP_UARTE
#define INKI_LP_UARTE

#include <stdlib.h>
#include <stdio.h>
#include "lib/d_vector/vector.h"
#include "lib/d_stack/stack.h"
#include <logging/log.h>
#include <logging/log_instance.h>
#include "lp_uarte_cfg.h"

struct lp_uarte
{
    LOG_INSTANCE_PTR_DECLARE(log);
    struct lp_uarte_dev_params param;
    void* private_ptr;
};


struct lp_uarte_params {
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

#define LP_UARTE_NAME "lp_uarte"

#define LP_UARTE_INIT(_name)  \
LOG_INSTANCE_REGISTER(LP_UARTE_NAME, _name, CONFIG_LP_UARTE_);  \
struct lp_uarte _name = {  \
            LOG_INSTANCE_PTR_INIT(log, LP_UARTE_NAME, _name)  \
}

int lp_uarte_init(struct lp_uarte* lp);
int lp_uarte_tx(struct lp_uarte* lp, void* data, size_t len);
int lp_uarte_rx(struct lp_uarte* lp);
int lp_uarte_tx_ft_en(struct lp_uarte* lp, size_t total_file_size);

int lp_uarte_register_rx_isr(struct lp_uarte* lp, void (*func_ptr)());
int lp_uarte_remove_rx_isr(struct lp_uarte* lp, void (*func_ptr)());
int lp_uarte_clear_all_rx_isrs(struct lp_uarte* lp);

int lp_uarte_register_tx_isr(struct lp_uarte* lp, void (*func_ptr)());
int lp_uarte_remove_tx_isr(struct lp_uarte* lp, void (*func_ptr)());
int lp_uarte_clear_all_tx_isrs(struct lp_uarte* lp);



#endif