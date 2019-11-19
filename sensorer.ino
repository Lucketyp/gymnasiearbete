// Sharp IR GP2Y0A41SK0F Distance Test
// http://tinkcore.com/sharp-ir-gp2y0a41-skf/

#define sensor1 A3 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
#define sensor2 A4
#define sensor3 A5

byte sensors[] = {sensor1, sensor2, sensor3};
float volts[3];
int distance[3];

void setup() {
  Serial.begin(9600); // start the serial port
}

void loop() {
  
  // 5v

  for (int i = 0; i < sizeof(sensors); i+=1) {
    volts[i] = analogRead(sensors[i]) * 0.0048828125; // Värde från sensor * konstant
    distance[i] = 13*pow(volts[i], -1); // uträknat från indiern på youtube
      if (distance[i] < 30 && distance[i] != 0) {
        Serial.print("distance");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.println(distance[i]); // Måste skriva det på detta efterblivna sätt för att man kan inte addera strings till variabler i arduino
      }
      
  }
}
