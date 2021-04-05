const int pingPin = 4; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 3; // Echo Pin of Ultrasonic Sensor
const int IN1_W1= 7;
const int IN2_W1 = 8;
const int EN_W1 = 9;
const int IN1_W2= 12;
const int IN2_W2 = 13;
const int EN_W2 = 11;
const int servo_pin = 2;

#include <Servo.h>
Servo myservo;
int pos = 90;
void setup() {
  myservo.attach(servo_pin);
  pinMode(IN1_W1, OUTPUT);
  pinMode(IN2_W1, OUTPUT);
  pinMode(EN_W1, OUTPUT);
  pinMode(IN1_W2, OUTPUT);
  pinMode(IN2_W2, OUTPUT);
  pinMode(EN_W2, OUTPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600); // Starting Serial Terminal
}

void loop() {
  int inches;
  inches = ultra_sonic();
  Serial.print(inches);
  Serial.print("in, ");
  Serial.println();
  delay(100);
  if(inches > 10){
    set_clockwise_wheel_1(HIGH);
    set_clockwise_wheel_2(HIGH);
    set_speed_wheel_1(200);
    set_speed_wheel_2(200);
    
  }
 else{
  set_speed_wheel_1(inches);
  set_speed_wheel_1(inches);
  
 }
  
}

int ultra_sonic(){
   long duration, inches;
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   return inches;
 
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
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

int look_for_space(){

}

void move_base_fwd(){
  set_clockwise_wheel_1(HIGH);
  set_clockwise_wheel_2(HIGH);
  set_speed_wheel_1(200);
  set_speed_wheel_2(200);
}

void move_base_back(){
  set_clockwise_wheel_1(HIGH);
  set_clockwise_wheel_2(HIGH);
  set_speed_wheel_1(200);
  set_speed_wheel_2(200);
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
  set_speed_wheel_2(100)
}
