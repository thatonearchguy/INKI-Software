/*
 * Copyright (c) 2021 INKI-Systems Inc.
 *
 * Licensed under GPL 3
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

#include "lp_uarte.h"
#include "lp_uarte_dev.h"


LOG_LEVEL_SET(LOG_LEVEL_INF);

#define LP_ERR_CHECK(logger, message, rc) \
if(rc < 0) \
{ \
    LOG_INST_ERR(logger, message); \
    return rc; \
}

static int lp_uarte_verify_pins(const struct lp_uarte_dev* dev)
{
    uint32_t check_arr[7] = {dev->p.rts_pin, dev->p.cts_pin, dev->p.tx_pin, dev->p.rx_pin, dev->p.s0_pin, dev->p.s1_pin, dev->p.s2_pin};
    uint32_t counted[7];
    for(int i = 0; i < ARRAY_SIZE(check_arr); i++)
    {
        for(int x = 0; x < ARRAY_SIZE(check_arr); x++)
        {
            if((x!=i)&&(check_arr[x] == check_arr[i])) return -EINVAL;
        }
    }
    return 1;
}

static int lp_uarte_verify_bools(const struct lp_uarte_dev* dev)
{
    if((dev->p.even_parity) && (dev->p.odd_parity)) return -EINVAL;
}



