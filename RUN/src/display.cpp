#include "main.h"
#include "display.h"
#include <string.h>

lv_obj_t*sys_battery_meter;
lv_obj_t*ledboi;

void Display::createImage(){};

void Display::createScreen(void){
  lv_theme_t * theme = lv_theme_nemo_init(40, NULL); //60 For TTYellow
  lv_theme_set_current(theme);
  createTitle();
  linemeter();
  lv_ex_led_1();
};

void Display::createTitle(void){
  /*lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label1, "1010H 2021");
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);*/
};

void Display::linemeter(void)
{
    sys_battery_meter = lv_lmeter_create(lv_scr_act(), NULL);
    lv_lmeter_set_range(sys_battery_meter, 0, 100);
    lv_lmeter_set_value(sys_battery_meter, 75);
    lv_lmeter_set_scale(sys_battery_meter, 240, 21);
    lv_obj_set_size(sys_battery_meter, 150, 150);
    lv_obj_align(sys_battery_meter, NULL, LV_ALIGN_CENTER, -110, 0);
    ///////////////
    lv_obj_t * symbol_label =  lv_label_create(sys_battery_meter, NULL);
    lv_label_set_text(symbol_label, "Bat Percent");
    lv_obj_align(symbol_label, NULL, LV_ALIGN_CENTER, 0, 0);
}

void Display::lv_ex_led_1(void)
{
    ledboi  = lv_led_create(lv_scr_act(), NULL);
		lv_obj_align(ledboi, NULL, LV_ALIGN_CENTER, 0, 0);
  }

void Display::refresh(){
  int batmeter = pros::battery::get_capacity();
  lv_lmeter_set_value(sys_battery_meter, batmeter);
  int ledthingy;
  if (master.get_digital(DIGITAL_A)){lv_led_on(ledboi);}
  else {lv_led_off(ledboi);}
  //lv_label_set_text(symbol_label, (std::to_string(batmeter)+"%").c_str()); //Caden Hewlet's mix
  delay(10);
};
