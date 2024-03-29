/*******************************************************************************
 * Size: 30 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef HYPERLEGIBLE_30
#define HYPERLEGIBLE_30 1
#endif

#if HYPERLEGIBLE_30

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x0,
    0x6f, 0xf6,

    /* U+0022 "\"" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x30,

    /* U+0023 "#" */
    0x3, 0xc, 0x0, 0xc3, 0x0, 0x30, 0xc0, 0x1c,
    0x30, 0x7, 0x1c, 0x1f, 0xff, 0xe7, 0xff, 0xf8,
    0x18, 0x60, 0x6, 0x18, 0x1, 0x86, 0x0, 0xe1,
    0x80, 0x38, 0x60, 0xe, 0x38, 0x3f, 0xff, 0xcf,
    0xff, 0xf0, 0x30, 0xc0, 0xc, 0x30, 0x7, 0xc,
    0x1, 0xc7, 0x0, 0x71, 0xc0,

    /* U+0024 "$" */
    0x3, 0x0, 0x6, 0x0, 0x1c, 0x0, 0xff, 0x87,
    0xff, 0x8e, 0x67, 0xb8, 0xc6, 0x71, 0x80, 0xe3,
    0x1, 0xc6, 0x1, 0xec, 0x3, 0xfc, 0x3, 0xff,
    0x0, 0xff, 0x0, 0xdf, 0x1, 0x8f, 0x3, 0xe,
    0x6, 0x1f, 0x8c, 0x3f, 0x18, 0xf7, 0xb3, 0xc7,
    0xff, 0x3, 0xf8, 0x1, 0x80, 0x3, 0x0, 0x6,
    0x0,

    /* U+0025 "%" */
    0x1f, 0x0, 0x38, 0x1f, 0xc0, 0x38, 0x1c, 0x70,
    0x18, 0x18, 0xc, 0x1c, 0xc, 0x6, 0x1c, 0x6,
    0x3, 0xc, 0x3, 0x1, 0x8e, 0x0, 0xe3, 0x8e,
    0x0, 0x3f, 0x86, 0x0, 0xf, 0x86, 0x1e, 0x0,
    0x7, 0x1f, 0x80, 0x7, 0x18, 0xe0, 0x3, 0x1c,
    0x38, 0x3, 0x8c, 0xc, 0x3, 0x86, 0x6, 0x1,
    0x83, 0x3, 0x1, 0xc1, 0xc3, 0x81, 0xc0, 0x61,
    0x81, 0xc0, 0x1f, 0x80, 0xe0, 0x7, 0x80,

    /* U+0026 "&" */
    0x3, 0xe0, 0x0, 0xff, 0x80, 0x1e, 0x3c, 0x1,
    0xc1, 0xc0, 0x1c, 0x1c, 0x1, 0xc1, 0xc0, 0x1e,
    0x3c, 0x0, 0xff, 0x80, 0x7, 0xf0, 0x0, 0xfc,
    0x0, 0x3f, 0xc1, 0x87, 0x8e, 0x18, 0x70, 0x73,
    0x8e, 0x3, 0xf8, 0xe0, 0x1f, 0xe, 0x0, 0xf0,
    0xf0, 0x1f, 0x87, 0x83, 0xfc, 0x3f, 0xf9, 0xe0,
    0xfc, 0xf,

    /* U+0027 "'" */
    0xff, 0xf0,

    /* U+0028 "(" */
    0x18, 0xc3, 0x1c, 0x61, 0x86, 0x30, 0xc3, 0xc,
    0x30, 0xc3, 0xc, 0x30, 0xc1, 0x86, 0x18, 0x30,
    0xc3, 0x86, 0xc,

    /* U+0029 ")" */
    0x60, 0xc3, 0xe, 0x18, 0x61, 0x83, 0xc, 0x30,
    0xc3, 0xc, 0x30, 0xc3, 0x1c, 0x61, 0x86, 0x30,
    0xc7, 0x18, 0xc0,

    /* U+002A "*" */
    0xc, 0x3, 0x4, 0xc9, 0xfe, 0x1e, 0x7, 0x83,
    0x30, 0xcc,

    /* U+002B "+" */
    0x3, 0x80, 0x7, 0x0, 0xe, 0x0, 0x1c, 0x0,
    0x38, 0x0, 0x70, 0x0, 0xe0, 0x7f, 0xff, 0xff,
    0xfe, 0x7, 0x0, 0xe, 0x0, 0x1c, 0x0, 0x38,
    0x0, 0x70, 0x0, 0xe0, 0x0,

    /* U+002C "," */
    0x6f, 0xf6, 0x66, 0xc0,

    /* U+002D "-" */
    0xff, 0xff, 0xc0,

    /* U+002E "." */
    0x6f, 0xf6,

    /* U+002F "/" */
    0x0, 0xe0, 0x18, 0x7, 0x0, 0xe0, 0x38, 0x7,
    0x0, 0xc0, 0x38, 0x7, 0x0, 0xc0, 0x38, 0x6,
    0x1, 0xc0, 0x38, 0x6, 0x1, 0xc0, 0x30, 0xe,
    0x1, 0xc0, 0x30, 0x0,

    /* U+0030 "0" */
    0x7, 0xe0, 0x1f, 0xf8, 0x3c, 0x3c, 0x78, 0x1e,
    0x7c, 0xe, 0x7c, 0xe, 0xee, 0x7, 0xe7, 0x7,
    0xe3, 0x87, 0xe3, 0x87, 0xe1, 0xc7, 0xe0, 0xe7,
    0xe0, 0xe7, 0xe0, 0x77, 0x70, 0x3e, 0x70, 0x3e,
    0x78, 0x1e, 0x3c, 0x3c, 0x1f, 0xf8, 0x7, 0xe0,

    /* U+0031 "1" */
    0x1, 0x81, 0xc3, 0xff, 0xff, 0xf8, 0x1c, 0xe,
    0x7, 0x3, 0x81, 0xc0, 0xe0, 0x70, 0x38, 0x1c,
    0xe, 0x7, 0x3, 0x81, 0xc0, 0xe0, 0x70,

    /* U+0032 "2" */
    0x7, 0xe0, 0x7f, 0xc3, 0x87, 0x9c, 0xf, 0x60,
    0x1c, 0x0, 0x70, 0x1, 0xc0, 0x7, 0x0, 0x38,
    0x1, 0xe0, 0x7, 0x0, 0x38, 0x1, 0xc0, 0xe,
    0x0, 0xf0, 0x7, 0x80, 0x38, 0x1, 0xc0, 0xf,
    0xff, 0xff, 0xff,

    /* U+0033 "3" */
    0xf, 0xe0, 0xff, 0xe7, 0x87, 0x9c, 0x7, 0x60,
    0x1c, 0x0, 0x70, 0x1, 0xc0, 0x1e, 0x7, 0xe0,
    0x1f, 0xc0, 0x7, 0x80, 0xf, 0x0, 0x1c, 0x0,
    0x72, 0x1, 0xf8, 0x7, 0x70, 0x3d, 0xe1, 0xe3,
    0xff, 0x3, 0xf0,

    /* U+0034 "4" */
    0x0, 0x38, 0x0, 0x78, 0x0, 0xf8, 0x1, 0xf8,
    0x1, 0xb8, 0x3, 0x38, 0x7, 0x38, 0xe, 0x38,
    0x1c, 0x38, 0x18, 0x38, 0x38, 0x38, 0x70, 0x38,
    0xe0, 0x38, 0xff, 0xff, 0xff, 0xff, 0x0, 0x38,
    0x0, 0x38, 0x0, 0x38, 0x0, 0x38, 0x0, 0x38,

    /* U+0035 "5" */
    0x7f, 0xf9, 0xff, 0xe6, 0x0, 0x18, 0x0, 0x60,
    0x1, 0x80, 0x6, 0xfc, 0x3f, 0xfc, 0xf0, 0x7b,
    0x80, 0xe0, 0x1, 0xc0, 0x7, 0x0, 0x1c, 0x0,
    0x70, 0x1, 0xf0, 0xf, 0xe0, 0x39, 0xc1, 0xc3,
    0xff, 0x3, 0xf0,

    /* U+0036 "6" */
    0x7, 0xc0, 0x7f, 0xc3, 0x87, 0x8c, 0xc, 0x70,
    0x1, 0x80, 0xe, 0x0, 0x39, 0xf0, 0xef, 0xf3,
    0xe1, 0xef, 0x3, 0xb8, 0x7, 0xe0, 0x1f, 0x80,
    0x7e, 0x1, 0xd8, 0x7, 0x70, 0x38, 0xe1, 0xe1,
    0xff, 0x3, 0xf0,

    /* U+0037 "7" */
    0xff, 0xff, 0xff, 0xf0, 0x1, 0xc0, 0xe, 0x0,
    0x38, 0x1, 0xc0, 0x7, 0x0, 0x38, 0x0, 0xe0,
    0x7, 0x0, 0x1c, 0x0, 0x70, 0x3, 0x80, 0xe,
    0x0, 0x70, 0x1, 0xc0, 0xe, 0x0, 0x38, 0x1,
    0xc0, 0x7, 0x0,

    /* U+0038 "8" */
    0x7, 0xc0, 0x1f, 0xc0, 0x71, 0xc1, 0x80, 0xc3,
    0x1, 0x86, 0x3, 0xc, 0x6, 0xe, 0x38, 0x1f,
    0xf0, 0x7f, 0xf1, 0xe0, 0xf3, 0x80, 0xee, 0x0,
    0xfc, 0x1, 0xf8, 0x3, 0xf0, 0x7, 0x70, 0x1c,
    0xf0, 0x78, 0xff, 0xe0, 0x7f, 0x0,

    /* U+0039 "9" */
    0x7, 0xc0, 0x3f, 0xe0, 0xf1, 0xe3, 0x80, 0xef,
    0x1, 0xfc, 0x1, 0xf8, 0x3, 0xf0, 0x7, 0xe0,
    0xf, 0xe0, 0x3d, 0xc0, 0x71, 0xe3, 0xc1, 0xff,
    0x80, 0xfe, 0x0, 0x1c, 0x0, 0x70, 0x1, 0xc0,
    0x3, 0x80, 0xe, 0x0, 0x38, 0x0,

    /* U+003A ":" */
    0x6f, 0xf6, 0x0, 0x0, 0x0, 0x6, 0xff, 0x60,

    /* U+003B ";" */
    0x6f, 0xf6, 0x0, 0x0, 0x0, 0x0, 0x6f, 0xf6,
    0x66, 0xc0,

    /* U+003C "<" */
    0x0, 0x4, 0x0, 0x70, 0x7, 0xc0, 0x7e, 0x7,
    0xc0, 0xfc, 0xf, 0xc0, 0x38, 0x0, 0xf8, 0x0,
    0xf8, 0x0, 0xfc, 0x0, 0xfc, 0x0, 0xfc, 0x0,
    0x70, 0x0, 0x40,

    /* U+003D "=" */
    0xff, 0xff, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x3f, 0xff, 0xff, 0xff,

    /* U+003E ">" */
    0x80, 0x3, 0x80, 0xf, 0x80, 0x1f, 0x80, 0xf,
    0x80, 0xf, 0xc0, 0xf, 0xc0, 0x7, 0x0, 0x7c,
    0x7, 0xc0, 0xfc, 0xf, 0xc0, 0xfc, 0x3, 0x80,
    0x8, 0x0, 0x0,

    /* U+003F "?" */
    0xf, 0xc1, 0xff, 0x9c, 0x1c, 0xc0, 0x76, 0x3,
    0x80, 0x1c, 0x0, 0xe0, 0xe, 0x1, 0xe0, 0x1e,
    0x1, 0xe0, 0x1c, 0x0, 0xe0, 0x7, 0x0, 0x0,
    0x0, 0x0, 0x6, 0x0, 0x78, 0x3, 0xc0, 0xc,
    0x0,

    /* U+0040 "@" */
    0x1, 0xf8, 0x0, 0x7f, 0xf0, 0x1e, 0x7, 0x83,
    0x80, 0x1c, 0x30, 0x0, 0xe6, 0xf, 0xe6, 0x61,
    0xfe, 0x7c, 0x38, 0xe3, 0xc7, 0xe, 0x3c, 0x70,
    0xe3, 0xc7, 0xe, 0x3c, 0x70, 0xe3, 0xc7, 0x9e,
    0x66, 0x3f, 0xfe, 0x71, 0xe3, 0xc3, 0x0, 0x0,
    0x1c, 0x0, 0x0, 0xf0, 0x20, 0x7, 0xfe, 0x0,
    0x1f, 0xc0,

    /* U+0041 "A" */
    0x0, 0xe0, 0x0, 0x7c, 0x0, 0x1f, 0x0, 0xe,
    0xc0, 0x3, 0xb8, 0x0, 0xce, 0x0, 0x71, 0x80,
    0x1c, 0x70, 0x6, 0x1c, 0x3, 0x83, 0x80, 0xe0,
    0xe0, 0x70, 0x18, 0x1c, 0x7, 0x7, 0xff, 0xc3,
    0xff, 0xf0, 0xe0, 0xe, 0x30, 0x3, 0x9c, 0x0,
    0x77, 0x0, 0x1f, 0x80, 0x7,

    /* U+0042 "B" */
    0xff, 0xe1, 0xff, 0xe3, 0x80, 0xe7, 0x1, 0xee,
    0x1, 0xdc, 0x3, 0xb8, 0x7, 0x70, 0xe, 0xe0,
    0x39, 0xff, 0xe3, 0xff, 0xe7, 0x0, 0xee, 0x1,
    0xfc, 0x1, 0xf8, 0x3, 0xf0, 0x7, 0xe0, 0x1f,
    0xc0, 0x7b, 0xff, 0xe7, 0xff, 0x0,

    /* U+0043 "C" */
    0x3, 0xf8, 0x7, 0xff, 0x7, 0x83, 0xc7, 0x0,
    0xf7, 0x0, 0x33, 0x80, 0x3, 0x80, 0x1, 0xc0,
    0x0, 0xe0, 0x0, 0x70, 0x0, 0x38, 0x0, 0x1c,
    0x0, 0xe, 0x0, 0x7, 0x80, 0x1, 0xc0, 0x0,
    0xe0, 0x6, 0x38, 0x3, 0x8f, 0x7, 0x83, 0xff,
    0x80, 0x7f, 0x0,

    /* U+0044 "D" */
    0xff, 0xc0, 0xff, 0xf0, 0xe0, 0x78, 0xe0, 0x1c,
    0xe0, 0xe, 0xe0, 0xe, 0xe0, 0x7, 0xe0, 0x7,
    0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7,
    0xe0, 0x7, 0xe0, 0x7, 0xe0, 0xe, 0xe0, 0xe,
    0xe0, 0x1c, 0xe0, 0x78, 0xff, 0xf0, 0xff, 0xc0,

    /* U+0045 "E" */
    0xff, 0xff, 0xff, 0xfe, 0x0, 0x38, 0x0, 0xe0,
    0x3, 0x80, 0xe, 0x0, 0x38, 0x0, 0xe0, 0x3,
    0xff, 0x8f, 0xfe, 0x38, 0x0, 0xe0, 0x3, 0x80,
    0xe, 0x0, 0x38, 0x0, 0xe0, 0x3, 0x80, 0xf,
    0xff, 0xff, 0xff,

    /* U+0046 "F" */
    0xff, 0xff, 0xff, 0xf8, 0x1, 0xc0, 0xe, 0x0,
    0x70, 0x3, 0x80, 0x1c, 0x0, 0xe0, 0x7, 0xff,
    0xff, 0xff, 0xc0, 0xe, 0x0, 0x70, 0x3, 0x80,
    0x1c, 0x0, 0xe0, 0x7, 0x0, 0x38, 0x1, 0xc0,
    0x0,

    /* U+0047 "G" */
    0x3, 0xf8, 0x3, 0xff, 0x81, 0xe0, 0xf0, 0xe0,
    0x1e, 0x70, 0x3, 0x1c, 0x0, 0xe, 0x0, 0x3,
    0x80, 0x0, 0xe0, 0x0, 0x38, 0x0, 0xe, 0x7,
    0xff, 0x81, 0xff, 0xe0, 0x1, 0xf8, 0x0, 0x77,
    0x0, 0x1d, 0xc0, 0xf, 0x38, 0x3, 0xc7, 0x83,
    0xf0, 0xff, 0xcc, 0xf, 0xc3,

    /* U+0048 "H" */
    0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7,
    0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7,
    0xe0, 0x7, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x7,
    0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7,
    0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7,

    /* U+0049 "I" */
    0xff, 0xff, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c,
    0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c,
    0x1c, 0x1c, 0xff, 0xff,

    /* U+004A "J" */
    0x0, 0x38, 0x1, 0xc0, 0xe, 0x0, 0x70, 0x3,
    0x80, 0x1c, 0x0, 0xe0, 0x7, 0x0, 0x38, 0x1,
    0xc0, 0xe, 0x0, 0x70, 0x3, 0x80, 0x1f, 0x80,
    0xfc, 0x7, 0xf0, 0x73, 0xc7, 0x8f, 0xf8, 0x3f,
    0x0,

    /* U+004B "K" */
    0xe0, 0xe, 0xe0, 0x1c, 0xe0, 0x38, 0xe0, 0x70,
    0xe0, 0xe0, 0xe1, 0xe0, 0xe3, 0xc0, 0xe7, 0x80,
    0xef, 0x0, 0xff, 0x80, 0xff, 0x80, 0xf9, 0xc0,
    0xf1, 0xe0, 0xe0, 0xf0, 0xe0, 0x70, 0xe0, 0x38,
    0xe0, 0x3c, 0xe0, 0x1e, 0xe0, 0xe, 0xe0, 0x7,

    /* U+004C "L" */
    0xe0, 0x3, 0x80, 0xe, 0x0, 0x38, 0x0, 0xe0,
    0x3, 0x80, 0xe, 0x0, 0x38, 0x0, 0xe0, 0x3,
    0x80, 0xe, 0x0, 0x38, 0x0, 0xe0, 0x3, 0x80,
    0xe, 0x0, 0x38, 0x0, 0xe0, 0x3, 0x80, 0xf,
    0xff, 0xff, 0xff,

    /* U+004D "M" */
    0xf8, 0x1, 0xff, 0x80, 0x1f, 0xfc, 0x3, 0xff,
    0xc0, 0x3f, 0xec, 0x3, 0x7e, 0xe0, 0x77, 0xee,
    0x7, 0x7e, 0x60, 0x77, 0xe7, 0xe, 0x7e, 0x70,
    0xe7, 0xe3, 0xe, 0x7e, 0x30, 0xc7, 0xe3, 0x9c,
    0x7e, 0x39, 0xc7, 0xe1, 0x98, 0x7e, 0x1f, 0x87,
    0xe1, 0xf8, 0x7e, 0xf, 0x7, 0xe0, 0xf0, 0x7e,
    0xf, 0x7,

    /* U+004E "N" */
    0xf8, 0x7, 0xf8, 0x7, 0xfc, 0x7, 0xfc, 0x7,
    0xee, 0x7, 0xee, 0x7, 0xe7, 0x7, 0xe7, 0x7,
    0xe3, 0x87, 0xe3, 0x87, 0xe1, 0xc7, 0xe1, 0xc7,
    0xe0, 0xe7, 0xe0, 0xe7, 0xe0, 0x77, 0xe0, 0x77,
    0xe0, 0x3f, 0xe0, 0x3f, 0xe0, 0x1f, 0xe0, 0x1f,

    /* U+004F "O" */
    0x3, 0xf8, 0x1, 0xff, 0xc0, 0x78, 0x3c, 0x1c,
    0x1, 0xc7, 0x80, 0x3c, 0xe0, 0x3, 0xbc, 0x0,
    0x7f, 0x0, 0x7, 0xe0, 0x0, 0xfc, 0x0, 0x1f,
    0x80, 0x3, 0xf0, 0x0, 0x7e, 0x0, 0xf, 0xe0,
    0x3, 0xdc, 0x0, 0x73, 0xc0, 0x1e, 0x38, 0x3,
    0x83, 0xc1, 0xe0, 0x3f, 0xf8, 0x1, 0xfc, 0x0,

    /* U+0050 "P" */
    0xff, 0xe1, 0xff, 0xf3, 0x80, 0xf7, 0x0, 0xfe,
    0x0, 0xfc, 0x1, 0xf8, 0x3, 0xf0, 0x7, 0xe0,
    0x1f, 0xc0, 0x7b, 0xff, 0xe7, 0xff, 0xe, 0x0,
    0x1c, 0x0, 0x38, 0x0, 0x70, 0x0, 0xe0, 0x1,
    0xc0, 0x3, 0x80, 0x7, 0x0, 0x0,

    /* U+0051 "Q" */
    0x3, 0xf8, 0x0, 0x7f, 0xf0, 0x7, 0x83, 0xc0,
    0x70, 0x7, 0x7, 0x80, 0x3c, 0x38, 0x0, 0xe3,
    0xc0, 0x7, 0x1c, 0x0, 0x1c, 0xe0, 0x0, 0xe7,
    0x1, 0x7, 0x38, 0x1c, 0x39, 0xc0, 0xf1, 0xce,
    0x3, 0xce, 0x78, 0xf, 0xf1, 0xc0, 0x3f, 0xf,
    0x0, 0xf8, 0x38, 0x3, 0xc0, 0xf0, 0x7f, 0x3,
    0xff, 0xbe, 0x7, 0xf0, 0xf0, 0x0, 0x1, 0x0,

    /* U+0052 "R" */
    0xff, 0xe0, 0xff, 0xf8, 0xe0, 0x3c, 0xe0, 0xe,
    0xe0, 0xe, 0xe0, 0xe, 0xe0, 0xe, 0xe0, 0xe,
    0xe0, 0x3c, 0xff, 0xf8, 0xff, 0xe0, 0xe3, 0xc0,
    0xe1, 0xc0, 0xe0, 0xe0, 0xe0, 0xf0, 0xe0, 0x78,
    0xe0, 0x38, 0xe0, 0x3c, 0xe0, 0x1e, 0xe0, 0xe,

    /* U+0053 "S" */
    0xf, 0xc0, 0x7f, 0xe1, 0xe1, 0xe7, 0x80, 0xee,
    0x0, 0x1c, 0x0, 0x3c, 0x0, 0x7c, 0x0, 0x7f,
    0x80, 0x7f, 0xe0, 0x1f, 0xe0, 0x3, 0xe0, 0x1,
    0xe0, 0x1, 0xc0, 0x3, 0xf0, 0x7, 0xe0, 0x1c,
    0xf0, 0x78, 0xff, 0xe0, 0x7e, 0x0,

    /* U+0054 "T" */
    0xff, 0xff, 0xff, 0xff, 0x1, 0xc0, 0x1, 0xc0,
    0x1, 0xc0, 0x1, 0xc0, 0x1, 0xc0, 0x1, 0xc0,
    0x1, 0xc0, 0x1, 0xc0, 0x1, 0xc0, 0x1, 0xc0,
    0x1, 0xc0, 0x1, 0xc0, 0x1, 0xc0, 0x1, 0xc0,
    0x1, 0xc0, 0x1, 0xc0, 0x1, 0xc0, 0x1, 0xc0,

    /* U+0055 "U" */
    0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7,
    0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7,
    0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7,
    0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7, 0x70, 0xe,
    0x70, 0xe, 0x38, 0x1c, 0x3f, 0xf8, 0xf, 0xf0,

    /* U+0056 "V" */
    0xf0, 0x3, 0xb8, 0x1, 0xdc, 0x1, 0xef, 0x0,
    0xe3, 0x80, 0x71, 0xc0, 0x70, 0x70, 0x38, 0x38,
    0x1c, 0x1c, 0x1c, 0x6, 0xe, 0x3, 0x87, 0x1,
    0xc7, 0x0, 0x63, 0x80, 0x39, 0xc0, 0x1c, 0xc0,
    0x6, 0xe0, 0x3, 0xf0, 0x1, 0xf0, 0x0, 0x78,
    0x0, 0x3c, 0x0,

    /* U+0057 "W" */
    0xf0, 0x1c, 0x3, 0xb8, 0xf, 0x3, 0xdc, 0xf,
    0x81, 0xce, 0x7, 0xc0, 0xe7, 0x3, 0x60, 0x71,
    0xc1, 0xb0, 0x78, 0xe1, 0xdc, 0x38, 0x70, 0xe6,
    0x1c, 0x38, 0x63, 0xe, 0xe, 0x31, 0x87, 0x7,
    0x18, 0xe7, 0x3, 0x9c, 0x73, 0x81, 0xce, 0x19,
    0xc0, 0x76, 0xc, 0xe0, 0x3b, 0x6, 0xe0, 0x1d,
    0x83, 0xf0, 0xf, 0xc0, 0xf8, 0x3, 0xc0, 0x7c,
    0x1, 0xe0, 0x3c, 0x0, 0xf0, 0x1e, 0x0,

    /* U+0058 "X" */
    0x70, 0x3, 0xce, 0x1, 0xe3, 0xc0, 0x70, 0x78,
    0x38, 0xe, 0x1e, 0x1, 0xc7, 0x0, 0x7b, 0x80,
    0xf, 0xe0, 0x1, 0xf0, 0x0, 0x38, 0x0, 0x1f,
    0x0, 0xf, 0xc0, 0x3, 0xb8, 0x1, 0xcf, 0x0,
    0xf1, 0xc0, 0x78, 0x38, 0x1c, 0xf, 0xe, 0x1,
    0xe7, 0x80, 0x39, 0xc0, 0x7,

    /* U+0059 "Y" */
    0xe0, 0x3, 0xb8, 0x3, 0x9c, 0x1, 0xc7, 0x1,
    0xc3, 0x81, 0xe0, 0xe0, 0xe0, 0x38, 0xe0, 0x1c,
    0x70, 0x7, 0x70, 0x3, 0xb8, 0x0, 0xf8, 0x0,
    0x38, 0x0, 0x1c, 0x0, 0xe, 0x0, 0x7, 0x0,
    0x3, 0x80, 0x1, 0xc0, 0x0, 0xe0, 0x0, 0x70,
    0x0, 0x38, 0x0,

    /* U+005A "Z" */
    0xff, 0xfe, 0xff, 0xfe, 0x0, 0x1e, 0x0, 0x1c,
    0x0, 0x38, 0x0, 0x70, 0x0, 0xf0, 0x0, 0xe0,
    0x1, 0xc0, 0x3, 0x80, 0x7, 0x80, 0x7, 0x0,
    0xe, 0x0, 0x1c, 0x0, 0x1c, 0x0, 0x38, 0x0,
    0x70, 0x0, 0xe0, 0x0, 0xff, 0xff, 0xff, 0xff,

    /* U+005B "[" */
    0xff, 0xfe, 0x38, 0xe3, 0x8e, 0x38, 0xe3, 0x8e,
    0x38, 0xe3, 0x8e, 0x38, 0xe3, 0x8e, 0x38, 0xe3,
    0x8e, 0x3f, 0xfc,

    /* U+005C "\\" */
    0x60, 0xe, 0x1, 0xc0, 0x18, 0x3, 0x80, 0x30,
    0x7, 0x0, 0xe0, 0xc, 0x1, 0xc0, 0x18, 0x3,
    0x80, 0x70, 0x6, 0x0, 0xe0, 0xc, 0x1, 0x80,
    0x38, 0x3, 0x0, 0x70,

    /* U+005D "]" */
    0xff, 0xfc, 0x38, 0x70, 0xe1, 0xc3, 0x87, 0xe,
    0x1c, 0x38, 0x70, 0xe1, 0xc3, 0x87, 0xe, 0x1c,
    0x38, 0x70, 0xe1, 0xc3, 0xff, 0xfe,

    /* U+005E "^" */
    0x6, 0x0, 0x38, 0x3, 0xc0, 0x1f, 0x1, 0xdc,
    0x1c, 0xe0, 0xe3, 0x8e, 0x1c, 0x70, 0x77, 0x3,
    0xb8, 0xe,

    /* U+005F "_" */
    0xff, 0xff, 0xfc,

    /* U+0060 "`" */
    0xc7, 0x1c, 0x60,

    /* U+0061 "a" */
    0xf, 0xc0, 0xff, 0xc3, 0x87, 0x1c, 0xe, 0x0,
    0x38, 0x0, 0xe0, 0x7f, 0x8f, 0xfe, 0x78, 0x3b,
    0x80, 0xee, 0x3, 0xb8, 0x1e, 0xf0, 0xf9, 0xfe,
    0xe3, 0xf1, 0x80,

    /* U+0062 "b" */
    0xe0, 0x3, 0x80, 0xe, 0x0, 0x38, 0x0, 0xe0,
    0x3, 0x9f, 0xe, 0xff, 0x3e, 0x1e, 0xf0, 0x3b,
    0xc0, 0xfe, 0x1, 0xf8, 0x7, 0xe0, 0x1f, 0x80,
    0x7e, 0x1, 0xfc, 0xf, 0xf0, 0x3b, 0xe1, 0xee,
    0xff, 0x31, 0xf0,

    /* U+0063 "c" */
    0xf, 0xc0, 0xff, 0x8e, 0x1e, 0xe0, 0x6f, 0x0,
    0x70, 0x3, 0x80, 0x1c, 0x0, 0xe0, 0x7, 0x0,
    0x3c, 0x0, 0xe0, 0x23, 0x87, 0x8f, 0xf8, 0x3f,
    0x0,

    /* U+0064 "d" */
    0x0, 0x1c, 0x0, 0x70, 0x1, 0xc0, 0x7, 0x0,
    0x1c, 0x3e, 0x73, 0xfd, 0xde, 0x1f, 0x70, 0x3f,
    0xc0, 0xfe, 0x1, 0xf8, 0x7, 0xe0, 0x1f, 0x80,
    0x7e, 0x1, 0xfc, 0xf, 0x70, 0x3d, 0xe1, 0xf3,
    0xfd, 0xc3, 0xe3,

    /* U+0065 "e" */
    0xf, 0xc0, 0x7f, 0xc3, 0x87, 0x9c, 0x6, 0xe0,
    0x1f, 0x80, 0x7f, 0xff, 0xff, 0xff, 0xe0, 0x3,
    0x80, 0xe, 0x0, 0x1c, 0x0, 0x38, 0x38, 0x7f,
    0xc0, 0xfc, 0x0,

    /* U+0066 "f" */
    0x1f, 0x3f, 0x38, 0x38, 0x38, 0x38, 0xff, 0xff,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38,

    /* U+0067 "g" */
    0xf, 0x8c, 0xff, 0x77, 0x87, 0xdc, 0xf, 0xf0,
    0x1f, 0x80, 0x7e, 0x1, 0xf8, 0x7, 0xe0, 0x1f,
    0x80, 0x7f, 0x3, 0xdc, 0xf, 0x78, 0x7c, 0xff,
    0x70, 0xf9, 0xc0, 0x7, 0x0, 0x1c, 0xc0, 0xe3,
    0x87, 0x87, 0xfc, 0xf, 0xe0,

    /* U+0068 "h" */
    0xe0, 0xe, 0x0, 0xe0, 0xe, 0x0, 0xe0, 0xe,
    0x7c, 0xef, 0xef, 0x8e, 0xf0, 0x7e, 0x7, 0xe0,
    0x7e, 0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7e, 0x7,
    0xe0, 0x7e, 0x7, 0xe0, 0x7e, 0x7,

    /* U+0069 "i" */
    0x18, 0xf1, 0x80, 0x0, 0xf, 0xbe, 0x38, 0xe3,
    0x8e, 0x38, 0xe3, 0x8e, 0x38, 0xe3, 0x8e, 0x38,

    /* U+006A "j" */
    0x6, 0xf, 0x6, 0x0, 0x0, 0x0, 0xe, 0xe,
    0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe,
    0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0xe, 0x1e,
    0xfc, 0xf8,

    /* U+006B "k" */
    0xe0, 0x7, 0x0, 0x38, 0x1, 0xc0, 0xe, 0x0,
    0x70, 0x3b, 0x83, 0x9c, 0x38, 0xe3, 0x87, 0x38,
    0x3b, 0x81, 0xfc, 0xf, 0xe0, 0x7b, 0x83, 0x8e,
    0x1c, 0x78, 0xe1, 0xc7, 0x7, 0x38, 0x1d, 0xc0,
    0xe0,

    /* U+006C "l" */
    0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce,
    0x73, 0x9c, 0xe7, 0x3e, 0xf0,

    /* U+006D "m" */
    0xc7, 0xc3, 0xe7, 0x7f, 0x7f, 0xbe, 0x3f, 0x1d,
    0xe0, 0xf0, 0x7e, 0x7, 0x3, 0xf0, 0x38, 0x1f,
    0x81, 0xc0, 0xfc, 0xe, 0x7, 0xe0, 0x70, 0x3f,
    0x3, 0x81, 0xf8, 0x1c, 0xf, 0xc0, 0xe0, 0x7e,
    0x7, 0x3, 0xf0, 0x38, 0x1f, 0x81, 0xc0, 0xe0,

    /* U+006E "n" */
    0xc7, 0xce, 0xfe, 0xf8, 0xef, 0x7, 0xe0, 0x7e,
    0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7e, 0x7, 0xe0,
    0x7e, 0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x70,

    /* U+006F "o" */
    0xf, 0xc0, 0x7f, 0x83, 0x87, 0x1c, 0xe, 0xf0,
    0x3f, 0x80, 0x7e, 0x1, 0xf8, 0x7, 0xe0, 0x1f,
    0x80, 0x7f, 0x3, 0xdc, 0xe, 0x38, 0x70, 0x7f,
    0x80, 0xfc, 0x0,

    /* U+0070 "p" */
    0xc7, 0xc3, 0xbf, 0xcf, 0x87, 0xbc, 0xe, 0xf0,
    0x3f, 0x80, 0x7e, 0x1, 0xf8, 0x7, 0xe0, 0x1f,
    0x80, 0x7f, 0x3, 0xfc, 0xe, 0xf8, 0x7b, 0xbf,
    0xce, 0x7c, 0x38, 0x0, 0xe0, 0x3, 0x80, 0xe,
    0x0, 0x38, 0x0,

    /* U+0071 "q" */
    0xf, 0x8c, 0xf, 0xf7, 0x7, 0x87, 0xc1, 0xc0,
    0xf0, 0xf0, 0x3c, 0x38, 0x7, 0xe, 0x1, 0xc3,
    0x80, 0x70, 0xe0, 0x1c, 0x38, 0x7, 0xf, 0x3,
    0xc1, 0xc0, 0xf0, 0x78, 0x7c, 0xf, 0xf7, 0x0,
    0xf9, 0xc0, 0x0, 0x70, 0x0, 0x1c, 0x0, 0x7,
    0x80, 0x0, 0xfc, 0x0, 0x1f,

    /* U+0072 "r" */
    0xc7, 0xef, 0xf8, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0,
    0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,

    /* U+0073 "s" */
    0x1f, 0x7, 0xfc, 0xf1, 0xee, 0x8, 0xe0, 0xf,
    0x0, 0x7f, 0x3, 0xfe, 0x3, 0xe0, 0x7, 0x0,
    0x7e, 0x7, 0xf0, 0xf7, 0xfe, 0x1f, 0x80,

    /* U+0074 "t" */
    0x38, 0x38, 0x38, 0x38, 0xff, 0xff, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
    0x38, 0x3f, 0x1f,

    /* U+0075 "u" */
    0xe0, 0x7e, 0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7e,
    0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7e, 0x7, 0xe0,
    0x7e, 0xf, 0x71, 0xf7, 0xf7, 0x3e, 0x30,

    /* U+0076 "v" */
    0xe0, 0x3b, 0x1, 0xdc, 0xc, 0xe0, 0xe3, 0x7,
    0x1c, 0x30, 0xe3, 0x83, 0x1c, 0x1c, 0xc0, 0xee,
    0x3, 0x70, 0x1f, 0x0, 0xf8, 0x3, 0x80, 0x1c,
    0x0,

    /* U+0077 "w" */
    0xe0, 0xe0, 0x6e, 0xf, 0x6, 0x60, 0xf0, 0xe7,
    0xf, 0xe, 0x71, 0xb0, 0xc3, 0x1b, 0x9c, 0x31,
    0x99, 0xc3, 0xb9, 0x9c, 0x3b, 0x19, 0x81, 0xb0,
    0xf8, 0x1b, 0xf, 0x81, 0xf0, 0xf0, 0xe, 0xf,
    0x0, 0xe0, 0x70, 0xe, 0x7, 0x0,

    /* U+0078 "x" */
    0x70, 0x39, 0xc0, 0xe3, 0x87, 0x7, 0x38, 0x1d,
    0xc0, 0x3f, 0x0, 0x78, 0x1, 0xe0, 0x7, 0x80,
    0x3f, 0x1, 0xce, 0xe, 0x38, 0x38, 0x71, 0xc0,
    0xee, 0x3, 0x80,

    /* U+0079 "y" */
    0xe0, 0x3f, 0x1, 0x98, 0x1c, 0xe0, 0xe7, 0x6,
    0x18, 0x70, 0xe3, 0x83, 0x18, 0x19, 0xc0, 0xee,
    0x3, 0x60, 0x1f, 0x0, 0xf8, 0x3, 0x80, 0x1c,
    0x0, 0xe0, 0x6, 0x0, 0x70, 0x1f, 0x0, 0xf0,
    0x0,

    /* U+007A "z" */
    0xff, 0xef, 0xfe, 0x0, 0xe0, 0x1c, 0x3, 0x80,
    0x30, 0x7, 0x0, 0xe0, 0x1c, 0x1, 0x80, 0x30,
    0x7, 0x0, 0xe0, 0xf, 0xff, 0xff, 0xf0,

    /* U+007B "{" */
    0x1f, 0x3f, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x70, 0xe0, 0xe0, 0x78, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x3f,
    0x1f,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xe0,

    /* U+007D "}" */
    0xf8, 0xfc, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c,
    0x1c, 0x1c, 0x1c, 0xc, 0x7, 0x7, 0x1c, 0x1c,
    0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xfc,
    0xf8,

    /* U+007E "~" */
    0x3e, 0x9, 0xfe, 0x3e, 0x3f, 0xd0, 0x3c
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 134, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 135, .box_w = 4, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 11, .adv_w = 144, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 14},
    {.bitmap_index = 16, .adv_w = 314, .box_w = 18, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 285, .box_w = 15, .box_h = 26, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 110, .adv_w = 445, .box_w = 25, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 338, .box_w = 20, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 77, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 14},
    {.bitmap_index = 225, .adv_w = 144, .box_w = 6, .box_h = 25, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 244, .adv_w = 144, .box_w = 6, .box_h = 25, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 263, .adv_w = 208, .box_w = 10, .box_h = 8, .ofs_x = 2, .ofs_y = 12},
    {.bitmap_index = 273, .adv_w = 289, .box_w = 15, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 98, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 306, .adv_w = 177, .box_w = 9, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 309, .adv_w = 98, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 181, .box_w = 11, .box_h = 20, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 311, .box_w = 16, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 379, .adv_w = 193, .box_w = 9, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 264, .box_w = 14, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 276, .box_w = 14, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 295, .box_w = 16, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 512, .adv_w = 280, .box_w = 14, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 547, .adv_w = 287, .box_w = 14, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 245, .box_w = 14, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 617, .adv_w = 295, .box_w = 15, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 655, .adv_w = 287, .box_w = 15, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 693, .adv_w = 98, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 701, .adv_w = 98, .box_w = 4, .box_h = 19, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 711, .adv_w = 265, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 738, .adv_w = 289, .box_w = 15, .box_h = 8, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 753, .adv_w = 265, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 780, .adv_w = 250, .box_w = 13, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 813, .adv_w = 374, .box_w = 20, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 863, .adv_w = 300, .box_w = 18, .box_h = 20, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 908, .adv_w = 297, .box_w = 15, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 946, .adv_w = 315, .box_w = 17, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 989, .adv_w = 323, .box_w = 16, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1029, .adv_w = 272, .box_w = 14, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1064, .adv_w = 263, .box_w = 13, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1097, .adv_w = 341, .box_w = 18, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1142, .adv_w = 331, .box_w = 16, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1182, .adv_w = 199, .box_w = 8, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1202, .adv_w = 245, .box_w = 13, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1235, .adv_w = 301, .box_w = 16, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1275, .adv_w = 259, .box_w = 14, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1310, .adv_w = 394, .box_w = 20, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1360, .adv_w = 331, .box_w = 16, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1400, .adv_w = 349, .box_w = 19, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1448, .adv_w = 288, .box_w = 15, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1486, .adv_w = 361, .box_w = 21, .box_h = 21, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1542, .adv_w = 297, .box_w = 16, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1582, .adv_w = 286, .box_w = 15, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1620, .adv_w = 268, .box_w = 16, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1660, .adv_w = 331, .box_w = 16, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1700, .adv_w = 283, .box_w = 17, .box_h = 20, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1743, .adv_w = 403, .box_w = 25, .box_h = 20, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1806, .adv_w = 299, .box_w = 18, .box_h = 20, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1851, .adv_w = 286, .box_w = 17, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1894, .adv_w = 291, .box_w = 16, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1934, .adv_w = 151, .box_w = 6, .box_h = 25, .ofs_x = 2, .ofs_y = -5},
    {.bitmap_index = 1953, .adv_w = 181, .box_w = 11, .box_h = 20, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1981, .adv_w = 151, .box_w = 7, .box_h = 25, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 2003, .adv_w = 265, .box_w = 13, .box_h = 11, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 2021, .adv_w = 190, .box_w = 11, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2024, .adv_w = 129, .box_w = 5, .box_h = 4, .ofs_x = 2, .ofs_y = 17},
    {.bitmap_index = 2027, .adv_w = 252, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2054, .adv_w = 272, .box_w = 14, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2089, .adv_w = 240, .box_w = 13, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2114, .adv_w = 271, .box_w = 14, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2149, .adv_w = 259, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2176, .adv_w = 149, .box_w = 8, .box_h = 21, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2197, .adv_w = 269, .box_w = 14, .box_h = 21, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 2234, .adv_w = 262, .box_w = 12, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2264, .adv_w = 133, .box_w = 6, .box_h = 21, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2280, .adv_w = 122, .box_w = 8, .box_h = 26, .ofs_x = -2, .ofs_y = -5},
    {.bitmap_index = 2306, .adv_w = 235, .box_w = 13, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2339, .adv_w = 115, .box_w = 5, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2352, .adv_w = 404, .box_w = 21, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2392, .adv_w = 262, .box_w = 12, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2415, .adv_w = 265, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2442, .adv_w = 272, .box_w = 14, .box_h = 20, .ofs_x = 2, .ofs_y = -5},
    {.bitmap_index = 2477, .adv_w = 276, .box_w = 18, .box_h = 20, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2522, .adv_w = 163, .box_w = 8, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2537, .adv_w = 226, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2560, .adv_w = 156, .box_w = 8, .box_h = 19, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2579, .adv_w = 257, .box_w = 12, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2602, .adv_w = 212, .box_w = 13, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2627, .adv_w = 314, .box_w = 20, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2665, .adv_w = 221, .box_w = 14, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2692, .adv_w = 206, .box_w = 13, .box_h = 20, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 2725, .adv_w = 221, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2748, .adv_w = 153, .box_w = 8, .box_h = 25, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2773, .adv_w = 112, .box_w = 3, .box_h = 25, .ofs_x = 2, .ofs_y = -5},
    {.bitmap_index = 2783, .adv_w = 153, .box_w = 8, .box_h = 25, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2808, .adv_w = 266, .box_w = 14, .box_h = 4, .ofs_x = 1, .ofs_y = 6}
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
    15, -10, -23, -15, 15, -26, -10, -46,
    -9, 8, -4, -9, -11, -8, -11, -9,
    15, -26, 13, -23, 17, -23, -15, -13,
    -9, -11, -11, -9, -11, 9, -18, -18,
    -18, -18, -32, -13, -32, -23, -32, -10,
    -13, -12, -19, -21, 10, -19, -9, -9,
    -9, -13, -7, -9, -9, -9, -9, -11,
    -18, -13, -18, -13, -9, -9, -23, -9,
    -13, -9, -9, -9, -9, -9, 8, 9,
    -18, -15, 11, -11, -9, -13, -23, -13,
    -13, -13, -13, -10, -13, -13, -23, -23,
    -23, -23, -21, -24, -24, -24, 13, -18,
    -18, 13, -18, -18, -50, -10, -32, -18,
    13, -41, -9, -18, -23, 13, -18, -18,
    -13, -18, -13, -9, -9, -23, -9, -13,
    -9, -39, -32, -14, -9, -9, -13, -9,
    13, 9, -18, 9, 9, -10, -10, -10,
    -10, -8, -9, -9, -9, -32, -18, -18,
    -50, -18, -18, 11, 18, 13, 9, -27,
    -41, -41, -41, 9, -32, -32, -32, -41,
    -27, -41, -27, -18, -27, -13, -32, -13,
    -13, -18, -13, -13, 18, 9, 9, 9,
    -18, -23, -23, -23, -23, -9, -9, -23,
    -23, -9, -23, -9, -9, -13, -9, -9,
    13, 9, -13, -11, -11, -11, -13, -11,
    -11, -13, -13, -13, -13, -9, -9, -13,
    -9, -9, -32, -23, -23, -27, -23, -23,
    9, 9, -36, -41, -41, -41, -41, -41,
    -41, -27, -18, -9, -9, -13, -13, -13,
    -13, -13, -13, -23, -13, -36, -32, -18,
    -13, -9, -36, 13, 9, -15, -10, -10,
    -10, -10, -10, -23, -27, -13, -32, -5,
    -5, -5, -7, -5, -5, -6, 12, 13,
    -9, -9, -9, -9, -7, -7, -7, -7,
    -7, -6, 16, 16, 9, -9, 10, 6,
    6, -27, -13, -32, -5, -5, -5, -7,
    -5, -5, -6, -27, -13, -32, -5, -5,
    -5, -7, -5, -5, -6, -23, -13, 13,
    -7, 9, 8, 12, 12, 10, 12, 10,
    -18, -9, -27, 12, -13, -34, -19, -27,
    -9, -9, -9, 10, 10, 8, 8, 10,
    -9, -27, -9, -9, -9, 10, 10, -9
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
const lv_font_t hyperlegible_30 = {
#else
lv_font_t hyperlegible_30 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 29,          /*The maximum line height required by the font*/
    .base_line = 6,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -2,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if HYPERLEGIBLE_30*/

