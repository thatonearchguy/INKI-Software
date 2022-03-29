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

#ifndef INKI_GPIOTE_DRV
#define INKI_GPIOTE_DRV

#include "lib/d_vector/vector.h"
#include "lib/d_stack/stack.h"
#include <logging/log.h>
#include <hal/nrf_gpiote.h>

/* This is just a little shell library to allow multiple functions to be executed off one ISR. */

int inki_gpiote_register_isr(void (*func_ptr)());
int inki_gpiote_remove_isr(void (*func_ptr)());
int inki_gpiote_clear_all();
int inki_gpiote_init();


#endif