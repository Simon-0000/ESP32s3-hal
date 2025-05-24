#pragma once
#include "TimerPWM.hpp"
#include "driver/ledc.h"

template<ledc_timer_t timer>
class LedCPWM : public TimerPWMAbs<timer> {
public:
    LedCPWM(ledc_channel_t channel, int gpioNumber, ledc_timer_bit_t dutyResolution, uint32_t timerFrequencyHz);
    LedCPWM(ledc_channel_t channel, int gpioNumber);

    void setPwmTicks(const uint16_t pwmTicks) override;
protected:
    esp_err_t enableOnce() override;
    esp_err_t disableOnce() override;
private:
    void createChannelForTimer(ledc_channel_t channel, int gpioNumber);
    static inline bool timerIsConfigured_ = false; 
};

#include "../template/LedCPWM.tpp"