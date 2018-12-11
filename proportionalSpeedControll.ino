#include <math.h>

int encl,encr;  //  encl left, encr right

const int E1 = 5; // right speed control
const int E2 = 6; // left speed control
const int M1 = 4; // right direction control
const int M2 = 7; // left direction control

const int enc_pinAR = 3;  // pin interrupt = 0
const int enc_pinAL = 2;  // pint interrupt = 1

const double dist = 200; // target distance move in cm
const double wheel_d = 4.2; // wheel diameter in cm
const double wheel_c = 3.14 * wheel_d; // wheel circumference in cm
const int oneRevTicks = 12; // in one rev 12 ticks encoder
const int motor_error = 5;

void setup() {
  Serial.begin(9600);
  pinMode(enc_pinAR, INPUT_PULLUP);
  pinMode(enc_pinAL, INPUT_PULLUP);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(enc_pinAR), countEncR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(enc_pinAL), countEncL, CHANGE);

  moveTopose(dist, 127);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void moveTopose(double targetDist, int speedpwm)
{
  int vR = speedpwm;
  int vL = speedpwm;

  double tmp_DistL = encl * 0.35;
  double tmp_DistR = encr * 0.35;
  
  encl = 0;
  encr = 0;
  
  int tmp_encl = encl;
  int tmp_encr = encr;

  int prev_encl = tmp_encl;
  int prev_encr = tmp_encr;

  int diff_encl = tmp_encl - prev_encl;
  int diff_encr = tmp_encr - prev_encr;

  double diff_distL = targetDist - tmp_DistL;
  double diff_distR = targetDist - tmp_DistR;

  double wheel_rev = targetDist / wheel_c;
  int targetTicks = wheel_rev * oneRevTicks;

  double diff_Dist = sqrt(pow(diff_distL, 2) + pow(diff_distR, 2));
  double prev_diff_dist = diff_Dist;

  while ((encl < targetTicks)&& (encr < targetTicks))
  { 
    moveForward(vR, vL);

    // temporary distance has been reach
    tmp_DistL = encl * 0.35;
    tmp_DistR = encr * 0.35;

    // temporary encoder ticks
    tmp_encl = encl;
    tmp_encr = encr;

    // count ticks differential after move
    diff_encl = tmp_encl - prev_encl;
    diff_encr = tmp_encr - prev_encr;

    // count left distance
    diff_distL = targetDist - tmp_DistL;
    diff_distR = targetDist - tmp_DistR;

    diff_Dist = sqrt(pow(diff_distL, 2) + pow(diff_distR, 2));

    // wheel speed proportional between right and left
    if(diff_encl > diff_encr)
    {
      vL -= motor_error;
      vR += motor_error;
    } else {
      vL += motor_error;
      vR -= motor_error;
    }

    // speed controlling
    if(((prev_diff_dist <= 20) && (diff_Dist <= 20)) || ((prev_diff_dist <= 40) && (diff_Dist <= 40)) ||
    ((prev_diff_dist <= 60) && (diff_Dist <= 60)) || ((prev_diff_dist <= 80) && (diff_Dist <= 80)) || 
    ((prev_diff_dist <= 100) && (diff_Dist <= 100)))
    {
      Serial.print("kecepatan konstan");
    }else if(diff_Dist > 100){
      Serial.print("Kecepatan konstan");
    } else {
      vL -= 20;
      vR -= 20;
    }
    
    prev_encl = tmp_encl;
    prev_encr = tmp_encr;
  }

  stopMoving();
}

void moveForward(int Vr, int Vl)
{
  digitalWrite(E1, Vr);
  digitalWrite(E2, Vl);
  analogWrite(M1, LOW);
  analogWrite(M2, LOW);
  delay(10);
}

void stopMoving()
{
  digitalWrite(E1, 0);
  digitalWrite(E2, 0);
  analogWrite(M1, LOW);
  analogWrite(M2, LOW);
  delay(10);
}

void countEncR()
{
  encr++;
}

void countEncL()
{
  encl++;
}
