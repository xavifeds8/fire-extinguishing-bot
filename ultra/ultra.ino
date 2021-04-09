#include <Servo.h>

const int trigPin = 7;
const int echoPin = 6;

long duration;
int distinCM;

Servo radarServo;

void setup() 
{
  pinMode(3,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  radarServo.attach(2);
}
void loop() 
{
  digitalWrite(3,HIGH);
  for(int i=0;i<=180;i+=20)
  {
    radarServo.write(i);
    delay(50);
    ultrasonic();
 
  }
  
  for(int i=180;i>=0;i-=20)
  {
    radarServo.write(i);
    delay(50);
    ultrasonic();
  }
}

void ultrasonic(){
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distinCM = duration*0.034/2;
    Serial.println(distinCM);
}
