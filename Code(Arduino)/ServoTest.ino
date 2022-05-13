#include<Servo.h>


Servo servoHor; //Horizontal Servo

int x;


int prevX;


void setup()
{
  Serial.begin(9600);

  servoHor.attach(6); //Attach Horizontal Servo to Pin 6

  servoHor.write(90);
}

void Pos()
{
  if(prevX != x)
  {
    //generate map
    int servoX = map(x, 0, 1280, 10, 179); 


    servoX = min(servoX, 179);
    servoX = max(servoX, 10);

    
    servoHor.write(servoX);

  }
}

void loop()
{
  if(Serial.available() > 0)
  {
    if(Serial.read() == 'X')
    {
      x = Serial.parseInt();
       Pos();
      }
    }
    while(Serial.available() > 0)
    {
      Serial.read();
    }
  }
