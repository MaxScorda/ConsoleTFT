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
#define SPIRE  16
#define NQIX  3
  int timedelay = 50; //delay non bloccante
  byte minpasso = 1,  maxpasso = 6; //range di calcolo rnd del passo tra spire
  static unsigned long timevis = 0;
  int ww = ssd1306_displayWidth() ;
  int hh = ssd1306_displayHeight() ;
  static byte x[NQIX][SPIRE][3];
  static byte y[NQIX][SPIRE][3];
  //Prima dimensione 0:valori x, 1:valori y, seconda dimensione x[0],x[1]
  static byte destinazione[NQIX][2][2];
  //passo,x=0 e y=1   VEDERE SE FARNE 4
  static byte passo[NQIX][SPIRE][2];
  //colori seconda dimensione 0: colore attuale, 1:colore da raggiungere
  static byte colore[NQIX][3][2] ;
  //indice vettori spire
  static byte spireidx = SPIRE - 1;
  int idxprec;
  static boolean primoGiro = false;
  //init
  if (!primoGiro) {
    for (int q = 0; q < NQIX; q++) {
      for (int i = 0; i < SPIRE; i++) {
        for (int j = 0; j < 2; j++) {
          passo[q][i][j] = RandNum(minpasso, maxpasso);
          x[q][i][j] = 0;
          y[q][i][j] = 0;
        }
      }
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
          colore[q][i][j] = 128;
        }
      }
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          destinazione[q][i][j] = 0;
        }
      }
    }
    primoGiro = true;
  }

  if ( timevis + timedelay < millis()) {
    idxprec = (spireidx + 1) % SPIRE;
    for (int q = 0; q < NQIX; q++) {
      ssd1306_setColor(RGB_COLOR8(0, 0, 0));
      ssd1306_drawLine8(x[q][idxprec][0], y[q][idxprec][0], x[q][idxprec][1], y[q][idxprec][1]);


      //spire
      for (int i = 0; i < 2; i++) {
        //punti x
        if (abs(x[q][spireidx][i] - destinazione[q][0][i]) <= passo[q][spireidx][0] )  {
          destinazione[q][0][i] = RandNum(0, ww - 1);
          passo[q][spireidx][0] = RandNum(minpasso, maxpasso);
        }
        if (x[q][spireidx][i] > destinazione[q][0][i]) x[q][spireidx][i] -= passo[q][spireidx][0];
        if (x[q][spireidx][i] < destinazione[q][0][i]) x[q][spireidx][i] += passo[q][spireidx][0];
        //punti y
        if (abs(y[q][spireidx][i] - destinazione[q][1][i]) <= passo[q][spireidx][1]) {
          destinazione[q][1][i] = RandNum(0, hh - 1);
          passo[q][spireidx][1] = RandNum(minpasso, maxpasso);
        }
        if (y[q][spireidx][i] > destinazione[q][1][i]) y[q][spireidx][i] -= passo[q][spireidx][1];
        if (y[q][spireidx][i] < destinazione[q][1][i]) y[q][spireidx][i] += passo[q][spireidx][1];
      }

      for (int g = 0; g < 2; g++)  {
        x[q][idxprec][g] = x[q][spireidx][g];
        y[q][idxprec][g] = y[q][spireidx][g];
        passo[q][idxprec][g] = passo[q][spireidx][g];
      }
      //colori
      for (int i = 0; i < 3; i++) {
        if (colore[q][i][0] == colore[q][i][1]) colore[q][i][1] = RandNum(128, 255);
        if (colore[q][i][0] > colore[q][i][1]) colore[q][i][0]--;
        if (colore[q][i][0] < colore[q][i][1]) colore[q][i][0]++;
      }

      // ssd1306_setColor(RGB_COLOR8(255, 255, 255));
      ssd1306_setColor(RGB_COLOR8(colore[q][0][0], colore[q][1][0], colore[q][2][0]));
      ssd1306_drawLine8( x[q][spireidx][0], y[q][spireidx][0] , x[q][spireidx][1], y[q][spireidx][1]);

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

    }
    spireidx = (spireidx + 1) % SPIRE;
    timevis = millis();
  }
}

void Stars() {
#define NSTELLE  24
  //struttura stelle
  int timedelay = 50; //delay non bloccante
  static unsigned long timevis = 0;
  int ccont = 0;
  if ( timevis + timedelay < millis()) {
    Star star1 = Star(1);

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
