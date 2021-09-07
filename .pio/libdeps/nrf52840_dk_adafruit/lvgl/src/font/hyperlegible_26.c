/*******************************************************************************
 * Size: 26 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef HYPERLEGIBLE_26
#define HYPERLEGIBLE_26 1
#endif

#if HYPERLEGIBLE_26

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x6d, 0xb6, 0xdb, 0x6d, 0xb0, 0x3f, 0xe0,

    /* U+0022 "\"" */
    0xcf, 0x3c, 0xf3, 0xcc,

    /* U+0023 "#" */
    0x6, 0x30, 0xc, 0x60, 0x18, 0xc0, 0x71, 0x87,
    0xff, 0xef, 0xff, 0xc3, 0x18, 0x6, 0x30, 0xc,
    0x60, 0x18, 0xc0, 0x31, 0x87, 0xff, 0xef, 0xff,
    0xc3, 0x1c, 0x6, 0x30, 0xc, 0x60, 0x18, 0xc0,

    /* U+0024 "$" */
    0x6, 0x0, 0x30, 0x7, 0xe0, 0x7f, 0xc7, 0x6f,
    0x63, 0x1b, 0x18, 0x18, 0xc0, 0xe6, 0x3, 0xf0,
    0xf, 0xe0, 0x1f, 0xc0, 0x6f, 0x3, 0x1c, 0x18,
    0x68, 0xc3, 0xc6, 0x1b, 0x33, 0x9f, 0xf8, 0x3f,
    0x80, 0x60, 0x3, 0x0,

    /* U+0025 "%" */
    0x3e, 0x0, 0xc1, 0xfc, 0x6, 0xe, 0x38, 0x30,
    0x30, 0x60, 0xc0, 0xc1, 0x86, 0x3, 0x6, 0x30,
    0xe, 0x39, 0xc0, 0x1f, 0xc6, 0x0, 0x1e, 0x31,
    0xf0, 0x1, 0x8f, 0xe0, 0x6, 0x71, 0xc0, 0x31,
    0x83, 0x1, 0x86, 0xc, 0xc, 0x18, 0x30, 0x30,
    0x71, 0xc1, 0x80, 0xfe, 0xc, 0x0, 0xf0,

    /* U+0026 "&" */
    0x7, 0xc0, 0x7, 0xf0, 0x7, 0x1c, 0x3, 0x6,
    0x1, 0x83, 0x0, 0xe3, 0x80, 0x3b, 0x80, 0x1f,
    0x0, 0x3f, 0x86, 0x38, 0xe3, 0x38, 0x3b, 0x98,
    0xf, 0x8c, 0x3, 0xc6, 0x1, 0xe1, 0xc1, 0xf8,
    0xff, 0xce, 0x1f, 0x83, 0x80,

    /* U+0027 "'" */
    0xff, 0xc0,

    /* U+0028 "(" */
    0x18, 0xc2, 0x18, 0x61, 0x8c, 0x30, 0xc3, 0xc,
    0x30, 0xc3, 0x6, 0x18, 0x60, 0xc3, 0x6, 0x18,

    /* U+0029 ")" */
    0x60, 0xc3, 0x6, 0x18, 0x60, 0xc3, 0xc, 0x30,
    0xc3, 0xc, 0x31, 0x86, 0x18, 0xc3, 0x18, 0x60,

    /* U+002A "*" */
    0x18, 0x18, 0xdb, 0x7e, 0x3c, 0x3c, 0x66,

    /* U+002B "+" */
    0x6, 0x0, 0x30, 0x1, 0x80, 0xc, 0x0, 0x60,
    0x3, 0x3, 0xff, 0xff, 0xff, 0x6, 0x0, 0x30,
    0x1, 0x80, 0xc, 0x0, 0x60, 0x0,

    /* U+002C "," */
    0xff, 0xa5, 0x80,

    /* U+002D "-" */
    0xff, 0xff,

    /* U+002E "." */
    0xff, 0x80,

    /* U+002F "/" */
    0x1, 0x80, 0xc0, 0xc0, 0x60, 0x70, 0x30, 0x18,
    0x18, 0xc, 0xe, 0x6, 0x3, 0x3, 0x1, 0x81,
    0xc0, 0xc0, 0x60, 0x0,

    /* U+0030 "0" */
    0xf, 0xc0, 0xff, 0xc3, 0x87, 0x1c, 0x6, 0x78,
    0x1b, 0x70, 0x3c, 0xe0, 0xf1, 0x83, 0xc3, 0xf,
    0xe, 0x3c, 0x1c, 0xf0, 0x3b, 0x60, 0x69, 0x80,
    0xe3, 0x87, 0xf, 0xfc, 0xf, 0xc0,

    /* U+0031 "1" */
    0x6, 0x1f, 0xff, 0xf0, 0x60, 0xc1, 0x83, 0x6,
    0xc, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x6,

    /* U+0032 "2" */
    0xf, 0x81, 0xff, 0x1e, 0x1c, 0xc0, 0x62, 0x3,
    0x0, 0x18, 0x0, 0xc0, 0xc, 0x0, 0xc0, 0xe,
    0x0, 0xe0, 0xe, 0x0, 0xc0, 0x1c, 0x1, 0xc0,
    0x1f, 0xff, 0xff, 0xf8,

    /* U+0033 "3" */
    0xf, 0x81, 0xff, 0x1c, 0x1c, 0xc0, 0x60, 0x3,
    0x0, 0x18, 0x1, 0x80, 0xf8, 0x7, 0xe0, 0x3,
    0x80, 0x6, 0x0, 0x32, 0x1, 0xb0, 0xd, 0xc1,
    0xc7, 0xfc, 0xf, 0xc0,

    /* U+0034 "4" */
    0x0, 0x60, 0x3, 0x80, 0x1e, 0x0, 0xf8, 0x7,
    0x60, 0x39, 0x80, 0xc6, 0x6, 0x18, 0x38, 0x61,
    0xc1, 0x8e, 0x6, 0x3f, 0xff, 0xff, 0xfc, 0x1,
    0x80, 0x6, 0x0, 0x18, 0x0, 0x60,

    /* U+0035 "5" */
    0x3f, 0xe7, 0xfe, 0x60, 0x6, 0x0, 0x60, 0x6,
    0xf8, 0x7f, 0xc7, 0xe, 0x60, 0x70, 0x3, 0x0,
    0x30, 0x3, 0x40, 0x3e, 0x7, 0x70, 0xe3, 0xfc,
    0x1f, 0x80,

    /* U+0036 "6" */
    0xf, 0x81, 0xfe, 0x30, 0x66, 0x0, 0x60, 0xc,
    0xf8, 0xdf, 0xcf, 0xe, 0xe0, 0x7c, 0x3, 0xc0,
    0x3c, 0x3, 0xc0, 0x36, 0x6, 0x70, 0xe3, 0xfc,
    0x1f, 0x80,

    /* U+0037 "7" */
    0xff, 0xff, 0xff, 0x0, 0x70, 0x6, 0x0, 0xe0,
    0xc, 0x1, 0xc0, 0x18, 0x3, 0x80, 0x30, 0x7,
    0x0, 0x60, 0xe, 0x0, 0xc0, 0x1c, 0x1, 0xc0,
    0x38, 0x0,

    /* U+0038 "8" */
    0xf, 0x80, 0xfe, 0xe, 0x38, 0x60, 0xc3, 0x6,
    0x18, 0x30, 0xe3, 0x83, 0xf8, 0x3f, 0xe3, 0x83,
    0xb0, 0xf, 0x80, 0x3c, 0x1, 0xe0, 0xd, 0xc1,
    0xc7, 0xfc, 0x1f, 0xc0,

    /* U+0039 "9" */
    0xf, 0x3, 0xfc, 0x70, 0xee, 0x6, 0xc0, 0x3c,
    0x3, 0xc0, 0x3c, 0x3, 0x60, 0x67, 0xe, 0x3f,
    0xc0, 0xfc, 0x1, 0x80, 0x38, 0x3, 0x0, 0x60,
    0xe, 0x0,

    /* U+003A ":" */
    0xff, 0x80, 0x0, 0x3, 0xfe,

    /* U+003B ";" */
    0xff, 0x80, 0x0, 0x3, 0xfe, 0x96,

    /* U+003C "<" */
    0x0, 0x8, 0x1, 0xc0, 0x7e, 0xf, 0x81, 0xf0,
    0x7c, 0x3, 0x80, 0x1f, 0x0, 0x3e, 0x0, 0x7e,
    0x0, 0x7c, 0x0, 0xf0, 0x1, 0x80,

    /* U+003D "=" */
    0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x0, 0x0,
    0x7f, 0xff, 0xff, 0xe0,

    /* U+003E ">" */
    0x80, 0x7, 0x0, 0x3e, 0x0, 0x7e, 0x0, 0x7c,
    0x0, 0xf8, 0x1, 0xe0, 0x1f, 0x7, 0xc0, 0xf8,
    0x3f, 0x1, 0xc0, 0x8, 0x0, 0x0,

    /* U+003F "?" */
    0x1f, 0xf, 0xfb, 0xc3, 0xe0, 0x34, 0x6, 0x0,
    0xc0, 0x30, 0xc, 0x7, 0x1, 0xc0, 0x30, 0x6,
    0x0, 0x0, 0x0, 0x7, 0x0, 0xe0, 0x1c, 0x0,

    /* U+0040 "@" */
    0x3, 0xf0, 0x3, 0xff, 0x1, 0xc0, 0xf0, 0xe0,
    0xe, 0x63, 0xf1, 0x99, 0xfc, 0x7c, 0xe3, 0xf,
    0x30, 0xc3, 0xcc, 0x30, 0xf3, 0xc, 0x3c, 0xe7,
    0x19, 0x9f, 0xfe, 0x63, 0x8f, 0xc, 0x0, 0x3,
    0xc0, 0x0, 0x3f, 0xc0, 0x3, 0xe0, 0x0,

    /* U+0041 "A" */
    0x1, 0xc0, 0x3, 0xc0, 0x3, 0xc0, 0x7, 0x60,
    0x6, 0x60, 0x6, 0x70, 0xe, 0x30, 0xc, 0x30,
    0xc, 0x38, 0x1c, 0x18, 0x18, 0x1c, 0x3f, 0xfc,
    0x3f, 0xfc, 0x30, 0xe, 0x70, 0x6, 0x60, 0x6,
    0xe0, 0x7,

    /* U+0042 "B" */
    0xff, 0x87, 0xff, 0x30, 0x1d, 0x80, 0x6c, 0x3,
    0x60, 0x1b, 0x1, 0xdf, 0xfc, 0xff, 0xf6, 0x1,
    0xb0, 0x7, 0x80, 0x3c, 0x1, 0xe0, 0xf, 0x0,
    0xdf, 0xfe, 0xff, 0xc0,

    /* U+0043 "C" */
    0x7, 0xe0, 0x7f, 0xc3, 0x83, 0x9c, 0x7, 0x60,
    0x3, 0x0, 0xc, 0x0, 0x30, 0x0, 0xc0, 0x3,
    0x0, 0xc, 0x0, 0x38, 0x0, 0x60, 0x1, 0xc0,
    0x73, 0x83, 0x87, 0xfc, 0x7, 0xe0,

    /* U+0044 "D" */
    0xff, 0x83, 0xff, 0x8c, 0xf, 0x30, 0xe, 0xc0,
    0x1b, 0x0, 0x3c, 0x0, 0xf0, 0x3, 0xc0, 0xf,
    0x0, 0x3c, 0x0, 0xf0, 0x3, 0xc0, 0x1b, 0x0,
    0xec, 0xf, 0x3f, 0xf8, 0xff, 0x80,

    /* U+0045 "E" */
    0xff, 0xff, 0xff, 0xc0, 0xc, 0x0, 0xc0, 0xc,
    0x0, 0xc0, 0xf, 0xfc, 0xff, 0xcc, 0x0, 0xc0,
    0xc, 0x0, 0xc0, 0xc, 0x0, 0xc0, 0xf, 0xff,
    0xff, 0xf0,

    /* U+0046 "F" */
    0xff, 0xff, 0xff, 0xc0, 0xc, 0x0, 0xc0, 0xc,
    0x0, 0xc0, 0xf, 0xff, 0xff, 0xfc, 0x0, 0xc0,
    0xc, 0x0, 0xc0, 0xc, 0x0, 0xc0, 0xc, 0x0,
    0xc0, 0x0,

    /* U+0047 "G" */
    0x7, 0xe0, 0x3f, 0xf0, 0xe0, 0xf3, 0x80, 0x66,
    0x0, 0x18, 0x0, 0x30, 0x0, 0x60, 0x0, 0xc0,
    0xff, 0x81, 0xff, 0x0, 0x1e, 0x0, 0x36, 0x0,
    0x6e, 0x1, 0xce, 0xf, 0x8f, 0xfb, 0x7, 0xe2,

    /* U+0048 "H" */
    0xc0, 0xf, 0x0, 0x3c, 0x0, 0xf0, 0x3, 0xc0,
    0xf, 0x0, 0x3c, 0x0, 0xff, 0xff, 0xff, 0xff,
    0x0, 0x3c, 0x0, 0xf0, 0x3, 0xc0, 0xf, 0x0,
    0x3c, 0x0, 0xf0, 0x3, 0xc0, 0xc,

    /* U+0049 "I" */
    0xff, 0xfc, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18,
    0x30, 0x60, 0xc1, 0x83, 0x6, 0x7f, 0xfe,

    /* U+004A "J" */
    0x0, 0x60, 0xc, 0x1, 0x80, 0x30, 0x6, 0x0,
    0xc0, 0x18, 0x3, 0x0, 0x60, 0xc, 0x1, 0xa0,
    0x3c, 0x7, 0xc0, 0xdc, 0x33, 0xfe, 0x1f, 0x0,

    /* U+004B "K" */
    0xc0, 0x73, 0x3, 0x8c, 0xe, 0x30, 0x70, 0xc3,
    0x83, 0x1c, 0xc, 0xe0, 0x37, 0x80, 0xfe, 0x3,
    0xdc, 0xe, 0x38, 0x30, 0x70, 0xc1, 0xc3, 0x3,
    0x8c, 0x7, 0x30, 0xc, 0xc0, 0x38,

    /* U+004C "L" */
    0xc0, 0xc, 0x0, 0xc0, 0xc, 0x0, 0xc0, 0xc,
    0x0, 0xc0, 0xc, 0x0, 0xc0, 0xc, 0x0, 0xc0,
    0xc, 0x0, 0xc0, 0xc, 0x0, 0xc0, 0xf, 0xff,
    0xff, 0xf0,

    /* U+004D "M" */
    0xf0, 0x7, 0xf8, 0x3, 0xfe, 0x3, 0xff, 0x1,
    0xfd, 0x80, 0xde, 0xe0, 0xef, 0x70, 0x77, 0x98,
    0x33, 0xce, 0x39, 0xe3, 0x18, 0xf1, 0x8c, 0x78,
    0xee, 0x3c, 0x36, 0x1e, 0x1b, 0xf, 0xf, 0x87,
    0x83, 0x83, 0xc1, 0xc1, 0x80,

    /* U+004E "N" */
    0xf0, 0xf, 0xc0, 0x3f, 0x80, 0xf6, 0x3, 0xdc,
    0xf, 0x38, 0x3c, 0xe0, 0xf1, 0xc3, 0xc3, 0xf,
    0xe, 0x3c, 0x1c, 0xf0, 0x73, 0xc0, 0xef, 0x1,
    0xbc, 0x7, 0xf0, 0xf, 0xc0, 0x3c,

    /* U+004F "O" */
    0x7, 0xe0, 0x1f, 0xf8, 0x3c, 0x3c, 0x70, 0xe,
    0x60, 0x6, 0xe0, 0x7, 0xc0, 0x3, 0xc0, 0x3,
    0xc0, 0x3, 0xc0, 0x3, 0xc0, 0x3, 0xe0, 0x7,
    0x60, 0x6, 0x70, 0xe, 0x38, 0x3c, 0x1f, 0xf8,
    0x7, 0xe0,

    /* U+0050 "P" */
    0xff, 0x8f, 0xfe, 0xc0, 0x7c, 0x3, 0xc0, 0x3c,
    0x3, 0xc0, 0x3c, 0x7, 0xff, 0xef, 0xf8, 0xc0,
    0xc, 0x0, 0xc0, 0xc, 0x0, 0xc0, 0xc, 0x0,
    0xc0, 0x0,

    /* U+0051 "Q" */
    0x7, 0xe0, 0x7, 0xfe, 0x3, 0xc3, 0xc1, 0xc0,
    0x38, 0x60, 0x6, 0x38, 0x1, 0xcc, 0x0, 0x33,
    0x0, 0xc, 0xc0, 0xc3, 0x30, 0x78, 0xcc, 0xf,
    0x33, 0x81, 0xfc, 0x60, 0x1e, 0x1c, 0x3, 0x83,
    0x83, 0xf0, 0x7f, 0xee, 0x7, 0xe1, 0xc0, 0x0,
    0x20,

    /* U+0052 "R" */
    0xff, 0xc3, 0xff, 0xcc, 0x7, 0xb0, 0x6, 0xc0,
    0x1b, 0x0, 0x6c, 0x1, 0xb0, 0xc, 0xff, 0xf3,
    0xff, 0xc, 0x78, 0x30, 0xf0, 0xc1, 0xc3, 0x3,
    0x8c, 0x7, 0x30, 0xc, 0xc0, 0x18,

    /* U+0053 "S" */
    0x1f, 0x83, 0xff, 0x1c, 0x1d, 0x80, 0x4c, 0x0,
    0x60, 0x1, 0xc0, 0xf, 0xe0, 0xf, 0xe0, 0x7,
    0x80, 0xe, 0x0, 0x34, 0x1, 0xe0, 0xd, 0xc1,
    0xc7, 0xfc, 0x1f, 0x80,

    /* U+0054 "T" */
    0xff, 0xff, 0xff, 0xf0, 0x30, 0x0, 0xc0, 0x3,
    0x0, 0xc, 0x0, 0x30, 0x0, 0xc0, 0x3, 0x0,
    0xc, 0x0, 0x30, 0x0, 0xc0, 0x3, 0x0, 0xc,
    0x0, 0x30, 0x0, 0xc0, 0x3, 0x0,

    /* U+0055 "U" */
    0xc0, 0xf, 0x0, 0x3c, 0x0, 0xf0, 0x3, 0xc0,
    0xf, 0x0, 0x3c, 0x0, 0xf0, 0x3, 0xc0, 0xf,
    0x0, 0x3c, 0x0, 0xf0, 0x3, 0xc0, 0xd, 0x80,
    0x67, 0x3, 0x8f, 0xfc, 0xf, 0xc0,

    /* U+0056 "V" */
    0xe0, 0xe, 0xc0, 0x1d, 0xc0, 0x33, 0x80, 0xe3,
    0x1, 0x87, 0x3, 0x6, 0xe, 0xc, 0x18, 0x1c,
    0x30, 0x18, 0xe0, 0x31, 0x80, 0x73, 0x0, 0x6e,
    0x0, 0xd8, 0x1, 0xf0, 0x1, 0xe0, 0x3, 0x80,

    /* U+0057 "W" */
    0xe0, 0x70, 0x19, 0x81, 0xe0, 0x67, 0x7, 0x83,
    0x9c, 0x1e, 0xe, 0x70, 0xf8, 0x30, 0xc3, 0x30,
    0xc3, 0x8c, 0xc7, 0xe, 0x33, 0x1c, 0x38, 0xcc,
    0x60, 0x66, 0x31, 0x81, 0x98, 0x6e, 0x7, 0x61,
    0xb8, 0x1d, 0x86, 0xc0, 0x3c, 0x1b, 0x0, 0xf0,
    0x3c, 0x3, 0xc0, 0xf0, 0xf, 0x3, 0x80,

    /* U+0058 "X" */
    0x70, 0xe, 0x38, 0xe, 0x38, 0x1c, 0x1c, 0x38,
    0xe, 0x70, 0x7, 0x70, 0x7, 0xe0, 0x3, 0xc0,
    0x3, 0xc0, 0x3, 0xc0, 0x7, 0xe0, 0xe, 0x70,
    0xc, 0x38, 0x1c, 0x38, 0x38, 0x1c, 0x70, 0xe,
    0x70, 0x7,

    /* U+0059 "Y" */
    0xe0, 0x1d, 0x80, 0x67, 0x3, 0x8c, 0xc, 0x38,
    0x70, 0x61, 0x80, 0xcc, 0x3, 0xf0, 0x7, 0x80,
    0x1e, 0x0, 0x30, 0x0, 0xc0, 0x3, 0x0, 0xc,
    0x0, 0x30, 0x0, 0xc0, 0x3, 0x0,

    /* U+005A "Z" */
    0xff, 0xfb, 0xff, 0xe0, 0x3, 0x80, 0x1c, 0x0,
    0xe0, 0x7, 0x0, 0x18, 0x0, 0xe0, 0x7, 0x0,
    0x38, 0x1, 0xc0, 0x6, 0x0, 0x38, 0x1, 0xc0,
    0xe, 0x0, 0x3f, 0xff, 0xff, 0xfc,

    /* U+005B "[" */
    0xff, 0xfc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xc,
    0x30, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0x3f, 0xfc,

    /* U+005C "\\" */
    0x60, 0x30, 0x1c, 0x6, 0x3, 0x0, 0xc0, 0x60,
    0x38, 0xc, 0x6, 0x1, 0x80, 0xc0, 0x70, 0x18,
    0xc, 0x3, 0x1, 0x80,

    /* U+005D "]" */
    0xff, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x8c, 0x63, 0x18, 0xc7, 0xff, 0x80,

    /* U+005E "^" */
    0x6, 0x0, 0xf0, 0xf, 0x81, 0xd8, 0x19, 0xc3,
    0x8c, 0x30, 0xe7, 0x6, 0x60, 0x70,

    /* U+005F "_" */
    0xff, 0xff, 0xf0,

    /* U+0060 "`" */
    0xc, 0x63,

    /* U+0061 "a" */
    0x1f, 0x87, 0xf9, 0xc3, 0xb0, 0x30, 0x6, 0x7,
    0xcf, 0xfb, 0x83, 0xc0, 0x78, 0x1f, 0x87, 0xbf,
    0xf3, 0xe6,

    /* U+0062 "b" */
    0xc0, 0xc, 0x0, 0xc0, 0xc, 0x0, 0xcf, 0x8d,
    0xfc, 0xf0, 0xee, 0x6, 0xc0, 0x3c, 0x3, 0xc0,
    0x3c, 0x3, 0xc0, 0x3e, 0x6, 0xf0, 0xed, 0xfc,
    0xcf, 0x80,

    /* U+0063 "c" */
    0xf, 0x7, 0xf9, 0xc3, 0x30, 0xc, 0x1, 0x80,
    0x30, 0x6, 0x0, 0xc0, 0xc, 0x1, 0xc3, 0x9f,
    0xe1, 0xf0,

    /* U+0064 "d" */
    0x0, 0x30, 0x3, 0x0, 0x30, 0x3, 0x1f, 0x33,
    0xfb, 0x70, 0xf6, 0x7, 0xc0, 0x3c, 0x3, 0xc0,
    0x3c, 0x3, 0xc0, 0x36, 0x7, 0x70, 0xf3, 0xfb,
    0x1f, 0x30,

    /* U+0065 "e" */
    0xf, 0x83, 0xfc, 0x70, 0xe6, 0x7, 0xc0, 0x3f,
    0xff, 0xff, 0xfc, 0x0, 0xc0, 0x6, 0x0, 0x70,
    0xe3, 0xfe, 0xf, 0x80,

    /* U+0066 "f" */
    0x1e, 0x7c, 0xc1, 0x83, 0x1f, 0xff, 0x98, 0x30,
    0x60, 0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60,

    /* U+0067 "g" */
    0x1f, 0x33, 0xfb, 0x70, 0xf6, 0x7, 0xc0, 0x3c,
    0x3, 0xc0, 0x3c, 0x3, 0xc0, 0x36, 0x7, 0x70,
    0xf3, 0xfb, 0x1f, 0x30, 0x3, 0x0, 0x37, 0x6,
    0x3f, 0xe1, 0xf8,

    /* U+0068 "h" */
    0xc0, 0x18, 0x3, 0x0, 0x60, 0xc, 0xf9, 0xbf,
    0xbc, 0x3f, 0x3, 0xc0, 0x78, 0xf, 0x1, 0xe0,
    0x3c, 0x7, 0x80, 0xf0, 0x1e, 0x3, 0xc0, 0x60,

    /* U+0069 "i" */
    0x39, 0xce, 0x0, 0x7f, 0xe3, 0x18, 0xc6, 0x31,
    0x8c, 0x63, 0x18, 0xc0,

    /* U+006A "j" */
    0xe, 0x1c, 0x38, 0x0, 0x0, 0xc1, 0x83, 0x6,
    0xc, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x6, 0xc,
    0x18, 0x7f, 0xdf, 0x0,

    /* U+006B "k" */
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc1, 0xb0, 0xcc,
    0x73, 0x38, 0xdc, 0x3e, 0xf, 0xc3, 0xb8, 0xc6,
    0x31, 0xcc, 0x3b, 0x6, 0xc1, 0xc0,

    /* U+006C "l" */
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf,
    0x70,

    /* U+006D "m" */
    0xcf, 0xf, 0x37, 0xef, 0xef, 0x1e, 0x1f, 0x83,
    0x83, 0xc0, 0xc0, 0xf0, 0x30, 0x3c, 0xc, 0xf,
    0x3, 0x3, 0xc0, 0xc0, 0xf0, 0x30, 0x3c, 0xc,
    0xf, 0x3, 0x3, 0xc0, 0xc0, 0xc0,

    /* U+006E "n" */
    0xcf, 0x9b, 0xfb, 0xc3, 0xf0, 0x3c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x78, 0xf, 0x1, 0xe0,
    0x3c, 0x6,

    /* U+006F "o" */
    0xf, 0x3, 0xfc, 0x70, 0xe6, 0x6, 0xc0, 0x3c,
    0x3, 0xc0, 0x3c, 0x3, 0xc0, 0x36, 0x6, 0x70,
    0xe3, 0xfc, 0xf, 0x0,

    /* U+0070 "p" */
    0xcf, 0x8d, 0xfc, 0xf0, 0xee, 0x6, 0xc0, 0x3c,
    0x3, 0xc0, 0x3c, 0x3, 0xc0, 0x3e, 0x6, 0xf0,
    0xed, 0xfc, 0xcf, 0x8c, 0x0, 0xc0, 0xc, 0x0,
    0xc0, 0x0,

    /* U+0071 "q" */
    0x1f, 0x30, 0x3f, 0xb0, 0x70, 0xf0, 0x60, 0x70,
    0xc0, 0x30, 0xc0, 0x30, 0xc0, 0x30, 0xc0, 0x30,
    0xc0, 0x30, 0x60, 0x70, 0x70, 0xf0, 0x3f, 0xb0,
    0x1f, 0x30, 0x0, 0x30, 0x0, 0x38, 0x0, 0x3f,
    0x0, 0x1f,

    /* U+0072 "r" */
    0xcf, 0xbf, 0xc7, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0x83, 0x6, 0xc, 0x0,

    /* U+0073 "s" */
    0x3e, 0x1f, 0xee, 0x1b, 0x0, 0xc0, 0x1e, 0x3,
    0xf0, 0x7, 0x0, 0xf0, 0x3e, 0x1d, 0xfe, 0x1f,
    0x0,

    /* U+0074 "t" */
    0x30, 0x60, 0xc7, 0xff, 0xe6, 0xc, 0x18, 0x30,
    0x60, 0xc1, 0x83, 0x6, 0xf, 0x8f,

    /* U+0075 "u" */
    0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xf0, 0x7e, 0x3d, 0xfb, 0x3c,
    0xc0,

    /* U+0076 "v" */
    0xe0, 0x6c, 0xd, 0x83, 0xb8, 0x63, 0xc, 0x63,
    0x8e, 0x60, 0xcc, 0x1b, 0x3, 0xe0, 0x3c, 0x7,
    0x0, 0xe0,

    /* U+0077 "w" */
    0xc1, 0xc1, 0xf0, 0xe1, 0xd8, 0x70, 0xcc, 0x6c,
    0x67, 0x36, 0x71, 0x9b, 0x30, 0xc8, 0x98, 0x6c,
    0x6c, 0x3e, 0x3e, 0xf, 0x1e, 0x7, 0x7, 0x3,
    0x83, 0x80, 0xc1, 0x80,

    /* U+0078 "x" */
    0x60, 0x67, 0xe, 0x39, 0xc1, 0x98, 0x1f, 0x80,
    0xf0, 0x6, 0x0, 0xf0, 0x1f, 0x83, 0x9c, 0x30,
    0xc7, 0xe, 0xe0, 0x70,

    /* U+0079 "y" */
    0xe0, 0x6c, 0x1d, 0x83, 0x38, 0x63, 0x1c, 0x63,
    0xe, 0x60, 0xdc, 0x1b, 0x3, 0xe0, 0x3c, 0x7,
    0x0, 0x60, 0x1c, 0x3, 0x3, 0xe0, 0x78, 0x0,

    /* U+007A "z" */
    0xff, 0xff, 0xf0, 0x1c, 0xe, 0x7, 0x1, 0x80,
    0xc0, 0x60, 0x38, 0x1c, 0xe, 0x3, 0xff, 0xff,
    0xc0,

    /* U+007B "{" */
    0x1e, 0x7c, 0xc1, 0x83, 0x6, 0xc, 0x18, 0x31,
    0xc3, 0x81, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60,
    0xc1, 0xf1, 0xe0,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,

    /* U+007D "}" */
    0xf1, 0xf0, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18,
    0x1c, 0x38, 0xc1, 0x83, 0x6, 0xc, 0x18, 0x30,
    0x67, 0xcf, 0x0,

    /* U+007E "~" */
    0x3e, 0x3f, 0xff, 0xc3, 0xe0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 116, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 117, .box_w = 3, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 8, .adv_w = 125, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 12},
    {.bitmap_index = 12, .adv_w = 272, .box_w = 15, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 247, .box_w = 13, .box_h = 22, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 80, .adv_w = 386, .box_w = 22, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 293, .box_w = 17, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 67, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 12},
    {.bitmap_index = 166, .adv_w = 125, .box_w = 6, .box_h = 21, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 182, .adv_w = 125, .box_w = 6, .box_h = 21, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 198, .adv_w = 180, .box_w = 8, .box_h = 7, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 205, .adv_w = 250, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 85, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 230, .adv_w = 153, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 232, .adv_w = 85, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 157, .box_w = 9, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 270, .box_w = 14, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 167, .box_w = 7, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 228, .box_w = 13, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 239, .box_w = 13, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 255, .box_w = 14, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 243, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 249, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 212, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 256, .box_w = 13, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 249, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 517, .adv_w = 85, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 522, .adv_w = 85, .box_w = 3, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 528, .adv_w = 230, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 550, .adv_w = 250, .box_w = 13, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 562, .adv_w = 230, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 584, .adv_w = 216, .box_w = 11, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 608, .adv_w = 324, .box_w = 18, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 647, .adv_w = 260, .box_w = 16, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 681, .adv_w = 258, .box_w = 13, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 709, .adv_w = 273, .box_w = 14, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 739, .adv_w = 280, .box_w = 14, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 769, .adv_w = 236, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 795, .adv_w = 228, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 821, .adv_w = 295, .box_w = 15, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 853, .adv_w = 287, .box_w = 14, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 883, .adv_w = 172, .box_w = 7, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 898, .adv_w = 212, .box_w = 11, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 922, .adv_w = 261, .box_w = 14, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 952, .adv_w = 224, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 978, .adv_w = 341, .box_w = 17, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1015, .adv_w = 287, .box_w = 14, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1045, .adv_w = 302, .box_w = 16, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1079, .adv_w = 250, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1105, .adv_w = 313, .box_w = 18, .box_h = 18, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1146, .adv_w = 257, .box_w = 14, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1176, .adv_w = 248, .box_w = 13, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1204, .adv_w = 232, .box_w = 14, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1234, .adv_w = 287, .box_w = 14, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1264, .adv_w = 245, .box_w = 15, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1296, .adv_w = 349, .box_w = 22, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1343, .adv_w = 259, .box_w = 16, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1377, .adv_w = 248, .box_w = 14, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1407, .adv_w = 253, .box_w = 14, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1437, .adv_w = 131, .box_w = 6, .box_h = 21, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 1453, .adv_w = 157, .box_w = 9, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1473, .adv_w = 131, .box_w = 5, .box_h = 21, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1487, .adv_w = 230, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1501, .adv_w = 165, .box_w = 10, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1504, .adv_w = 111, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 15},
    {.bitmap_index = 1506, .adv_w = 219, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1524, .adv_w = 235, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1550, .adv_w = 208, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1568, .adv_w = 235, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1594, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1614, .adv_w = 129, .box_w = 7, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1630, .adv_w = 233, .box_w = 12, .box_h = 18, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1657, .adv_w = 227, .box_w = 11, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1681, .adv_w = 116, .box_w = 5, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1693, .adv_w = 106, .box_w = 7, .box_h = 22, .ofs_x = -2, .ofs_y = -4},
    {.bitmap_index = 1713, .adv_w = 204, .box_w = 10, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1735, .adv_w = 99, .box_w = 4, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1744, .adv_w = 350, .box_w = 18, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1774, .adv_w = 227, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1792, .adv_w = 230, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1812, .adv_w = 235, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 1838, .adv_w = 240, .box_w = 16, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1872, .adv_w = 141, .box_w = 7, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1884, .adv_w = 196, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1901, .adv_w = 135, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1915, .adv_w = 223, .box_w = 10, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1932, .adv_w = 183, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1950, .adv_w = 272, .box_w = 17, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1978, .adv_w = 192, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1998, .adv_w = 178, .box_w = 11, .box_h = 17, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 2022, .adv_w = 191, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2039, .adv_w = 133, .box_w = 7, .box_h = 21, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2058, .adv_w = 97, .box_w = 2, .box_h = 21, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 2064, .adv_w = 133, .box_w = 7, .box_h = 21, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 2083, .adv_w = 231, .box_w = 12, .box_h = 3, .ofs_x = 1, .ofs_y = 5}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    9, 24,
    13, 72,
    14, 18,
    14, 19,
    14, 21,
    14, 24,
    15, 72,
    16, 16,
    17, 19,
    18, 10,
    19, 21,
    21, 22,
    21, 26,
    22, 26,
    23, 18,
    23, 19,
    24, 6,
    24, 14,
    24, 18,
    24, 21,
    24, 24,
    24, 25,
    25, 6,
    25, 18,
    25, 24,
    25, 26,
    26, 21,
    26, 24,
    26, 25,
    34, 34,
    34, 36,
    34, 40,
    34, 48,
    34, 50,
    34, 53,
    34, 54,
    34, 55,
    34, 56,
    34, 58,
    34, 77,
    34, 85,
    34, 86,
    34, 87,
    34, 88,
    34, 89,
    34, 90,
    35, 34,
    35, 55,
    35, 57,
    35, 58,
    35, 66,
    36, 36,
    36, 40,
    36, 48,
    36, 50,
    36, 58,
    37, 34,
    37, 42,
    37, 53,
    37, 55,
    37, 56,
    37, 57,
    37, 58,
    37, 59,
    37, 66,
    37, 91,
    38, 36,
    38, 40,
    38, 48,
    38, 50,
    38, 55,
    38, 56,
    39, 34,
    39, 43,
    39, 53,
    39, 66,
    40, 53,
    40, 55,
    40, 58,
    42, 36,
    42, 40,
    42, 48,
    42, 50,
    42, 71,
    42, 85,
    43, 34,
    44, 36,
    44, 40,
    44, 48,
    44, 50,
    44, 86,
    44, 87,
    44, 88,
    44, 90,
    45, 34,
    45, 36,
    45, 40,
    45, 43,
    45, 48,
    45, 50,
    45, 53,
    45, 54,
    45, 55,
    45, 56,
    45, 57,
    45, 58,
    45, 74,
    45, 87,
    45, 88,
    45, 89,
    45, 90,
    48, 34,
    48, 42,
    48, 53,
    48, 55,
    48, 56,
    48, 57,
    48, 58,
    48, 59,
    48, 66,
    48, 91,
    49, 34,
    49, 43,
    49, 57,
    49, 58,
    49, 59,
    49, 66,
    49, 84,
    50, 34,
    50, 57,
    50, 58,
    50, 91,
    51, 34,
    51, 36,
    51, 40,
    51, 48,
    51, 50,
    51, 58,
    51, 72,
    51, 86,
    52, 56,
    53, 34,
    53, 36,
    53, 40,
    53, 43,
    53, 48,
    53, 50,
    53, 53,
    53, 55,
    53, 56,
    53, 58,
    53, 66,
    53, 68,
    53, 69,
    53, 70,
    53, 71,
    53, 72,
    53, 78,
    53, 79,
    53, 80,
    53, 81,
    53, 82,
    53, 83,
    53, 84,
    53, 86,
    54, 34,
    55, 34,
    55, 36,
    55, 40,
    55, 43,
    55, 48,
    55, 50,
    55, 53,
    55, 55,
    55, 56,
    55, 58,
    55, 66,
    55, 68,
    55, 69,
    55, 70,
    55, 72,
    55, 78,
    55, 79,
    55, 80,
    55, 82,
    55, 84,
    56, 34,
    56, 36,
    56, 40,
    56, 43,
    56, 48,
    56, 50,
    56, 53,
    56, 55,
    56, 66,
    56, 68,
    56, 69,
    56, 70,
    56, 72,
    56, 80,
    56, 82,
    57, 36,
    57, 40,
    57, 48,
    57, 50,
    57, 66,
    57, 72,
    57, 86,
    57, 87,
    57, 90,
    58, 34,
    58, 36,
    58, 40,
    58, 43,
    58, 48,
    58, 50,
    58, 53,
    58, 55,
    58, 66,
    58, 68,
    58, 69,
    58, 70,
    58, 72,
    58, 80,
    58, 82,
    58, 84,
    58, 86,
    58, 89,
    58, 91,
    59, 36,
    59, 40,
    59, 48,
    59, 50,
    59, 72,
    59, 85,
    68, 53,
    68, 56,
    68, 58,
    70, 53,
    70, 55,
    70, 56,
    70, 57,
    70, 58,
    71, 53,
    71, 56,
    71, 66,
    71, 68,
    71, 69,
    71, 70,
    71, 80,
    71, 82,
    72, 58,
    73, 53,
    73, 56,
    73, 58,
    73, 68,
    73, 69,
    73, 70,
    73, 72,
    73, 80,
    73, 82,
    73, 85,
    75, 75,
    76, 34,
    76, 36,
    76, 40,
    76, 48,
    76, 50,
    76, 68,
    76, 69,
    76, 70,
    76, 80,
    76, 82,
    76, 85,
    77, 13,
    77, 15,
    77, 57,
    77, 74,
    77, 81,
    77, 87,
    77, 90,
    78, 53,
    78, 56,
    78, 58,
    78, 68,
    78, 69,
    78, 70,
    78, 72,
    78, 80,
    78, 82,
    78, 85,
    79, 53,
    79, 56,
    79, 58,
    79, 68,
    79, 69,
    79, 70,
    79, 72,
    79, 80,
    79, 82,
    79, 85,
    82, 53,
    82, 58,
    83, 56,
    83, 66,
    83, 71,
    83, 85,
    83, 87,
    83, 88,
    83, 89,
    83, 90,
    84, 43,
    84, 53,
    84, 55,
    84, 58,
    85, 34,
    85, 58,
    86, 53,
    86, 58,
    87, 34,
    87, 57,
    87, 59,
    87, 66,
    87, 71,
    87, 84,
    88, 87,
    88, 90,
    89, 34,
    89, 58,
    90, 34,
    90, 57,
    90, 59,
    90, 66,
    90, 71,
    90, 84,
    91, 58
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    13, -9, -20, -13, 13, -23, -9, -40,
    -8, 7, -3, -8, -9, -7, -10, -8,
    13, -23, 12, -20, 15, -20, -13, -12,
    -8, -10, -10, -8, -10, 8, -15, -15,
    -15, -15, -27, -12, -28, -20, -27, -9,
    -11, -10, -17, -18, 8, -17, -8, -8,
    -8, -12, -6, -8, -8, -8, -8, -10,
    -16, -12, -16, -12, -8, -8, -20, -8,
    -12, -8, -8, -8, -8, -8, 7, 7,
    -16, -13, 10, -9, -8, -12, -20, -12,
    -12, -12, -12, -9, -12, -12, -20, -20,
    -20, -20, -18, -21, -21, -21, 12, -15,
    -15, 12, -15, -15, -43, -9, -27, -16,
    12, -35, -8, -16, -20, 12, -16, -16,
    -12, -16, -12, -8, -8, -20, -8, -12,
    -8, -34, -28, -12, -8, -8, -12, -8,
    12, 8, -16, 8, 7, -9, -9, -9,
    -9, -7, -8, -8, -8, -27, -16, -16,
    -43, -16, -16, 9, 16, 12, 8, -24,
    -36, -36, -36, 8, -28, -27, -27, -36,
    -24, -36, -24, -16, -24, -12, -28, -12,
    -12, -16, -12, -12, 16, 8, 8, 8,
    -16, -20, -20, -20, -20, -8, -8, -20,
    -20, -8, -20, -8, -8, -12, -8, -8,
    12, 8, -12, -10, -10, -10, -12, -10,
    -10, -12, -12, -12, -12, -8, -8, -12,
    -8, -8, -27, -20, -20, -24, -20, -20,
    8, 8, -32, -36, -36, -36, -35, -36,
    -36, -24, -16, -8, -8, -12, -12, -12,
    -12, -12, -12, -20, -12, -32, -27, -16,
    -12, -8, -32, 12, 8, -13, -9, -9,
    -9, -9, -9, -20, -24, -12, -27, -5,
    -5, -5, -6, -5, -5, -5, 10, 12,
    -8, -8, -8, -8, -6, -6, -6, -6,
    -6, -5, 14, 14, 8, -8, 9, 5,
    5, -24, -12, -27, -5, -5, -5, -6,
    -5, -5, -5, -24, -12, -27, -5, -5,
    -5, -6, -5, -5, -5, -20, -12, 12,
    -6, 8, 7, 11, 10, 9, 11, 9,
    -16, -8, -23, 10, -12, -29, -16, -23,
    -8, -8, -8, 9, 9, 7, 7, 8,
    -8, -23, -8, -8, -8, 9, 9, -8
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 336,
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
const lv_font_t hyperlegible_26 = {
#else
lv_font_t hyperlegible_26 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 25,          /*The maximum line height required by the font*/
    .base_line = 5,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if HYPERLEGIBLE_26*/

