#include <Servo.h>
const int trigPin = 4;
const int echoPin = 3;
const int IN1_W1= 7;
const int IN2_W1 = 8;
const int EN_W1 = 9;
const int IN1_W2= 12;
const int IN2_W2 = 13;
const int EN_W2 = 11;
int dist;
long duration;
int distinCM;

Servo radarServo;

void setup() 
{
  pinMode(IN1_W1, OUTPUT);
  pinMode(IN2_W1, OUTPUT);
  pinMode(EN_W1, OUTPUT);
  pinMode(IN1_W2, OUTPUT);
  pinMode(IN2_W2, OUTPUT);
  pinMode(EN_W2, OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  radarServo.attach(2);
  digitalWrite(3,HIGH);
}

void loop() 
{
  digitalWrite(3,HIGH);
  
  radarServo.write(0);
  delay(200);
  dist = ultrasonic();


  radarServo.write(45);
  delay(200);
  dist = ultrasonic();
  
  
  radarServo.write(90);
  delay(200);
  dist = ultrasonic();
  if(dist <
  
  radarServo.write(135);
  delay(200);
  dist = ultrasonic();
  
  radarServo.write(180);
  delay(200);
  dist = ultrasonic();
}


int ultrasonic(){
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distinCM = duration*0.034/2;
    Serial.println(distinCM);
}

void set_speed_wheel_1(int val_1){
  analogWrite(EN_W1,val_1);
}

void set_speed_wheel_2(int val_2){
  analogWrite(EN_W2,val_2);
}
void set_clockwise_wheel_1(bool dir1){
  digitalWrite(IN1_W1,dir1);
  digitalWrite(IN2_W1,!dir1);
}

void set_clockwise_wheel_2(bool dir2){
  digitalWrite(IN1_W2,dir2);
  digitalWrite(IN2_W2,!dir2);
}
void move_base_fwd(){
  set_clockwise_wheel_1(HIGH);
  set_clockwise_wheel_2(HIGH);
  set_speed_wheel_1(100);
  set_speed_wheel_2(100);
}
void move_base_back(){
  set_clockwise_wheel_1(LOW); 
  set_clockwise_wheel_2(LOW);
  set_speed_wheel_1(100);
  set_speed_wheel_2(100);
}

void move_base_left(){
  set_clockwise_wheel_1(HIGH);
  set_clockwise_wheel_2(LOW);
  set_speed_wheel_1(100);
  set_speed_wheel_2(100);
}

void move_base_right(){
  set_clockwise_wheel_1(LOW);
  set_clockwise_wheel_2(HIGH);
  set_speed_wheel_1(100);
  set_speed_wheel_2(100);
}
