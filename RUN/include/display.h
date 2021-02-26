#ifndef _LCD_H_
#define _LCD_H_
#include <stdio.h>
#include <errno.h>

class Display{
public:
  void createScreen();
  void createTitle();
  void createImage();
  void refresh();
  void batteryBoi();
  void linemeter();
  void lv_ex_led_1();
};

#endif
