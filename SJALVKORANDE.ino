char t;

const int LMVOLTAGE = 9;
const int RMVOLTAGE = 3;
int LMVOLTAGEVAL = 150;
int RMVOLTAGEVAL = 150;

#define LMF 13
#define LMR 12
#define RMF 11
#define RMR 10

void setup() {
  pinMode(13,OUTPUT);   //left motors forward
  pinMode(12,OUTPUT);   //left motors reverse
  pinMode(11,OUTPUT);   //right motors forward
  pinMode(10,OUTPUT);   //right motors reverse
  pinMode(LMVOLTAGE,OUTPUT);   //PWM PIN
  pinMode(RMVOLTAGE,OUTPUT);   //PWM PIN
  
  Serial.begin(9600);
}

void drive(uint8_t LMFVAL, uint8_t LMRVAL, uint8_t RMFVAL, uint8_t RMRVAL){
  digitalWrite(LMF, LMFVAL);
  digitalWrite(LMR, LMRVAL);
  digitalWrite(RMF, RMFVAL);
  digitalWrite(RMR, RMRVAL);
}



void loop() {
 
  if(Serial.available() > 0){
    t = Serial.read();
    Serial.println(t);
  }
  
  if(t == '1'){          //move reverse(all motors rotate in forward direction)
    drive(HIGH, LOW, HIGH, LOW);
    LMVOLTAGEVAL = 150;
    RMVOLTAGEVAL = 150;
  }
  
  else if(t == '2'){    //move forward (all motors rotate in reverse direction)
    drive(LOW, HIGH, LOW, HIGH);
    LMVOLTAGEVAL = 150;
    RMVOLTAGEVAL = 150;
    
  }
  
  else if(t == '3'){    //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
    drive(LOW, HIGH, LOW, HIGH);
    LMVOLTAGEVAL += 5;
    RMVOLTAGEVAL -= 5;
    if (LMVOLTAGEVAL > 150) {
      LMVOLTAGEVAL = 150;
    }
    if (RMVOLTAGEVAL < 0) {
      RMVOLTAGEVAL = 0;
    }
    Serial.print("RMVOLTAGEVAL: ");
    Serial.print(RMVOLTAGEVAL);
    Serial.print("    LMVOLTAGEVAL: ");
    Serial.print(LMVOLTAGEVAL);
    Serial.println();
    
    delay(100);
  }
  
  else if(t == '4'){    //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
    drive(LOW, HIGH, LOW, HIGH);
    LMVOLTAGEVAL -= 5;
    RMVOLTAGEVAL += 5;
    if (RMVOLTAGEVAL > 150) {
      RMVOLTAGEVAL = 150;
    }
    if (LMVOLTAGEVAL < 0) {
      LMVOLTAGEVAL = 0;
    }
    Serial.print("RMVOLTAGEVAL: ");
    Serial.print(RMVOLTAGEVAL);
    Serial.print("    LMVOLTAGEVAL: ");
    Serial.print(LMVOLTAGEVAL);
    Serial.println();
    delay(100);
  }
   
  else if(t == '5'){    //STOP (all motors stop)
    digitalWrite(LMF,LOW);
    digitalWrite(LMR,LOW);
    digitalWrite(RMF,LOW);
    digitalWrite(RMR,LOW);
  }
  else if(t == '6'){  // SPINNYBOI
    drive(LOW, HIGH, HIGH, LOW); 
    RMVOLTAGEVAL = 255;
    LMVOLTAGEVAL = 255;
  }
  
  analogWrite(LMVOLTAGE, LMVOLTAGEVAL);
  analogWrite(RMVOLTAGE, RMVOLTAGEVAL);
}
