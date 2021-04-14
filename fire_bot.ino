#include <Servo.h>
const int trigPin = 9;
const int echoPin = 10;
const int IN1_W1= 2;
const int IN2_W1 = 3;
const int EN_W1 = 5;
const int IN1_W2= 7;
const int IN2_W2 = 8;
float distinCM;
Servo radarServo;
float error;

void setup() 
{
  pinMode(13,OUTPUT);
  pinMode(IN1_W1, OUTPUT);
  pinMode(IN2_W1, OUTPUT);
  pinMode(EN_W1, OUTPUT);
  pinMode(IN1_W2, OUTPUT);
  pinMode(IN2_W2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  radarServo.attach(4);
    
  digitalWrite(13,HIGH);

}

void loop() 
{
  radarServo.write(90);
  delay(500);
  if(ultrasonic() < 20   && (radarServo.read() > 70 || radarServo.read() <120)){
    Serial.println("move hard right");
    move_base_back();
    delay(500);
    move_base_right();
    delay(500);
  }
  move_base_front();
}


float ultrasonic(){
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    distinCM = pulseIn(echoPin, HIGH)*0.034/2;
    Serial.println(distinCM);
    return distinCM;
}

void set_speed_wheel_1(int val_1){
  analogWrite(EN_W1,val_1);
}

void set_speed_wheel_2(int val_2){
  analogWrite(EN_W1,val_2);
}
void set_clockwise_wheel_1(bool dir1){
  digitalWrite(IN1_W1,dir1);
  digitalWrite(IN2_W1,!dir1);
}

void set_clockwise_wheel_2(bool dir2){
  digitalWrite(IN1_W2,dir2);
  digitalWrite(IN2_W2,!dir2);
}
void move_base_back(){
  set_clockwise_wheel_1(HIGH);
  set_clockwise_wheel_2(HIGH);
  set_speed_wheel_1(200);
  set_speed_wheel_2(200);
}
void move_base_front (){
  set_clockwise_wheel_1(LOW); 
  set_clockwise_wheel_2(LOW);
  set_speed_wheel_1(200);
  set_speed_wheel_2(200);
}

void move_base_left(){

  set_clockwise_wheel_1(HIGH);
  set_clockwise_wheel_2(LOW);
  set_speed_wheel_1(200);
  set_speed_wheel_2(200);
}

void move_base_right(){

  set_clockwise_wheel_1(LOW);
  set_clockwise_wheel_2(HIGH);
  set_speed_wheel_1(255);
  set_speed_wheel_2(255);
}
