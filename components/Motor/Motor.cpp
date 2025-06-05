#include "Motor.hpp"
#include <esp_check.h>
#include "esp_log.h"

Motor::Motor(TimerPWM* pwmTimer) : EnableableSmart(pwmTimer),
        timer_(pwmTimer)
{
    setPwm(0);
}

void Motor::setPwm(const uint16_t pwm){
    timer_->setPwm(currentPwm_ = pwm);
    syncChildren(System::getUniqueId<Motor>());
}
void Motor::setPwmTicks(const uint16_t pwmTicks){
    timer_->setPwmTicks(pwmTicks);
    currentPwm_ = timer_->ticksToPwm(pwmTicks);
    syncChildren(System::getUniqueId<Motor>());
}

esp_err_t Motor::enableOnce() {
    return timer_->start();
}
esp_err_t Motor::disableOnce() {
    return timer_->stop();
}

void Motor::syncSelf(uint8_t  eventId) {
    EnableableSmart::syncSelf(eventId);
    if(parent_ && eventId == System::getUniqueId<Motor>()){
        setPwm(static_cast<Motor*>(parent_)->currentPwm_);
    }

}
