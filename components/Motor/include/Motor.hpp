#pragma once
#include "TimerPWM.hpp"
#include "Gpio.hpp"
#include "Enableable.hpp"

#include <cstdlib>


class Motor : public EnableableSmart{
public:
    Motor(TimerPWM* pwmTimer);
    void syncSelf(uint8_t eventId) override;
    
protected:
    void setPwm(const uint16_t speed);
    void setPwmTicks(const uint16_t pwmTicks);
    esp_err_t enableOnce() override;
    esp_err_t disableOnce() override;
    


    TimerPWM* timer_;
    int16_t currentPwm_;
};

