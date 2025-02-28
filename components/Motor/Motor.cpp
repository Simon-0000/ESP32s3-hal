#include "Motor.hpp"
#include <esp_check.h>

Motor::Motor(TimerPWM* pwmTimer) : EnableableSmart(pwmTimer),
        timer_(pwmTimer)
{
    linkChild(pwmTimer);
    setPwm(0);
}

void Motor::setPwm(const uint16_t pwm){
    timer_->setPwm(currentPwm_ = pwm);
    syncChildren();
}
void Motor::setPwmTicks(const uint16_t pwmTicks){
    timer_->setPwmTicks(pwmTicks);
    currentPwm_ = timer_->ticksToPwm(pwmTicks);
    syncChildren();
}

// void Motor::syncSelf() {
//     EnableableSmart::syncSelf();
//     if (Motor* motor = dynamic_cast<Motor*>(parent_))
//         setPwm(motor->currentPwm_);
// }

esp_err_t Motor::enableOnce() {
    return timer_->start();
}
esp_err_t Motor::disableOnce() {
    return timer_->stop();
}

