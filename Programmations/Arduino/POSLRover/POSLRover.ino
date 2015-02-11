/*
                    POSL Rover

    Debut de programmation 30/01/2015 Par Almisuifre
    Aide à la programmation Phil
    
    Les instructions sont basés sur le format CSV.
    Exemples (moteur):
          dir,vitesseAVG,dir,vitesseARG,dir,vitesseAVD,dir,vitesseARG
      !,1,0,0,0,0,0,0,0,0,* = STOP
      !,1,1,100,1,100,1,100,1,100,* = Moteurs Marche AV
      !,1,0,100,0,100,0,100,0,100,* = Moteurs Marche AR
      
    Exemples (Directions):
          AVG,ARG,AVD,ARD
      !,2,90,90,90,90,*  = Roues au centre
      !,2,70,110,70,110,*  = Roues permettant de tourner à gauche
      !,2,110,70,110,70,* = Roues permettant de tournet à droite
      !,2,70,70,70,70,*  = En diagonale gauche
      !,2,110,110,110,110,*  = En diagonale droite
      !,2,140,40,40,140,*  = Tourner sur place
      
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

#define BUFFER_SIZE          11  // Taille du buffer de données  // basé sur ! , instruction(int) , 90 , 90 , 90 , 90 , 90, 90, 90, 90, *
#define START_CHAR           '!' // caractere de début
#define STOP_CHAR            '*' // caractere de fin
#define SEP_CHAR             ',' // caractere de séparation
#define INSTRUCTION_MOTEURS  1   // instruction moteur
#define INSTRUCTION_DIR      2   // instruction direction

#define SERVO_CENTRE_AVG  88
#define SERVO_CENTRE_ARG  94
#define SERVO_CENTRE_AVD  90
#define SERVO_CENTRE_ARD  94

/* -- INSTANCIATIONS -- */
Servo ServoAvantGauche;  //Servomoteur avant gauche
Servo ServoArrieGauche;  //Servomoteur arriere gauche

Servo ServoAvantDroit;  //Servomoteur avant droit
Servo ServoArrieDroit;  //Servomoteur arriere droit

Dri2 MoteurAvantGauche(SEN_MAvG, PWM_MAvG);
Dri2 MoteurAvantDroit(SEN_MAvD, PWM_MAvD);
Dri2 MoteurArriereGauche(SEN_MArG, PWM_MArG);
Dri2 MoteurArriereDroit(SEN_MArD, PWM_MArD);

/* -- VARIABLES -- */
char  buffer[BUFFER_SIZE];                  // String buffer 
boolean transmissionTerminee = false; // Boolean qui indique que la transmission est terminée
int index = 0;
char a;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

/* -- SETUP -- */
void setup() {
  
  //Connexion série
  Serial.begin(9600);    //Port USB utilisé en mode débug
  Serial1.begin(9600);   //Port série utilisé par le XBeePro
  
  ServoAvantGauche.attach(ServoAvG);     //Attache la pin 2 au servomoteur
  ServoArrieGauche.attach(ServoArG);     //Attache la pin 3 au servomoteur
  ServoAvantDroit.attach(ServoAvD);      //Attache la pin 4 au servomoteur
  ServoArrieDroit.attach(ServoArD);      //Attache la pin 5 au servomoteur
  
  //Fixe la position au centre
  ServoAvantGauche.write(SERVO_CENTRE_AVG);
  ServoArrieGauche.write(SERVO_CENTRE_ARG);
  ServoAvantDroit.write(SERVO_CENTRE_AVD);
  ServoArrieDroit.write(SERVO_CENTRE_ARD);
  
  inputString.reserve(200);
}

/* -- LOOP -- */
void loop() {
  
  if (stringComplete) {
    // TRES MOCHE : on compte le nombre de START_CHAR pour savoir si on a pas 2 (voir plus) trame concaténée par erreur
    int firstStartChar = inputString.indexOf(START_CHAR);
    int secondStartChar = inputString.indexOf(START_CHAR, firstStartChar + 1);
    
    if(firstStartChar == 0 && secondStartChar == -1)
    {
      traitementMessage(inputString);
    } 
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  
  while (Serial.available()) {
    
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == STOP_CHAR) {
      stringComplete = true;
    }
    Serial.flush();  //Nettoyage de buffer
  }
}


