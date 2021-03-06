  // Infrared Remote Control library: http://tech.cyborg5.com/irlib/
// Hexapod code based on example code from DAGU_
// Adafruit_PWMServoDriver library: https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "meArm_Adafruit.h"  //meArm library
#include <IRLib.h> 
#define MY_PROTOCOL SONY
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want

float SERVOFREQ = 50;
float pulseconstant;                              

int angle;                                                 // determines the direction/angle (0Â°-360Â°) that the robot will walk in 
int rotate;                                                // rotate mode: -1 = anticlockwise, +1 = clockwise, 0 = no rotation
int Speed;                                                 // walking speed: -15 to +15 
int Stride;                                                // size of step: exceeding 400 may cause the legs to hit each other

int xdirPin = A0;
int ydirPin = A1;
int zdirPin = A3;
int gdirPin = A2;
int SERVOMIN = 400;
int SERVOMAX = 2400;
int servoPosition = 1500;
int servoIncrement = 200;

int data = 13;
int clock = 11;
int latch = 12; 
int IRrecLED = 4;
int sensorLED = 3;
int sensorVal = 0;
int RECV_PIN = 10;                                  
IRrecv irrecv(RECV_PIN);
IRdecode My_Decoder;

#define ZERO 0x20DF08F7
#define FORWARD 0x20DF02FD
#define CC 0x20DF9C63
#define FAV 0x20DF7887
#define RETURN 0x20DFDA25
#define QMENU 0x20DFA25D
#define ENTER 0x20DF22DD
#define REVERSE 0x20DF827D
#define MUTE 0x20DF906F
#define LEFT 0x20DFE01F 
#define RIGHT 0x20DF609F
#define CHANNELUP 0x20DF00FF
#define CHANNELDOWN 0x20DF807F
#define VOLUMEUP 0x20DF40BF
#define VOLUMEDOWN 0x20DFC03F
#define MENU 0x20DFC23D
#define DASH 0x20DF32CD
#define FLASHBACK 0x20DF58A7

void setup()
{
  
  Serial.begin(9600);                     
  irrecv.enableIRIn();
  pulseconstant = (1000000/SERVOFREQ)/4096;
pinMode(IRrecLED, OUTPUT);
pinMode(sensorLED, OUTPUT);
pinMode(data, OUTPUT);
pinMode(clock, OUTPUT);
pinMode(latch, OUTPUT);
digitalWrite(4, HIGH);
  pwm.begin();
  pwm.setPWMFreq(SERVOFREQ);
  
  for(int i=0;i<16;i++)
  {
    servoWrite(i,1500);                       // initialize servos to center
  }
}

void loop()
{


  if (irrecv.GetResults(&My_Decoder))                            
  {                                                 
    My_Decoder.decode();
    //My_Decoder.DumpResults();
    unsigned long IRC=My_Decoder.value;
    Serial.println(IRC,HEX);       
   
  
    if(IRC==ENTER)                              // STOP
    {
      Speed=0;
      angle=0;
      rotate=0;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);
     
    }

    if(IRC==FORWARD)                              // FORWARD
    {
      Speed=15;
      rotate=0;
      angle=0;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);
    }

    if(IRC==REVERSE)                             // REVERSE    
    {
      Speed=-15;
      rotate=0;
      angle=0;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);
    }

    if(IRC==RIGHT)                                          // ROTATE CLOCKWISE  
    {
      Speed=15;
      rotate=1;
      angle=0;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);
    }

    if(IRC==LEFT)                                          // ROTATE COUNTER CLOCKWISE  
    {
      Speed=15;
      rotate=-1;
      angle=0;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);
    }

    if(IRC==FAV)                                            // 45 DEGREES    
    {
      Speed=15;
      rotate=0;
      angle=45;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);
    }

    if(IRC==CC)                                          // 90 DEGREES    
    {
      Speed=15;
      rotate=0;
      angle=90;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);
    }

    if(IRC==MUTE)                                          // 135 DEGREES    
    {
      Speed=15;
      rotate=0;
      angle=135;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);
    }

    if(IRC==MENU)                                           // 225 DEGREES    
    {
      Speed=15;
      rotate=0;
      angle=225;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);

    }

    if(IRC==QMENU)                                          // 270 DEGREES    
    {
      Speed=15;
      rotate=0;
      angle=270;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);

    }

    if(IRC==RETURN)                                          // 315 DEGREES    
    {
      Speed=15;
      rotate=0;
      angle=315;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);
          
    }
    if(IRC==CHANNELUP)                              // STOP
    {
      Speed=0;
      angle=0;
      rotate=0;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);
      servoPosition += servoIncrement;
      servoWrite(13, servoPosition);
      delay(10);
      
     
    }
    if(IRC==CHANNELDOWN)                              // STOP
    {
      Speed=0;
      angle=0;
      rotate=0;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);
      servoPosition -= servoIncrement;
      servoWrite(13, servoPosition);
      delay(10);
      
     
    }
    if(IRC==VOLUMEUP)                              // STOP
    {
      Speed=0;
      angle=0;
      rotate=0;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);
     servoPosition += servoIncrement;
      servoWrite(14, servoPosition);
      delay(10);
      
    }
    if(IRC==VOLUMEDOWN)                              // STOP
    {
      Speed=0;
      angle=0;
      rotate=0;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);
      servoPosition -= servoIncrement;
      servoWrite(14, servoPosition);
      delay(10);
     
    }
    if(IRC==DASH)                              // STOP
    {
      Speed=0;
      angle=0;
      rotate=0;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);
      servoPosition += servoIncrement;
     servoWrite(15, servoPosition);
      delay(10);
     
    }
    if(IRC==FLASHBACK)                              // STOP
    {
      Speed=0;
      angle=0;
      rotate=0;
      digitalWrite(IRrecLED, LOW);
      delay(500);
      digitalWrite(IRrecLED, HIGH);
      servoPosition -= servoIncrement;
      servoWrite(15, servoPosition);
      
      
      delay(10);
     
    }
    
    
    irrecv.resume();              
   
  }


  if (angle<0) angle+=360;                                 // keep travel angle within 0Â°-360Â°
  if (angle>359) angle-=360;                               // keep travel angle within 0Â°-360Â°
  Walk();                                                  // move legs to generate walking gait
  delay(15);
}
 

