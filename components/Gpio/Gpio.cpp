#include "Gpio.hpp"


Gpio::Gpio(gpio_num_t gpioPin, const gpio_mode_t mode) : gpioPin_(gpioPin)
{
    gpio_config_t config = {
        1ULL << gpioPin,
        mode,
        GPIO_PULLUP_DISABLE,
        GPIO_PULLDOWN_ENABLE,
        GPIO_INTR_DISABLE
    };
    ESP_ERROR_CHECK(gpio_config(&config));
}
bool Gpio::isHigh(){
    return gpio_get_level(gpioPin_);
}
void Gpio::setState(bool pulledHigh){
    ESP_ERROR_CHECK(gpio_set_level(gpioPin_,pulledHigh));
}
