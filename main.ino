#include <Wire.h>
#include <DS1307.h>
#include <math.h>

DS1307 clock;

int lum;
int h;
boolean eclairement;

uint8_t voie1 = 2;
uint8_t voie2 = 3;
int sensorPin = A2;     // Capteur d'humidité branché sur A2
int sensorValue = 0;    // Définition de la variable sensorValue
int pinTempSensor = A0; // Capteur de température connécté à A0

int B = 4275;      // B valeur de la thermistance du capteur
float R0 = 100000; // R0 = 100k

void setup()
{
  //eau
  pinMode(voie2, OUTPUT);
  voie2 == LOW;
  Serial.begin(9600); // Initialisation de la vitesse du moniteur série
  //éclairement
  pinMode(A3, INPUT);
  pinMode(7, OUTPUT);
  clock.begin();
  clock.fillByYMD(2013, 1, 19); //Permet d'initialiser le jours, le mois et l'année
  clock.fillByHMS(8, 59, 00);   //Initialise l'heure la minute la seconde
  clock.setTime();              //Envoi les données d'initialisation dans le module RTC
  pinMode(voie1, OUTPUT);
  voie1 == LOW;
  Serial.begin(9600); // Initialisation de la vitesse du moniteur série
                      // Faire Ctrl+Maj+M pour afficher le moniteur série
}

void loop()
{
  clock.getTime();                     // Lecture de l'heure courante du module RTC
  h = clock.hour;                      // Affecte la valeur de l'heure à la variable h
  sensorValue = analogRead(sensorPin); // On affecte la valeur issue du capteur à la variable SensorValue
  lum = analogRead(A3);
  int a = analogRead(pinTempSensor);
  float R = 1023.0 / a - 1.0;
  R = R0 * R;
  float temperature = 1.0 / (log(R / R0) / B + 1 / 298.15) - 273.15; // Conversion de la mesure en valeur de température
  Serial.print("Temperature = ");
  Serial.println(temperature);
  delay(1000);
  Serial.print("Luminosite="); // Affichage de la valeur fournie par le capteur
  Serial.println(lum);         // Affichage de la valeur issue du capteur
  Serial.print("Humidité = ");
  Serial.println(sensorValue); // Affichage de la valeur issue du capteur
  Serial.println(h);           // Affiche la valeur de h dans le moniteur série
  Serial.println(clock.minute);
  Serial.println("------------------");
  delay(3000);

  delay(1000);
  if (sensorValue <= 550)
  {
    digitalWrite(voie2, HIGH);
  }
  else
  {
    digitalWrite(voie2, LOW);
  }

  if (h >= 6 && h <= 20)
  {
    eclairement = true;
  }
  else
  {
    eclairement = false;
  }

  if (lum < 200 && eclairement == true)
  {
    //digitalWrite(7,HIGH);
    Serial.println("allumé");
  }
  else
  {
    //digitalWrite(7,LOW);
    Serial.println("étein");
  }
  if (temperature > 26)
  {
    digitalWrite(voie1, HIGH);
  }
  delay(5000);
}
