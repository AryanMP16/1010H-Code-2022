#pragma once
#include "main.h"
using namespace pros;

class dpidClass{
public:
  void stop(void);
  void movePID(int direction, int target, int timeout, int cap);
  void strafePID(int direction, int target, int timeout, int cap);
  void turnPID(int direction, int target, int timeout);
};

class opClass{
public:
    void opControl(void);
    void moveAt (Motor motor, int accFactor, int velCap);
};

double getVelocity(Motor motor);
void AccTask_fn(void*par);
