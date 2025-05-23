

/*
 * Fareed Read
 * http://www.facebook.com/fareedreads
 *
 * arialblack10
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : arialblack10.h
 * Date                : 16.01.2023
 * Font size in bytes  : 5722
 * Font width          : 10
 * Font height         : 10
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

#ifndef ARIALBLACK10_H
#define ARIALBLACK10_H

#define ARIALBLACK10_WIDTH 10
#define ARIALBLACK10_HEIGHT 10

const static uint8_t arialblack10[] PROGMEM = {
    0x16, 0x5A, // size
    0x0A, // width
    0x0A, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x03, 0x06, 0x07, 0x06, 0x09, 0x08, 0x03, 0x04, 0x04, 
    0x04, 0x07, 0x03, 0x04, 0x03, 0x04, 0x06, 0x05, 0x06, 0x06, 
    0x08, 0x06, 0x06, 0x06, 0x06, 0x06, 0x03, 0x03, 0x06, 0x06, 
    0x06, 0x07, 0x08, 0x08, 0x07, 0x07, 0x07, 0x06, 0x06, 0x07, 
    0x07, 0x03, 0x07, 0x08, 0x06, 0x08, 0x07, 0x07, 0x06, 0x07, 
    0x08, 0x06, 0x07, 0x07, 0x08, 0x0A, 0x08, 0x09, 0x06, 0x04, 
    0x04, 0x04, 0x07, 0x06, 0x04, 0x06, 0x06, 0x06, 0x06, 0x06, 
    0x05, 0x06, 0x06, 0x03, 0x04, 0x06, 0x03, 0x09, 0x06, 0x06, 
    0x06, 0x06, 0x05, 0x05, 0x05, 0x06, 0x06, 0x0A, 0x06, 0x06, 
    0x05, 0x05, 0x02, 0x05, 0x07, 0x06, 
    
    // font data
    0xDE, 0xDE, 0xDE, 0x00, 0x00, 0x00, // 33
    0x0E, 0x0E, 0x0E, 0x00, 0x0E, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 34
    0xFC, 0xFE, 0xFE, 0x6E, 0xFC, 0xFE, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 35
    0x4C, 0xDE, 0xFF, 0xFF, 0xF6, 0x64, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, // 36
    0x0C, 0x1E, 0x92, 0xFE, 0x7C, 0xEE, 0x92, 0xF0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 37
    0x60, 0xEC, 0xFE, 0xDE, 0xF6, 0x7E, 0xEC, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 38
    0x0E, 0x0E, 0x0E, 0x00, 0x00, 0x00, // 39
    0xF8, 0xFC, 0xFE, 0x02, 0x00, 0x40, 0xC0, 0x80, // 40
    0x02, 0xFE, 0xFC, 0xF8, 0x80, 0xC0, 0x40, 0x00, // 41
    0x14, 0x1E, 0x0E, 0x14, 0x00, 0x00, 0x00, 0x00, // 42
    0x18, 0x18, 0x7E, 0x7E, 0x7E, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 43
    0xC0, 0xC0, 0xC0, 0x80, 0xC0, 0x40, // 44
    0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, // 45
    0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, // 46
    0xC0, 0xF8, 0x3E, 0x06, 0x00, 0x00, 0x00, 0x00, // 47
    0x7C, 0xFE, 0xFE, 0xC6, 0xFE, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 48
    0x0C, 0x0C, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, // 49
    0xC4, 0xE6, 0xF6, 0xFE, 0xDE, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 50
    0x44, 0xC6, 0xD6, 0xFE, 0xFE, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 51
    0x60, 0x70, 0x78, 0x6C, 0xFE, 0xFE, 0xFE, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 52
    0x58, 0xDE, 0xDE, 0xF6, 0xF6, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 53
    0x7C, 0xFE, 0xFE, 0xD6, 0xF6, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 54
    0x06, 0xC6, 0xF6, 0xFE, 0x1E, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 55
    0x6C, 0xFE, 0xFE, 0xD6, 0xFE, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 56
    0x4C, 0xDE, 0xDE, 0xF6, 0xFE, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 57
    0xD8, 0xD8, 0xD8, 0x00, 0x00, 0x00, // 58
    0xD8, 0xD8, 0xD8, 0x80, 0xC0, 0x40, // 59
    0x38, 0x38, 0x7C, 0x6C, 0xEE, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 60
    0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 61
    0xC6, 0xEE, 0x6C, 0x7C, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 62
    0x0C, 0x0E, 0xAE, 0xA6, 0xBE, 0x1E, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 63
    0x78, 0xFC, 0x86, 0x72, 0x4A, 0x7A, 0x42, 0x3C, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, // 64
    0xC0, 0xF8, 0xFE, 0x7E, 0x66, 0xFE, 0xF8, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 65
    0xFE, 0xFE, 0xFE, 0xD6, 0xFE, 0xFE, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 66
    0x7C, 0xFE, 0xFE, 0xC6, 0xEE, 0xEE, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 67
    0xFE, 0xFE, 0xFE, 0xC6, 0xFE, 0xFE, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 68
    0xFE, 0xFE, 0xFE, 0xD6, 0xD6, 0xD6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 69
    0xFE, 0xFE, 0xFE, 0x16, 0x16, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 70
    0x7C, 0xFE, 0xFE, 0xC6, 0xF6, 0xF6, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 71
    0xFE, 0xFE, 0xFE, 0x18, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 72
    0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, // 73
    0x60, 0xE0, 0xE0, 0xC0, 0xFE, 0xFE, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 74
    0xFE, 0xFE, 0xFE, 0x18, 0x7E, 0xF6, 0xE2, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 75
    0xFE, 0xFE, 0xFE, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 76
    0xFE, 0xFE, 0xFE, 0x1C, 0xE0, 0x1E, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 77
    0xFE, 0xFE, 0xFE, 0x1C, 0xF0, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 78
    0x7C, 0xFE, 0xFE, 0xC6, 0xFE, 0xFE, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 79
    0xFE, 0xFE, 0xFE, 0x36, 0x3E, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 80
    0x7C, 0xFE, 0xFE, 0xC6, 0xFE, 0xFE, 0xBC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, // 81
    0xFE, 0xFE, 0xFE, 0x36, 0xFE, 0xFE, 0xDC, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 82
    0x4C, 0xDE, 0xDE, 0xF6, 0xF6, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 83
    0x06, 0x06, 0xFE, 0xFE, 0xFE, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 84
    0x7E, 0xFE, 0xFE, 0xC0, 0xFE, 0xFE, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 85
    0x06, 0x3E, 0xFE, 0xF8, 0xC0, 0xFE, 0x3E, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 86
    0xFE, 0xFE, 0xF0, 0xFE, 0x0E, 0xFE, 0xFE, 0xF0, 0xFE, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 87
    0x82, 0xE6, 0xFE, 0x7C, 0x38, 0xFE, 0xE6, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 88
    0x02, 0x06, 0x0E, 0xFC, 0xF8, 0xFC, 0x0E, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 89
    0xC6, 0xF6, 0xFE, 0xFE, 0xCE, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 90
    0xFE, 0xFE, 0xFE, 0x06, 0xC0, 0xC0, 0xC0, 0xC0, // 91
    0x06, 0x3E, 0xF8, 0xC0, 0x00, 0x00, 0x00, 0x00, // 92
    0x06, 0xFE, 0xFE, 0xFE, 0xC0, 0xC0, 0xC0, 0xC0, // 93
    0x10, 0x1C, 0x1E, 0x0E, 0x1E, 0x1C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, // 95
    0x02, 0x06, 0x06, 0x04, 0x00, 0x00, 0x00, 0x00, // 96
    0xC8, 0xE8, 0xE8, 0xB8, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 97
    0xFE, 0xFE, 0xFE, 0xD8, 0xF8, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 98
    0x70, 0xF8, 0xF8, 0xD8, 0xD8, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 99
    0x70, 0xF8, 0xF8, 0xDE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 100
    0x70, 0xF8, 0xF8, 0xA8, 0xB8, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 101
    0x08, 0xFE, 0xFE, 0xFE, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, // 102
    0x70, 0xF8, 0xF8, 0xD8, 0xF8, 0xF8, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0x40, // 103
    0xFE, 0xFE, 0xFE, 0x10, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 104
    0xFA, 0xFA, 0xFA, 0x00, 0x00, 0x00, // 105
    0x00, 0xFA, 0xFA, 0xFA, 0xC0, 0xC0, 0xC0, 0x40, // 106
    0xFE, 0xFE, 0xFE, 0x70, 0xF8, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 107
    0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, // 108
    0xF8, 0xF8, 0xF8, 0x10, 0xF8, 0xF0, 0x18, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 109
    0xF8, 0xF8, 0xF8, 0x10, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 110
    0x70, 0xF8, 0xF8, 0xD8, 0xF8, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 111
    0xF8, 0xF8, 0xF8, 0xD8, 0xF8, 0x70, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, // 112
    0x70, 0xF8, 0xF8, 0xD8, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, // 113
    0xF8, 0xF8, 0xF8, 0x10, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, // 114
    0x90, 0xB8, 0xF8, 0xE8, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, // 115
    0x08, 0xFC, 0xFE, 0xFE, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, // 116
    0xF8, 0xF8, 0xF8, 0xC0, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 117
    0x18, 0xF8, 0xF8, 0xC0, 0xF8, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 118
    0x08, 0x78, 0xF8, 0xE0, 0x78, 0x18, 0xF8, 0xE0, 0x78, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 119
    0xF8, 0xF8, 0x20, 0xF8, 0xF8, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 120
    0x18, 0xF8, 0xF8, 0xC0, 0xF8, 0x18, 0x80, 0x80, 0xC0, 0x40, 0x00, 0x00, // 121
    0xC8, 0xE8, 0xF8, 0xB8, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, // 122
    0x30, 0xFC, 0xFE, 0xEE, 0x06, 0x00, 0x40, 0xC0, 0xC0, 0xC0, // 123
    0xFE, 0xFE, 0xC0, 0xC0, // 124
    0x06, 0xEE, 0xFE, 0xFC, 0x30, 0xC0, 0xC0, 0xC0, 0x40, 0x00, // 125
    0x30, 0x38, 0x18, 0x38, 0x30, 0x38, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0xFC, 0xFC, 0x84, 0x84, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // 127
    
};

#endif
