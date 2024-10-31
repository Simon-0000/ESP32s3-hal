#pragma once
#include <cstdint>
#include <esp_log.h>
class TimerPWM{
public:
    TimerPWM() = default;
    TimerPWM(const uint32_t dutyResolution) {dutyResolution_ = dutyResolution;}
    virtual ~TimerPWM() = default;
    
    virtual void setPwmTicks(const uint32_t pwmTicks) = 0;
    virtual void setPwm(const uint32_t pwm) {
        ESP_LOGI("TimerPWM","resolution: %d, speed: %d",static_cast<int>(dutyResolution_), static_cast<int> (pwm / static_cast<float>(UINT32_MAX) * dutyResolution_));
        setPwmTicks(pwm / static_cast<float>(UINT32_MAX) * dutyResolution_);
    }
    void enable(){
        if(isEnabled_ == false){
            enableTimer();
            isEnabled_ = true;
        }
    }
    void disable() {
        if(isEnabled_){
            disableTimer();
            isEnabled_ = false;
        }

    }
    void toggle() {
        if(isEnabled_)
            disable();
        else
            enable();
    }
protected:
    virtual void enableTimer() = 0;
    virtual void disableTimer() = 0;
private:
    bool isEnabled_ = false;
    static inline uint32_t dutyResolution_ = UINT32_MAX;

};