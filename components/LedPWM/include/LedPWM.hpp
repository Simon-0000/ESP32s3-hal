#pragma once
#include "TimerPWM.hpp"
class LedPWM : public TimerPWM{
public:
    void setPwm(const uint32_t pwm) override;

protected:
    void enableTimer() override;
    void disableTimer() override;
private:


};

#include "LedPWM.tpp"