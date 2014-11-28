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
  
  Serial.begin(9600);
  
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
  delay(500);
  long distanceL = ping();
  delayMicroseconds(20);
  servo1.write(60);
  delay(500);
  long distanceR = ping();
  delayMicroseconds(20);
  servo1.write(90);
  
  Serial.print(distanceL);
  Serial.print(" : ");
  Serial.println(distanceR);
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
  delay(500);
  halt();
}

void loop(){
  
  long distance = 0;
  
  // check for obstacles
  for(int i = 0;i < 3; i++){
    distance += ping();
  }
  
  distance = distance / 3;
  
  Serial.println(distance);
  
  if (distance < 20) {
    avoid();
  } else {
    forward();
  }
  
  delay(1000);
  
}
