#include "Arduino.h"
#include "Styrning.h"

Styrning::Styrning()
{ 
  pinMode(LMF,OUTPUT);   //left motors forward
  pinMode(LMR,OUTPUT);   //left motors reverse
  pinMode(RMF,OUTPUT);   //right motors forward
  pinMode(RMR,OUTPUT);   //right motors reverse
  pinMode(LM,OUTPUT);   //PWM PIN
  pinMode(RM,OUTPUT);   //PWM PIN	
}

void Styrning::steer (float steering) {

  drive(HIGH, LOW, HIGH, LOW); // kör framåt 
  float k = steering - 0.5f;
	if (k > 0) {
    int a = baseDrive + k * addedDrive * 2; // Max värde blir 255
    analogWrite(RM, baseDrive); // Andra motors spänning är konstant
    analogWrite(LM, a);// Ändrar motors spänning
  } else if (k < 0) {
    int a = baseDrive + k * addedDrive * 2 * -1; 
    analogWrite(RM, a); 
    analogWrite(LM, baseDrive);   
  }
}

void Styrning::drive(uint8_t LMFVAL, uint8_t LMRVAL, uint8_t RMFVAL, uint8_t RMRVAL){
  digitalWrite(LMF, LMFVAL);
  digitalWrite(LMR, LMRVAL);
  digitalWrite(RMF, RMFVAL);
  digitalWrite(RMR, RMRVAL);
}