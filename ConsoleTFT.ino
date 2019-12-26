/**
     Nano/Atmega328 PINS: connect LCD to D5 (D/C), D4 (CS), D3 (RES), D11(DIN), D13(CLK)
     Attiny SPI PINS:     connect LCD to D4 (D/C), GND (CS), D3 (RES), D1(DIN), D2(CLK)
     ESP8266: connect LCD to D1(D/C), D2(CS), RX(RES), D7(DIN), D5(CLK)
*/


#include "ssd1306.h"
#include "nano_engine.h"
#include "sova.h"

SAppMenu menu;

const char *menuItems[] =
{
  "draw bitmap",
  "sprites",
  "fonts",
  "nano canvas",
  "draw lines",
};

NanoPoint sprite;
NanoEngine8 engine;
uint8_t rotation = 0;


//gestione led
uint8_t pinInputLed = 2;
boolean StatusLed, oldStatusLed, primoGiro = false;

void setup() {
  InitScreen();
  //led
  pinMode(pinInputLed, INPUT);
  StatusLed = digitalRead(pinInputLed);
  oldStatusLed = !StatusLed;
}

void loop() {
  InputFromZ80();
}
