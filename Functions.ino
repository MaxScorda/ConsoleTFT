void InitScreen() {
//  ssd1306_setFixedFont(free_calibri11x12);
    ssd1306_setFixedFont(ssd1306xled_font6x8);
  il9163_128x128_spi_init(12, 10, 9);
    // RGB functions do not work in default SSD1306 compatible mode
  ssd1306_setMode( LCD_MODE_NORMAL );
  ssd1306_clearScreen8( );
//  ssd1306_createMenu( &menu, menuItems, sizeof(menuItems) / sizeof(char *) );
//  ssd1306_showMenu8( &menu );

}
