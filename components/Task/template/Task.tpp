#include "Task.hpp"
#include "esp_log.h"

static const char* TAG = "TASK";

template <size_t NStackSize>
void Task<NStackSize>::setStatus(const TaskStatus& status){
    switch(status)
    {
        case TaskStatus::STARTED:
            start();
            break;
        case TaskStatus::STOPPED:
            stop();
            break;
        case TaskStatus::SUSPENDED:
            suspend();
            break;
    }
}

template <size_t NStackSize>
TaskStatus Task<NStackSize>::getStatus(){
    return status;
}


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
        status = TaskStatus::STOPPED;
        vTaskDelete(handle_);
        onStop();
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
            onInit();
            handle_ = xTaskCreateStaticPinnedToCore(runTask, name_, NStackSize, (void*)this, priority_, stack_.data(), &taskBuffer_, coreId_);
            break;
    }

}

template<size_t NStackSize>
void Task<NStackSize>::bindLocally(Chainable* parent) {
    if (Task<NStackSize>* parentTask = dynamic_cast<Task<NStackSize>*>(parent))
        setStatus(parentTask->getStatus());
}


template <size_t NStackSize>
void Task<NStackSize>::runTask(void* pvParameters) {            
    static_cast<Task<NStackSize>*>(pvParameters)->run(); 
}

