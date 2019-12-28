void InputFromZ80() {
  static boolean primoGiro = false;
  static int ccont = 14;
  char cstr[10];
  //I know setup but i want to keep it clean
  if (!primoGiro) {
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

void Qix() {
  int spire = 3; //ex n
  int a, s, c;
  int x1, y1, x2, y2;
  int ww = ssd1306_displayWidth() ;
  int hh = ssd1306_displayHeight() ;
  ssd1306_clearScreen8( );
  DIM l(spire, 2)
  x1 = 300;
  y1 = 100;
  x2 = 350;
  y2 = 150;
  a = RandNum(1, 8);
  s = RandNum(1, 8);
  c = RadnNum(5, 25);
  for (int f = 1; f <= a; f++)  {
    ssd1306_setColor(RGB_COLOR8(0, 0, 0));
    ssd1306_drawLine8(x(1, 1), y(1, 1), x(1, 2), y(1, 2));
    if ( s == 1 ) {
      x1 = x1 + c;
      x2 = x2 - c;
    }
    else if (s == 2 ) {
      x2 = x2 + c;
      x1 = x1 - c;
    }
    else if (s == 3 ) {
      y1 = y1 + c;
      y2 = y2 - c;
    }
    else if (s == 4) {
      y2 = y2 + c;
      y1 = y1 - c;
    }
    else if (s == 5) {
      x1 = x1 + c;
      x2 = x2 + c;
    }
    else if (s == 6) {
      x2 = x2 - c;
      x1 = x1 - c;
    }
    else if (s == 7) {
      y1 = y1 + c;
      y2 = y2 + c;
    }
    else if (s == 8) {
      y1 = y1 - c;
      y2 = y2 - c;
    }

    if ( x1 > ww - 1) {
      x1 = x1 - c;
    }
    else  if ( x1 < 1 ) {
      x1 = x1 + c;
    }

    if ( x2 > ww - 1 ) {
      x2 = x2 - c;
    }
    else if ( x2 < 1) {
      x2 = x2 + c;
    }
    if (y1 > hh) {
      y1 = y1 - c;
    }
    else if (y1 < 1 ) {
      y1 = y1 + c;
    }
    if ( y2 > hh - 1) {
      y2 = y2 - c;
    }
    else if ( y2 < 1) {
      y2 = y2 + c;
    }
    shiftSpire();
    ssd1306_setColor(RGB_COLOR8(RandNum(128, 255), RandNum(128, 255), RandNum(128, 255)));
    ssd1306_drawLine8( (x(spire, 1), y(spire, 1)) - (x(spire, 2), y(spire, 2))
  }
}

void shiftSpire() {
  for (int g = 2; g <= spire; g++)  {
    x(g - 1, 1) = x(g, 1);
    x(g - 1, 2) = x(g, 2);
    y(g - 1, 1) = y(g, 1);
    y(g - 1, 2) = y(g, 2);
  }
  x(spire, 1) = x1;
  x(spire, 2) = x2;
  y(spire, 1) = y1;
  y(spire, 2) = y2;
}
