#include "main.h"
#include "display.h"
#include <string.h>
#include "display/lvgl.h"
string Rdist;
lv_obj_t * btn2;
lv_obj_t * btnLeftAuto;
lv_obj_t * btnRightAuto;
lv_obj_t * btnSkillsAuto;
lv_obj_t * labelA;
lv_obj_t * labelBTEST;
lv_obj_t * TESTTEST;
lv_obj_t * sys_battery_meter;
lv_obj_t * battery_text;
lv_obj_t * tabs = lv_tabview_create(lv_scr_act(), NULL);
lv_obj_t * main_tab = lv_tabview_add_tab(tabs, "MAIN");
lv_obj_t * adv_tab = lv_tabview_add_tab(tabs, "ADV/DIAG");
lv_obj_t * auto_tab = lv_tabview_add_tab(tabs, "AUTO");
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

  btnSkillsAuto = lv_btn_create(adv_tab, NULL);
  lv_obj_set_size(btnSkillsAuto, 150, 40);
  lv_obj_align(btnSkillsAuto, NULL, LV_ALIGN_CENTER, -20, 50);
  labelBTEST = lv_label_create(btnSkillsAuto, NULL);
  lv_label_set_text(labelBTEST, "Auto SKILLS");
  lv_btn_set_toggle(btnSkillsAuto, true);

  btnRightAuto = lv_btn_create(adv_tab, NULL);
  lv_obj_set_size(btnRightAuto, 150, 40);
  lv_obj_align(btnRightAuto, NULL, LV_ALIGN_CENTER, -20, 87);
  TESTTEST = lv_label_create(btnRightAuto, NULL);
  lv_label_set_text(TESTTEST, "R When On");
  lv_btn_set_toggle(btnRightAuto, true);
}

void Display::refresh(void)
{
  ////////////////////////////////////////
  if (lv_btn_get_state(btnSkillsAuto) >= 1){
    AUTOState = 1;
  }
  else if (lv_btn_get_state(btnRightAuto) >= 1 && lv_btn_get_state(btnSkillsAuto) == 0){
    AUTOState = 2; //RIGHT AUTO
  }
  else if (lv_btn_get_state(btnRightAuto) == 0 && lv_btn_get_state(btnSkillsAuto) == 0){
    AUTOState = 3; //LEFT AUTO
  }
  else{
    AUTOState = 0;
  }
  /////////////////////////////////
  if (lv_btn_get_state(btn2) >= 1){
    pros::delay(3000);
    lv_led_on(led1);
    RECState = 1;
  }
  else{
    lv_led_off(led1);
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
