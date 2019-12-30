static void drawBoxDemo()
{
  ssd1306_clearScreen8();
  ssd1306_setColor(RGB_COLOR8(255, 0, 0));

  ssd1306_drawLine8(0, 0, ssd1306_displayWidth() - 1, 0);
  ssd1306_setColor(RGB_COLOR8(0, 255, 0));
  ssd1306_drawLine8(ssd1306_displayWidth() - 1, 0, ssd1306_displayWidth() - 1,  ssd1306_displayHeight() - 1);
  ssd1306_setColor(RGB_COLOR8(0, 0, 255));
  ssd1306_drawLine8( ssd1306_displayWidth() - 1,  ssd1306_displayHeight() - 1, 0, ssd1306_displayHeight() - 1);
  ssd1306_setColor(RGB_COLOR8(255, 255, 255));
  ssd1306_drawLine8(  0, ssd1306_displayHeight() - 1, 0, 0);

  delay(3000);
}
