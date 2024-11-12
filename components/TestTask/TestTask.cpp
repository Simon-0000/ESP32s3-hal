#include "TestTask.hpp"
#include "esp_log.h"

void TestTask::run() {
    while(true){
        ESP_LOGI("TEST TASK", ".");
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}

void TestTask::onInit(){
    // ESP_LOGI("TEST TASK", "INIT");
}
void TestTask::onResume(){
    // ESP_LOGI("TEST TASK", "RESUME");
}
void TestTask::onStop(){
    // ESP_LOGI("TEST TASK", "STOP");
}
void TestTask::onSuspend(){
    // ESP_LOGI("TEST TASK", "SUSPEND");
}