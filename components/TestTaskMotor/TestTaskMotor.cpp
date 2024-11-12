#include "TestTaskMotor.hpp"
#include "esp_log.h"


void TestTaskMotor::run() {

    while(true){
        for(int i = INT32_MIN; i < INT32_MAX; i+= (UINT32_MAX / 255)){
            ESP_LOGI("TEST TASK MOTOR","speed: %d, pwm(percentage): %f direction: %d",i,abs(i)/(float)INT32_MAX * 100,i > 0);
            motor_.setSpeed(static_cast<int32_t>(i));
            vTaskDelay(10/portTICK_PERIOD_MS);
        }
    }
}

void TestTaskMotor::onInit(){
    ESP_LOGI("TEST TASK MOTOR", "INIT");
    
}
void TestTaskMotor::onResume(){
    ESP_LOGI("TEST TASK MOTOR", "RESUME");
}
void TestTaskMotor::onStop(){
    ESP_LOGI("TEST TASK MOTOR", "STOP");
}
void TestTaskMotor::onSuspend(){
    ESP_LOGI("TEST TASK MOTOR", "SUSPEND");
}