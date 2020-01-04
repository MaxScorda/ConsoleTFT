#if PROCEDURE<=5
void Qix() {
  //il principio e': determino una meta per x0,x1,y0,y1 e quando lo raggiungo lo cambio
#define SPIRE  16
#define NQIX  3
  byte timedelay = 25; //delay non bloccante
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
  byte idxprec;
  static boolean primoGiro = false;
  //init

  if (!primoGiro) {
    //meglio senza ma da testare ancora
    /*
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
    */
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

void Stars_Array() {
  //Stelle
  // 5 velocita' (passi)
  // colori pulsanti
  // 4 grandezze
  // se configurato ATTIVALAMPEGGIO= 1 stelle scomparsa/lampeggianti. Sistemare annche i due IF
#define ATTIVALAMPEGGIO  0
#define NSTELLE  48
  //struttura stelle
  struct dstars {
    byte id;
    byte xpos; //meglio int avendo spazio
    byte ypos; //meglio int avendo spazio
    byte grandezza;
    byte velocita; //1:ad ogni step fai un passo, 2:ogni 2 step un passo
    char contavelocita; //conteggio velocita, ogni stap tolgo 1 finche' non arrivo a 1
    byte passi; //quanti pixel avanzo
    byte colore[3];
    char segno;
  };
  typedef struct dstars SDStars;
  static SDStars Stars[NSTELLE];
  //
  int ww = ssd1306_displayWidth() ;
  int hh = ssd1306_displayHeight() ;
  byte timedelay = 25; //delay non bloccante
  byte stepcolore = 5;
  static unsigned long timevis = 0;
  boolean trovato = false;

  if ( timevis + timedelay < millis()) {
    for (int i = 0; i < NSTELLE; i++) {
      //se la stella e' vuota la creo. NB 1 sola per giro pero'
      if (Stars[i].id == 0) {
        if (trovato == false) {
          Stars[i].id = i + 1;
          Stars[i].xpos = RandNum(0, ww - 1);
          Stars[i].ypos = 0;
#if  ATTIVALAMPEGGIO==1
          Stars[i].velocita = RandNum(1, 5);
#else
          Stars[i].velocita = RandNum(1, 1);
#endif
          Stars[i].contavelocita = Stars[i].velocita;
          Stars[i].passi = RandNum(1, 5);
          Stars[i].grandezza = RandNum(0, 3);
          Stars[i].colore[0] = RandNum(128, 255);
          Stars[i].colore[1] = RandNum(128, 255);
          Stars[i].colore[2] = RandNum(128, 255);
          trovato = true;
        }
      }
      else {
        if (Stars[i].contavelocita <= 1) { // ATTIVALAMPEGGIO IF qui per stelle senza lampeggio
          ssd1306_setColor(RGB_COLOR8(0, 0, 0));
          if (Stars[i].grandezza > 0) {
            ssd1306_drawVLine8 (Stars[i].xpos , Stars[i].ypos - Stars[i].grandezza, Stars[i].ypos + Stars[i].grandezza);
            ssd1306_drawHLine8 (Stars[i].xpos - Stars[i].grandezza, Stars[i].ypos , Stars[i].xpos + Stars[i].grandezza + 1);
          }
          else {
            ssd1306_putPixel8(Stars[i].xpos , Stars[i].ypos);
          }
          //  if (Stars[i].contavelocita <= 1) { // ATTIVALAMPEGGIO IF qui per stelle CON lampeggio NB:attivare Stars[i].velocita
          Stars[i].contavelocita = Stars[i].velocita;
          Stars[i].ypos += Stars[i].passi;
          if ( Stars[i].ypos > hh - 1) {
            Stars[i].id = 0;
          }
        }
        else {
          Stars[i].contavelocita--;
        }
      }
      //disegna stella
      if (Stars[i].id > 0) {
        if (Stars[i].contavelocita == Stars[i].velocita) {
          // calcolo colore: vado verso il bianco, il primo che arriva a 255, scendo verso il nero
          if ((Stars[i].colore[0] == 255) || (Stars[i].colore[1] == 255) || (Stars[i].colore[2] == 255)) {
            Stars[i].segno = -stepcolore;
          }
          if ((Stars[i].colore[0] == 128) || (Stars[i].colore[1] == 128) || (Stars[i].colore[2] == 128)) {
            Stars[i].segno = stepcolore;
          }
          for (int g = 0; g < 2; g++) {
            Stars[i].colore[g] = constrain((long) (Stars[i].colore[g] + stepcolore), 128, 255);
          }
          // fine calcolo colore
          //Se grandezza>0 (star di 1 punto), inutile disegnare i raggi, faccio solo il punto
          ssd1306_setColor(RGB_COLOR8(Stars[i].colore[0], Stars[i].colore[1], Stars[i].colore[2]));
          if (Stars[i].grandezza > 0) {
            ssd1306_drawVLine8 (Stars[i].xpos , Stars[i].ypos - Stars[i].grandezza, Stars[i].ypos + Stars[i].grandezza);
            ssd1306_drawHLine8 (Stars[i].xpos - Stars[i].grandezza, Stars[i].ypos , Stars[i].xpos + Stars[i].grandezza + 1);
            ssd1306_setColor(RGB_COLOR8(255, 255, 255));
          }
          ssd1306_putPixel8(Stars[i].xpos , Stars[i].ypos);
        }
      }
    }
    timevis = millis();
  }
}

void ScrollText() {
  static unsigned long timescroll = 0;
  String strInfo = "";
  char cstr[20];
  char menuChoice[20];
  static boolean primoGiro = false;
  //init
  if (!primoGiro) {
    for (int i = 0; i < 5; i++) {
      strInfo +=   strcpy_P(menuChoice, (char*)pgm_read_word(&(menu_Info[i])));
    }
    Row1.NewString(strInfo);
    primoGiro = true;
  }

  if (timescroll + 250 < millis()) {
    strInfo = Row1.ScrollT();
    Serial.println("-" +  strInfo + "-");
    strInfo.toCharArray(cstr, 20);
    // Serial.println(strInfo);
    ssd1306_setColor(RGB_COLOR8(255, 255, 255));
    ssd1306_printFixed8(FARLEFT + 4 , 120, cstr , STYLE_BOLD);
    timescroll = millis();
  }
}
#endif

void SinDemo_1() {
  int ww = ssd1306_displayWidth() ;
  int hh = ssd1306_displayHeight() ;
  static int x[2], y[2];
  byte passo = 4;
  byte ccont = 0;
  float sinval;
  static boolean primoGiro = false;
  //init

  if (!primoGiro) {
    ssd1306_setColor(RGB_COLOR8(255, 255, 255));
    for (int yy = 27; yy >= 24; yy = yy - 8) {
      for (int xx = 0; xx < ww; xx++) {
        sinval = returnSin((ww - 1) / 4, 16 + (ccont * 2) % 16, xx);
        x[0] = xx + (ccont * passo) - 32;
        y[0] = yy + sinval;
        ssd1306_putPixel8(x[0] , y[0] );
        if (xx > 0)
          ssd1306_drawLine8(x[0], y[0], x[1], y[1]);

      x[1] = x[0];
      y[1] = y[0];
      // Serial.println((float)sinval, 5);
    }
    ccont++;
  }
  primoGiro = true;
  ssd1306_drawLine8(0, 68, ssd1306_displayWidth() - 1, 68);
}
}

void SinDemo_2() {
  int ww = ssd1306_displayWidth() ;
  int hh = ssd1306_displayHeight() ;
  int yy = 64;
  static int x[2], y[2];
  byte passo = 2;
  static byte ccont = 0;
  static unsigned long timevis = 0;
  byte timedelay = 50; //delay non bloccante
  float sinval;

  if ( timevis + timedelay < millis()) {
    ssd1306_setColor(RGB_COLOR8(255, 255, 255));
    ssd1306_clearScreen8( );
    for (int xx = 0; xx < ww; xx++) {
      sinval = returnSin((ww - 1) / 4, 16 + (ccont * 2) % 16, xx+ccont);
      x[0] = xx + (ccont * passo);
      y[0] = yy + sinval;
      ssd1306_putPixel8(x[0] , y[0] );
      if (xx > 0)
        ssd1306_drawLine8(x[0], y[0], x[1], y[1]);
      x[1] = x[0];
      y[1] = y[0];
      // Serial.println((float)sinval, 5);
    }
    ccont+=passo;
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
