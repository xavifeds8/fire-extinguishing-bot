#include<Servo.h>
int pos = 0;
Servo myservo;
#define trigPin1 3
#define echoPin1 2
#define trigPin2 5
#define echoPin2 4
#define trigPin3 7
#define echoPin3 10
double fl , ff , fr;
float R = 0.04;
float L = 0.135;
const int IN1_W1 = 9;
const int IN2_W1 = 8;
const int EN_W1 = 6;
const int IN1_W2 = 13;
const int IN2_W2 = 12;
const int EN_W2 = 11;
float v , w;
int wl , wr;
double error, currentTime, elapsedTime, cum_error, rate_error, previousTime, last_error;
double duration, distance, dr, df, dl;
double L_prev;
double L_thresh = 7.0;
double kp = 0.5;
double kd = 0.5;
double ki = 0.00;
double out = 0.00;
void setup()
{
  pinMode(IN1_W1, OUTPUT);
  pinMode(IN2_W1, OUTPUT);
  pinMode(EN_W1, OUTPUT);
  pinMode(EN_W2, OUTPUT);
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
  pinMode(A0 , OUTPUT);
  pinMode(A1 , OUTPUT);
  myservo.attach(A2);
  Serial.begin(9600);

}

void loop()
{
  myservo.write(20);
  drive();
}

void drive() {
  
  read_data();
  if(!isFire()){
    wall_following();
  }
}

void read_data(){
  read_sonar();
  read_fire();
}

void fire_path(){
    Serial.println("FIRE PATH");
    float threshf = 80;
    while(fl < 700 or ff<700 or fr<700){
      read_fire();
    Serial.print("!!!FIRE DETECTED!!!");
    int f = min_val();
    float x = min(fl,ff);
    x = min(x,fr);
    if(f==0){
      wl = 100;
      wr = 200;
      inv_kin();
      if(x<threshf){
        wl=0;
        wr = 0;
        inv_kin();
        pump(0);
        break;
      }}
    if(f==1){
      wl = 180;
      wr = 180;
      inv_kin();
      if(x<=threshf){
        wl=0;
        wr = 0;
        inv_kin();
        pump(1);
        break;
      }}
    if(f==2){
      wl = 200;
      wr = 100;
      inv_kin();
      if(x<=threshf){
        wl=0;
        wr = 0;
        inv_kin();
        pump(1);
        break;
      }}
     
  }
}

int min_val(){
  if(fl<ff and fl < fr){ //fl=0 ff = 1 fr =2
    return 0;
  }
  if(ff<fr){
    return 1;
  }
  else{
    return 2;
  }
}
void pump(int x) {
  if(fl < 700 or ff<700 or fr<700){
      analogWrite(A0,255);
      servo_rotate(x);
      analogWrite(A0,0);
    
  }
}

bool isFire(){
  if(fl < 700 or ff<700 or fr<700){
    fire_path();
    return true;
  }
  return false;
}

void servo_rotate(int loc) {
  if(loc ==1){
    for (pos = 0; pos <= 90; pos += 5) {
      myservo.write(pos);              
      delay(15);           
  }
  for (pos = 80; pos >= 0; pos -= 5) {
    myservo.write(pos);              
    delay(15);                       
  }
  }
  else{
    for (pos = 90; pos <= 180; pos += 5) {
      myservo.write(pos);              
      delay(15);           
  }
  for (pos = 180; pos >= 90; pos -= 5) {
    myservo.write(pos);              
    delay(15);                       
  }
  }
}

void read_fire() {
  fl = analogRead(A5);
  ff = analogRead(A4);
  fr = analogRead(A3);
  Serial.print("fireflame readings : ");
  Serial.print(fl);
  Serial.print(" - ");
  Serial.print(ff);
  Serial.print(" - ");
  Serial.println(fr);
}


