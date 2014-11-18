#include <AFMotor.h>

// define pins for rangefinder
#define peepPin A0
#define echoPin A1

// define motors
AF_DCMotor motorL(1, MOTOR12_64KHZ);
AF_DCMotor motorR(2, MOTOR12_64KHZ);

void setup(){
  
  // set pin modes for ping
  pinMode(peepPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
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

void loop(){
  
  long distance;
  
  // check for obstacles
  distance = ping();
  
  if (distance < 20) {
    halt();
    delay(10);
    motorL.run(RELEASE);
    motorR.run(BACKWARD);
    delay(50);
    motorR.run(RELEASE);
  } else {
    forward();
  }
  
}
