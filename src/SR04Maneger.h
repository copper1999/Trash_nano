#ifndef __SR04MANEGER_H__
#define __SR04MANEGER_H__

#include <HCSR04.h>
#include <Arduino.h>

class SR04Maneger
{
private:
    UltraSonicDistanceSensor *m_hcsr04;
    float m_distance;
    bool m_action;

public:
    SR04Maneger(/* args */);
    ~SR04Maneger();
    bool distance_cm(float value);
};

#endif // __SR04MANEGER_H__