#pragma once
#include "TimerPWM.hpp"
#include "Gpio.hpp"
#include <cstdlib>


class DCMotor{
public:
    DCMotor(TimerPWM* pwmTimer, Gpio* directionPin, bool turnClockwise);
    void setSpeed(const int speed);
    esp_err_t setSpeedDirection(bool direction);
    void enable();
    void disable();
    void toggle();


private:
    TimerPWM* timer_;
    Gpio* directionPin_;
    bool direction_;
};

