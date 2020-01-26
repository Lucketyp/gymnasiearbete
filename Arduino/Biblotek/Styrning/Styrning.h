#ifndef Styrning_h
#define Styrning_h

#include "Arduino.h"

class Styrning 
{
  public:
  Styrning();
  void steer(float steering);
  
  private:
  void drive(uint8_t LMFVAL, uint8_t LMRVAL, uint8_t RMFVAL, uint8_t RMRVAL);
  const int LMF = 12;
  const int LMR = 13;
  const int RMF = 10;
  const int RMR = 11;
  const int LM = 9;
  const int RM = 3;

  const int baseDrive = 100;
  const int addedDrive = 155;
//bDrive+aDrive = 255
  
};

#endif