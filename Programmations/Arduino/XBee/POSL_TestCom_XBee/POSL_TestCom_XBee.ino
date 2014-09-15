/*
  Test Communication bi directionnel
*/

String content = "";

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Si on a reçu des données sur la liaison série     
  if(Serial.available() > 0) {
    
    char inData;
    content = "";
    
    while(Serial.available()>0){
      inData = Serial.read();
      content.concat(inData);
    }
    
    Serial.flush();
  }
  
  if(content > 0) {
    //Renvoyer les données
    Serial.println(content);
    
    content = "";
  } 
  
  delay(150);
}
