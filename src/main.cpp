#include <Arduino.h>
#include <Servo.h>
#include "SR04Maneger.h"

#define MAX 120
#define MIN 70

Servo my_servo;
int pos = 0;
SR04Maneger sr04Maneger;
bool on = false;

unsigned long MOVING_TIME = 2500; // moving time is 3 seconds
unsigned long moveStartTime;
int startAngle = MIN; // 30°
int stopAngle  = MAX; // 90°
                   

void setup()
{
  Serial.begin(9600);
  my_servo.attach(A1);                                
}

void loop()
{
  static bool is_openned = false;

  if (sr04Maneger.distance_cm(40) == true)
  {
    if (not is_openned)
    {
      moveStartTime = millis();
      unsigned long time_to_convert = 0;
        // my_servo.write(startAngle);
      while (true)
      {
        time_to_convert = millis() - moveStartTime;
        if (time_to_convert > 1000) break;
        unsigned long time_to_angle = map(time_to_convert, 0, 1000, stopAngle, startAngle);
        my_servo.write(time_to_angle);
      }
      is_openned = true;
    }
  }
  else
  {
    if (is_openned)
    {
      moveStartTime = millis();
      unsigned long time_to_convert = 0;
        // my_servo.write(stopAngle);

      while (true)
      {
        time_to_convert = millis() - moveStartTime;
        if (time_to_convert > MOVING_TIME) break;
        unsigned long time_to_angle = map(time_to_convert, 0, MOVING_TIME, startAngle, stopAngle);
        my_servo.write(time_to_angle);
      }
      is_openned = false;
    }
  }
  Serial.println(sr04Maneger.distance_cm(40));
}

/*

#include <Servo.h>

Servo myServo;
unsigned long MOVING_TIME = 3000; // moving time is 3 seconds
unsigned long moveStartTime;
int startAngle = 30; // 30°
int stopAngle  = 90; // 90°

void setup() {
  myServo.attach(9);
  moveStartTime = millis(); // start moving

  // TODO: other code
}

void loop() {
  unsigned long progress = millis() - moveStartTime;

  if (progress <= MOVING_TIME) {
    long angle = map(progress, 0, MOVING_TIME, startAngle, stopAngle);
    myServo.write(angle); 
  }

  // TODO: other code
}

*/