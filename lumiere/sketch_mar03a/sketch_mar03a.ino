

#include <Wire.h>
#include <DS1307.h>
int lum;
DS1307 clock;
int h; 
boolean eclairement; 


void setup()
{
  Serial.begin(9600); 
  pinMode(A3, INPUT); 
  pinMode(7, OUTPUT);
  clock.begin() ;
  clock.fillByYMD(2013,1,19);//Permet d'initialiser le jours, le mois et l'année
  clock.fillByHMS(8,59,00);//Initialise l'heure la minute la seconde
  clock.setTime();//Envoi les données d'initialisation dans le module RTC
}

void loop()
{
  lum =analogRead(A3);
  Serial.print("Luminosite="); // Affichage de la valeur fournie par le capteur
  Serial.println(lum); // Faire Ctrl+Maj+M pour afficher le moniteur série
  delay(1000);  
  clock.getTime(); // Lecture de l'heure courante du module RTC
  h=clock.hour; // Affecte la valeur de l'heure à la variable h
  Serial.println(h); // Affiche la valeur de h dans le moniteur série
  Serial.println(clock.minute); 

    if (h >= 6 && h <= 20) { 
       eclairement = true;
      } else {
       eclairement = false;
      }
 
 
  if(lum < 200 && eclairement== true){
    //digitalWrite(7,HIGH);
    Serial.println("allumé");
  }  else{
   //digitalWrite(7,LOW);
    Serial.println("étein");
  }
  delay(1000); 
}
