/**
     Nano/Atmega328 PINS: connect LCD to D5 (D/C), D4 (CS), D3 (RES), D11(DIN), D13(CLK)
     Attiny SPI PINS:     connect LCD to D4 (D/C), GND (CS), D3 (RES), D1(DIN), D2(CLK)
     ESP8266: connect LCD to D1(D/C), D2(CS), RX(RES), D7(DIN), D5(CLK)
*/
#include "ssd1306.h"
#if PROCEDURE==20
#include "nano_engine.h"
#include "sova.h"
#endif
#include <TEFX.h>
#include "Config.h";
#include "Classes.h"

//0 Tutto
//1-5 procedure demo qix,stars, scroll
//6 SinDemo
//10 I/O Z80
//20 old procedure
//50 extra demo
#define PROCEDURE  5

#if PROCEDURE==20
gestione sprite
NanoPoint sprite;
NanoEngine8 engine;
uint8_t rotation = 0;
#endif

//gestione led
uint8_t pinInputLed = 2;
boolean StatusLed, oldStatusLed = true;

//serial
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

//scroll
TEFX Row1("", 20);

void setup() {
  InitScreen();
#if PROCEDURE==10
  LayoutScreen() ;
#endif
  //led
  pinMode(pinInputLed, INPUT);
  StatusLed = digitalRead(pinInputLed);
  oldStatusLed = !StatusLed;

  // initialize serial:
  Serial.begin(19200);
#if PROCEDURE==10
  inputString.reserve(80);
#endif

  //vari
  goodRandomseed() ;
}

void loop() {
#if PROCEDURE==20
  InputFromZ80();
  serialZ80();
#endif

#if PROCEDURE<=5
  Qix() ;
  Stars_Array() ;
  ScrollText();
#endif

#if PROCEDURE==6
  SinDemo_2();
#endif
}
