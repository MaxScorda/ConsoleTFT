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
#define SPIRE  24
  int timedelay = 50;
  byte minpasso = 1,  maxpasso = 6;
  static unsigned long timevis = 0;
  int ww = ssd1306_displayWidth() ;
  int hh = ssd1306_displayHeight() ;
  static byte x[SPIRE][3];
  static byte y[SPIRE][3];
  //Prima dimensione 0:valori x, 1:valori y
  //seconda dimensione x[0],x[1]
  static byte destinazione[2][2];
  //passo,x=0 e y=1   VEDERE SE FARNE 4
  static byte passo[2];
  //colori seconda dimensione 0: colore attuale, 1:colore da raggiungere
  static byte colore[3][2] = {{128, 0}, {128, 0}, {128, 0}};

  if ( timevis + timedelay < millis()) {
    ssd1306_setColor(RGB_COLOR8(0, 0, 0));
    ssd1306_drawLine8(x[0][0], y[0][0], x[0][1], y[0][1]);

    //spire
    for (int i = 0; i < 2; i++) {
      //punti x
      if (abs(x[SPIRE - 1][i] - destinazione[0][i]) <= passo[0])  {
        destinazione[0][i] = RandNum(0, ww - 1);
        passo[0] = RandNum(minpasso, maxpasso);
      }
      if (x[SPIRE - 1][i] > destinazione[0][i]) x[SPIRE - 1][i] -= passo[0];
      if (x[SPIRE - 1][i] < destinazione[0][i]) x[SPIRE - 1][i] += passo[0];
      //punti y
      if (abs(y[SPIRE - 1][i] - destinazione[1][i]) <= passo[1]) {
        destinazione[1][i] = RandNum(0, hh - 1);
        passo[1] = RandNum(minpasso, maxpasso);
      }
      if (y[SPIRE - 1][i] > destinazione[1][i]) y[SPIRE - 1][i] -= passo[1];
      if (y[SPIRE - 1][i] < destinazione[1][i]) y[SPIRE - 1][i] += passo[1];
    }
    //colori
    for (int i = 0; i < 3; i++) {
      if (colore[i][0] == colore[i][1]) colore[i][1] = RandNum(128, 255);
      if (colore[i][0] > colore[i][1]) colore[i][0]--;
      if (colore[i][0] < colore[i][1]) colore[i][0]++;
    }

    //  shiftSpire();
    for (int g = 1; g < SPIRE; g++)  {
      x[g - 1][0] = x[g][0];
      x[g - 1][1] = x[g][1];
      y[g - 1][0] = y[g][0];
      y[g - 1][1] = y[g][1];
    }

    // ssd1306_setColor(RGB_COLOR8(255, 255, 255));
    ssd1306_setColor(RGB_COLOR8(colore[0][0], colore[1][0], colore[2][0]));
    ssd1306_drawLine8( x[SPIRE - 1][0], y[SPIRE - 1][0] , x[SPIRE - 1][1], y[SPIRE - 1][1]);

    Serial.print(String(x[SPIRE - 1][0]) + " - ");
    Serial.print(String(y[SPIRE - 1][0]) + " - ");
    Serial.print(String(x[SPIRE - 1][1]) + " - ");
    Serial.println(String(y[SPIRE - 1][1], DEC) );


    timevis = millis();
  }
}
