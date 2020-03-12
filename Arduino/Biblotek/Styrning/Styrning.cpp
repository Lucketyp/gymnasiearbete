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

	//Kör funktionen ska bli mellan 0 och 255
	//100 och 250
	//Just nu är min 0.45 max 0.65
  drive(HIGH, LOW, HIGH, LOW); // kör framåt 
  float k = steering - 0.45f;
  int a = k * addedDrive + m; // Max värde blir 255
	if (k > 0.1) {
    analogWrite(RM, baseDrive); // Andra motors spänning är konstant
    analogWrite(LM, a);// Ändrar motors spänning
  } else if (k < 0.1) {
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