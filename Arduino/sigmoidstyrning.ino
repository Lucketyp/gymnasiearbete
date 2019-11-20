const int LM = 9;
const int RM = 3;

#define LMF 13
#define LMR 12
#define RMF 11
#define RMR 10
#define sensor1 A3 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
#define sensor2 A4
#define sensor3 A5

byte sensors[] = {sensor1, sensor2, sensor3};
float volts[3];

void setup() {
  pinMode(13,OUTPUT);   //left motors forward
  pinMode(12,OUTPUT);   //left motors reverse
  pinMode(11,OUTPUT);   //right motors forward
  pinMode(10,OUTPUT);   //right motors reverse
  pinMode(LM,OUTPUT);   //PWM PIN
  pinMode(RM,OUTPUT);   //PWM PIN
  
  Serial.begin(115200);
}

void loop() {
 
}

void drive(uint8_t LMFVAL, uint8_t LMRVAL, uint8_t RMFVAL, uint8_t RMRVAL){
  digitalWrite(LMF, LMFVAL);
  digitalWrite(LMR, LMRVAL);
  digitalWrite(RMF, RMFVAL);
  digitalWrite(RMR, RMRVAL);
}

float Activation(float x){
  float activatedValue = 1 / (1 + exp(-1 * x));
  return activatedValue;
}

void steer (float Kval) {

  drive(HIGH, LOW, HIGH, LOW); // kör framåt 
  float k = Activation(Kval) - 0.5f;
  if (k > 0) {
    int steering = k * 255 * 2; // Max värde blir 255
    analogWrite(RM, 150); // Andra motors spänning är konstant
    analogWrite(LM, steering);// Ändrar motors spänning
  } else if (k < 0) {
    int steering = k * 255 * 2 * -1; // * -1 då värdet måste vara positivt
    analogWrite(RM, steering); 
    analogWrite(LM, 150);
   
  }
}

void getSensors () {
  int distance[3];
  for (int i = 0; i < sizeof(sensors); i+=1) {
    volts[i] = analogRead(sensors[i]) * 0.0048828125; // Värde från sensor * konstant
    distance[i] = 13*pow(volts[i], -1); // uträknat från indiern på youtube
  }
  return distance;
}

  
