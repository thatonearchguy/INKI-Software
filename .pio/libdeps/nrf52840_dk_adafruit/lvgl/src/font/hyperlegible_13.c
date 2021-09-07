/*******************************************************************************
 * Size: 13 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef HYPERLEGIBLE_13
#define HYPERLEGIBLE_13 1
#endif

#if HYPERLEGIBLE_13

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfd, 0x80,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x12, 0x16, 0x7f, 0x34, 0x24, 0x24, 0x7f, 0x24,
    0x24,

    /* U+0024 "$" */
    0x10, 0xc7, 0xa4, 0x91, 0xc3, 0x85, 0x17, 0x57,
    0x84,

    /* U+0025 "%" */
    0x71, 0x91, 0x22, 0x28, 0x45, 0x7, 0x5c, 0x1c,
    0x42, 0x88, 0x91, 0x31, 0xc0,

    /* U+0026 "&" */
    0x38, 0x22, 0x11, 0x5, 0x5, 0xa4, 0x72, 0x19,
    0x8c, 0x79, 0x0,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x4a, 0x49, 0x24, 0x49, 0x0,

    /* U+0029 ")" */
    0x48, 0x92, 0x49, 0x4a, 0x0,

    /* U+002A "*" */
    0x23, 0x88, 0xa0,

    /* U+002B "+" */
    0x10, 0x41, 0x3f, 0x10, 0x41, 0x0,

    /* U+002C "," */
    0xe8,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x18, 0x84, 0x42, 0x31, 0x8, 0xc0,

    /* U+0030 "0" */
    0x38, 0x8b, 0x8d, 0x19, 0x31, 0x63, 0xa2, 0x38,

    /* U+0031 "1" */
    0x3c, 0x92, 0x49, 0x20,

    /* U+0032 "2" */
    0x79, 0x10, 0x41, 0x8, 0x42, 0x10, 0xfc,

    /* U+0033 "3" */
    0x7b, 0x10, 0x4e, 0xc, 0x18, 0x53, 0x78,

    /* U+0034 "4" */
    0x8, 0x30, 0xa1, 0x44, 0x91, 0x3f, 0x84, 0x8,

    /* U+0035 "5" */
    0x7d, 0x4, 0x2e, 0xcc, 0x10, 0x73, 0x78,

    /* U+0036 "6" */
    0x39, 0x38, 0x2e, 0xce, 0x18, 0x73, 0x78,

    /* U+0037 "7" */
    0xfc, 0x10, 0x82, 0x10, 0x43, 0x8, 0x60,

    /* U+0038 "8" */
    0x39, 0x14, 0x5e, 0xce, 0x18, 0x73, 0x78,

    /* U+0039 "9" */
    0x7b, 0x38, 0x61, 0xcd, 0xe1, 0x84, 0x30,

    /* U+003A ":" */
    0xc6,

    /* U+003B ";" */
    0xc3, 0x80,

    /* U+003C "<" */
    0x4, 0x77, 0x20, 0x60, 0x70, 0x40,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0x83, 0x83, 0x81, 0x19, 0x88, 0x0,

    /* U+003F "?" */
    0x72, 0x42, 0x33, 0x10, 0x4, 0x20,

    /* U+0040 "@" */
    0x1e, 0x31, 0xb7, 0x74, 0x9a, 0x4d, 0x27, 0x7c,
    0xc0, 0x3c, 0x0,

    /* U+0041 "A" */
    0x18, 0x18, 0x3c, 0x24, 0x24, 0x66, 0x7e, 0x42,
    0xc1,

    /* U+0042 "B" */
    0xfa, 0x18, 0x61, 0xfa, 0x18, 0x61, 0xf8,

    /* U+0043 "C" */
    0x3c, 0x8e, 0x4, 0x8, 0x10, 0x20, 0x23, 0x3c,

    /* U+0044 "D" */
    0xf9, 0xa, 0xc, 0x18, 0x30, 0x60, 0xc2, 0xf8,

    /* U+0045 "E" */
    0xfe, 0x8, 0x20, 0xf2, 0x8, 0x20, 0xfc,

    /* U+0046 "F" */
    0xfc, 0x21, 0xf, 0xc2, 0x10, 0x80,

    /* U+0047 "G" */
    0x3c, 0x42, 0x80, 0x80, 0x8f, 0x81, 0x81, 0x43,
    0x3d,

    /* U+0048 "H" */
    0x83, 0x6, 0xc, 0x1f, 0xf0, 0x60, 0xc1, 0x82,

    /* U+0049 "I" */
    0xf4, 0x44, 0x44, 0x44, 0xf0,

    /* U+004A "J" */
    0x8, 0x42, 0x10, 0x86, 0x31, 0x70,

    /* U+004B "K" */
    0x8d, 0x12, 0x45, 0xf, 0x1a, 0x22, 0x46, 0x84,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0xfc,

    /* U+004D "M" */
    0xc1, 0xe0, 0xf8, 0xf4, 0x5a, 0x6c, 0xa6, 0x53,
    0x39, 0x88, 0x80,

    /* U+004E "N" */
    0xc3, 0x86, 0x8d, 0x99, 0x33, 0x62, 0xc3, 0x86,

    /* U+004F "O" */
    0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x81, 0x42,
    0x3c,

    /* U+0050 "P" */
    0xfa, 0x18, 0x61, 0xfa, 0x8, 0x20, 0x80,

    /* U+0051 "Q" */
    0x3c, 0x21, 0x20, 0x50, 0x28, 0x94, 0x6a, 0x1c,
    0x86, 0x3d, 0x80,

    /* U+0052 "R" */
    0xfa, 0x18, 0x61, 0xfa, 0x49, 0xa2, 0x84,

    /* U+0053 "S" */
    0x7a, 0x38, 0x30, 0x38, 0x30, 0x61, 0x78,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,

    /* U+0055 "U" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xe3, 0x7c,

    /* U+0056 "V" */
    0xc2, 0x42, 0x46, 0x64, 0x24, 0x2c, 0x38, 0x18,
    0x18,

    /* U+0057 "W" */
    0xc4, 0x79, 0x89, 0x29, 0x25, 0x24, 0xac, 0xd5,
    0xc, 0x61, 0x8c, 0x31, 0x80,

    /* U+0058 "X" */
    0x42, 0x66, 0x34, 0x18, 0x18, 0x1c, 0x24, 0x66,
    0xc3,

    /* U+0059 "Y" */
    0x82, 0x89, 0xb1, 0x43, 0x82, 0x4, 0x8, 0x10,

    /* U+005A "Z" */
    0xfe, 0xc, 0x30, 0x41, 0x6, 0x18, 0x60, 0xfe,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x93, 0x80,

    /* U+005C "\\" */
    0xc2, 0x10, 0xc2, 0x10, 0x42, 0x18,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x27, 0x80,

    /* U+005E "^" */
    0x23, 0x95, 0x98, 0x80,

    /* U+005F "_" */
    0xf8,

    /* U+0060 "`" */
    0xa0,

    /* U+0061 "a" */
    0x74, 0x42, 0xf8, 0xcd, 0xa0,

    /* U+0062 "b" */
    0x82, 0xb, 0xb3, 0x86, 0x18, 0x73, 0xb8,

    /* U+0063 "c" */
    0x7e, 0x61, 0x8, 0x65, 0xe0,

    /* U+0064 "d" */
    0x4, 0x17, 0x73, 0x86, 0x18, 0x73, 0x74,

    /* U+0065 "e" */
    0x7b, 0x28, 0x7f, 0x83, 0x27, 0x80,

    /* U+0066 "f" */
    0xd, 0x74, 0x92, 0x48,

    /* U+0067 "g" */
    0x77, 0x38, 0x61, 0x87, 0x37, 0x41, 0x4d, 0xe0,

    /* U+0068 "h" */
    0x84, 0x2d, 0x98, 0xc6, 0x31, 0x88,

    /* U+0069 "i" */
    0x53, 0x55, 0x50,

    /* U+006A "j" */
    0x4, 0x12, 0x49, 0x24, 0xf0,

    /* U+006B "k" */
    0x84, 0x27, 0x6a, 0x72, 0xd2, 0x88,

    /* U+006C "l" */
    0xaa, 0xaa, 0xc0,

    /* U+006D "m" */
    0xb7, 0x66, 0x62, 0x31, 0x18, 0x8c, 0x46, 0x22,

    /* U+006E "n" */
    0xb6, 0x63, 0x18, 0xc6, 0x20,

    /* U+006F "o" */
    0x7b, 0x38, 0x61, 0x87, 0x37, 0x80,

    /* U+0070 "p" */
    0xbb, 0x38, 0x61, 0x87, 0x3b, 0xa0, 0x80,

    /* U+0071 "q" */
    0x74, 0xcc, 0x84, 0x84, 0x84, 0xcc, 0x74, 0x4,
    0x7,

    /* U+0072 "r" */
    0xba, 0x49, 0x20,

    /* U+0073 "s" */
    0x74, 0x60, 0xe0, 0xc5, 0xc0,

    /* U+0074 "t" */
    0x44, 0xf4, 0x44, 0x44, 0x70,

    /* U+0075 "u" */
    0x8c, 0x63, 0x18, 0xcd, 0xa0,

    /* U+0076 "v" */
    0x8f, 0x24, 0x96, 0x70, 0xc3, 0x0,

    /* U+0077 "w" */
    0x89, 0x6c, 0x96, 0x4a, 0xe6, 0x63, 0x30, 0x88,

    /* U+0078 "x" */
    0xcd, 0x23, 0xc, 0x31, 0x2c, 0xc0,

    /* U+0079 "y" */
    0x8c, 0xe4, 0xa5, 0x30, 0x84, 0xc0,

    /* U+007A "z" */
    0xf8, 0xc4, 0x44, 0x63, 0xe0,

    /* U+007B "{" */
    0x69, 0x25, 0x12, 0x49, 0x80,

    /* U+007C "|" */
    0xff, 0xe0,

    /* U+007D "}" */
    0xc9, 0x24, 0x52, 0x4b, 0x0,

    /* U+007E "~" */
    0xe6, 0x60
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 58, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 58, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 63, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 5, .adv_w = 136, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 124, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 23, .adv_w = 193, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 147, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 33, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 48, .adv_w = 62, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 53, .adv_w = 62, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 58, .adv_w = 90, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 61, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 43, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 68, .adv_w = 77, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 69, .adv_w = 43, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 78, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 135, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 84, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 114, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 119, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 121, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 124, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 106, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 124, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 43, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 43, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 148, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 125, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 157, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 108, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 162, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 180, .adv_w = 130, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 129, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 136, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 140, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 212, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 114, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 148, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 144, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 86, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 106, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 130, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 261, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 171, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 279, .adv_w = 143, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 151, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 157, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 129, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 124, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 116, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 144, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 123, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 353, .adv_w = 175, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 130, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 126, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 391, .adv_w = 66, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 396, .adv_w = 78, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 66, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 407, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 411, .adv_w = 82, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 412, .adv_w = 56, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 413, .adv_w = 109, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 104, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 117, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 65, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 116, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 455, .adv_w = 114, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 461, .adv_w = 58, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 53, .box_w = 3, .box_h = 12, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 469, .adv_w = 102, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 50, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 175, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 486, .adv_w = 114, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 497, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 504, .adv_w = 120, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 513, .adv_w = 71, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 98, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 67, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 526, .adv_w = 111, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 531, .adv_w = 92, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 136, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 545, .adv_w = 96, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 89, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 557, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 66, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 567, .adv_w = 48, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 569, .adv_w = 66, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 574, .adv_w = 115, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 3}
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
    6, -4, -10, -6, 6, -11, -4, -20,
    -4, 3, -2, -4, -5, -3, -5, -4,
    6, -11, 6, -10, 7, -10, -7, -6,
    -4, -5, -5, -4, -5, 4, -8, -8,
    -8, -8, -14, -6, -14, -10, -14, -4,
    -6, -5, -8, -9, 4, -8, -4, -4,
    -4, -6, -3, -4, -4, -4, -4, -5,
    -8, -6, -8, -6, -4, -4, -10, -4,
    -6, -4, -4, -4, -4, -4, 4, 4,
    -8, -7, 5, -5, -4, -6, -10, -6,
    -6, -6, -6, -4, -6, -6, -10, -10,
    -10, -10, -9, -10, -10, -10, 6, -8,
    -8, 6, -8, -8, -22, -4, -14, -8,
    6, -18, -4, -8, -10, 6, -8, -8,
    -6, -8, -6, -4, -4, -10, -4, -6,
    -4, -17, -14, -6, -4, -4, -6, -4,
    6, 4, -8, 4, 4, -4, -4, -4,
    -4, -3, -4, -4, -4, -14, -8, -8,
    -22, -8, -8, 5, 8, 6, 4, -12,
    -18, -18, -18, 4, -14, -14, -14, -18,
    -12, -18, -12, -8, -12, -6, -14, -6,
    -6, -8, -6, -6, 8, 4, 4, 4,
    -8, -10, -10, -10, -10, -4, -4, -10,
    -10, -4, -10, -4, -4, -6, -4, -4,
    6, 4, -6, -5, -5, -5, -6, -5,
    -5, -6, -6, -6, -6, -4, -4, -6,
    -4, -4, -14, -10, -10, -12, -10, -10,
    4, 4, -16, -18, -18, -18, -18, -18,
    -18, -12, -8, -4, -4, -6, -6, -6,
    -6, -6, -6, -10, -6, -16, -14, -8,
    -6, -4, -16, 6, 4, -6, -4, -4,
    -4, -4, -4, -10, -12, -6, -14, -2,
    -2, -2, -3, -2, -2, -3, 5, 6,
    -4, -4, -4, -4, -3, -3, -3, -3,
    -3, -2, 7, 7, 4, -4, 4, 2,
    2, -12, -6, -14, -2, -2, -2, -3,
    -2, -2, -3, -12, -6, -14, -2, -2,
    -2, -3, -2, -2, -3, -10, -6, 6,
    -3, 4, 3, 5, 5, 4, 5, 4,
    -8, -4, -12, 5, -6, -15, -8, -12,
    -4, -4, -4, 4, 4, 3, 3, 4,
    -4, -12, -4, -4, -4, 4, 4, -4
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
const lv_font_t hyperlegible_13 = {
#else
lv_font_t hyperlegible_13 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if HYPERLEGIBLE_13*/

