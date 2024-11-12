#include "esp_log.h"
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "LedCPWM.hpp"
#include "TestTask.hpp"
#include "TestTaskMotor.hpp"

static const char* TAG_MAIN = "MAIN";


extern "C" void app_main(void)
{
    ESP_LOGI(TAG_MAIN,"HELLOOO!");
    TestTask test;
    TestTaskMotor testMotorTask;

    test.start();
    testMotorTask.start();
    
    while(true){
        vTaskDelay(20/portTICK_PERIOD_MS);    
    }
    // //Motor Tests
    // MCPWM<MCPWM_TIMER_CLK_SRC_DEFAULT,McpwmConfigs::TimerGroup::GROUP_0> mcPWM(0,mcpwm_timer_count_mode_t::MCPWM_TIMER_COUNT_MODE_UP,10000,20000);
    // // LedCPWM<ledc_timer_t::LEDC_TIMER_0> ledcPWM(ledc_channel_t::LEDC_CHANNEL_0, 1,ledc_timer_bit_t::LEDC_TIMER_10_BIT,20000);
    // Gpio directionPin(gpio_num_t::GPIO_NUM_8,gpio_mode_t::GPIO_MODE_OUTPUT);
    // DCMotor motor(&mcPWM,&directionPin,true);
    
    // while(true){
    //     for(int i = INT32_MIN; i < INT32_MAX; i+= (UINT32_MAX / 255)){
    //         ESP_LOGI(TAG_MAIN,"speed: %d, pwm(percentage): %f direction: %d",i,abs(i)/(float)INT32_MAX * 100,i > 0);
    //         motor.setSpeed(static_cast<int32_t>(i));
    //         vTaskDelay(10/portTICK_PERIOD_MS);
    //     }
    // }
}
