#ifndef _LCD_H_
#define _LCD_H_
#include <stdio.h>
#include <errno.h>

class Display{
public:
  lv_obj_t * tabs = lv_tabview_create(lv_scr_act(), NULL);
  lv_obj_t * main_tab = lv_tabview_add_tab(tabs, "MAIN");
  lv_obj_t * adv_tab = lv_tabview_add_tab(tabs, "ADV");
  void createScreen();
  void createTitle();
  void createImage();
  void refresh();
  void batteryBoi();
  void linemeter();
  void lv_ex_led_1();
  void lv_ex_led_2();
  void createButton();
};

 /*extern Task disp_task;
 extern void DispTask_fn(void*par); //task for motor acceleration
 */

#endif
