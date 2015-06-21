#include "Arduino.h"
#include "Dri2.h"

/* -- CONSTRUCTEUR -- */

Dri2::Dri2(int pin_pole, int pin_pwm) {
  pinMode(pin_pole, OUTPUT);		//M en sortie
  pinMode(pin_pwm, OUTPUT);		//E en sortie
  
  digitalWrite(pin_pole, LOW);	        //Sens 0 sur M
  analogWrite(pin_pwm, LOW);		//Pwm à 0 sur E
  
  _pin_pole = pin_pole;
  _pin_pwm = pin_pwm;

}

/* -- SETTER -- */

void Dri2::Action(int dir, int vitesse) {
  analogWrite(_pin_pwm, vitesse);
  
  if(dir) {
    digitalWrite(_pin_pole, HIGH);
  }
  else {
    digitalWrite(_pin_pole, LOW);
  }
}

/* -- FONCTIONS -- */
