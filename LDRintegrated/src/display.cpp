#include "main.h"
#include "display.h"
#include <string.h>
#include "display/lvgl.h"
//UC Schools: Look at these files :)
string Rdist;
lv_obj_t * btn2;
lv_obj_t*labelA;
lv_obj_t * sys_battery_meter;
lv_obj_t * battery_text;
lv_obj_t * tabs = lv_tabview_create(lv_scr_act(), NULL);
lv_obj_t * main_tab = lv_tabview_add_tab(tabs, "MAIN");
lv_obj_t * adv_tab = lv_tabview_add_tab(tabs, "ADV/DIAG");
lv_obj_t * led1;

void Display::lv_ex_led_1(void) {
    led1 = lv_led_create(adv_tab, NULL);
    lv_obj_align(led1, NULL, LV_ALIGN_CENTER, -205, -200);
    lv_obj_set_size(led1, 95, 70);
}

void Display::linemeter(void){
    sys_battery_meter = lv_lmeter_create(main_tab, NULL);
    lv_lmeter_set_range(sys_battery_meter, 0, 100);                   /*Set the range*/
    lv_lmeter_set_scale(sys_battery_meter, 240, 21);                  /*Set the angle and number of lines*/
    lv_obj_set_size(sys_battery_meter, 150, 150);
    lv_obj_align(sys_battery_meter, NULL, LV_ALIGN_CENTER, -130, 0);

    battery_text = lv_label_create(sys_battery_meter, NULL);
    lv_obj_t * symbol_label =  lv_label_create(sys_battery_meter, NULL);
    lv_label_set_text(symbol_label, "Battery:");
    lv_obj_align(battery_text, sys_battery_meter, LV_ALIGN_CENTER, 0, 20);
    lv_obj_align(symbol_label, battery_text, LV_ALIGN_CENTER, 0, -20);
}

void Display::createTitle(void){
    lv_obj_t*label1 = lv_label_create(adv_tab, NULL);
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, -185, 33);
    lv_label_set_text(label1, "");
}

void Display::createImage(void){
  lv_obj_t * freemanboris = lv_img_create(main_tab, NULL);
  LV_IMG_DECLARE(borisfreeman);
  lv_img_set_src(freemanboris, & borisfreeman);
  lv_obj_align(freemanboris, NULL, LV_ALIGN_CENTER, 95, 0);
}

void Display::createButton(void){
  btn2 = lv_btn_create(adv_tab, NULL);

  lv_obj_set_size(btn2, 150, 40);
  lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, -20, 0);

  labelA = lv_label_create(btn2, NULL);
  lv_label_set_text(labelA, "Record ON");

  lv_btn_set_toggle(btn2, true);
}

void Display::refresh(void)
{
  //printf("%d\n", lv_btn_get_state(btn2));
  if (lv_btn_get_state(btn2) >= 1){
    int time = 0;
    RECState = 1;
  }
  else{
    RECState = 0;
  }

  int boi = pros::battery::get_capacity();
  lv_lmeter_set_value(sys_battery_meter, boi);
  lv_label_set_text(battery_text, (std::to_string(boi)+"%").c_str());  //Caden Hewlet's fix
  //lv_label_set_text(battery_text, (std::to_string(boi)+"%").c_str());
  delay(10);
}

void Display::createScreen(void) 
{
  lv_theme_t * theme = lv_theme_nemo_init(30, NULL); //60 For TTYellow
  lv_theme_set_current(theme);
  lv_ex_led_1();
  linemeter();
  createTitle();
  createImage();
  createButton();
}
