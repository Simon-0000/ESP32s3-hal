#pragma once
#include "driver/gpio.h"

class Gpio{
public:
    Gpio(gpio_num_t gpioPin, const gpio_mode_t ioMode);
    bool isHigh();
    void setState(bool pulledHigh);
    bool isInput() const;
    bool isOutput() const;
private:
    gpio_num_t  gpioPin_;
    bool isInput_, isOutput_;
     
};