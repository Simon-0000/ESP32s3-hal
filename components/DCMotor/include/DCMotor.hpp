#pragma once
#include "Motor.hpp"
#include <cstdlib>


class DCMotor : public Motor{
public:
    DCMotor(TimerPWM* pwmTimer, Gpio* directionPin, bool turnClockwise = true);
    void setSpeed(const int16_t speed);
    esp_err_t configureDirection(bool direction);
    void syncSelf() override;
private:
    Gpio* directionPin_;
    bool direction_;
};

