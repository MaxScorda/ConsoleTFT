void Oldloop(){
    delay(1000);
    switch (ssd1306_menuSelection(&menu))
    {
        case 0:
            bitmapDemo();
            break;

        case 1:
            spriteDemo();
            break;

        case 2:
            textDemo();
            break;

        case 3:
            canvasDemo();
            break;

        case 4:
            drawLinesDemo();
            break;

        default:
            break;
    }
    if ((menu.count - 1) == ssd1306_menuSelection(&menu))
    {
         il9163_setRotation((++rotation) & 0x03);
    }
    ssd1306_clearScreen8( );
    ssd1306_setColor(RGB_COLOR16(255,255,255));
    ssd1306_showMenu8(&menu);
    delay(500);
    ssd1306_menuDown(&menu);
    ssd1306_updateMenu8(&menu);
}

static void bitmapDemo()
{
  ssd1306_setColor(RGB_COLOR8(64, 64, 255));
  ssd1306_drawMonoBitmap8(0, 0, 128, 64, Sova);
  ssd1306_drawBitmap8(0, 0, 8, 8, heartImage8);
  ssd1306_setColor(RGB_COLOR8(255, 64, 64));
  ssd1306_drawMonoBitmap8(0, 16, 8, 8, heartImage);
  delay(3000);
}


static void spriteDemo()
{
  // We not need to clear screen, engine will do it for us
  engine.begin();
  // Force engine to refresh the screen
  engine.refresh();
  // Set function to draw our sprite
  engine.drawCallback( []()->bool {
    engine.canvas.clear();
    engine.canvas.setColor( RGB_COLOR8(255, 32, 32) );
    engine.canvas.drawBitmap1( sprite.x, sprite.y, 8, 8, heartImage );
    return true;
  } );
  sprite.x = 0;
  sprite.y = 0;
  for (int i = 0; i < 250; i++)
  {
    delay(15);
    // Tell the engine to refresh screen at old sprite position
    engine.refresh( sprite.x, sprite.y, sprite.x + 8 - 1, sprite.y + 8 - 1 );
    sprite.x++;
    if (sprite.x >= ssd1306_displayWidth())
    {
      sprite.x = 0;
    }
    sprite.y++;
    if (sprite.y >= ssd1306_displayHeight())
    {
      sprite.y = 0;
    }
    // Tell the engine to refresh screen at new sprite position
    engine.refresh( sprite.x, sprite.y, sprite.x + 8 - 1, sprite.y + 8 - 1 );
    // Do refresh required parts of screen
    engine.display();
  }
}

static void textDemo(){
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_clearScreen8();
  ssd1306_setColor(RGB_COLOR8(255, 255, 0));
  ssd1306_printFixed8(0,  8, "Normal text", STYLE_NORMAL);
  ssd1306_setColor(RGB_COLOR8(0, 255, 0));
  ssd1306_printFixed8(0, 16, "bold text?", STYLE_BOLD);
  ssd1306_setColor(RGB_COLOR8(0, 255, 255));
  ssd1306_printFixed8(0, 24, "Italic text?", STYLE_ITALIC);
  ssd1306_negativeMode();
  ssd1306_setColor(RGB_COLOR8(255, 255, 255));
  ssd1306_printFixed8(0, 32, "Inverted bold?", STYLE_BOLD);
  ssd1306_positiveMode();
  delay(3000);
}

static void canvasDemo()
{
  uint8_t buffer[64 * 16 / 8];
  NanoCanvas1_8 canvas(64, 16, buffer);
  ssd1306_setColor(RGB_COLOR8(0, 255, 0));
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_clearScreen8();
  canvas.clear();
  canvas.fillRect(10, 3, 80, 5);
  canvas.blt((ssd1306_displayWidth() - 64) / 2, 1);
  delay(500);
  canvas.fillRect(50, 1, 60, 15);
  canvas.blt((ssd1306_displayWidth() - 64) / 2, 1);
  delay(1500);
  canvas.printFixed(20, 1, " DEMO ", STYLE_BOLD );
  canvas.blt((ssd1306_displayWidth() - 64) / 2, 1);
  delay(3000);
}

static void drawLinesDemo() {
  ssd1306_clearScreen8();
  ssd1306_setColor(RGB_COLOR8(255, 0, 0));
  for (uint8_t y = 0; y < ssd1306_displayHeight(); y += 8)
  {
    ssd1306_drawLine8(0, 0, ssd1306_displayWidth() - 1, y);
  }
  ssd1306_setColor(RGB_COLOR8(0, 255, 0));
  for (uint8_t x = ssd1306_displayWidth() - 1; x > 7; x -= 8)
  {
    ssd1306_drawLine8(0, 0, x, ssd1306_displayHeight() - 1);
  }
  delay(3000);
}


void Qix_old() {
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
        /*
      Serial.print(String(destinazione[0][0]) + " - ");
      Serial.print(String(destinazione[0][1]) + " - ");
      Serial.print(String(destinazione[1][0]) + " - ");
      Serial.println(String(destinazione[1][1]) );
    */
    timevis = millis();
  }
}
