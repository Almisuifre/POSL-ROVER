/*
    CONFIGURATION DU RECSEAU

    XBee0
    ATMY9990  //Adresse source
    ATDL9991  //Adresse destination (bit de poids faible)
    ATDH0     //Adresse destination (bit de poids fort)
    ATID8756  //Identifiant du réseau
    
    XBee1
    ATMY9991  //Adresse source
    ATDL9990  //Adresse destination (bit de poids faible)
    ATDH0     //Adresse destination (bit de poids fort)
    ATID8756  //Identifiant du réseau
*/

void setup() {
  Serial.begin(9600);
  XBeeConf(0);
}

void loop() {
  delay(1000);
  Serial.print("42\n");
}

void XBeeConf (int num){
  Serial.print("+++");  //Initialisation de la configuration
  
  if(num == 0) {
    Serial.print("ATDH0\r");     //Adresse destination (bit de poids fort
    Serial.print("ATDL9991\r");  //Adresse destination (bit de poids faible)
    Serial.print("ATMY9990\r");  //Adresse source
    Serial.print("ATDID8756\r"); //Identifiant du réseau
  }
  else if(num == 1) {
    Serial.print("ATDH0\r");     //Adresse destination (bit de poids fort
    Serial.print("ATDL9990\r");  //Adresse destination (bit de poids faible)
    Serial.print("ATMY9991\r");  //Adresse source
    Serial.print("ATDID8756\r"); //Identifiant du réseau
  }
  
  Serial.print("ATCN\r");  //Sortir su mode de configuration 
}
