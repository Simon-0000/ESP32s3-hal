#pragma once
#include <cstdint>

class TimerPWM{
public:
    virtual ~TimerPWM() = default;
    virtual void setPwm(const uint32_t pwm) = 0;
    void enable(){
        enableTimer();
        isEnabled_ = true;
    }
    void disable() {
        disableTimer();
        isEnabled_ = false;
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

};