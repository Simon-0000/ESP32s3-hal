#include "esp_log.h"
#include <stdio.h>
#include "MotorControlPWM.hpp"
#include "Gpio.hpp"
#include "DCMotor.hpp"
static const char* TAG_MAIN = "MAIN";

extern "C" void app_main(void)
{
    ESP_LOGI(TAG_MAIN,"HELLOOO!");
    MotorControlPWM<MCPWM_TIMER_CLK_SRC_DEFAULT,McpwmConfigs::TimerGroup::GROUP_0> mcPWM(7,mcpwm_timer_count_mode_t::MCPWM_TIMER_COUNT_MODE_UP,1000000,20000);
    Gpio directionPin(gpio_num_t::GPIO_NUM_8,gpio_mode_t::GPIO_MODE_OUTPUT);

    DCMotor motor(&mcPWM,&directionPin,true);
    while(true){

    }
}
