#pragma once
#include "freertos/FreeRTOS.h"
#include <array>



static const size_t ONE_KIBIBYTE = 1024;
template <size_t NStackSize = 5*ONE_KIBIBYTE>
class Task{
public:
    enum CoreId {PROTOCOL_CPU = 0, APP_CPU = 1, AUTOMATIC_CPU = tskNO_AFFINITY};

    Task(const char* const name, const CoreId coreId = AUTOMATIC_CPU, const UBaseType_t priority =DEFAULT_PRIORITY) : 
                                                                name_(name), priority_(priority), coreId_(coreId) {}
    virtual ~Task() = default;

    virtual void run() = 0;
    virtual void onInit() {}
    virtual void onStop() {}
    virtual void onSuspend() {}
    virtual void onResume() {}

    void suspend();
    void stop();
    void start();

private: 
	static void runTask(void* pvParameters);

    const char* const name_;
    const UBaseType_t priority_;
    const CoreId coreId_;

    enum class TaskStatus {STARTED, STOPPED, SUSPENDED};
    TaskStatus status = TaskStatus::STOPPED;


	std::array<StackType_t,NStackSize> stack_;
	StaticTask_t taskBuffer_;
    TaskHandle_t handle_;


    constexpr static uint32_t DEFAULT_PRIORITY = configMAX_PRIORITIES / 2;

};

#include "../template/Task.tpp"