void Walk()                                                // all legs move in a circular motion
{
  if(Speed==0)                                             // return all legs to default position when stopped
  {
    Stride-=25;                                            // as Stride aproaches 0, all servos return to center position
    if(Stride<0) Stride=0;                                 // do not allow negative values, this would reverse movements
  }
  else                                                     // this only affects the robot if it was stopped
  {
    Stride+=25;                                            // slowly increase Stride value so that servos start up smoothly
    if(Stride>450) Stride=450;                             // maximum value reached, prevents legs from colliding.
  }

  float A;                                                 // temporary value for angle calculations
  double Xa,Knee,Hip;                                      // results of trigometric functions
  static int Step;                                         // position of legs in circular motion from 0Â° to 360Â°                               

  for(int i=0;i<6;i+=2)                                    // calculate positions for odd numbered legs 1,3,5
  {
    A=float(60*i+angle);                                   // angle of leg on the body + angle of travel
    if(A>359) A-=360;                                      // keep value within 0Â°-360Â°

    A=A*PI/180;                                            // convert degrees to radians for SIN function

    Xa=Stride*rotate;                                      // Xa value for rotation
    if(rotate==0)                                          // hip movement affected by walking angle
    {
      Xa=sin(A)*-Stride;                                   // Xa hip position multiplier for walking at an angle
    }

    A=float(Step);                                         // angle of leg
    A=A*PI/180;                                            // convert degrees to radians for SIN function
    Knee=sin(A)*Stride;
    Hip=cos(A)*Xa;

    servoWrite(i*2,1500+int(Knee));  // update knee  servos 1,3,5
    servoWrite(i*2+1,1500+int(Hip)); // update hip servos 1,3,5
  }

  for(int i=1;i<6;i+=2)                                    // calculate positions for even numbered legs 2,4,6
  {
    A=float(60*i+angle);                                   // angle of leg on the body + angle of travel
    if(A>359) A-=360;                                      // keep value within 0Â°-360Â°

    A=A*PI/180;                                            // convert degrees to radians for SIN function
    Xa=Stride*rotate;                                      // Xa value for rotation
    if(rotate==0)                                          // hip movement affected by walking angle
    {
      Xa=sin(A)*-Stride;                                   // Xa hip position multiplier for walking at an angle
    }

    A=float(Step+180);                                     // angle of leg
    if(A>359) A-=360;                                      // keep value within 0Â°-360Â°
    A=A*PI/180;                                            // convert degrees to radians for SIN function
    Knee=sin(A)*Stride;
    Hip=cos(A)*Xa;
    
    servoWrite(i*2,1500+int(Knee)); // update knee  servos 2,4,6
    servoWrite(i*2+1,1500+int(Hip)); // update hip servos 2,4,6

  }

  Step+=Speed;                                             // cycle through circular motion of gait
  if (Step>359) Step-=360;                                 // keep value within 0Â°-360Â°
  if (Step<0) Step+=360;                                   // keep value within 0Â°-360Â°
}


// you can use this function if you'd like to set the pulse length in useconds
// e.g. servoWrite(0, 1500) is a 1500usecond pulsewidth
void servoWrite(uint8_t n, float pulse) {
  float pulsetick;
  pulsetick = pulse/pulseconstant;
  //Serial.println(pulsetick);
  pwm.setPWM(n, 0, pulsetick);
}
