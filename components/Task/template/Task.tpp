#include "Task.hpp"
#include "esp_log.h"

static const char* TAG = "TASK";

template <size_t NStackSize>
void Task<NStackSize>::suspend(){
    if(status == TaskStatus::SUSPENDED)
        ESP_LOGW(TAG, "Task was already suspended");
    else if(status == TaskStatus::STARTED){
        vTaskSuspend(handle_);
        onSuspend();
        status = TaskStatus::SUSPENDED;
    }
}

template <size_t NStackSize>
void Task<NStackSize>::stop(){
    if(status == TaskStatus::STOPPED)
        ESP_LOGW(TAG, "Task was already stopped");
    else
    {
        vTaskDelete(handle_);
        onStop();
        status = TaskStatus::STOPPED;
    }
}

template <size_t NStackSize>
void Task<NStackSize>::start(){
    switch (status)
    {
        case TaskStatus::STARTED:
            ESP_LOGW(TAG, "Task was already started");
            break;
        case TaskStatus::SUSPENDED:
            onResume();
            vTaskResume(handle_);
            break;
        case TaskStatus::STOPPED:
            status = TaskStatus::STARTED;
            handle_ = xTaskCreateStaticPinnedToCore(runTask, name_, NStackSize, (void*)this, priority_, stack_.data(), &taskBuffer_, coreId_);
            break;
    }

}
template <size_t NStackSize>
void Task<NStackSize>::runTask(void* pvParameters) {            
    // ((Task<NStackSize>*)pvParameters)->onInit();
    static_cast<Task<NStackSize>*>(pvParameters)->run(); 
}

// template<std::size_t NStackSize>
// void Task<NStackSize>::run(void*) {
//     run();
//     stop();
// }