/**
     Nano/Atmega328 PINS: connect LCD to D5 (D/C), D4 (CS), D3 (RES), D11(DIN), D13(CLK)
     Attiny SPI PINS:     connect LCD to D4 (D/C), GND (CS), D3 (RES), D1(DIN), D2(CLK)
     ESP8266: connect LCD to D1(D/C), D2(CS), RX(RES), D7(DIN), D5(CLK)
*/


#include "ssd1306.h"
#include "nano_engine.h"
#include "sova.h"
#include "config.h";


SAppMenu menu;

const char *menuItems[] =
{
  "draw bitmap",
  "sprites",
  "fonts",
  "nano canvas",
  "draw lines",
};


/* Sprites are not implemented for color modes.
   But there is NanoEngine support
   To make example clear, we use lambda as function pointer. Since lambda can be
   passed to function only if it doesn't capture, all variables should be global.
   Refer to C++ documentation.
*/
NanoPoint sprite;
NanoEngine8 engine;
uint8_t rotation = 0;
byte idx = 0;

void setup()
{
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  il9163_128x128_spi_init(12, 10, 9);

  // RGB functions do not work in default SSD1306 compatible mode
  ssd1306_setMode( LCD_MODE_NORMAL );
  ssd1306_setStartLine(0);
  ssd1306_clearScreen8( );


}

void loop() {
  delay(1000);
  idx = idx % 6;
  
  switch (idx)  {
    case 0:
      bitmapDemo();
      break;

    case 1:
      spriteDemo();
      break;

    case 2:
      textDemo();
      break;

    case 3:
      canvasDemo();
      break;

    case 4:
      drawLinesDemo();
      break;

    case 5:
      drawBoxDemo();
      break;

    default:
      break;
  }

  idx++;
  il9163_setRotation((++rotation) & 0x03);
  ssd1306_clearScreen8( );
  ssd1306_setColor(RGB_COLOR16(255, 255, 255));

}
