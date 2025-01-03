

/*
 * Fareed Read
 * http://www.facebook.com/fareedreads
 *
 * arialblack8
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : arialblack8.h
 * Date                : 16.01.2023
 * Font size in bytes  : 3430
 * Font width          : 10
 * Font height         : 8
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef ARIALBLACK8_H
#define ARIALBLACK8_H

#define ARIALBLACK8_WIDTH 10
#define ARIALBLACK8_HEIGHT 8

const static uint8_t arialblack8[] PROGMEM = {
    0x0D, 0x66, // size
    0x0A, // width
    0x08, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x02, 0x04, 0x05, 0x05, 0x08, 0x05, 0x02, 0x03, 0x03, 
    0x03, 0x05, 0x02, 0x02, 0x02, 0x02, 0x05, 0x03, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x02, 0x02, 0x05, 0x05, 
    0x05, 0x05, 0x06, 0x06, 0x05, 0x06, 0x05, 0x04, 0x04, 0x06, 
    0x05, 0x01, 0x05, 0x05, 0x04, 0x06, 0x05, 0x06, 0x04, 0x06, 
    0x05, 0x05, 0x06, 0x05, 0x06, 0x08, 0x06, 0x06, 0x06, 0x02, 
    0x02, 0x02, 0x03, 0x04, 0x02, 0x05, 0x05, 0x05, 0x05, 0x05, 
    0x03, 0x05, 0x05, 0x01, 0x02, 0x05, 0x01, 0x08, 0x05, 0x05, 
    0x05, 0x05, 0x04, 0x05, 0x03, 0x05, 0x05, 0x07, 0x05, 0x05, 
    0x04, 0x03, 0x01, 0x03, 0x05, 0x04, 
    
    // font data
    0x03, 0x2F, // 33
    0x03, 0x03, 0x03, 0x03, // 34
    0x14, 0x3E, 0x37, 0x3E, 0x17, // 35
    0x12, 0x37, 0x7F, 0x2B, 0x3A, // 36
    0x02, 0x07, 0x27, 0x18, 0x06, 0x39, 0x38, 0x10, // 37
    0x3A, 0x2F, 0x2D, 0x3F, 0x38, // 38
    0x03, 0x03, // 39
    0x18, 0x7E, 0x81, // 40
    0x81, 0x7E, 0x18, // 41
    0x06, 0x07, 0x02, // 42
    0x0C, 0x0C, 0x1E, 0x0C, 0x0C, // 43
    0x30, 0x70, // 44
    0x18, 0x18, // 45
    0x30, 0x30, // 46
    0x38, 0x07, // 47
    0x0C, 0x3F, 0x21, 0x3F, 0x1E, // 48
    0x06, 0x3F, 0x3F, // 49
    0x22, 0x33, 0x39, 0x2F, 0x26, // 50
    0x12, 0x3B, 0x25, 0x3F, 0x1A, // 51
    0x18, 0x1C, 0x16, 0x3F, 0x10, // 52
    0x10, 0x3F, 0x27, 0x3F, 0x1B, // 53
    0x0C, 0x3F, 0x25, 0x2F, 0x3A, // 54
    0x03, 0x23, 0x3B, 0x07, 0x03, // 55
    0x10, 0x3F, 0x25, 0x3F, 0x3E, // 56
    0x06, 0x2F, 0x29, 0x3F, 0x1E, // 57
    0x34, 0x34, // 58
    0x34, 0x74, // 59
    0x08, 0x0C, 0x1C, 0x16, 0x12, // 60
    0x1C, 0x1C, 0x1C, 0x1C, 0x1C, // 61
    0x12, 0x16, 0x1C, 0x0C, 0x08, // 62
    0x02, 0x03, 0x2D, 0x07, 0x02, // 63
    0x3E, 0x5E, 0x63, 0x7D, 0x65, 0x1E, // 64
    0x20, 0x3C, 0x1F, 0x17, 0x3E, 0x30, // 65
    0x3F, 0x29, 0x2D, 0x3F, 0x1A, // 66
    0x0C, 0x3E, 0x33, 0x23, 0x33, 0x12, // 67
    0x3F, 0x23, 0x23, 0x3F, 0x1E, // 68
    0x3F, 0x2F, 0x2F, 0x2F, // 69
    0x3F, 0x0F, 0x0F, 0x0F, // 70
    0x0C, 0x3E, 0x33, 0x29, 0x2B, 0x3A, // 71
    0x3F, 0x0C, 0x0C, 0x3F, 0x3F, // 72
    0x3F, // 73
    0x10, 0x30, 0x20, 0x3F, 0x1F, // 74
    0x3F, 0x0C, 0x0E, 0x3F, 0x31, // 75
    0x3F, 0x20, 0x20, 0x20, // 76
    0x3F, 0x0F, 0x38, 0x3E, 0x03, 0x3F, // 77
    0x3F, 0x06, 0x1C, 0x3F, 0x3F, // 78
    0x0C, 0x3E, 0x33, 0x23, 0x37, 0x1E, // 79
    0x3F, 0x09, 0x0B, 0x0F, // 80
    0x0C, 0x3E, 0x33, 0x33, 0x37, 0x3E, // 81
    0x3F, 0x09, 0x19, 0x37, 0x26, // 82
    0x10, 0x37, 0x2D, 0x2F, 0x3A, // 83
    0x03, 0x03, 0x3F, 0x3F, 0x03, 0x03, // 84
    0x3F, 0x30, 0x20, 0x3F, 0x1F, // 85
    0x03, 0x0F, 0x3C, 0x38, 0x1F, 0x03, // 86
    0x07, 0x3F, 0x38, 0x0F, 0x0F, 0x38, 0x3F, 0x07, // 87
    0x21, 0x33, 0x1E, 0x1E, 0x3F, 0x21, // 88
    0x01, 0x03, 0x3E, 0x3C, 0x07, 0x01, // 89
    0x33, 0x3B, 0x2F, 0x27, 0x23, 0x20, // 90
    0xFF, 0xC3, // 91
    0x0F, 0x30, // 92
    0xC1, 0xFF, // 93
    0x06, 0x03, 0x06, // 94
    0x80, 0x80, 0x80, 0x80, // 95
    0x01, 0x01, // 96
    0x30, 0x34, 0x2C, 0x3C, 0x3C, // 97
    0x3F, 0x3F, 0x24, 0x3C, 0x3C, // 98
    0x18, 0x3C, 0x24, 0x24, 0x34, // 99
    0x18, 0x3C, 0x24, 0x3F, 0x3F, // 100
    0x18, 0x3C, 0x34, 0x2C, 0x2C, // 101
    0x04, 0x3F, 0x05, // 102
    0x58, 0xFC, 0xA4, 0xFC, 0x7C, // 103
    0x3F, 0x3F, 0x04, 0x3C, 0x3C, // 104
    0x3D, // 105
    0xC0, 0xFD, // 106
    0x3F, 0x3F, 0x18, 0x3C, 0x24, // 107
    0x3F, // 108
    0x3C, 0x3C, 0x04, 0x3C, 0x3C, 0x04, 0x3C, 0x38, // 109
    0x3C, 0x3C, 0x04, 0x3C, 0x3C, // 110
    0x18, 0x3C, 0x24, 0x3C, 0x1C, // 111
    0xFC, 0xFC, 0x24, 0x3C, 0x3C, // 112
    0x18, 0x3C, 0x24, 0xFC, 0xFC, // 113
    0x3C, 0x3C, 0x04, 0x04, // 114
    0x08, 0x2C, 0x2C, 0x3C, 0x10, // 115
    0x04, 0x3E, 0x24, // 116
    0x1C, 0x3C, 0x20, 0x3C, 0x3C, // 117
    0x04, 0x1C, 0x30, 0x1C, 0x04, // 118
    0x04, 0x3C, 0x30, 0x0C, 0x3C, 0x30, 0x1C, // 119
    0x20, 0x3C, 0x18, 0x3C, 0x24, // 120
    0x84, 0xDC, 0x70, 0x3C, 0x04, // 121
    0x24, 0x34, 0x2C, 0x24, // 122
    0x18, 0xFF, 0xC3, // 123
    0xFF, // 124
    0xC3, 0xFF, 0x18, // 125
    0x08, 0x04, 0x0C, 0x08, 0x0C, // 126
    0x3E, 0x22, 0x22, 0x3E // 127
    
};

#endif
