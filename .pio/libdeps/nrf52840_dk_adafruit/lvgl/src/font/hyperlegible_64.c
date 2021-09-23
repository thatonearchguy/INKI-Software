/*******************************************************************************
 * Size: 64 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef HYPERLEGIBLE_64
#define HYPERLEGIBLE_64 1
#endif

#if HYPERLEGIBLE_64

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0030 "0" */
    0x0, 0xf, 0xfc, 0x0, 0x0, 0xf, 0xff, 0xc0,
    0x0, 0xf, 0xff, 0xfc, 0x0, 0xf, 0xff, 0xff,
    0xc0, 0x7, 0xfc, 0xf, 0xf8, 0x3, 0xfc, 0x0,
    0xff, 0x0, 0xfc, 0x0, 0xf, 0xc0, 0x7f, 0x80,
    0x1, 0xf8, 0x1f, 0xe0, 0x0, 0x7e, 0xf, 0xfc,
    0x0, 0xf, 0xc3, 0xff, 0x80, 0x3, 0xf1, 0xff,
    0xf0, 0x0, 0x7e, 0x7e, 0xfc, 0x0, 0x1f, 0x9f,
    0xbf, 0x80, 0x7, 0xe7, 0xe7, 0xf0, 0x1, 0xfb,
    0xf0, 0xfc, 0x0, 0x3f, 0xfc, 0x3f, 0x80, 0xf,
    0xff, 0x7, 0xf0, 0x3, 0xff, 0xc0, 0xfc, 0x0,
    0xff, 0xf0, 0x3f, 0x80, 0x3f, 0xfc, 0x7, 0xf0,
    0xf, 0xff, 0x0, 0xfe, 0x3, 0xff, 0xc0, 0x3f,
    0x80, 0xff, 0xf0, 0x7, 0xf0, 0x3f, 0xfc, 0x0,
    0xfe, 0xf, 0xff, 0x0, 0x3f, 0x83, 0xff, 0xc0,
    0x7, 0xf0, 0xff, 0xf0, 0x0, 0xfe, 0x3f, 0xfc,
    0x0, 0x3f, 0xdf, 0xdf, 0x80, 0x7, 0xf7, 0xe7,
    0xe0, 0x0, 0xff, 0xf9, 0xf8, 0x0, 0x3f, 0xfe,
    0x7e, 0x0, 0x7, 0xff, 0x8f, 0xc0, 0x0, 0xff,
    0xc3, 0xf0, 0x0, 0x3f, 0xf0, 0x7e, 0x0, 0x7,
    0xf8, 0x1f, 0x80, 0x0, 0xfe, 0x3, 0xf0, 0x0,
    0x3f, 0x0, 0xff, 0x0, 0x3f, 0xc0, 0x1f, 0xf0,
    0x3f, 0xe0, 0x3, 0xff, 0xff, 0xf0, 0x0, 0x3f,
    0xff, 0xf0, 0x0, 0x7, 0xff, 0xf0, 0x0, 0x0,
    0x3f, 0xe0, 0x0,

    /* U+0031 "1" */
    0x0, 0x3, 0xc0, 0x1, 0xf0, 0x0, 0x7c, 0x0,
    0x3f, 0x0, 0x3f, 0xc0, 0x7f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0,
    0xfc, 0x0, 0x3f, 0x0, 0xf, 0xc0, 0x3, 0xf0,
    0x0, 0xfc, 0x0, 0x3f, 0x0, 0xf, 0xc0, 0x3,
    0xf0, 0x0, 0xfc, 0x0, 0x3f, 0x0, 0xf, 0xc0,
    0x3, 0xf0, 0x0, 0xfc, 0x0, 0x3f, 0x0, 0xf,
    0xc0, 0x3, 0xf0, 0x0, 0xfc, 0x0, 0x3f, 0x0,
    0xf, 0xc0, 0x3, 0xf0, 0x0, 0xfc, 0x0, 0x3f,
    0x0, 0xf, 0xc0, 0x3, 0xf0, 0x0, 0xfc, 0x0,
    0x3f, 0x0, 0xf, 0xc0, 0x3, 0xf0, 0x0, 0xfc,
    0x0, 0x3f, 0x0, 0xf, 0xc0, 0x3, 0xf0,

    /* U+0032 "2" */
    0x0, 0xf, 0xf8, 0x0, 0x0, 0xff, 0xfe, 0x0,
    0x7, 0xff, 0xfe, 0x0, 0x1f, 0xff, 0xff, 0x0,
    0xff, 0x81, 0xff, 0x1, 0xfc, 0x0, 0xfe, 0x7,
    0xe0, 0x0, 0xfe, 0x1f, 0x80, 0x0, 0xfc, 0x3f,
    0x0, 0x1, 0xfc, 0x7c, 0x0, 0x1, 0xf8, 0x38,
    0x0, 0x3, 0xf0, 0x0, 0x0, 0x7, 0xe0, 0x0,
    0x0, 0xf, 0xc0, 0x0, 0x0, 0x1f, 0x80, 0x0,
    0x0, 0x3f, 0x0, 0x0, 0x0, 0xfc, 0x0, 0x0,
    0x1, 0xf8, 0x0, 0x0, 0x7, 0xf0, 0x0, 0x0,
    0xf, 0xc0, 0x0, 0x0, 0x3f, 0x80, 0x0, 0x0,
    0x7e, 0x0, 0x0, 0x1, 0xfc, 0x0, 0x0, 0x7,
    0xf0, 0x0, 0x0, 0x1f, 0xc0, 0x0, 0x0, 0x7f,
    0x0, 0x0, 0x1, 0xfc, 0x0, 0x0, 0x7, 0xf0,
    0x0, 0x0, 0x1f, 0xc0, 0x0, 0x0, 0x7f, 0x0,
    0x0, 0x1, 0xfc, 0x0, 0x0, 0x7, 0xf0, 0x0,
    0x0, 0x1f, 0xc0, 0x0, 0x0, 0xff, 0x0, 0x0,
    0x3, 0xf8, 0x0, 0x0, 0xf, 0xe0, 0x0, 0x0,
    0x3f, 0x80, 0x0, 0x1, 0xfe, 0x0, 0x0, 0x7,
    0xf0, 0x0, 0x0, 0x1f, 0xc0, 0x0, 0x0, 0x7f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,

    /* U+0033 "3" */
    0x0, 0x3f, 0xf0, 0x0, 0x7, 0xff, 0xf8, 0x0,
    0x3f, 0xff, 0xf8, 0x3, 0xff, 0xff, 0xf0, 0x1f,
    0xe0, 0x3f, 0xe0, 0xfe, 0x0, 0x3f, 0xc3, 0xf0,
    0x0, 0x7f, 0x1f, 0x80, 0x0, 0xfe, 0x7e, 0x0,
    0x3, 0xfb, 0xf0, 0x0, 0x7, 0xe3, 0xc0, 0x0,
    0x1f, 0x81, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x1,
    0xf8, 0x0, 0x0, 0x7, 0xe0, 0x0, 0x0, 0x3f,
    0x0, 0x0, 0x0, 0xfc, 0x0, 0x0, 0x7, 0xe0,
    0x0, 0x0, 0x3f, 0x80, 0x0, 0x7, 0xfc, 0x0,
    0x7, 0xff, 0xc0, 0x0, 0x1f, 0xfc, 0x0, 0x0,
    0x7f, 0xfc, 0x0, 0x1, 0xff, 0xfc, 0x0, 0x0,
    0x1f, 0xf8, 0x0, 0x0, 0xf, 0xf0, 0x0, 0x0,
    0xf, 0xc0, 0x0, 0x0, 0x3f, 0x80, 0x0, 0x0,
    0x7e, 0x0, 0x0, 0x0, 0xfc, 0x0, 0x0, 0x3,
    0xf0, 0x0, 0x0, 0xf, 0xc0, 0x0, 0x0, 0x3f,
    0x8, 0x0, 0x0, 0xfd, 0xe0, 0x0, 0x3, 0xff,
    0xc0, 0x0, 0xf, 0xff, 0x0, 0x0, 0x7e, 0x7e,
    0x0, 0x3, 0xf9, 0xfc, 0x0, 0xf, 0xc3, 0xf8,
    0x0, 0xff, 0x7, 0xf8, 0xf, 0xf8, 0xf, 0xff,
    0xff, 0xc0, 0x1f, 0xff, 0xfc, 0x0, 0x1f, 0xff,
    0xc0, 0x0, 0xf, 0xf8, 0x0,

    /* U+0034 "4" */
    0x0, 0x0, 0x7, 0xe0, 0x0, 0x0, 0x3, 0xf8,
    0x0, 0x0, 0x1, 0xfe, 0x0, 0x0, 0x0, 0xff,
    0x80, 0x0, 0x0, 0x3f, 0xe0, 0x0, 0x0, 0x1f,
    0xf8, 0x0, 0x0, 0xf, 0xfe, 0x0, 0x0, 0x7,
    0xff, 0x80, 0x0, 0x1, 0xf7, 0xe0, 0x0, 0x0,
    0xfd, 0xf8, 0x0, 0x0, 0x7e, 0x7e, 0x0, 0x0,
    0x3f, 0x1f, 0x80, 0x0, 0xf, 0x87, 0xe0, 0x0,
    0x7, 0xe1, 0xf8, 0x0, 0x3, 0xf0, 0x7e, 0x0,
    0x1, 0xf8, 0x1f, 0x80, 0x0, 0x7c, 0x7, 0xe0,
    0x0, 0x3f, 0x1, 0xf8, 0x0, 0x1f, 0x80, 0x7e,
    0x0, 0xf, 0xc0, 0x1f, 0x80, 0x3, 0xe0, 0x7,
    0xe0, 0x1, 0xf8, 0x1, 0xf8, 0x0, 0xfc, 0x0,
    0x7e, 0x0, 0x7e, 0x0, 0x1f, 0x80, 0x1f, 0x0,
    0x7, 0xe0, 0xf, 0xc0, 0x1, 0xf8, 0x7, 0xe0,
    0x0, 0x7e, 0x3, 0xf0, 0x0, 0x1f, 0x80, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x0, 0x0, 0x7, 0xe0, 0x0, 0x0, 0x1, 0xf8,
    0x0, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x0, 0x1f,
    0x80, 0x0, 0x0, 0x7, 0xe0, 0x0, 0x0, 0x1,
    0xf8, 0x0, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x0,
    0x1f, 0x80, 0x0, 0x0, 0x7, 0xe0, 0x0, 0x0,
    0x1, 0xf8, 0x0,

    /* U+0035 "5" */
    0x1f, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xc1,
    0xff, 0xff, 0xff, 0x7, 0xff, 0xff, 0xfc, 0x1f,
    0x0, 0x0, 0x0, 0x7c, 0x0, 0x0, 0x1, 0xf0,
    0x0, 0x0, 0x7, 0x80, 0x0, 0x0, 0x3e, 0x0,
    0x0, 0x0, 0xf8, 0x0, 0x0, 0x3, 0xe0, 0x0,
    0x0, 0xf, 0x80, 0x0, 0x0, 0x3e, 0x0, 0x0,
    0x0, 0xf8, 0x0, 0x0, 0x3, 0xe1, 0xff, 0x0,
    0xf, 0xbf, 0xff, 0x0, 0x7d, 0xff, 0xff, 0x1,
    0xff, 0xff, 0xfe, 0x7, 0xfe, 0x7, 0xfc, 0x1f,
    0xe0, 0x3, 0xf8, 0x7f, 0x0, 0x7, 0xf0, 0xf8,
    0x0, 0xf, 0xe0, 0x40, 0x0, 0x1f, 0x80, 0x0,
    0x0, 0x7e, 0x0, 0x0, 0x1, 0xfc, 0x0, 0x0,
    0x3, 0xf0, 0x0, 0x0, 0xf, 0xc0, 0x0, 0x0,
    0x3f, 0x0, 0x0, 0x0, 0xfc, 0x0, 0x0, 0x3,
    0xf0, 0x0, 0x0, 0xf, 0xc2, 0x0, 0x0, 0x3f,
    0x78, 0x0, 0x1, 0xff, 0xf0, 0x0, 0x7, 0xef,
    0xc0, 0x0, 0x3f, 0x9f, 0x80, 0x0, 0xfc, 0x7f,
    0x0, 0x7, 0xf0, 0xfe, 0x0, 0x3f, 0x81, 0xfe,
    0x7, 0xfc, 0x3, 0xff, 0xff, 0xe0, 0x7, 0xff,
    0xff, 0x0, 0x7, 0xff, 0xf0, 0x0, 0x3, 0xfe,
    0x0, 0x0,

    /* U+0036 "6" */
    0x0, 0x7, 0xf8, 0x0, 0x0, 0x7f, 0xfe, 0x0,
    0x3, 0xff, 0xff, 0x0, 0xf, 0xff, 0xff, 0x0,
    0x3f, 0x81, 0xff, 0x0, 0xfc, 0x0, 0xfe, 0x3,
    0xf0, 0x0, 0xfe, 0x7, 0xc0, 0x0, 0xe0, 0x1f,
    0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0xf8,
    0x0, 0x0, 0x1, 0xf0, 0x0, 0x0, 0x7, 0xc0,
    0x0, 0x0, 0xf, 0x80, 0x0, 0x0, 0x1f, 0x0,
    0x0, 0x0, 0x3e, 0x3, 0xfc, 0x0, 0x7c, 0x3f,
    0xff, 0x1, 0xf9, 0xff, 0xff, 0x3, 0xe7, 0xff,
    0xff, 0x7, 0xdf, 0x80, 0xff, 0xf, 0xfc, 0x0,
    0x7f, 0x1f, 0xf0, 0x0, 0x7f, 0x3f, 0xc0, 0x0,
    0x7e, 0x7f, 0x0, 0x0, 0x7e, 0xfe, 0x0, 0x0,
    0xfd, 0xfc, 0x0, 0x1, 0xff, 0xf0, 0x0, 0x1,
    0xff, 0xe0, 0x0, 0x3, 0xff, 0xc0, 0x0, 0x7,
    0xff, 0x80, 0x0, 0xf, 0xdf, 0x0, 0x0, 0x1f,
    0xbe, 0x0, 0x0, 0x3f, 0x7c, 0x0, 0x0, 0x7e,
    0xfc, 0x0, 0x1, 0xf8, 0xf8, 0x0, 0x3, 0xf1,
    0xf0, 0x0, 0x7, 0xe3, 0xf0, 0x0, 0x1f, 0x83,
    0xf0, 0x0, 0x7f, 0x3, 0xf0, 0x1, 0xfc, 0x7,
    0xf8, 0xf, 0xf0, 0x7, 0xff, 0xff, 0xc0, 0x3,
    0xff, 0xff, 0x0, 0x3, 0xff, 0xf8, 0x0, 0x0,
    0xff, 0x80, 0x0,

    /* U+0037 "7" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0,
    0x0, 0x0, 0xfc, 0x0, 0x0, 0x7, 0xe0, 0x0,
    0x0, 0x1f, 0x80, 0x0, 0x0, 0xfc, 0x0, 0x0,
    0x3, 0xf0, 0x0, 0x0, 0x1f, 0x80, 0x0, 0x0,
    0x7e, 0x0, 0x0, 0x3, 0xf0, 0x0, 0x0, 0xf,
    0xc0, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x1, 0xf8,
    0x0, 0x0, 0xf, 0xc0, 0x0, 0x0, 0x3f, 0x0,
    0x0, 0x1, 0xfc, 0x0, 0x0, 0x7, 0xe0, 0x0,
    0x0, 0x3f, 0x80, 0x0, 0x0, 0xfc, 0x0, 0x0,
    0x7, 0xf0, 0x0, 0x0, 0x1f, 0x80, 0x0, 0x0,
    0xfe, 0x0, 0x0, 0x3, 0xf0, 0x0, 0x0, 0x1f,
    0xc0, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x3, 0xf8,
    0x0, 0x0, 0xf, 0xc0, 0x0, 0x0, 0x7f, 0x0,
    0x0, 0x1, 0xf8, 0x0, 0x0, 0xf, 0xe0, 0x0,
    0x0, 0x3f, 0x0, 0x0, 0x1, 0xfc, 0x0, 0x0,
    0x7, 0xe0, 0x0, 0x0, 0x3f, 0x80, 0x0, 0x0,
    0xfc, 0x0, 0x0, 0x7, 0xf0, 0x0, 0x0, 0x1f,
    0x80, 0x0, 0x0, 0xfe, 0x0, 0x0, 0x3, 0xf0,
    0x0, 0x0, 0x1f, 0xc0, 0x0, 0x0,

    /* U+0038 "8" */
    0x0, 0xf, 0xf0, 0x0, 0x0, 0x3f, 0xfc, 0x0,
    0x0, 0x7f, 0xfe, 0x0, 0x1, 0xff, 0xff, 0x80,
    0x1, 0xf8, 0x1f, 0x80, 0x3, 0xf0, 0xf, 0xc0,
    0x7, 0xe0, 0x7, 0xe0, 0x7, 0xc0, 0x3, 0xe0,
    0xf, 0xc0, 0x3, 0xf0, 0xf, 0x80, 0x1, 0xf0,
    0xf, 0x80, 0x1, 0xf0, 0xf, 0x80, 0x1, 0xf0,
    0xf, 0x80, 0x1, 0xf0, 0xf, 0x80, 0x1, 0xf0,
    0xf, 0xc0, 0x3, 0xf0, 0x7, 0xc0, 0x3, 0xe0,
    0x7, 0xe0, 0x7, 0xe0, 0x3, 0xf0, 0xf, 0xc0,
    0x3, 0xf8, 0x3f, 0xc0, 0x1, 0xff, 0xff, 0x80,
    0x0, 0xff, 0xff, 0x0, 0x3, 0xff, 0xff, 0xc0,
    0xf, 0xff, 0xff, 0xf0, 0x1f, 0xf0, 0xf, 0xf8,
    0x3f, 0xc0, 0x3, 0xfc, 0x3f, 0x80, 0x1, 0xfc,
    0x7f, 0x0, 0x0, 0xfe, 0x7e, 0x0, 0x0, 0x7e,
    0xfc, 0x0, 0x0, 0x7f, 0xfc, 0x0, 0x0, 0x3f,
    0xfc, 0x0, 0x0, 0x3f, 0xfc, 0x0, 0x0, 0x3f,
    0xfc, 0x0, 0x0, 0x3f, 0xfc, 0x0, 0x0, 0x3f,
    0xfc, 0x0, 0x0, 0x3f, 0x7e, 0x0, 0x0, 0x7e,
    0x7f, 0x0, 0x0, 0xfe, 0x3f, 0x0, 0x0, 0xfc,
    0x3f, 0xc0, 0x3, 0xfc, 0x1f, 0xf0, 0xf, 0xf8,
    0xf, 0xff, 0xff, 0xf0, 0x3, 0xff, 0xff, 0xc0,
    0x0, 0xff, 0xff, 0x0, 0x0, 0x1f, 0xf8, 0x0,

    /* U+0039 "9" */
    0x0, 0x1f, 0xf0, 0x0, 0x0, 0xff, 0xf8, 0x0,
    0x7, 0xff, 0xfc, 0x0, 0x3f, 0xff, 0xfe, 0x0,
    0xff, 0x83, 0xfe, 0x3, 0xfc, 0x1, 0xfe, 0x7,
    0xe0, 0x0, 0xfc, 0x1f, 0x80, 0x1, 0xfc, 0x7f,
    0x0, 0x1, 0xf8, 0xfc, 0x0, 0x1, 0xf9, 0xf8,
    0x0, 0x3, 0xf7, 0xe0, 0x0, 0x3, 0xff, 0xc0,
    0x0, 0x7, 0xff, 0x80, 0x0, 0xf, 0xff, 0x0,
    0x0, 0x1f, 0xfe, 0x0, 0x0, 0x3f, 0xfc, 0x0,
    0x0, 0x7f, 0xf8, 0x0, 0x0, 0xff, 0xf8, 0x0,
    0x3, 0xfb, 0xf0, 0x0, 0x7, 0xe7, 0xe0, 0x0,
    0xf, 0xc7, 0xe0, 0x0, 0x3f, 0x8f, 0xe0, 0x0,
    0xfe, 0xf, 0xc0, 0x3, 0xfc, 0x1f, 0xe0, 0xf,
    0xf0, 0x1f, 0xf0, 0x7f, 0xc0, 0x1f, 0xff, 0xff,
    0x80, 0xf, 0xff, 0xfe, 0x0, 0x7, 0xff, 0xfc,
    0x0, 0x3, 0xff, 0xf0, 0x0, 0x0, 0xf, 0xe0,
    0x0, 0x0, 0x1f, 0x80, 0x0, 0x0, 0x7e, 0x0,
    0x0, 0x1, 0xfc, 0x0, 0x0, 0x3, 0xf0, 0x0,
    0x0, 0xf, 0xe0, 0x0, 0x0, 0x3f, 0x80, 0x0,
    0x0, 0x7e, 0x0, 0x0, 0x1, 0xfc, 0x0, 0x0,
    0x7, 0xf0, 0x0, 0x0, 0xf, 0xc0, 0x0, 0x0,
    0x3f, 0x80, 0x0, 0x0, 0xfe, 0x0, 0x0,

    /* U+003A ":" */
    0x0, 0x7e, 0x7e, 0xff, 0xff, 0xff, 0x7e, 0x7e,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e,
    0x3c
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 664, .box_w = 34, .box_h = 44, .ofs_x = 4, .ofs_y = -1},
    {.bitmap_index = 187, .adv_w = 412, .box_w = 18, .box_h = 42, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 562, .box_w = 31, .box_h = 43, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 588, .box_w = 30, .box_h = 44, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 614, .adv_w = 629, .box_w = 34, .box_h = 42, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 793, .adv_w = 597, .box_w = 30, .box_h = 43, .ofs_x = 4, .ofs_y = -1},
    {.bitmap_index = 955, .adv_w = 612, .box_w = 31, .box_h = 44, .ofs_x = 4, .ofs_y = -1},
    {.bitmap_index = 1126, .adv_w = 522, .box_w = 30, .box_h = 42, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1284, .adv_w = 630, .box_w = 32, .box_h = 44, .ofs_x = 4, .ofs_y = -1},
    {.bitmap_index = 1460, .adv_w = 612, .box_w = 31, .box_h = 43, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 1627, .adv_w = 210, .box_w = 8, .box_h = 33, .ofs_x = 2, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 48, .range_length = 11, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    1, 3,
    3, 5,
    5, 6,
    5, 10,
    6, 10,
    7, 2,
    7, 3,
    8, 2,
    8, 5,
    8, 8,
    8, 9,
    9, 2,
    9, 8,
    9, 10,
    10, 5,
    10, 8,
    10, 9
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -19, -8, -19, -23, -16, -24, -19, 29,
    -48, 37, -48, -29, -19, -24, -24, -19,
    -24
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 17,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t hyperlegible_64 = {
#else
lv_font_t hyperlegible_64 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 44,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -5,
    .underline_thickness = 4,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if HYPERLEGIBLE_64*/
