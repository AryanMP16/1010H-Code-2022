#pragma once
#include "main.h"
using namespace pros;

class dpidClass{ //drive PID class
public:
  void stop(void); //stop function
  void movePID(int direction, int target, int timeout, int cap); //function for autonomous PID drive
  void strafePID(int direction, int target, int timeout, int cap); //PID strafe
  void turnPID(int direction, int target, int timeout); //PID turn
};

class opClass{ //operator control class
public:
    void opControl(void); //op control drive (expo drive)
    //void moveAt (Motor motor, int accFactor, int velCap);
    void temperatureControl(void); //temperature control function
    void Rollers(void); //roller function
    void ClawR(void); //right claw function
    void ClawL(void); //left claw function
};

double getVelocity(Motor motor); //for getting motor velocity
void AccTask_fn(void*par); //task for motor acceleration
int getTemperature(Motor motor); //for getting motor temperature
