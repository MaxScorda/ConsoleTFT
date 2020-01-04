#ifndef config_H
#define config_H

#include <avr/pgmspace.h>

#define FARLEFT  1

const char Info_00[] PROGMEM = "Demo ConsoleTFT 0.9 ";
const char Info_01[] PROGMEM = "(c) 2019-2020 ";
const char Info_02[] PROGMEM = "Max Scordamaglia ";
const char Info_03[] PROGMEM = "maxscorda@gmail.com ";
const char Info_04[] PROGMEM = " ... ";


const char* const menu_Info[] PROGMEM = {Info_00, Info_01, Info_02, Info_03, Info_04
                                        };

 /*
   Heart image below is defined directly in flash memory.
   This reduces SRAM consumption.
   The image is defined from bottom to top (bits), from left to
   right (bytes).
*/
                                       
const PROGMEM uint8_t heartImage[8] =
{
  0B00001110,
  0B00011111,
  0B00111111,
  0B01111110,
  0B01111110,
  0B00111101,
  0B00011001,
  0B00001110
};

const PROGMEM uint8_t heartImage8[ 8 * 8 ] =
{
  0x00, 0xE0, 0xE0, 0x00, 0x00, 0xE5, 0xE5, 0x00,
  0xE0, 0xC0, 0xE0, 0xE0, 0xE0, 0xEC, 0xEC, 0xE5,
  0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE5, 0xEC, 0xE5,
  0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE5, 0xE0,
  0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0x00,
  0x00, 0x00, 0x80, 0xE0, 0xE0, 0xE0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x80, 0xE0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};




#endif
