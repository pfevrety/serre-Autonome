
int bouton = 4;   //Bouton poussoir sur entrée 4 permettant de tester le bon fonctionnement du relais
uint8_t voie1 = 2;
uint8_t voie2 = 3;
#include <math.h>
int B = 4275;               // B valeur de la thermistance du capteur
float R0 = 100000;          // R0 = 100k
int pinTempSensor = A0;     // Capteur de température connécté à A0


void setup() {
pinMode(bouton, INPUT);
pinMode(voie1, OUTPUT);
voie1 == LOW;
    Serial.begin(9600);   // Initialisation de la vitesse du moniteur série
                          // Faire Ctrl+Maj+M pour afficher le moniteur série
}

void loop() {
  
  int a = analogRead(pinTempSensor);
  float R = 1023.0/a-1.0;
  R = R0*R;
  float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // Conversion de la mesure en valeur de température
  Serial.print("temperature = ");
  Serial.println(temperature);
  delay(1000);
  if(temperature > 26){
    if (digitalRead(bouton) == HIGH) {
      digitalWrite(voie1, HIGH);

    } else {
      digitalWrite(voie1, LOW);
  }
  }

}
