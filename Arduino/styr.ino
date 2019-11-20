

float Activation(float x){
    float activatedValue = 1 / (1 + exp(-1 * x));
    return activatedValue;
  }

void steer (float Kval) {

  drive(HIGH, LOW, HIGH, LOW); // kör framåt 
  float k = Activation(Kval) - 0.5f;
  if (k > 0) {
    int steering = k * 255 * 2; // Max värde blir 255
    analogWrite(RMVOLTAGE, 150); // Andra motors spänning är konstant
    analogWrite(LMVOLTAGE, steering);// Ändrar motors spänning
  } else if (k < 0) {
    int steering = k * 255 * 2 * -1; // * -1 då värdet måste vara positivt
    analogWrite(RMVOLTAGE, steering); 
    analogWrite(LMVOLTAGE, 150);
   
  }
}
