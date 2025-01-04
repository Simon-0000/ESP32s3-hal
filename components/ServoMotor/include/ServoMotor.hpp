#pragma once
#include "Motor.hpp"
#include <cstdlib>



class ServoMotor : public Motor{
public:
    ServoMotor(TimerPWM* pwmTimer);
    ServoMotor(TimerPWM* pwmTimer, const int16_t minAngle, const int16_t maxAngle);
    void setAngle(int16_t angle);
private:
    static constexpr uint32_t FREQUENCY_REQUIREMENT = 50;
    const int16_t MIN_ANGLE, MAX_ANGLE;
    const float ANGLE_SCALER;

    static const uint16_t SERVO_MIN_PULSEWIDTH_US = 500;
    static const uint16_t SERVO_MAX_PULSEWIDTH_US = 2500;

    static const int16_t DEFAULT_MIN_ANGLE = -90,  DEFAULT_MAX_ANGLE = 90;
     
};

