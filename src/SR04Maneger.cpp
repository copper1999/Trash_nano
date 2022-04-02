#include "SR04Maneger.h"

SR04Maneger::SR04Maneger(/* args */)
{
    m_hcsr04 = new UltraSonicDistanceSensor(A5, A4);
    m_distance = 0;
    m_action = false;
}

SR04Maneger::~SR04Maneger()
{
    delete m_hcsr04;
}

bool SR04Maneger::distance_cm(int value)
{
    static unsigned long last_time = 0;
    if (millis() - last_time < 3000)
    {
        return m_action;
    }
    
    m_distance = m_hcsr04->measureDistanceCm();
    if (m_distance <= value)
    {
       m_action = true;
    } else m_action = false;
    last_time = millis();
    return m_action;
}
