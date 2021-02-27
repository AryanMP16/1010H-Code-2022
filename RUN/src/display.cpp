#include "main.h"
#include "display.h"
#include <string.h>
//lv_obj_t*led1;
//int ledval;

void Display::refresh(void){
  //if(master.get_digital(DIGITAL_A)){ledval = 200;}
  //else{ledval = 0;}
  delay(10);
}

void Display::createScreen(void) {
  lv_theme_t * theme = lv_theme_nemo_init(40, NULL); //60 For TTYellow
  lv_theme_set_current(theme);
  lv_ex_led_1();
}

void Display::lv_ex_led_1(void) {
    lv_obj_t*led1 = lv_led_create(lv_scr_act(), NULL);
    lv_obj_align(led1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_led_set_bright(led1, 200);
}
