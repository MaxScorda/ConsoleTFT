#if PROCEDURE==10
void InputFromZ80() {
  //gestione led
  static boolean primoGiro = false;
  static int ccont = 14;
  char cstr[10];
  //I know setup but i want to keep it clean
  if (!primoGiro) {
    LayoutScreen() ;
    ssd1306_positiveMode();
    ssd1306_setColor(RGB_COLOR8(255, 255, 255));
    ssd1306_printFixed8(FARLEFT, 16, "Z80 RetroShield", STYLE_BOLD);
    ssd1306_printFixed8(FARLEFT, 24, "command say", STYLE_BOLD);
    primoGiro = true;
  }
  StatusLed = digitalRead(pinInputLed);
  if (StatusLed != oldStatusLed) {
    if (StatusLed) {
      ssd1306_negativeMode();
      ssd1306_setColor(RGB_COLOR8(0, 255, 0));
      ssd1306_printFixed8(FARLEFT, 40, "ACTIVATE  ", STYLE_BOLD);
    }
    else {
      ssd1306_positiveMode();
      ssd1306_setColor(RGB_COLOR8(255, 0, 0));
      ssd1306_printFixed8(FARLEFT, 40, "DEactivate", STYLE_NORMAL);
    }
    oldStatusLed = StatusLed;
    ssd1306_positiveMode();
    ssd1306_setColor(RGB_COLOR8(255, 255, 255));
    ssd1306_printFixed8(FARLEFT, 56, "Other " , STYLE_NORMAL);
    ssd1306_printFixed8(FARLEFT + 42, 56, "  " , STYLE_NORMAL);
    ssd1306_printFixed8(FARLEFT + 42, 56, itoa(ccont, cstr, 10), STYLE_NORMAL);
    if (ccont == 0) ccont = 14;
    ccont--;
  }
}

void serialZ80() {
  static boolean primoGiro = false;
  char cstr[10];
  //I know setup but i want to keep it clean
  if (!primoGiro) {
    ssd1306_positiveMode();
    ssd1306_setColor(RGB_COLOR8(255, 255, 255));
    ssd1306_printFixed8(FARLEFT, 72, "Serial Input", STYLE_NORMAL);
    primoGiro = true;
  }

  if (stringComplete) {
    //  Serial.println(inputString);
    ssd1306_positiveMode();
    ssd1306_setColor(RGB_COLOR8(255, 255, 255));
    inputString.toCharArray(cstr, 10);
    ssd1306_printFixed8(FARLEFT + 42, 80, cstr , STYLE_BOLD);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  byte ccont = 0;
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
    stringComplete = true;
    ccont++;
  }
}
#endif
