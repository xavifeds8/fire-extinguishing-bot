#define trigPin1 3
#define echoPin1 2
#define trigPin2 5
#define echoPin2 4
#define trigPin3 7
#define echoPin3 6
double fl , ff , fr;
float R = 0.04;
float L = 0.135;
const int IN1_W1= 9;
const int IN2_W1 = 8;
const int EN_W1 = 10;
const int IN1_W2= 13;
const int IN2_W2 = 12;
const int EN_W2 = 11;
float v , w;
int wl , wr;
double error,currentTime,elapsedTime,cum_error,rate_error,previousTime,last_error;
double duration, distance, dr,df,dl;
double L_prev;
double L_thresh = 7.0;
double kp = 0.5;
double kd = 0.05;
double ki = 0.0;
void setup() 
{
  pinMode(IN1_W1, OUTPUT);
  pinMode(IN2_W1, OUTPUT);
  pinMode(EN_W1, OUTPUT);
  pinMode(IN1_W2, OUTPUT);
  pinMode(IN2_W2, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(A5 , INPUT);
  pinMode(A4 , INPUT);
  pinMode(A3 , INPUT);
  Serial.begin(9600);
}

void loop() 
{
  fl = analogRead(A5);
  ff = analogRead(A4);
  fr = analogRead(A3);
  Serial.print(fl);
  Serial.print('-');
  Serial.print(ff);
  Serial.print('-');
  Serial.println(fr);
  delay(500);
  
//  if(df < 10 ){
//    turn();
//  }
//
//  read_sonar();
//  w = 10*compute_PID(dl);
//  Serial.print("error:");
//  Serial.println(w);
//  wl = 180+w;
//  wr = 180-w;
//  inv_kin();
  
} 
void turn(){
  
  if(dr > 15 && df < 10){
  while(df <35){
    set_clockwise_wheel_1(LOW);
    read_sonar();
    wl = 100;
    wr = 240;
    
    Serial.println("moving right");
    set_clockwise_wheel_1(LOW);
    set_clockwise_wheel_2(HIGH);

    set_speed_wheel_1(wl);
    set_speed_wheel_2(wr);
    
  }
    set_clockwise_wheel_1(HIGH);
  set_clockwise_wheel_2(HIGH);}
  
  if(dl > 15){
  while(df <35 ){
    set_clockwise_wheel_2(LOW);
    read_sonar();
    wl = 150;
    wr = 240;
    
    Serial.println("moving left");
    set_clockwise_wheel_1(HIGH);
    set_clockwise_wheel_2(LOW);

    set_speed_wheel_1(wl);
    set_speed_wheel_2(wr);
  }
  
  }
  
}
void inv_kin(){
  Serial.print(wl);
  Serial.print("-");
  Serial.println(wr);
  set_clockwise_wheel_1(HIGH);
  set_clockwise_wheel_2(HIGH);

  set_speed_wheel_1(wl);
  set_speed_wheel_2(wr);
  
 
}
double compute_PID(double inp){
  currentTime = millis();
  elapsedTime = (double)(currentTime - previousTime);
  error = L_thresh - inp;
  cum_error += error * elapsedTime;
  rate_error = (error - last_error)/elapsedTime;

  double out = kp*error + cum_error*ki + kd*rate_error;
  last_error = error;
  previousTime = currentTime;
  return out;
}

void set_speed_wheel_2(int val_1){
  analogWrite(EN_W1,val_1);
}

void set_speed_wheel_1(int val_2){
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
void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;

}

void read_sonar(){
  SonarSensor(trigPin1, echoPin1);
  dl = distance;
  SonarSensor(trigPin2, echoPin2);
  df = distance;
  SonarSensor(trigPin3, echoPin3);
  dr = distance;
  Serial.print(dl);
  Serial.print(" - ");
  Serial.print(df);
  Serial.print(" - ");
  Serial.println(dr);
 }
