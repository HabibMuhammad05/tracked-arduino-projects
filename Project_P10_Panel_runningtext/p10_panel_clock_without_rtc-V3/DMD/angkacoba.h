

/*
 * Fareed Read
 * http://www.facebook.com/fareedreads
 *
 * angkacoba
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : angkacoba.h
 * Date                : 16.01.2023
 * Font size in bytes  : 479
 * Font width          : 6
 * Font height         : -7
 * Font first char     : 48
 * Font last char      : 59
 * Font used chars     : 11
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

#ifndef ANGKACOBA_H
#define ANGKACOBA_H

#define ANGKACOBA_WIDTH 6
#define ANGKACOBA_HEIGHT -7

const static uint8_t angkacoba[] PROGMEM = {
    0x01, 0xDF, // size
    0x06, // width
    0x07, // height
    0x30, // first char
    0x0B, // char count
    
    // char widths
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 
    0x04, 
    
    // font data
    0x7C, 0xFE, 0x82, 0x82, 0xFE, 0x7C, // 48
    0x82, 0x82, 0xFE, 0xFE, 0x80, 0x80, // 49
    0xC2, 0xE2, 0xB2, 0x92, 0x9E, 0x8C, // 50
    0x82, 0x92, 0x92, 0x92, 0xFE, 0x6C, // 51
    0x70, 0x78, 0x44, 0xFE, 0xFE, 0x40, // 52
    0x9E, 0x9E, 0x92, 0x92, 0xF2, 0x62, // 53
    0x7C, 0xFE, 0x8A, 0x8A, 0xFA, 0x70, // 54
    0x02, 0x02, 0xC2, 0xF2, 0x1E, 0x0E, // 55
    0x6C, 0xFE, 0x92, 0x92, 0xFE, 0x6C, // 56
    0x0C, 0x9E, 0x92, 0x92, 0xFE, 0x7C, // 57
    0x00, 0x6C, 0x6C, 0x00 // 58
};

#endif
