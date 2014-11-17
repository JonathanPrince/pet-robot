#include <AFMotor.h>

AF_DCMotor motorL(1, MOTOR12_64KHZ);
AF_DCMotor motorR(2, MOTOR12_64KHZ);

void setup() {
  Serial.begin(9600);
  Serial.println("Motor test");
  
  motorL.setSpeed(200);
  motorR.setSpeed(200);
}

void loop(){

  
  motorL.run(FORWARD);
  motorR.run(FORWARD);
  delay(1500);
  
  motorL.run(RELEASE);
  delay(10);
  motorL.run(BACKWARD);
  //motorR.run(BACKWARD);
  delay(500);
 
  motorR.run(FORWARD);
  delay(1500);
  motorL.run(RELEASE);
  delay(10);
  motorL.run(FORWARD);
  delay(990);
  
  motorR.run(RELEASE);
  motorL.run(RELEASE);
  delay(2000);
}
