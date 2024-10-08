#pragma once
#include "driver/gpio.h"

class Gpio{
public:
    Gpio(gpio_num_t gpioPin, const gpio_mode_t ioMode);
    bool isHigh();
    void setState(bool pulledHigh);
private:
    gpio_num_t  gpioPin_;
};