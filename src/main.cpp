#include <Arduino.h>
#include <Servo.h>
#include "SR04Maneger.h"

#define MAX 120
#define MIN 70

Servo my_servo;
int pos = 0;
SR04Maneger sr04Maneger;
bool on = false;

unsigned long MOVING_TIME = 400;
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
  static bool is_openned = true;

  if (sr04Maneger.distance_cm(20.0f) == true)
  {
    if (not is_openned)
    {
      moveStartTime = millis();
      unsigned long time_to_convert = 0;
      while (true)
      {
        time_to_convert = millis() - moveStartTime;
        if (time_to_convert > 500) break;
        unsigned long time_to_angle = map(time_to_convert, 0, 500, stopAngle, startAngle);
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
}
