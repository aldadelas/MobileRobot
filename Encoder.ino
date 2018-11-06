const int enc_pin = 3;

// global
unsigned long ticks = 0;

const int E1 = 5; // right speed control
const int E2 = 6; // left speed control
const int M1 = 4; // right direction control
const int M2 = 7; // left direction control

const int dist = 1000; //mm
const int PWM = 127;
const int wheel_d = 42; //mm
const float c = 3.14 * wheel_d; //wheel circumference (mm)
const int one_wheel_rev = 24; // one wheel revolution tick = 24;

void setup() {
  Serial.begin(9600);
  pinMode(enc_pin, INPUT_PULLUP);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(enc_pin), countTicks, CHANGE);
  driveRobot(dist, PWM);
  
}

void loop() {
  // do nothing
}

void driveRobot(int distance, int power){
  int target_ticks = (distance/c) * one_wheel_rev;
  while(ticks <= target_ticks){
    forward(power);
    delay(10);
  }
  Serial.println(target_ticks);
  Serial.println(ticks);
  brake();
}

void countTicks(){
  ticks++;
}

void forward(int v){
  analogWrite(E1, v);
  analogWrite(E2, v);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
}

void brake(){
  analogWrite(E1, 0);
  analogWrite(E2, 0);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
}
