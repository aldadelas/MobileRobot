/*
 # This Sample code is for testing the MiniQ Discovery Kit.
  
 # Editor : Phoebe
 # Date   : 2014.6.19
 # Ver    : 0.1
 # Product: MiniQ Discovery Kit
 # SKU    : KIT0071
  
 # Description:     
 # Obstacle avoidance function of MiniQ Discovery Kit
  
 */

#include <math.h>                              
#include <Servo.h>                                //Include Servo library
Servo irservo;                                    // create servo object to control a servo 

#define Svo_Pin 9

int posnow;

int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;     //M1 Direction Control
int M2 = 7;     //M1 Direction Control

const int random_turn_base = 120;
const int random_turn_ceiling = 240;
const int random_forward_degree = 10;
const int delay_per_degree = 20;
const int forward_delay = 20;

void stop(void)                    //Stop
{
  digitalWrite(E1,0); 
  digitalWrite(M1,LOW);    
  digitalWrite(E2,0);   
  digitalWrite(M2,LOW);    
}   
void advance(char a,char b)          //Move forward
{
  analogWrite (E1,a);      //PWM Speed Control
  digitalWrite(M1,LOW);    
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
}  
void back_off (char a,char b)          //Move backward
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);   
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);
}
void turn_L (char a,char b)             //Turn Left
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);    
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);
}
void turn_R (char a,char b)             //Turn Right
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);    
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
}


void setup()
{
  int i;
  for(i=4;i<=7;i++)
   pinMode(i, OUTPUT); 
//  pinMode(2,OUTPUT);
//  Serial.println("Run keyboard control");
  digitalWrite(E1,LOW);   
  digitalWrite(E2,LOW);
//  irservo.attach(Svo_Pin);                         //attaches the servo on pin 9 to the servo object 
  Serial.begin(19200);                            //Set Baud Rate
  advance(80,80);
}

int pos=0;                                        // variable to store the servo position 
float distance;

void loop()
{
//  digitalWrite(2,HIGH); 
  for (int i=0;i<180;i++)          
  {
//    irservo.write(i);
    int x=analogRead(3);                   // connect the GP2Y0A21 distance sensor to Analog 0
    Serial.println(x);                    // print distance 
    if(x>250)
    {
//      digitalWrite(2,LOW);delay(100); digitalWrite(2,HIGH); delay(100); 
      randomTurn();           // akan berbelok secara random ketika ada obstacle
    }
    else {
//      randomForward();        // belok secara random lalu maju
      
      advance(80,80);       // maju lurus saja tidak berbelok terlebih dahulu
      delay(120);
    }
  } 
}

void randomTurn(){
  long randNumber1 = random(1,10);
  long randNumber2 = random(random_turn_base, random_turn_ceiling);

  int turn_time = (int) randNumber2 * delay_per_degree;

  if (randNumber1 >= 5){
    stop();
    turn_R(80,80);
    delay(120);
  }else{
    stop();
    turn_L(80,80);
    delay(120);
  }
}

void randomForward(){
  long rand_turn = random(10);
  long rand_dir = random(1,10);

  if(rand_dir > 5){
    turn_R(80,80);
    delay(120);
  } else {
    turn_L(80,80);
    delay(120);
  }
  advance(80,80);
  delay(500);
}
