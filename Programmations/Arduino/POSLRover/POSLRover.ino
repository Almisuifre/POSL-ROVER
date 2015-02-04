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

#define PWM_MAvG  6    //PWM sur sortie 6 (avant gauche) -> E1 Carte 1
#define SEN_MAvG  22   //Sens sur sortie 22 (avant gauche)  -> M1 Carte 1

#define PWM_MAvD  7    //PWM sur sortie 7 (avant gauche) -> E2 Carte 1
#define SEN_MAvD  24   //Sens sur sortie 24 (avant gauche)  -> M2 Carte 1

#define PWM_MArG  8    //PWM sur sortie 8 (arrière gauche) -> E1 Carte 2
#define SEN_MArG  23   //Sens sur sortie 23 (arrière gauche)  -> M1 Carte 2

#define PWM_MArD  9    //PWM sur sortie 9 (arrière gauche) -> E2 Carte 2
#define SEN_MArD  25   //Sens sur sortie 25 (arrière gauche)  -> M2 Carte 2


/* -- INSTANCIATIONS -- */
Servo ServoAvantGauche;  //Servomoteur avant gauche
Servo ServoArrieGauche;  //Servomoteur arriere gauche

Servo ServoAvantDroit;  //Servomoteur avant droit
Servo ServoArrieDroit;  //Servomoteur arriere droit

Dri2 MoteurAvantGauche(SEN_MAvG, PWM_MAvG);
Dri2 MoteurAvantDroit(SEN_MAvD, PWM_MAvD);
Dri2 MoteurArriereGauche(SEN_MArG, PWM_MArG);
Dri2 MoteurArriereDroit(SEN_MArD, PWM_MArD);

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
  
  /*
  //Centrage numérique 90°
  ServoAvantGauche.write(88);
  ServoArrieGauche.write(94);
  ServoAvantDroit.write(94);
  ServoArrieDroit.write(90);
  delay (20);
  */
  
  /*
  //Test direct moteurs
  MoteurAvantGauche.Action(0, 50);
  MoteurAvantDroit.Action(0, 50);
  MoteurArriereGauche.Action(0, 50);
  MoteurArriereDroit.Action(0, 50);
  delay(200);
  */
  
  /*
  //Test moteurs
  for(int i = 1; i <= 4; i++) {
    
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
      
      case 3:
        
        MoteurArriereGauche.Action(0, 50);
        delay(150);
        MoteurArriereGauche.Action(0, 100);
        delay(150);
        MoteurArriereGauche.Action(0, 0);
        delay(300);
        
        MoteurArriereGauche.Action(1, 50);
        delay(150);
        MoteurArriereGauche.Action(1, 100);
        delay(150);
        MoteurArriereGauche.Action(1, 0);
        delay(300);
        
        break;
      
      case 4:
        
        MoteurArriereDroit.Action(0, 50);
        delay(150);
        MoteurArriereDroit.Action(0, 100);
        delay(150);
        MoteurArriereDroit.Action(0, 0);
        delay(300);
        
        MoteurArriereDroit.Action(1, 50);
        delay(150);
        MoteurArriereDroit.Action(1, 100);
        delay(150);
        MoteurArriereDroit.Action(1, 0);
        delay(300);
        
        break;
    }
  }
  */
  /*
  //Test Direction
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
