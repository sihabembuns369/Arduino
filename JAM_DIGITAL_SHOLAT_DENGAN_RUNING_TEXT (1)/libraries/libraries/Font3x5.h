

/*
 *
 * Font3x5
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : font3x5.h
 * Date                : 09.05.2020
 * Font size in bytes  : 182
 * Font width          : 3
 * Font height         : 5
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

#ifndef FONT3X5_H
#define FONT3X5_H

#define FONT3X5_WIDTH 3
#define FONT3X5_HEIGHT 7

const static uint8_t Font3x5[] PROGMEM = {
    0x00, 0xB6, // size
    0x03, // width
    0x07, // height
    0x30, // first char
    0x0B, // char count
    
    // char widths
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 
    
    // font data
    0xF8, 0x88, 0xF8, // 48
    0x88, 0xF8, 0x80, // 49
    0xE8, 0xA8, 0xB8, // 50
    0xA8, 0xA8, 0xF8, // 51
    0x38, 0x20, 0xF8, // 52
    0xB8, 0xA8, 0xE8, // 53
    0xF8, 0xA8, 0xE8, // 54
    0xC8, 0x28, 0x18, // 55
    0xF8, 0xA8, 0xF8, // 56
    0xB8, 0xA8, 0xF8, // 57
    0x00, 0x50, 0x00 // 58
    
};

#endif
