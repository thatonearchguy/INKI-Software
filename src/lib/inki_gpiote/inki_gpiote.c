/*
 * Copyright (c) 2022 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 * 
 */



/*
___      ___    __ _ ___ _ ___ __
 | |\||/  |    /__|_) | / \ | |_ 
_|_| ||\ _|____\_||  _|_\_/ | |__

【 ＩＮＫＩ　Ｉｎｔｅｒｒｕｐｔ－ｂａｓｅｄ　ＧＰＩＯＴＥ　ｄｒｉｖｅｒ 】

*/


#include "inki_gpiote.h"

LOG_LEVEL_SET(LOG_LEVEL_INF);

void (*func_ptrs[8])() = {0}; //not using custom stack class for speed.
uint32_t occupied;


ISR_DIRECT_DECLARE(gpiote_handler)
{
    if(occupied > 0)
    {
        for(int i = 0; i < occupied; i ++)
        {
            (*func_ptrs[i])();
        }
    }
    //GTFO
    ISR_DIRECT_PM();
    return 1;
}

int inki_gpiote_init()
{
    occupied = 0;
    IRQ_DIRECT_CONNECT(GPIOTE_IRQn, 4, gpiote_handler, 0);
    return 1;
}

int inki_gpiote_register_isr(void (*func_ptr)())
{
    func_ptrs[occupied] = func_ptr;
    if(occupied++ == 0) irq_enable(GPIOTE_IRQn);
    return 1;
}
int inki_gpiote_remove_isr(void (*func_ptr)())
{
    int foundindex = -1;
    for(int i = 0; i < occupied - 1; i ++)
    {
        if(func_ptrs[i] == func_ptr)
        {
            foundindex = i;
        }
    }
    if(foundindex == -1) return -ENOENT;
    uint32_t start_offset = foundindex*sizeof(void(*)());
    if(foundindex < occupied - 1)
    {
        uint32_t move_offset = (foundindex+1)*sizeof(void(*)());
        memmove(func_ptrs+start_offset, func_ptrs+move_offset, (occupied - (foundindex+1))*sizeof(void(*)()));
    }
    else
    {
        memset(func_ptrs + start_offset, 0, sizeof(void(*)()));
    }
    --occupied;
    return 1;
}

int inki_gpiote_clear_all()
{
    memset(func_ptrs, 0, occupied * sizeof(void(*)()));
    occupied = 0;
    irq_disable(GPIOTE_IRQn);
    return 1;
}
