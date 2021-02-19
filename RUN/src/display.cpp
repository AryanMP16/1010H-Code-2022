#include "main.h"
#include "display.h"
#include <string.h>

lv_obj_t * battery_meter;

void Display::createImage(){};
void Display::screenRefresh(){
  delay(10);
};

void Display::createScreen(void){
  lv_theme_t * theme = lv_theme_nemo_init(40, NULL); //60 For TTYellow
  lv_theme_set_current(theme);
  createTitle();
  linemeter();
};

void Display::createTitle(void){
  /*lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label1, "1010H 2021");
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);*/
};

void Display::linemeter(void)
{
    lv_obj_t * lmeter;
    lmeter = lv_lmeter_create(lv_scr_act(), NULL);
    lv_lmeter_set_range(lmeter, 0, 100);
    lv_lmeter_set_value(lmeter, 80);
    lv_lmeter_set_scale(lmeter, 240, 21);
    lv_obj_set_size(lmeter, 150, 150);
    lv_obj_align(lmeter, NULL, LV_ALIGN_CENTER, 0, 0);
}
