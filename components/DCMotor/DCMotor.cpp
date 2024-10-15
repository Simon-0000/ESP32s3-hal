#include "DCMotor.hpp"
#include <esp_check.h>

static const char* TAG = "DCMotor";
DCMotor::DCMotor(TimerPWM* pwmTimer, Gpio* directionPin, bool turnClockwise) : 
        timer_(pwmTimer), directionPin_(directionPin), direction_(!turnClockwise) 
{
    
    ESP_ERROR_CHECK(configureDirection(direction_));
    setSpeed(0);
    enable();
}

void DCMotor::setSpeed(const int32_t speed){
    currentSpeed_ = speed;
    timer_->setPwm(static_cast<uint32_t>(abs(currentSpeed_)<<1));
    directionPin_->setState(currentSpeed_ >= 0? direction_ : !direction_);
    bindChildrens();
}
esp_err_t DCMotor::configureDirection(bool direction){
    ESP_RETURN_ON_FALSE(directionPin_->isOutput(),ESP_ERR_INVALID_ARG,TAG, "gpio pin should be an output pin");
    directionPin_->setState(direction);
    direction_ = direction;
    return ESP_OK;
}

void DCMotor::enable(){timer_->enable();}
void DCMotor::disable(){timer_->disable();}
void DCMotor::toggle(){timer_->toggle();}

void DCMotor::bindLocally(Chainable* parent) {
    if (DCMotor* motor = dynamic_cast<DCMotor*>(parent))
        setSpeed(motor->currentSpeed_);
}



