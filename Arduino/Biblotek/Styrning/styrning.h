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
  const int LMF = 13;
  const int LMR = 12;
  const int RMF = 11;
  const int RMR = 10;
  const int LM = 9;
  const int RM = 3;
};

#endif
