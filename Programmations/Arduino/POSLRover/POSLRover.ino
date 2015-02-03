;;/*
                    POSL Rover

    Debut de programmation 30/01/2015 Par Almisuifre
*/

/* -- INCLUDES -- */
#include "Servo.h"
#include "Dri2.h"

/* -- DEFINE -- */
#define ServoAvG  2    //Servo (avant gauche) sur patte 2
#define ServoArG  3    //Servo (arrière gauche) sur patte 3
#define ServoAvD  4    //Servo (avant droit) sur patte 4
#define ServoArD  5    //Servo (arrière droit) sur patte 5

#define PWM_MAvG  6    //PWM sur sortie 6 (avant gauche) -> E1
#define SEN_MAvG  22   //Sens sur sortie 22 (avant gauche)  -> M1

#define PWM_MAvD  7    //PWM sur sortie 7 (avant gauche) -> E2
#define SEN_MAvD  24   //Sens sur sortie 24 (avant gauche)  -> M2


/* -- INSTANCIATIONS -- */
Servo ServoAvantGauche;  //Servomoteur avant gauche
Servo ServoArrieGauche;  //Servomoteur arriere gauche

Servo ServoAvantDroit;  //Servomoteur avant droit
Servo ServoArrieDroit;  //Servomoteur arriere droit

Dri2 MoteurAvantGauche(SEN_MAvG, PWM_MAvG);
Dri2 MoteurAvantDroit(SEN_MAvD, PWM_MAvD);

void setup() {
  ServoAvantGauche.attach(ServoAvG);     //Attache la pin 2 au servomoteur
  ServoArrieGauche.attach(ServoArG);     //Attache la pin 3 au servomoteur
  ServoAvantDroit.attach(ServoAvD);      //Attache la pin 4 au servomoteur
  ServoArrieDroit.attach(ServoArD);      //Attache la pin 5 au servomoteur
  
  ServoAvantGauche.write(90);
  ServoArrieGauche.write(90);
  ServoAvantDroit.write(90);
  ServoArrieDroit.write(90);
}

void loop() {
  
  for(int i = 1; i <= 2; i++) {
    
    switch(i) {
      case 1:
        
        MoteurAvantGauche.Action(0, 50);
        delay(150);
        MoteurAvantGauche.Action(0, 100);
        delay(150);
        MoteurAvantGauche.Action(0, 0);
        delay(300);
        
        MoteurAvantGauche.Action(1, 50);
        delay(150);
        MoteurAvantGauche.Action(1, 100);
        delay(150);
        MoteurAvantGauche.Action(1, 0);
        delay(300);
        
        break;
        
      case 2:
        
        MoteurAvantDroit.Action(0, 50);
        delay(150);
        MoteurAvantDroit.Action(0, 100);
        delay(150);
        MoteurAvantDroit.Action(0, 0);
        delay(300);
        
        MoteurAvantDroit.Action(1, 50);
        delay(150);
        MoteurAvantDroit.Action(1, 100);
        delay(150);
        MoteurAvantDroit.Action(1, 0);
        delay(300);
        
        break;
    }
  }
  /*
  for(int i = 0; i < 179; i++) {
     ServoAvantGauche.write(i);
     ServoArrieGauche.write(i);
     ServoAvantDroit.write(i);
     ServoArrieDroit.write(i);
     
     delay (15);
  }
  for(int j = 179; j > 0; j--) {
     ServoAvantGauche.write(j);
     ServoArrieGauche.write(j);
     ServoAvantDroit.write(j);
     ServoArrieDroit.write(j);
     delay (15);
  }
  */
}
