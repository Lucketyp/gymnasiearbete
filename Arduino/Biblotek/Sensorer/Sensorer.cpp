#include "Arduino.h"
#include "Sensorer.h"

Sensorer::Sensorer(byte _sensors[3])
{
  for(int i = 0; i < 3; i++) {
    sensors[i] = _sensors[i];
  }
}

void Sensorer::readSensors() 
{
   for (int i = 0; i < sizeof(sensors); i+=1) {
    volts[i] = analogRead(sensors[i]) * 0.0048828125; // V�rde fr�n sensor * konstant
    distance[i] = 13*pow(volts[i], -1); // utr�knat fr�n indiern p� youtube
      if (distance[i] < 30 && distance[i] != 0) {
        inputDis[i] = 1 - distance[i]/30; //Ger v�rde mellan 1 och 0 
      } else {
        inputDis[i] = 0;
      }
   }
}