#include <AFMotor.h>

AF_DCMotor motorL(1, MOTOR12_64KHZ);
AF_DCMotor motorR(2, MOTOR12_64KHZ);

void setup() {
  Serial.begin(9600);
  motorL.setSpeed(200);
  motorR.setSpeed(200);
}

void forward(){
  motorL.run(FORWARD);
  motorR.run(FORWARD);
}

void backward(){
  motorL.run(BACKWARD);
  motorR.run(BACKWARD);
}

void halt(){
  motorR.run(RELEASE);
  motorL.run(RELEASE);
}

void loop(){
  
  
  
}
