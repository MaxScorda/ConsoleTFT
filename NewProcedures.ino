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

void Qix() {
  //il principio e': determino una meta per x0,x1,y0,y1 e quando lo raggiungo lo cambio
#define SPIRE  36
  int timedelay = 50; //delay non bloccante
  byte minpasso = 1,  maxpasso = 6; //range di calcolo rnd del passo tra spire
  static unsigned long timevis = 0;
  int ww = ssd1306_displayWidth() ;
  int hh = ssd1306_displayHeight() ;
  static int x[SPIRE][3];
  static int y[SPIRE][3];
  //Prima dimensione 0:valori x, 1:valori y, seconda dimensione x[0],x[1]
  static byte destinazione[2][2];
  //passo,x=0 e y=1   VEDERE SE FARNE 4
  static byte passo[SPIRE][2];
  //colori seconda dimensione 0: colore attuale, 1:colore da raggiungere
  static byte colore[3][2] ;
  //indice vettori spire
  static byte spireidx = SPIRE - 1;
  int idxprec;
  static boolean primoGiro = false;
  //init
  if (!primoGiro) {
    for (int i = 0; i < SPIRE; i++) {
      for (int j = 0; j < 2; j++) {
        passo[i][j] = RandNum(minpasso, maxpasso);
        x[i][j] = 0;
        y[i][j] = 0;
      }
    }
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 2; j++) {
        colore[i][j] = 128;
      }
    }
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        destinazione[i][j] = 0;
      }
    }
    primoGiro = true;
  }

  if ( timevis + timedelay < millis()) {
    idxprec = (spireidx + 1) % SPIRE;
    ssd1306_setColor(RGB_COLOR8(0, 0, 0));
    ssd1306_drawLine8(x[idxprec][0], y[idxprec][0], x[idxprec][1], y[idxprec][1]);

    //spire
    for (int i = 0; i < 2; i++) {
      //punti x
      if (abs(x[spireidx][i] - destinazione[0][i]) <= passo[spireidx][0] )  {
        destinazione[0][i] = RandNum(0, ww - 1);
        passo[spireidx][0] = RandNum(minpasso, maxpasso);
      }
      if (x[spireidx][i] > destinazione[0][i]) x[spireidx][i] -= passo[spireidx][0];
      if (x[spireidx][i] < destinazione[0][i]) x[spireidx][i] += passo[spireidx][0];
      //punti y
      if (abs(y[spireidx][i] - destinazione[1][i]) <= passo[spireidx][1]) {
        destinazione[1][i] = RandNum(0, hh - 1);
        passo[spireidx][1] = RandNum(minpasso, maxpasso);
      }
      if (y[spireidx][i] > destinazione[1][i]) y[spireidx][i] -= passo[spireidx][1];
      if (y[spireidx][i] < destinazione[1][i]) y[spireidx][i] += passo[spireidx][1];
    }

    for (int g = 0; g < 2; g++)  {
      x[idxprec][g] = x[spireidx][g];
      y[idxprec][g] = y[spireidx][g];
      passo[idxprec][g] = passo[spireidx][g];
    }
    //colori
    for (int i = 0; i < 3; i++) {
      if (colore[i][0] == colore[i][1]) colore[i][1] = RandNum(128, 255);
      if (colore[i][0] > colore[i][1]) colore[i][0]--;
      if (colore[i][0] < colore[i][1]) colore[i][0]++;
    }

    // ssd1306_setColor(RGB_COLOR8(255, 255, 255));
    ssd1306_setColor(RGB_COLOR8(colore[0][0], colore[1][0], colore[2][0]));
    ssd1306_drawLine8( x[spireidx][0], y[spireidx][0] , x[spireidx][1], y[spireidx][1]);

    /*
        Serial.print(String(spireidx) + ": ");
        Serial.print(String(x[spireidx][0]) + " - ");
        Serial.print(String(y[spireidx][0]) + " - ");
        Serial.print(String(x[spireidx][1]) + " - ");
        Serial.print(String(y[spireidx][1]) + " -- " );
        Serial.print(String(passo[spireidx][0]) + "-");
        Serial.print(String(passo[spireidx][1]) +  "   ");
        for (int i = 0; i < 2; i++) {
          for (int j = 0; j < 2; j++) {
            Serial.print(String(destinazione[i][j] ) + "+");
          }
        }
        Serial.println("");
    */
    spireidx = (spireidx + 1) % SPIRE;
    timevis = millis();
  }
}



float returnSin(byte lenx, byte hiy, int vval) {
  //lenx:lunghezza ciclo
  //hiy:altezza
  //vval: valore attuale
  //es:lenx=8, hiy=2  0 1 2 1 0 -1 -2 -1
  float duepi = 6.28318532;
  float ret;
  //onda triangolare
  vval = (vval + ((lenx * 3) / 4)) % lenx;
  ret = sin((vval * duepi) / lenx) * hiy;
  return ret;
}
