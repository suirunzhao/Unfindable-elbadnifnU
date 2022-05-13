#include<Servo.h>
#include <Adafruit_PWMServoDriver.h>


//define min/max pluse length count
#define SERVOMIN 240
#define SERVOMAX 440
#define SERVO_FREQ 60

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x42);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x40);

Servo servoHor;
int x;
int prevX;

uint8_t servonum = 0;


void setup(){
  Serial.begin(9600);
  //Serial.println("16 Servo follow test");

  //pwm setup
  pwm1.begin();
  pwm1.setPWMFreq(SERVO_FREQ);

  pwm2.begin();
  pwm2.setPWMFreq(SERVO_FREQ);

  pwm3.begin();
  pwm3.setPWMFreq(SERVO_FREQ);
  servoHor.write(90);
  
  
  }


void loop(){
  if(Serial.available() > 0){
    if(Serial.read() == 'X'){
      for(int i = 0; i < 16; i ++){
      int x = Serial.parseInt();
      int p = map(x,0,1280,SERVOMIN,SERVOMAX);
      //p = min(p,SERVOMAX);
      //p = max(p,SERVOMIN);
      if(x < 440 && x > 260){
        pwm1.setPWM(i,0,SERVOMIN);
        pwm3.setPWM(i,0,SERVOMAX);
        if(i < 8){
            pwm2.setPWM(i,0,SERVOMIN);
        }else if(i < 16 && i > 7){
            pwm2.setPWM(i,0,SERVOMAX);
          }
        }else{
      pwm1.setPWM(i,0,p);
      //delay(50);
      pwm2.setPWM(i,0,p);
      //delay(50);
      pwm3.setPWM(i,0,p);
        }
      }
    }
    while(Serial.available() > 0){
      Serial.read();
      }
  }
}
