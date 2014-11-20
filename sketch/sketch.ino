#include <AFMotor.h>
#include <Servo.h>

// define pins for rangefinder
#define peepPin A0
#define echoPin A1

// define motors
AF_DCMotor motorL(1, MOTOR12_64KHZ);
AF_DCMotor motorR(2, MOTOR12_64KHZ);
Servo servo1;

void setup(){
  
  // set pin modes for ping
  pinMode(peepPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // attach servo
  servo1.attach(9);
  // look straight ahead
  servo1.write(90);
  
  // set motor speed
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

long ping(){
  
  // declare some variables
  long time;
  
  // send out peep
  digitalWrite(peepPin, LOW);
  delayMicroseconds(2);
  digitalWrite(peepPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(peepPin, LOW);
  
  // get return time
  time = pulseIn(echoPin, HIGH);
  
  // return distance in cm
  return time / 58.2;
  
}

int look(){
  
  // move rangefinder left and right and check distances
  servo1.write(120);
  long distanceL = ping();
  servo1.write(60);
  long distanceR = ping();

  // if L > R return L else return R
  if (distanceL > distanceR){
    return 0;
  } else {
    return 1;
  }
}

void avoid(){
  halt();
  if (look() == 1){
    motorR.run(BACKWARD);
  } else {
    motorL.run(BACKWARD);
  }
  delay(50);
  halt();
}

void loop(){
  
  long distance;
  
  // check for obstacles
  distance = ping();
  
  if (distance < 20) {
    avoid();
  } else {
    forward();
  }
  
}
