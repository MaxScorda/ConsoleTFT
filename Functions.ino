void InitScreen() {
  //  ssd1306_setFixedFont(free_calibri11x12);
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  st7735_128x160_spi_init(8, 10, 9);;
  // il9163_128x128_spi_init(12, 10, 9);
  //   il9163_setOffset(2, 1);
  // RGB functions do not work in default SSD1306 compatible mode
  ssd1306_setMode( LCD_MODE_NORMAL );
  ssd1306_clearScreen8( );
#if PROCEDURE==20
  ssd1306_createMenu( &menu, menuItems, sizeof(menuItems) / sizeof(char *) );
  ssd1306_showMenu8( &menu );
#endif
}

void LayoutScreen() {
  ssd1306_setColor(RGB_COLOR8(0, 255, 0));
  ssd1306_drawLine8(0, 68, ssd1306_displayWidth() - 1, 68);
}


//================ Random ==============
int goodRandomseed() {
  unsigned long tempBits = 0;  // create a long of random bits to use as seed
  byte noOfBits = 31; //preassegnato

  for (int i = 1; i <= 32 ; i++) {
#if (defined(__SAM3X8E__))
    //valido solo per il DUE con un generatore casuale interno
    pmc_enable_periph_clk(ID_TRNG);
    trng_enable(TRNG);
    tempBits = trng_read_output_data(TRNG);
#endif
#if (defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__) )
    tempBits = ( tempBits |  analogRead( 3 ) | ( analogRead( 0 )  & 1 ) ) << 1;
    // tempBits = tempBits + ( analogRead( 2 ) | ( analogRead( 1 )  & 1 ) ) << 1;
#else
    tempBits = ( tempBits | ( analogRead( 0 ) & analogRead( 1 ) & 1 ) ) << 1;
#endif
  }
  randomSeed(tempBits);
}

int RandNum(int rmin, int rmax) {
  int result;
  result = random(rmin, rmax + 1);
  //serprint(String(result));
  return result;
}
