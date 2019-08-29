// Motor 1
int enA = 3;
int in1 = 13;
int in2 = 12;

// Motor 2
int enB = 9;
int in3 = 11;
int in4 = 8;

// Controler
int upDown = 10;
int leftRight = 6;

int comp(int LR){
  int motor;
  if (LR > 1400 && LR < 1500){
    motor = 0;
  }
  else if (LR < 1400 ) 
  {
    motor = 1;
  }
  else if (LR > 1500 ) 
  {
    motor = 2;
  }
  return motor;
}


void setup() {
  Serial.begin(9600);     //open serial and set the baudrate
  // set all the motor control pins to outputs
   pinMode(enA, OUTPUT);
   pinMode(enB, OUTPUT);
   pinMode(in1, OUTPUT);
   pinMode(in2, OUTPUT);
   pinMode(in3, OUTPUT);
   pinMode(in4, OUTPUT);
   pinMode(upDown, INPUT);
   pinMode(leftRight, INPUT);
}

void loop() {
  int pwm1 = 0;
  int pwm2 = 0;
  int cmp = 0;
  int rc4 = pulseIn(upDown, HIGH, 25000);
  int LR = pulseIn(leftRight, HIGH, 25000);
  cmp = comp(LR);
   if (rc4 == 0)
  {
    Serial.println("No Signal");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
    else if(rc4 < 1530 && rc4 > 1370) //right stick upDown 
  {
    //Serial.println("Stop");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
  else if(rc4 > 1530) //right stick upDown 
  {
    pwm1 = map(rc4, 1530, 1970, 0, 255); //map our speed to 0-255 range
    if (cmp == 0)
    {
      pwm1 = map(rc4, 1530, 1970, 0, 255);
      pwm2 = pwm1;
    }
    else if (cmp == 1)
    {
      int first = map(rc4, 1530, 1970, 0, 255);
      int second = map(LR, 1370, 900, 0, 255);
      pwm1 = first - second; 
      if (pwm1 < 0){pwm1 = 0;}
      pwm2 = map(rc4, 1370, 900, 0, 255);
      Serial.println("comp = 1");
      Serial.println("first");
      Serial.println(first);
      Serial.println("second");
      Serial.println(second);
      Serial.println("pwm1");
      Serial.println(pwm1);
      Serial.println("pwm2");
      Serial.println(pwm2);
      
    }
    else if (cmp == 2)
    {
      int first = map(rc4, 1530, 1970, 0, 255);
      int second = map(LR, 1530, 1970, 0, 255);
      pwm2 = first - second;
      if (pwm2 < 0){pwm2 = 0;}
      pwm1 = map(rc4, 1530, 1970, 0, 255);
      Serial.println("comp = 2");
      Serial.println("first");
      Serial.println(first);
      Serial.println("second");
      Serial.println(second);
      Serial.println("pwm1");
      Serial.println(pwm1);
      Serial.println("pwm2");
      Serial.println(pwm2);
    }

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, pwm1);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, pwm2);
  }
    else if(rc4 < 1370) //right stick upDown 
  {
    if (cmp == 0)
    {
      pwm1 = map(rc4, 1370, 900, 0, 255);
      pwm2 = pwm1;
    }
    else if (cmp == 1)
    {
      int first = map(rc4, 1370, 900, 0, 255);
      int second = map(LR, 1370, 900, 0, 255);
      pwm1 = first - second; 
      if (pwm1 < 0){pwm1 = 0;}
      pwm2 = map(rc4, 1370, 900, 0, 255);
      Serial.println("comp = 1");
      
    }
    else if (cmp == 2)
    {
      int first = map(rc4, 1370, 900, 0, 255);
      int second = map(LR, 1530, 1970, 0, 255);
      pwm2 = first - second;

      if (pwm2 < 0){pwm2 = 0;}
      pwm1 = map(rc4, 1370, 900, 0, 255);
      Serial.println("comp = 2");
    }
    
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, pwm1);
  
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enB, pwm2);
  }
  
  delay(50);
}
