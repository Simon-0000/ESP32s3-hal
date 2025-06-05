#include "Task.hpp"
#include "esp_log.h"

esp_err_t Task::suspend(){
    if(isSuspended_)
        return ESP_ERR_INVALID_STATE;
    else {
        vTaskSuspend(handle_);
        onSuspend();
        isSuspended_ = true;
        return ESP_OK;
    }
}


esp_err_t Task::disableOnce(){
    isSuspended_ = false;
    vTaskDelete(handle_);
    onStop();
    return ESP_OK;
}

esp_err_t Task::enableOnce(){
    if(isSuspended_){
        isSuspended_ = false;
        onResume();
        vTaskResume(handle_);
        return ESP_OK;
    }else{
        onInit();
        return xTaskCreatePinnedToCore(runTask, name_, stackSize_, (void*)this, priority_, &handle_, coreId_);
    }
    
}

void Task::syncSelf(uint8_t eventId) {
    EnableableSmart::syncSelf(eventId);
    if(parent_ && eventId == System::getUniqueId<Task>()){
        if(static_cast<Task*>(parent_)->isSuspended_)
            suspend();
    }

}

void Task::runTask(void* pvParameters) {            
    static_cast<Task*>(pvParameters)->run(); 
}

