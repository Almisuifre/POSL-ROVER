#ifndef DRI2_H
#define DRI2_H

#include "Arduino.h"

//#define AVANCE 0
//#define ARRIERE 1

class Dri2 {
  
  public:
    
    Dri2(int pin_pole, int pin_pwm);
    void Action(int dir, int vitesse);
  
  private:
    int _pin_pole;
    int _pin_pwm;
};

#endif
