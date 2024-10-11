#include "esp_log.h"
#include <stdio.h>
#include "MCPWM.hpp"
#include "Gpio.hpp"
#include "DCMotor.hpp"
#include "freertos/FreeRTOS.h"
static const char* TAG_MAIN = "MAIN";


extern "C" void app_main(void)
{
    ESP_LOGI(TAG_MAIN,"HELLOOO!");
    MCPWM<MCPWM_TIMER_CLK_SRC_DEFAULT,McpwmConfigs::TimerGroup::GROUP_0> mcPWM(0,mcpwm_timer_count_mode_t::MCPWM_TIMER_COUNT_MODE_UP,1000000,20000);
    Gpio directionPin(gpio_num_t::GPIO_NUM_8,gpio_mode_t::GPIO_MODE_OUTPUT);
    // directionPin.setState(true);
    DCMotor motor(&mcPWM,&directionPin,true);
    // mcPWM.setPwmTicks(19000);
    while(true){
        for(int i = INT32_MIN; i < INT32_MAX; i+=2000000){
            directionPin.setState(i%2);
            ESP_LOGI(TAG_MAIN,"speed: %d, pwm(percentage): %f direction: %d",i,abs(i)/(float)INT32_MAX * 100,i > 0);
            motor.setSpeed(static_cast<int32_t>(i));
            vTaskDelay(10/portTICK_PERIOD_MS);
        }
    }
}
