#pragma once
#include "TimerPWM.hpp"
#include "Gpio.hpp"
#include "Chainable.hpp"
#include <cstdlib>


class DCMotor : public Chainable{
public:
    DCMotor(TimerPWM* pwmTimer, Gpio* directionPin, bool turnClockwise);
    void setSpeed(const int32_t speed);
    esp_err_t configureDirection(bool direction);
    void enable();
    void disable();
    void toggle();
    void bindLocally(Chainable* parent) override;

private:
    TimerPWM* timer_;
    Gpio* directionPin_;
    bool direction_;
    int32_t currentSpeed_;

};

