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
  
  encl = 0;
  encr = 0;
  
  int tmp_encl = encl;
  int tmp_encr = encr;

  int prev_encl = tmp_encl;
  int prev_encr = tmp_encr;

  int diff_encl = tmp_encl - prev_encl;
  int diff_encr = tmp_encr - prev_encr;

  double wheel_rev = targetDist / wheel_c;
  int targetTicks = wheel_rev * oneRevTicks;

  while ((encl < targetTicks)&& (encr < targetTicks))
  {
    moveForward(vR, vL);
    
    tmp_encl = encl;
    tmp_encr = encr;

    diff_encl = tmp_encl - prev_encl;
    diff_encr = tmp_encr - prev_encr;

    if(diff_encl > diff_encr)
    {
      vL -= motor_error;
      vR += motor_error;
    } else {
      vL += motor_error;
      vR -= motor_error;
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
