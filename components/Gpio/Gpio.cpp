#include "Gpio.hpp"


Gpio::Gpio(gpio_num_t gpioPin, const gpio_mode_t mode) : gpioPin_(gpioPin)
{
    isInput_ = mode == gpio_mode_t::GPIO_MODE_INPUT || 
               mode == gpio_mode_t::GPIO_MODE_INPUT_OUTPUT || 
               mode == gpio_mode_t::GPIO_MODE_INPUT_OUTPUT_OD;
    isOutput_ = mode == gpio_mode_t::GPIO_MODE_OUTPUT || 
               mode == gpio_mode_t::GPIO_MODE_INPUT_OUTPUT || 
               mode == gpio_mode_t::GPIO_MODE_OUTPUT_OD || 
               mode == gpio_mode_t::GPIO_MODE_OUTPUT_OD;
               
    gpio_config_t config = {
        .pin_bit_mask = 1ULL << gpioPin,
        .mode = mode,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    ESP_ERROR_CHECK(gpio_config(&config));
}
bool Gpio::isHigh(){
    return gpio_get_level(gpioPin_);
}
void Gpio::setState(bool pulledHigh){
    ESP_ERROR_CHECK(gpio_set_level(gpioPin_,pulledHigh));
}

bool Gpio::isInput() const{
    return isInput_;
}
bool Gpio::isOutput() const{
    return isOutput_;
}