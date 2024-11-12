#include "Task.hpp"
#include "esp_log.h"

static const char* TAG = "TASK";

void Task::setStatus(const TaskStatus& status){
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

TaskStatus Task::getStatus(){
    return status;
}


void Task::suspend(){
    if(status == TaskStatus::SUSPENDED)
        ESP_LOGW(TAG, "Task was already suspended");
    else if(status == TaskStatus::STARTED){
        vTaskSuspend(handle_);
        onSuspend();
        status = TaskStatus::SUSPENDED;
    }
}

void Task::stop(){
    if(status == TaskStatus::STOPPED)
        ESP_LOGW(TAG, "Task was already stopped");
    else
    {
        status = TaskStatus::STOPPED;
        vTaskDelete(handle_);
        onStop();
    }
}

void Task::start(){
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
            xTaskCreatePinnedToCore(runTask, name_, stackSize_, (void*)this, priority_, &handle_, coreId_);
            break;
    }

}

void Task::bindLocally(Chainable* parent) {
    if (Task* parentTask = dynamic_cast<Task*>(parent))
        setStatus(parentTask->getStatus());
}


void Task::runTask(void* pvParameters) {            
    static_cast<Task*>(pvParameters)->run(); 
}

