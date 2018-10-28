const byte interruptPin = 2;                //pin for emergency interrupt

volatile byte state = LOW;
const byte pwmPin = 3;                      //PWM out pin to motor
const int startSpeed = 255 * 0.3;           //float is percentage of motor speed for start button. currently 30%
const byte speedUpRate = 5;                 //spin up rate for start button
const byte speedAdjustRate = 10;            //rate at which speed up/down modifies current speed
byte motorSpeed = 0;
const byte maxSpeed = 255 * 0.6;            //determines max speed. currently 60%
const byte pollingInterval = 10;
const byte startPin = 4;                    //start pin
const byte stopPin = 5;                     //stop pin
const byte speedUpPin = 6;                  //speed increase pin
const byte speedDownPin = 7;                //speed decrease pin
const byte resetPin = 8;                    //reset pin
const int buttonIntervalDelay = 1000;       //delay between accepting button commands (ms)
bool emergency = false;                     //emergency stop flag

void setup() {
  Serial.begin(9600);
  Serial.print("setting up\n");
  pinMode(pwmPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(startPin, INPUT_PULLUP);
  pinMode(stopPin, INPUT_PULLUP);
  pinMode(speedUpPin, INPUT_PULLUP);
  pinMode(speedDownPin, INPUT_PULLUP);
  pinMode(resetPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), emergencyStop, LOW);
}

void loop() {
  
  if(digitalRead(stopPin) == LOW && !emergency){
    Serial.print("stop pressed\n");
    stop();
    delay(buttonIntervalDelay);
  }else if(digitalRead(speedDownPin) == LOW && !emergency){
    Serial.print("speed down pressed\n");
    adjustSpeed(false);
    delay(buttonIntervalDelay);
  }else if(digitalRead(speedUpPin) == LOW && !emergency){
    Serial.print("speed up pressed\n");
    adjustSpeed(true);
    delay(buttonIntervalDelay);
  }else if(digitalRead(startPin) == LOW && !emergency){
    Serial.print("start pressed\n");
    startMotor();
    delay(buttonIntervalDelay);
  }else if(digitalRead(resetPin) == LOW && emergency == true){
    Serial.print("reset pressed\n");
    emergency = false;
    delay(buttonIntervalDelay);
  }
}

void startMotor(){
  if(motorSpeed > 0){
    Serial.print("stopping\n");
    stop();
  }else{
    for( int i = 0; i <= startSpeed; i += speedUpRate){
      if(emergency){
        break;
      }
      Serial.print("motor speed: " + String(motorSpeed) + "\n");
      analogWrite(pwmPin, i);
      motorSpeed = i;
      delay(500);
   }
   Serial.print("spin up complete\n");
  }
}

void emergencyStop(){
  Serial.print("emergency stop pressed\n");
  analogWrite(pwmPin, 0);
  motorSpeed = 0;
  emergency = true;
  Serial.print("motor speed: " + String(motorSpeed) + "\n");
}

void stop(){
  Serial.print("stop pressed\n");
  analogWrite(pwmPin, 0);
  motorSpeed = 0;
  Serial.print("motor speed: " + String(motorSpeed) + "\n");
}

void adjustSpeed(bool speedAdjustment){
 
  Serial.print("speed up/down pressed\n");
  if(motorSpeed <= 0){
    return;
  }
  if(speedAdjustment == true && motorSpeed + speedAdjustRate <= maxSpeed){
    analogWrite(pwmPin, motorSpeed + speedAdjustRate);
  }else if(speedAdjustment == false){
    analogWrite(pwmPin, motorSpeed - speedAdjustRate);
  }
   Serial.print("motor speed: " + String(motorSpeed) + "\n");
}


