#pragma once
#include "LedCPWM.hpp"
#include "esp_log.h"

template<ledc_timer_t timer>
LedCPWM<timer>::LedCPWM(ledc_channel_t channel, int gpioNumber, ledc_timer_bit_t dutyResolution, uint32_t timerFrequencyHz) : TimerPWMAbs(dutyResolution,timerFrequencyHz){
    if(timerIsConfigured_)
        ESP_LOGW("LedCPWM", "Redifinition of timer: %d (redefining the frequency)",static_cast<int>(timer));

    const ledc_timer_config_t timerConfig{
        .speed_mode = ledc_mode_t::LEDC_LOW_SPEED_MODE,
        .duty_resolution = dutyResolution,
        .timer_num = timer,
        .freq_hz = timerFrequencyHz,
        .clk_cfg = LEDC_AUTO_CLK,
        .deconfigure = false
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timerConfig));
    createChannelForTimer(channel,gpioNumber);

}

template<ledc_timer_t timer>
LedCPWM<timer>::LedCPWM(ledc_channel_t channel, int gpioNumber){
    if(!timerIsConfigured_)
        ESP_LOGE("LedCPWM", "Trying to assign a channel to a timer that isnt instantiated");
    createChannelForTimer(channel,gpioNumber);
}

template<ledc_timer_t timer>
void LedCPWM<timer>::createChannelForTimer(ledc_channel_t channel, int gpioNumber){
    const ledc_channel_config_t channelConfig{
        .gpio_num = gpioNumber,
        .speed_mode     = ledc_mode_t::LEDC_LOW_SPEED_MODE,
        .channel        = channel,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = timer,
        .duty           = 0,
        .hpoint         = 0,

    };

    ESP_ERROR_CHECK(ledc_channel_config(&channelConfig));
}

template<ledc_timer_t timer>
void LedCPWM<timer>::setPwmTicks(const uint16_t pwm) {

}
template<ledc_timer_t timer>
void LedCPWM<timer>::enableOnce(){
}

template<ledc_timer_t timer>
void LedCPWM<timer>::disableOnce(){
}