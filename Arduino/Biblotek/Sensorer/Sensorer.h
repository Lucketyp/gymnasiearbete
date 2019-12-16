#ifndef Sensorer_h
#define Sensorer_h

#include "Arduino.h"

class Sensorer 
{
  public:
  Sensorer(byte _sensors[3]);
  void readSensors();
  float inputDis[3];
  
  private:
  float volts[3];
  float distance[3];
  byte sensors[3];
};

 #endif