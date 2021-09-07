/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef HYPERLEGIBLE_20
#define HYPERLEGIBLE_20 1
#endif

#if HYPERLEGIBLE_20

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0xc3, 0xc0,

    /* U+0022 "\"" */
    0xff, 0xff,

    /* U+0023 "#" */
    0x8, 0x83, 0x30, 0x66, 0x3f, 0xf1, 0x18, 0x22,
    0x4, 0x40, 0x88, 0xff, 0xe6, 0x60, 0xcc, 0x19,
    0x82, 0x30,

    /* U+0024 "$" */
    0x8, 0x7, 0x7, 0xf3, 0xa6, 0xc8, 0x32, 0xe,
    0x81, 0xe0, 0x3f, 0x2, 0xe0, 0x8c, 0x23, 0xc8,
    0xda, 0x63, 0xf0, 0x20, 0x8, 0x0,

    /* U+0025 "%" */
    0x3c, 0x8, 0x33, 0xc, 0x30, 0xcc, 0x18, 0x64,
    0x6, 0x66, 0x1, 0xe6, 0x0, 0x2, 0x78, 0x3,
    0x66, 0x3, 0x61, 0x81, 0x30, 0xc1, 0x98, 0x61,
    0x86, 0x60, 0x81, 0xe0,

    /* U+0026 "&" */
    0x1f, 0x1, 0x8c, 0xc, 0x60, 0x63, 0x1, 0xb0,
    0x7, 0x1, 0xf8, 0x8c, 0xec, 0xc3, 0xe6, 0xe,
    0x30, 0x38, 0xc7, 0xe3, 0xe3, 0x80,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x31, 0x18, 0xcc, 0x63, 0x18, 0xc6, 0x30, 0xc6,
    0x10, 0xc2,

    /* U+0029 ")" */
    0x61, 0xc, 0x61, 0x8c, 0x63, 0x18, 0xc6, 0x63,
    0x11, 0x88,

    /* U+002A "*" */
    0x21, 0x3e, 0xe5, 0x0,

    /* U+002B "+" */
    0xc, 0x3, 0x0, 0xc0, 0x30, 0xc, 0x3f, 0xf0,
    0xc0, 0x30, 0xc, 0x3, 0x0,

    /* U+002C "," */
    0xf6, 0x80,

    /* U+002D "-" */
    0xfc,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x6, 0xc, 0x30, 0x60, 0x83, 0x6, 0x18, 0x30,
    0x41, 0x83, 0xc, 0x0,

    /* U+0030 "0" */
    0x1f, 0x6, 0x31, 0xc3, 0x7c, 0x3d, 0x87, 0x98,
    0xf1, 0x9e, 0x33, 0xc3, 0x78, 0x3d, 0x87, 0x18,
    0xc1, 0xf0,

    /* U+0031 "1" */
    0xc, 0x7f, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30,
    0xc3, 0xc,

    /* U+0032 "2" */
    0x3e, 0x18, 0xc4, 0x18, 0x6, 0x1, 0x80, 0xe0,
    0x30, 0x18, 0xc, 0x6, 0x3, 0x1, 0x80, 0xff,
    0xc0,

    /* U+0033 "3" */
    0x1f, 0x18, 0x76, 0xc, 0x3, 0x1, 0x83, 0xc0,
    0x18, 0x3, 0x0, 0xd0, 0x36, 0xd, 0x86, 0x1f,
    0x0,

    /* U+0034 "4" */
    0x3, 0x0, 0xe0, 0x3c, 0xd, 0x81, 0x30, 0x66,
    0x18, 0xc6, 0x18, 0xff, 0xe0, 0x60, 0xc, 0x1,
    0x80, 0x30,

    /* U+0035 "5" */
    0x3f, 0x98, 0x6, 0x1, 0x80, 0x7f, 0x18, 0x60,
    0xc, 0x3, 0x0, 0xc0, 0x34, 0xd, 0x86, 0x1f,
    0x0,

    /* U+0036 "6" */
    0x1f, 0xc, 0x66, 0x1, 0x0, 0xdf, 0x38, 0x6c,
    0xf, 0x3, 0xc0, 0xf0, 0x34, 0xd, 0x86, 0x1e,
    0x0,

    /* U+0037 "7" */
    0xff, 0x80, 0xc0, 0xc0, 0x60, 0x20, 0x30, 0x18,
    0x18, 0xc, 0xc, 0x6, 0x6, 0x3, 0x0,

    /* U+0038 "8" */
    0x1e, 0xc, 0xc6, 0x19, 0x86, 0x33, 0xf, 0xc6,
    0x1b, 0x3, 0xc0, 0xf0, 0x3c, 0xd, 0x86, 0x3f,
    0x0,

    /* U+0039 "9" */
    0x1e, 0x18, 0x6e, 0x1b, 0x3, 0xc0, 0xf0, 0x3e,
    0x1d, 0x86, 0x1f, 0x0, 0xc0, 0x60, 0x30, 0xc,
    0x0,

    /* U+003A ":" */
    0xf0, 0x0, 0xf0,

    /* U+003B ";" */
    0xf0, 0x3, 0xda,

    /* U+003C "<" */
    0x0, 0x40, 0xf0, 0xf0, 0xf0, 0xe0, 0x38, 0x3,
    0x80, 0x3c, 0x3, 0xc0, 0x30,

    /* U+003D "=" */
    0xff, 0xc0, 0x0, 0x0, 0x0, 0xff, 0xc0,

    /* U+003E ">" */
    0x80, 0x38, 0x7, 0x80, 0x38, 0x3, 0xc0, 0xf0,
    0xf0, 0xf0, 0xe0, 0x20, 0x0,

    /* U+003F "?" */
    0x7c, 0xc6, 0x83, 0x3, 0x7, 0xe, 0x1c, 0x38,
    0x30, 0x30, 0x0, 0x30, 0x30,

    /* U+0040 "@" */
    0xf, 0x81, 0x83, 0x18, 0x4, 0x8f, 0xb8, 0xcc,
    0xcc, 0x66, 0x63, 0x33, 0x3b, 0x8f, 0x72, 0x0,
    0x18, 0x0, 0x30, 0x80, 0xfc, 0x0,

    /* U+0041 "A" */
    0x7, 0x0, 0x70, 0xf, 0x0, 0xd8, 0x19, 0x81,
    0x98, 0x18, 0xc3, 0xc, 0x30, 0x63, 0xfe, 0x60,
    0x66, 0x3, 0xc0, 0x30,

    /* U+0042 "B" */
    0xff, 0x30, 0x6c, 0xf, 0x3, 0xc0, 0xf0, 0x6f,
    0xf3, 0x6, 0xc0, 0xf0, 0x3c, 0xf, 0x6, 0xff,
    0x0,

    /* U+0043 "C" */
    0xf, 0x86, 0x1d, 0x81, 0xb0, 0xc, 0x1, 0x80,
    0x30, 0x6, 0x0, 0xc0, 0xc, 0x1, 0x81, 0x98,
    0x71, 0xf8,

    /* U+0044 "D" */
    0xfe, 0x18, 0x33, 0x3, 0x60, 0x2c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x78, 0x1f, 0x3, 0x60,
    0xcf, 0xe0,

    /* U+0045 "E" */
    0xff, 0xe0, 0x30, 0x18, 0xc, 0x6, 0x3, 0xf9,
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xf, 0xf8,

    /* U+0046 "F" */
    0xff, 0xe0, 0x30, 0x18, 0xc, 0x6, 0x3, 0xff,
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x0,

    /* U+0047 "G" */
    0xf, 0x83, 0xe, 0x60, 0x66, 0x0, 0xc0, 0xc,
    0x0, 0xc3, 0xfc, 0x3, 0xc0, 0x36, 0x3, 0x60,
    0x73, 0xf, 0x1f, 0x90,

    /* U+0048 "H" */
    0xc0, 0x78, 0xf, 0x1, 0xe0, 0x3c, 0x7, 0x80,
    0xff, 0xfe, 0x3, 0xc0, 0x78, 0xf, 0x1, 0xe0,
    0x3c, 0x6,

    /* U+0049 "I" */
    0xfc, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3,
    0xc, 0xfc,

    /* U+004A "J" */
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
    0x3, 0xc3, 0xc3, 0xe6, 0x3c,

    /* U+004B "K" */
    0xc0, 0xd8, 0x33, 0xc, 0x63, 0xc, 0xc1, 0xb0,
    0x3f, 0x7, 0x30, 0xc7, 0x18, 0x63, 0x6, 0x60,
    0x6c, 0xe,

    /* U+004C "L" */
    0xc0, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3, 0x1,
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xf, 0xf8,

    /* U+004D "M" */
    0xe0, 0x3f, 0x83, 0xfc, 0x1f, 0xa0, 0xfd, 0x8d,
    0xec, 0x6f, 0x63, 0x79, 0xb3, 0xcd, 0x9e, 0x6c,
    0xf1, 0x47, 0x8e, 0x3c, 0x71, 0x80,

    /* U+004E "N" */
    0xe0, 0x7e, 0xf, 0xc1, 0xec, 0x3d, 0x87, 0x98,
    0xf1, 0x1e, 0x33, 0xc3, 0x78, 0x6f, 0x7, 0xe0,
    0xfc, 0xe,

    /* U+004F "O" */
    0xf, 0x81, 0xc7, 0x18, 0xc, 0xc0, 0x6c, 0x1,
    0xe0, 0xf, 0x0, 0x78, 0x3, 0xc0, 0x1b, 0x1,
    0x98, 0xc, 0x71, 0xc0, 0xf8, 0x0,

    /* U+0050 "P" */
    0xff, 0x30, 0x6c, 0xf, 0x3, 0xc0, 0xf0, 0x6f,
    0xf3, 0x0, 0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0,
    0x0,

    /* U+0051 "Q" */
    0xf, 0x80, 0x71, 0xc1, 0x80, 0xc3, 0x1, 0x8c,
    0x1, 0x98, 0x3, 0x30, 0x46, 0x61, 0xcc, 0xc1,
    0xd8, 0xc1, 0xf1, 0x81, 0xc1, 0xc3, 0xc0, 0xfd,
    0xc0, 0x0, 0x80,

    /* U+0052 "R" */
    0xff, 0x30, 0x6c, 0xf, 0x3, 0xc0, 0xf0, 0x6f,
    0xf3, 0x38, 0xc6, 0x30, 0xcc, 0x3b, 0x6, 0xc0,
    0xc0,

    /* U+0053 "S" */
    0x3e, 0x18, 0x6c, 0x3, 0x0, 0xe0, 0x1f, 0x83,
    0xf8, 0x1f, 0x1, 0xc0, 0x3c, 0xd, 0x86, 0x3e,
    0x0,

    /* U+0054 "T" */
    0xff, 0xe1, 0x80, 0x30, 0x6, 0x0, 0xc0, 0x18,
    0x3, 0x0, 0x60, 0xc, 0x1, 0x80, 0x30, 0x6,
    0x0, 0xc0,

    /* U+0055 "U" */
    0xc0, 0x78, 0xf, 0x1, 0xe0, 0x3c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x78, 0xd, 0x83, 0x30,
    0x61, 0xf8,

    /* U+0056 "V" */
    0xc0, 0x66, 0x6, 0x60, 0x66, 0xc, 0x30, 0xc3,
    0xc, 0x31, 0x81, 0x98, 0x19, 0x80, 0xb0, 0xf,
    0x0, 0xf0, 0x6, 0x0,

    /* U+0057 "W" */
    0xc1, 0xc3, 0x30, 0xe1, 0x98, 0x70, 0xcc, 0x68,
    0x66, 0x36, 0x61, 0x9b, 0x30, 0xc9, 0x98, 0x64,
    0x4c, 0x36, 0x2c, 0xf, 0x1e, 0x7, 0xf, 0x3,
    0x83, 0x81, 0xc1, 0x80,

    /* U+0058 "X" */
    0x60, 0x73, 0x6, 0x38, 0xc1, 0x98, 0xf, 0x80,
    0xf0, 0x7, 0x0, 0xf0, 0x1d, 0x81, 0x9c, 0x30,
    0xc7, 0x6, 0x60, 0x30,

    /* U+0059 "Y" */
    0xe0, 0x76, 0x6, 0x30, 0xc3, 0xc, 0x19, 0x80,
    0xf0, 0xf, 0x0, 0x60, 0x6, 0x0, 0x60, 0x6,
    0x0, 0x60, 0x6, 0x0,

    /* U+005A "Z" */
    0xff, 0xc0, 0x70, 0x18, 0xc, 0x6, 0x1, 0x80,
    0xc0, 0x60, 0x38, 0xc, 0x6, 0x3, 0x0, 0xff,
    0xc0,

    /* U+005B "[" */
    0xfe, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8c,
    0x63, 0x1f,

    /* U+005C "\\" */
    0xc0, 0xc1, 0x81, 0x3, 0x6, 0x6, 0xc, 0x8,
    0x18, 0x30, 0x30, 0x60,

    /* U+005D "]" */
    0xf8, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x8c, 0x7f,

    /* U+005E "^" */
    0x1c, 0xe, 0xd, 0x86, 0xc6, 0x33, 0x1b, 0x6,

    /* U+005F "_" */
    0xff,

    /* U+0060 "`" */
    0x19, 0x80,

    /* U+0061 "a" */
    0x3e, 0x31, 0x80, 0x60, 0x31, 0xfb, 0xcf, 0x7,
    0x83, 0xc3, 0xbe, 0xc0,

    /* U+0062 "b" */
    0xc0, 0x60, 0x30, 0x1b, 0xce, 0x36, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x7c, 0x6d, 0xe0,

    /* U+0063 "c" */
    0x1e, 0x31, 0x98, 0x18, 0xc, 0x6, 0x3, 0x0,
    0xc0, 0x63, 0x8f, 0x0,

    /* U+0064 "d" */
    0x1, 0x80, 0xc0, 0x67, 0xb6, 0x3e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x6c, 0x73, 0xd8,

    /* U+0065 "e" */
    0x1e, 0x31, 0x90, 0x78, 0x3f, 0xfe, 0x3, 0x0,
    0xc0, 0x63, 0x9f, 0x0,

    /* U+0066 "f" */
    0x39, 0x8c, 0x6f, 0x98, 0xc6, 0x31, 0x8c, 0x63,
    0x18,

    /* U+0067 "g" */
    0x3d, 0xb1, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0x63, 0x9e, 0xc0, 0x60, 0x36, 0x31, 0xf0,

    /* U+0068 "h" */
    0xc0, 0xc0, 0xc0, 0xde, 0xe7, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+0069 "i" */
    0x6c, 0xe, 0xdb, 0x6d, 0xb6, 0xc0,

    /* U+006A "j" */
    0x18, 0xc0, 0x1, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x8c, 0x63, 0xf0,

    /* U+006B "k" */
    0xc0, 0x60, 0x30, 0x18, 0x6c, 0x66, 0x63, 0x61,
    0xf0, 0xf8, 0x66, 0x31, 0x98, 0xcc, 0x30,

    /* U+006C "l" */
    0xdb, 0x6d, 0xb6, 0xdb, 0x6e,

    /* U+006D "m" */
    0xde, 0x7b, 0x9e, 0x7c, 0x30, 0xf0, 0xc3, 0xc3,
    0xf, 0xc, 0x3c, 0x30, 0xf0, 0xc3, 0xc3, 0xf,
    0xc, 0x30,

    /* U+006E "n" */
    0xde, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3,

    /* U+006F "o" */
    0x1e, 0x18, 0xe6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xd, 0x86, 0x61, 0x87, 0x80,

    /* U+0070 "p" */
    0xde, 0x71, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xe3, 0x6f, 0x30, 0x18, 0xc, 0x0,

    /* U+0071 "q" */
    0x3d, 0x86, 0x38, 0xc1, 0x8c, 0x18, 0xc1, 0x8c,
    0x18, 0xc1, 0x8c, 0x18, 0x63, 0x83, 0xd8, 0x1,
    0x80, 0x18, 0x0, 0xf0,

    /* U+0072 "r" */
    0xdf, 0x8e, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0x0,

    /* U+0073 "s" */
    0x3c, 0xc6, 0xc0, 0xe0, 0x7e, 0x1f, 0x3, 0x43,
    0xc7, 0x3c,

    /* U+0074 "t" */
    0x31, 0x8d, 0xf3, 0x18, 0xc6, 0x31, 0x8c, 0x63,
    0x80,

    /* U+0075 "u" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xe7, 0x7b,

    /* U+0076 "v" */
    0xc1, 0xa1, 0x98, 0xcc, 0x62, 0x61, 0xb0, 0xd8,
    0x28, 0x1c, 0xc, 0x0,

    /* U+0077 "w" */
    0xc3, 0x1e, 0x38, 0xd1, 0x44, 0xca, 0x66, 0xdb,
    0x16, 0xd8, 0xa2, 0x87, 0x1c, 0x38, 0xe0, 0xc2,
    0x0,

    /* U+0078 "x" */
    0x61, 0xb1, 0x8d, 0x83, 0xc1, 0xc0, 0xe0, 0xd8,
    0x6c, 0x63, 0x60, 0xc0,

    /* U+0079 "y" */
    0xc1, 0xb0, 0x98, 0xcc, 0x63, 0x21, 0xb0, 0x58,
    0x28, 0x1c, 0x6, 0x2, 0x3, 0x7, 0x0,

    /* U+007A "z" */
    0xff, 0x3, 0x6, 0xc, 0x18, 0x18, 0x30, 0x60,
    0xc0, 0xff,

    /* U+007B "{" */
    0x1c, 0xc3, 0xc, 0x30, 0xc3, 0x30, 0x30, 0xc3,
    0xc, 0x30, 0xc3, 0x7,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff,

    /* U+007D "}" */
    0xe1, 0x8c, 0x63, 0x18, 0xc1, 0x31, 0x8c, 0x63,
    0x18, 0xdc,

    /* U+007E "~" */
    0x78, 0xc7, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 90, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 90, .box_w = 2, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 96, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 7, .adv_w = 210, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 190, .box_w = 10, .box_h = 17, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 47, .adv_w = 297, .box_w = 17, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 226, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 51, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 98, .adv_w = 96, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 108, .adv_w = 96, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 118, .adv_w = 139, .box_w = 5, .box_h = 6, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 122, .adv_w = 193, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 66, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 137, .adv_w = 118, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 138, .adv_w = 66, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 121, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 207, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 129, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 176, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 184, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 196, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 187, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 191, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 265, .adv_w = 163, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 197, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 191, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 66, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 317, .adv_w = 66, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 320, .adv_w = 177, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 333, .adv_w = 193, .box_w = 10, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 340, .adv_w = 177, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 353, .adv_w = 166, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 250, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 200, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 408, .adv_w = 198, .box_w = 10, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 210, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 215, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 461, .adv_w = 181, .box_w = 9, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 476, .adv_w = 175, .box_w = 9, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 227, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 511, .adv_w = 221, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 529, .adv_w = 132, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 539, .adv_w = 163, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 552, .adv_w = 201, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 570, .adv_w = 172, .box_w = 9, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 262, .box_w = 13, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 607, .adv_w = 220, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 625, .adv_w = 233, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 647, .adv_w = 192, .box_w = 10, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 664, .adv_w = 241, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 691, .adv_w = 198, .box_w = 10, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 708, .adv_w = 191, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 725, .adv_w = 179, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 221, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 761, .adv_w = 188, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 781, .adv_w = 269, .box_w = 17, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 809, .adv_w = 199, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 829, .adv_w = 190, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 849, .adv_w = 194, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 866, .adv_w = 101, .box_w = 5, .box_h = 16, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 876, .adv_w = 121, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 888, .adv_w = 101, .box_w = 5, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 898, .adv_w = 177, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 906, .adv_w = 127, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 907, .adv_w = 86, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 909, .adv_w = 168, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 921, .adv_w = 181, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 936, .adv_w = 160, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 948, .adv_w = 180, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 963, .adv_w = 172, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 975, .adv_w = 100, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 984, .adv_w = 179, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1000, .adv_w = 175, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1013, .adv_w = 89, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1019, .adv_w = 81, .box_w = 5, .box_h = 17, .ofs_x = -2, .ofs_y = -3},
    {.bitmap_index = 1030, .adv_w = 157, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1045, .adv_w = 76, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1050, .adv_w = 269, .box_w = 14, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1068, .adv_w = 175, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1078, .adv_w = 177, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1091, .adv_w = 181, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1106, .adv_w = 184, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1126, .adv_w = 109, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1134, .adv_w = 151, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1144, .adv_w = 104, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1153, .adv_w = 172, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1163, .adv_w = 141, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1175, .adv_w = 209, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1192, .adv_w = 148, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1204, .adv_w = 137, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1219, .adv_w = 147, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1229, .adv_w = 102, .box_w = 6, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1241, .adv_w = 75, .box_w = 2, .box_h = 16, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 1245, .adv_w = 102, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1255, .adv_w = 178, .box_w = 9, .box_h = 2, .ofs_x = 1, .ofs_y = 4}
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
    10, -7, -15, -10, 10, -18, -7, -30,
    -6, 5, -3, -6, -7, -5, -7, -6,
    10, -18, 9, -15, 12, -15, -10, -9,
    -6, -7, -7, -6, -7, 6, -12, -12,
    -12, -12, -21, -9, -21, -15, -21, -7,
    -9, -8, -13, -14, 6, -13, -6, -6,
    -6, -9, -4, -6, -6, -6, -6, -7,
    -12, -9, -12, -9, -6, -6, -15, -6,
    -9, -6, -6, -6, -6, -6, 5, 6,
    -12, -10, 7, -7, -6, -9, -15, -9,
    -9, -9, -9, -7, -9, -9, -15, -15,
    -15, -15, -14, -16, -16, -16, 9, -12,
    -12, 9, -12, -12, -33, -7, -21, -12,
    9, -27, -6, -12, -15, 9, -12, -12,
    -9, -12, -9, -6, -6, -15, -6, -9,
    -6, -26, -21, -9, -6, -6, -9, -6,
    9, 6, -12, 6, 6, -7, -7, -7,
    -7, -5, -6, -6, -6, -21, -12, -12,
    -33, -12, -12, 7, 12, 9, 6, -18,
    -28, -28, -28, 6, -21, -21, -21, -28,
    -18, -28, -18, -12, -18, -9, -21, -9,
    -9, -12, -9, -9, 12, 6, 6, 6,
    -12, -15, -15, -15, -15, -6, -6, -15,
    -15, -6, -15, -6, -6, -9, -6, -6,
    9, 6, -9, -7, -7, -7, -9, -7,
    -7, -9, -9, -9, -9, -6, -6, -9,
    -6, -6, -21, -15, -15, -18, -15, -15,
    6, 6, -24, -28, -28, -28, -27, -28,
    -28, -18, -12, -6, -6, -9, -9, -9,
    -9, -9, -9, -15, -9, -24, -21, -12,
    -9, -6, -24, 9, 6, -10, -7, -7,
    -7, -7, -7, -15, -18, -9, -21, -4,
    -4, -4, -4, -4, -4, -4, 8, 9,
    -6, -6, -6, -6, -5, -5, -5, -5,
    -5, -4, 11, 11, 6, -6, 7, 4,
    4, -18, -9, -21, -4, -4, -4, -4,
    -4, -4, -4, -18, -9, -21, -4, -4,
    -4, -4, -4, -4, -4, -15, -9, 9,
    -5, 6, 5, 8, 8, 7, 8, 7,
    -12, -6, -18, 8, -9, -22, -12, -18,
    -6, -6, -6, 7, 7, 5, 5, 6,
    -6, -18, -6, -6, -6, 7, 7, -6
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
const lv_font_t hyperlegible_20 = {
#else
lv_font_t hyperlegible_20 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if HYPERLEGIBLE_20*/

