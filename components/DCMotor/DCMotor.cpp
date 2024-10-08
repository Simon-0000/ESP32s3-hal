#include "DCMotor.hpp"
#include <esp_check.h>

static const char* TAG = "DCMotor";
DCMotor::DCMotor(TimerPWM* pwmTimer, Gpio* directionPin, bool turnClockwise) : 
        timer_(pwmTimer), directionPin_(directionPin), direction_(!turnClockwise) 
{
    
    ESP_ERROR_CHECK(setSpeedDirection(direction_));
    setSpeed(0);
}

void DCMotor::setSpeed(const int speed){
    timer_->setPwm(static_cast<uint32_t>(abs(speed)));
    directionPin_->setState(speed >= 0? direction_ : !direction_);
}
esp_err_t DCMotor::setSpeedDirection(bool direction){
    ESP_RETURN_ON_FALSE(directionPin_->isOutput(),ESP_ERR_INVALID_ARG,TAG, "gpio pin should be an output pin");
    directionPin_->setState(direction);
    direction_ = direction;
    return ESP_OK;
}

void DCMotor::enable(){timer_->enable();}
void DCMotor::disable(){timer_->disable();}
void DCMotor::toggle(){timer_->toggle();}




