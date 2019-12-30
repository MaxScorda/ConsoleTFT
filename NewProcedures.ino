void InputFromZ80() {
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

void Qix() {
  int spire = 16; //ex n
  int timedelay = 50;
  static unsigned long timevis = 0;
  int a, s, c;
  int ww = ssd1306_displayWidth() ;
  int hh = ssd1306_displayHeight() ;

  //porre x come spire
  static int x[16][2];
  static int y[16][2];

  if ( timevis + timedelay < millis()) {
    a = RandNum(1, 8);
    s = RandNum(1, 8);
    c = RandNum(5, 25);

    ssd1306_setColor(RGB_COLOR8(0, 0, 0));
     ssd1306_drawLine8(x[0][0], y[0][0], x[0][1], y[0][1]);


    //  shiftSpire();
    for (int g = 1; g < spire; g++)  {
      x[g - 1][0] = x[g][0];
      x[g - 1][1] = x[g][1];
      y[g - 1][0] = y[g][0];
      y[g - 1][1] = y[g][1];
    }

    if ( s == 1 ) {
      if ( x[spire - 1][0] + c > ww - 1) x[spire - 1][0] = x[spire - 1][0]  - c;
      else x[spire - 1][0] = x[spire - 1][0] + c;
      if ( x[spire - 1][1] - c < 1 ) x[spire - 1][1] = x[spire - 1][1] + c;
      else x[spire - 1][1] = x[spire - 1][1] - c;

    }
    else if (s == 2 ) {
      if ( x[spire - 1][0] - c < 1 ) x[spire - 1][0] = x[spire - 1][0] + c;
      else x[spire - 1][0] = x[spire - 1][0] - c;
      if ( x[spire - 1][1] + c > ww - 1) x[spire - 1][1] = x[spire - 1][1]  - c;
      else x[spire - 1][1] = x[spire - 1][1] + c;
    }

    else if (s == 3 ) {
      if ( y[spire - 1][0] + c > hh - 1) y[spire - 1][0] = y[spire - 1][0] - c;
      else y[spire - 1][0] = y[spire - 1][0] + c;
      if ( y[spire - 1][1] - c < 1 ) y[spire - 1][1] = y[spire - 1][1] + c;
      else y[spire - 1][1] = y[spire - 1][1] - c;
    }
    else if (s == 4) {
      if ( y[spire - 1][0] - c < 1 ) y[spire - 1][0] = y[spire - 1][0] + c;
      else y[spire - 1][0] = y[spire - 1][0] - c;
      if ( y[spire - 1][1] + c > hh - 1) y[spire - 1][1] = y[spire - 1][1] - c;
      else y[spire - 1][1] = y[spire - 1][1] + c;
    }
    else if (s == 5) {
      if ( x[spire - 1][0] + c > ww - 1) x[spire - 1][0] = x[spire - 1][0]  - c;
      else x[spire - 1][0] = x[spire - 1][0] + c;
      if ( x[spire - 1][1] + c > ww - 1) x[spire - 1][1] = x[spire - 1][1]  - c;
      else x[spire - 1][1] = x[spire - 1][1] + c;
    }
    else if (s == 6) {
      if ( x[spire - 1][0] - c < 1 ) x[spire - 1][0] = x[spire - 1][0] + c;
      else x[spire - 1][0] = x[spire - 1][0] - c;
      if ( x[spire - 1][1] - c < 1 ) x[spire - 1][1] = x[spire - 1][1] + c;
      else x[spire - 1][1] = x[spire - 1][1] - c;
    }
    else if (s == 7) {
      if ( y[spire - 1][0] + c > hh - 1) y[spire - 1][0] = y[spire - 1][0] - c;
      else y[spire - 1][0] = y[spire - 1][0] + c;
      if ( y[spire - 1][1] + c > hh - 1) y[spire - 1][1] = y[spire - 1][1] - c;
      else y[spire - 1][1] = y[spire - 1][1] + c;
    }
    else if (s == 8) {
      if ( y[spire - 1][0] - c < 1 ) y[spire - 1][0] = y[spire - 1][0] + c;
      else y[spire - 1][0] = y[spire - 1][0] - c;
      if ( y[spire - 1][1] - c < 1 ) y[spire - 1][1] = y[spire - 1][1] + c;
      else y[spire - 1][1] = y[spire - 1][1] - c;
    }

    // ssd1306_setColor(RGB_COLOR8(255, 255, 255));
    ssd1306_setColor(RGB_COLOR8(RandNum(128, 255), RandNum(128, 255), RandNum(128, 255)));
    ssd1306_drawLine8( x[spire - 1][0], y[spire - 1][0] , x[spire - 1][1], y[spire - 1][1]);
    Serial.print(String(s) + ": ");
    Serial.print(String(x[spire - 1][0]) + " - ");
    Serial.print(String(y[spire - 1][0]) + " - ");
    Serial.print(String(x[spire - 1][1]) + " - ");
    Serial.println(String(y[spire - 1][1], DEC) );
    timevis = millis();
  }
}

void shiftSpire() {
  /*
    for (int g = 2; g <= spire; g++)  {
    x(g - 1, 1) = x(g, 1);
    x(g - 1, 2) = x(g, 2);
    y(g - 1, 1) = y(g, 1);
    y(g - 1, 2) = y(g, 2);
    }
    x(spire, 1) = x[spire-1][0];
    x(spire, 2) = x[spire-1][1];
    y(spire, 1) = y[spire-1][0];
    y(spire, 2) = y[spire-1][1];
  */
}
