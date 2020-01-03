/**
     Nano/Atmega328 PINS: connect LCD to D5 (D/C), D4 (CS), D3 (RES), D11(DIN), D13(CLK)
     Attiny SPI PINS:     connect LCD to D4 (D/C), GND (CS), D3 (RES), D1(DIN), D2(CLK)
     ESP8266: connect LCD to D1(D/C), D2(CS), RX(RES), D7(DIN), D5(CLK)
*/
#include "ssd1306.h"
#include "nano_engine.h"
#include "sova.h"
#include <TEFX.h>
#include "Config.h";
#include "Classes.h"


//NanoPoint sprite;
//NanoEngine8 engine;
//uint8_t rotation = 0;

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
  // LayoutScreen() ;
  //led
  pinMode(pinInputLed, INPUT);
  StatusLed = digitalRead(pinInputLed);
  oldStatusLed = !StatusLed;

  // initialize serial:
  Serial.begin(19200);
 // inputString.reserve(80);

  //vari
  goodRandomseed() ;
}

void loop() {
  //InputFromZ80();
  //serialZ80();
  Qix() ;
  Stars_Array() ;
 ScrollText();
}
