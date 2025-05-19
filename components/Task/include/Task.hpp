#pragma once
#include "freertos/FreeRTOS.h"
#include "Enableable.hpp"


enum class TaskStatus {RUNNING, STOPPED, SUSPENDED};


class Task : public EnableableSmart{
public:
    enum CoreId {PROTOCOL_CPU = 0, APP_CPU = 1, AUTOMATIC_CPU = tskNO_AFFINITY};

    Task(const char* const name, const CoreId coreId = AUTOMATIC_CPU, 
         const UBaseType_t priority = DEFAULT_PRIORITY, uint32_t stackSize = DEFAULT_STACK_SIZE) : 
            name_(name), priority_(priority), stackSize_(stackSize), coreId_(coreId){}
            
    virtual ~Task() = default;

    esp_err_t suspend();
    void syncSelf() override;
    bool isIdEqualTo(const uniqueId_t otherId) const override;
protected:
    esp_err_t enableOnce() override;
    esp_err_t disableOnce() override;

    virtual void run() = 0;
    virtual void onInit() {}
    virtual void onStop() {}
    virtual void onSuspend() {}
    virtual void onResume() {}
private: 
	static void runTask(void* pvParameters);

    const char* const name_;
    const UBaseType_t priority_;
    uint32_t stackSize_;

    const CoreId coreId_;

    TaskHandle_t handle_;
    bool isSuspended_ = false;


    constexpr static uint32_t DEFAULT_PRIORITY = configMAX_PRIORITIES / 2;
    constexpr static uint32_t DEFAULT_STACK_SIZE =  5 * 1024;


};

