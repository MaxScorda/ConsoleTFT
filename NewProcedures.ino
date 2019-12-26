void InputFromZ80() {
  static int ccont = 14;
  char cstr[10];
  //I know setup but i want to keep it clean
  if (!primoGiro) {
    ssd1306_printFixed8(FARLEFT, 16, "Z80 RetroShield", STYLE_BOLD);
    ssd1306_printFixed8(FARLEFT, 24, "command say", STYLE_BOLD);
    primoGiro = true;
  }
  StatusLed = digitalRead(pinInputLed);
  if (StatusLed != oldStatusLed) {
    if (StatusLed) {
      ssd1306_negativeMode();
      ssd1306_setColor(RGB_COLOR8(0, 255, 0));
      ssd1306_printFixed8(FARLEFT, 48, "ACTIVATE  ", STYLE_BOLD);
    }
    else {
      ssd1306_positiveMode();
      ssd1306_setColor(RGB_COLOR8(255, 0, 0));
      ssd1306_printFixed8(FARLEFT, 48, "DEactivate", STYLE_NORMAL);
    }
    oldStatusLed = StatusLed;
    ssd1306_positiveMode();
    ssd1306_setColor(RGB_COLOR8(255, 255, 255));
    ssd1306_printFixed8(FARLEFT, 64, "Other " , STYLE_NORMAL);
    ssd1306_printFixed8(FARLEFT, 72, "  " , STYLE_NORMAL);
    ssd1306_printFixed8(FARLEFT, 72, itoa(ccont, cstr, 10), STYLE_NORMAL);
    if (ccont == 0) ccont = 14;
    ccont--;
  }
}
