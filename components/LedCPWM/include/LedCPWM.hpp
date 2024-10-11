#pragma once
#include "TimerPWM.hpp"
#include "driver/ledc.h"

template<ledc_timer_t timerSrc>
class LedCPWM : public TimerPWM{
public:
    LedCPWM();
    void setPwm(const uint32_t pwm) override;

protected:
    void enableTimer() override;
    void disableTimer() override;
private:


};

#include "LedCPWM.tpp"