void wall_following(){
  isFire();
  read_sonar();
  out = compute_PID(dl);
  Serial.println(out);
  if (out < 0.6 && out > -0.6 && df >20 && dl < 20) {
    Serial.println("go straight");
      wl = 180;
      wr = 180;
     inv_kin();
  }
  else if (out > 0.6 && dl < 20 && df > 20) { /*turn right*/
    Serial.println("turn right");
    wl = 180 + out * 10;
    wr = 180;
    inv_kin();
  }

  else if (out < -0.6 && dl < 20 && df > 20) { /*turn left*/
    Serial.println("turn left");
    wl = 180;
    wr = 180 + out * 10 * -1;
    inv_kin();
  }

  if (dl > 20 && dr > 20 && df > 20) { //find left wall
    Serial.println("find left wall");
    wl = -10;
    wr = 255;
    inv_kin();
  }

  if ( df < 30 ) { //ROTATE right or ROTATE left
    Serial.println("ROTATE right or ROTATE left");
    wl = -150;
    wr = -150;
    inv_kin();
    delay(1000);
    int dl_count = 0;
    if(dl<10 && df<10 && dr<10){
      while(dl<20 && dr<20){
         wl = -150;
         wr = -150;
         Serial.println("move backwards");
        inv_kin();
        
      }
      
    }
    if ( dl < dr + 10 ) { //ROTATE right
      Serial.println("ROTATE right");
      wl = 200;
      wr = -100;
      inv_kin();
      int fcount = 0;
      int rcount = 0;
      while (df < 30 or dl >20 or fcount < 5 or rcount < 5) {
        read_data();
        if (df > 30) {
          fcount++;
        }
        if (dr > 30) {
          rcount++;
        }
      }

    }
    else if (dr < dl + 10) { //ROTATE LEFT
      Serial.println("ROTATE LEFT");
      wl = -100;
      wr = 200;
      inv_kin();
      int fcount = 0;
      int lcount = 0;
      while (df < 30 or dr >30 or fcount < 10 or lcount < 10) {
        read_data();
        if (df > 30) {
          fcount++;
        }
        if (dr > 30) {
          lcount++;
        }
      }
    }
  }
}

void inv_kin() {
  Serial.print(wl);
  Serial.print("-");
  Serial.println(wr);
  set_clockwise_wheel_1(HIGH);
  set_clockwise_wheel_2(HIGH);
  if (wl < 0) {
    set_clockwise_wheel_1(LOW);
    set_speed_wheel_1(abs(wl));
    set_speed_wheel_2(abs(wr));
  }
  else if (wr < 0) {
    set_clockwise_wheel_2(HIGH);
    set_speed_wheel_1(abs(wl));
    set_speed_wheel_2(abs(wr));
  }
  else {
    set_speed_wheel_1(wl);
    set_speed_wheel_2(wr);
  }
}

double compute_PID(double inp) {
  currentTime = millis();
  elapsedTime = (double)(currentTime - previousTime);
  error = L_thresh - inp;
  cum_error += error * elapsedTime;
  rate_error = (error - last_error) / elapsedTime;

  double out = kp * error + cum_error * ki + kd * rate_error;
  last_error = error;
  previousTime = currentTime;
  return out;
}

void set_speed_wheel_2(int val_1) {
  Serial.println(val_1);
  analogWrite(EN_W1, val_1);
}

void set_speed_wheel_1(int val_2) {
  analogWrite(EN_W2, val_2);
}
void set_clockwise_wheel_1(bool dir1) {
  digitalWrite(IN1_W2, dir1);
  digitalWrite(IN2_W2, !dir1);
}

void set_clockwise_wheel_2(bool dir2) {
  digitalWrite(IN1_W1, dir2);
  digitalWrite(IN2_W1, !dir2);
}
void SonarSensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 29 / 2);

}

void read_sonar() {
  SonarSensor(trigPin1, echoPin1);
  dl = distance;
  SonarSensor(trigPin2, echoPin2);
  df = distance;
  SonarSensor(trigPin3, echoPin3);
  dr = distance;
  Serial.print("sonar readings: ");
  Serial.print(dl);
  Serial.print(" - ");
  Serial.print(df);
  Serial.print(" - ");
  Serial.println(dr);
}