void serialEvent1() {
  
  while (Serial1.available()) {
    
    // get the new byte:
    char inChar = (char)Serial1.read();
    // add it to the inputString:
    inputString += inChar;
    
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == STOP_CHAR) {
      stringComplete = true;
    }
    Serial1.flush();  //Nettoyage de buffer
  }
}

void traitementMessage(String message)
{
  /*
  Exemples (moteur):
          dir,vitesseAVG,dir,vitesseARG,dir,vitesseAVD,dir,vitesseARG
      !,1,0,0,0,0,0,0,0,0,* = STOP
      !,1,1,100,1,100,1,100,1,100,* = Moteurs Marche AV
      !,1,0,100,0,100,0,100,0,100,* = Moteurs Marche AR
      
      !,1,2,102,3,103,4,104,5,105,*
      
    Exemples (Directions):
          AVG,ARG,AVD,ARD
      !,2,90,90,90,90,*  = Roues au centre
      !,2,70,110,70,110,*  = Roues permettant de tourner à gauche
      !,2,110,70,110,70,* = Roues permettant de tournet à droite
      !,2,70,70,70,70,*  = En diagonale gauche
      !,2,110,110,110,110,*  = En diagonale droite
      !,2,140,40,40,140,*  = Tourner sur place
  */
  String data;
  int instruction = 0;
  int data1 = 0, data2 = 0, data3 = 0, data4 = 0, data5 = 0, data6 = 0, data7 = 0, data8 = 0; 
  int index = 0, index2 = 0;
  
  int positionServoAvG = SERVO_CENTRE_AVG;
  int positionServoArG = SERVO_CENTRE_ARG;
  int positionServoAvD = SERVO_CENTRE_AVD;
  int positionServoArD = SERVO_CENTRE_ARD;
  
  // On récupère l'instruction
  index   = message.indexOf(SEP_CHAR);
  index2  = message.indexOf(SEP_CHAR, index +1);
  data    = message.substring(index +1 , index2);
  message = message.substring(index2 +1 );
  
  instruction = data.toInt();
  
  switch (instruction)
  {
    case INSTRUCTION_MOTEURS :
      for(int i = 0; i < 8; i++)
      {
        index = message.indexOf(SEP_CHAR);
        data = message.substring(0, index);
        message = message.substring(index+1);
        
        if(i == 0) data1 = data.toInt();
        if(i == 1) data2 = data.toInt();
        if(i == 2) data3 = data.toInt();
        if(i == 3) data4 = data.toInt();        
        if(i == 4) data5 = data.toInt();
        if(i == 5) data6 = data.toInt();
        if(i == 6) data7 = data.toInt();
        if(i == 7) data8 = data.toInt();     
      }
      
      MoteurAvantGauche.Action(data1, data2);
      MoteurAvantDroit.Action(data3, data4);
      MoteurArriereGauche.Action(data5, data6);
      MoteurArriereDroit.Action(data7, data8);

      
      break;
  
    case INSTRUCTION_DIR :
      for(int i = 0; i < 4; i++)
      {
        index = message.indexOf(SEP_CHAR);
        data = message.substring(0, index);
        message = message.substring(index+1);
        
        if(i == 0) data1 = data.toInt();
        if(i == 1) data2 = data.toInt();
        if(i == 2) data3 = data.toInt();
        if(i == 3) data4 = data.toInt();            
      }
      
      positionServoAvG = ((data1 * SERVO_CENTRE_AVG)/90);
      positionServoArG = ((data2 * SERVO_CENTRE_ARG)/90);
      positionServoAvD = ((data3 * SERVO_CENTRE_AVD)/90);
      positionServoArD = ((data4 * SERVO_CENTRE_ARD)/90);
      
      ServoAvantGauche.write(positionServoAvG);
      ServoArrieGauche.write(positionServoArG);
      ServoAvantDroit.write(positionServoAvD);
      ServoArrieDroit.write(positionServoArD);
      break;
  }
}
