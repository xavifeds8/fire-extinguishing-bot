#define trigPin1 3
#define echoPin1 2
#define trigPin2 4
#define echoPin2 5
#define trigPin3 7
#define echoPin3 8
long error,currentTime,elapsedTime,cum_error,rate_error,previousTime,last_error;

const int IN1_W1= 13;
const int IN2_W1 = 12;
const int EN_W1 = 6;
const int IN1_W2= 9;
const int IN2_W2 = 10;
double duration, distance, dr,df,dl;
double L_prev;
int thresh = 8;
float kp = 0.075;
float kd = 1;
float ki = 0.0;
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
  Serial.begin(9600);
}

void loop() 
{
  SonarSensor(trigPin1, echoPin1);
  dr = distance;
  SonarSensor(trigPin2, echoPin2);
  df = distance;
  SonarSensor(trigPin3, echoPin3);
  dl = distance;
  Serial.print(dl);
  Serial.print(" - ");
  Serial.print(df);
  Serial.print(" - ");
  Serial.println(dr); 
  error = thresh-dl;
  if(df<7){
    move_base_right_hard();
    while(1){
      if(df>50.0 && dr<15.0 && dl<10.0){
        break;
      }
      SonarSensor(trigPin2, echoPin2);
      df = distance;
      SonarSensor(trigPin1, echoPin1);
      dr = distance;
      Serial.println("hard right");
    }
    
  }
  SonarSensor(trigPin1, echoPin1);
  dr = distance;
  SonarSensor(trigPin2, echoPin2);
  df = distance;
  SonarSensor(trigPin3, echoPin3);
  dl = distance;
  move_base_front();
  if(error > 0.1 && df > 7.0){ //move left
    move_base_right();
    delay(compute_PID(thresh));
  }
  if(error < -0.1 && df > 7.0){
    move_base_left();
    delay(compute_PID(thresh)*-1);
  }
  move_base_front();
}

double compute_PID(double inp){
  currentTime = millis();
  elapsedTime = (double)(currentTime - previousTime);
  error = thresh - inp;
  cum_error += error * elapsedTime;
  rate_error = (error - last_error)/elapsedTime;

  double out = kp*error + cum_error*ki + kd*rate_error;
  last_error = error;
  previousTime = currentTime;
  return out;
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
  set_speed_wheel_1(255);
  set_speed_wheel_2(255);
}
void move_base_front (){
  Serial.println("movefront");
  set_clockwise_wheel_1(LOW); 
  set_clockwise_wheel_2(LOW);
  set_speed_wheel_1(200);
  set_speed_wheel_2(200);
}

void move_base_left(){
  Serial.println("move left");
  set_clockwise_wheel_1(HIGH);
  set_clockwise_wheel_2(LOW);
  set_speed_wheel_1(255);
  set_speed_wheel_2(255);
}

void move_base_right(){
  Serial.println("move right");
  set_clockwise_wheel_1(LOW);
  set_clockwise_wheel_2(HIGH);
  set_speed_wheel_1(255);
  set_speed_wheel_2(255);
}
void move_base_right_hard(){
  Serial.println("move hard right");
  set_clockwise_wheel_1(LOW);
  set_clockwise_wheel_2(HIGH);
  set_speed_wheel_1(230);
  set_speed_wheel_2(230);
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
