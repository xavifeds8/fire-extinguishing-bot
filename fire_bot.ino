#include <Servo.h>
const int trigPin = 9;
const int echoPin = 10;
const int IN1_W1= 2;
const int IN2_W1 = 3;
const int EN_W1 = 5;
const int IN1_W2= 7;
const int IN2_W2 = 8;
int dist;
long duration;
int distinCM;
Servo radarServo;

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
  move_base_front();
  
  radarServo.write(0); //look right
  if(ultrasonic() < 20){
    move_base_left();
    delay(50);
    move_base_front();
  }
  delay(500);

  
  radarServo.write(90); //look front
  if(ultrasonic() < 20){
    move_base_right();
  }
  delay(500);
  
  radarServo.write(180); //look left
  if(ultrasonic() < 20){
    move_base_right();
    delay(50);
    move_base_front();
  }
  delay(500);
  radarServo.write(90); //look right
  if(ultrasonic() < 20){
    move_base_right();
  }
  delay(500);
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
  set_speed_wheel_1(100);
  set_speed_wheel_2(100);
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
  set_speed_wheel_1(200);
  set_speed_wheel_2(200);
}
