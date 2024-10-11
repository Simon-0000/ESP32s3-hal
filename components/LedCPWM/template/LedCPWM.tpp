#pragma once
#include "LedCPWM.hpp"

template<ledc_timer_t timerSrc>
LedCPWM<timerSrc>::LedCPWM(int gpioNumber, ledc_timer_bit_t dutyResolution, uint32_t timerFrequencyHz){
    ledc_timer_config_t timerConfig{
        .speed_mode = ledc_mode_t::LEDC_LOW_SPEED_MODE,
        .duty_resolution = dutyResolution,
        .timer_num = timerSrc,
        .freq_hz = timerFrequencyHz,
        .clk_cfg = LEDC_SLOW_CLK_RC_FAST,
        .deconfigure = false
    };
    ESP_ERROR_CHECK(ledc_timer_config(timerConfig));
    ledc_channel_config_t channelConfig{
        .gpio_num = gpioNumber,
    }
    // int gpio_num;                   /*!< the LEDC output gpio_num, if you want to use gpio16, gpio_num = 16 */
    // ledc_mode_t speed_mode;         /*!< LEDC speed speed_mode, high-speed mode (only exists on esp32) or low-speed mode */
    // ledc_channel_t channel;         /*!< LEDC channel (0 - LEDC_CHANNEL_MAX-1) */
    // ledc_intr_type_t intr_type;     /*!< configure interrupt, Fade interrupt enable  or Fade interrupt disable */
    // ledc_timer_t timer_sel;         /*!< Select the timer source of channel (0 - LEDC_TIMER_MAX-1) */
    // uint32_t duty;                  /*!< LEDC channel duty, the range of duty setting is [0, (2**duty_resolution)] */
    // int hpoint;                     /*!< LEDC channel hpoint value, the range is [0, (2**duty_resolution)-1] */
    // struct {
    //     unsigned int output_invert: 1;/*!< Enable (1) or disable (0) gpio output invert */
    // } flags;  

}

template<ledc_timer_t timerSrc>
void LedCPWM::setPwm(const uint32_t pwm) {

}

template<ledc_timer_t timerSrc>
void LedCPWM::enableTimer(){
    //TODO enable timer 
}

template<ledc_timer_t timerSrc>
void LedCPWM::disableTimer(){
    //TODO disable timer
}