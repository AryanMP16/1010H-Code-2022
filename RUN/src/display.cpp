#include "main.h"
#include "display.h"
#include <string.h>
#include "display/lvgl.h"

lv_obj_t*led1;

void Display::lv_ex_led_1(void) {
    led1 = lv_led_create(lv_scr_act(), NULL);
    lv_obj_align(led1, NULL, LV_ALIGN_CENTER, 0, 0);
}

void Display::refresh(void)
{
  if(master.get_digital(DIGITAL_A)){lv_led_on(led1);}
  else{lv_led_off(led1);}
  delay(10);
}

void Display::createScreen(void)
{
  lv_theme_t * theme = lv_theme_nemo_init(0, NULL); //60 For TTYellow
  lv_theme_set_current(theme);
  lv_ex_led_1();
}
