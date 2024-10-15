#pragma once
#include "TimerPWM.hpp"
#include "driver/ledc.h"

template<ledc_timer_t timer>
class LedCPWM : public TimerPWM {
public:
    LedCPWM(ledc_channel_t channel, int gpioNumber, ledc_timer_bit_t dutyResolution, uint32_t timerFrequencyHz);
    LedCPWM(ledc_channel_t channel, int gpioNumber);

    void setPwm(const uint32_t pwm);
    void setPwmTicks(const uint32_t pwmTicks) override;
protected:
    void enableTimer() override;
    void disableTimer() override;
private:
    void createChannelForTimer(ledc_channel_t channel, int gpioNumber);
    static inline bool timerIsConfigured_ = false; 
};

#include "../template/LedCPWM.tpp"