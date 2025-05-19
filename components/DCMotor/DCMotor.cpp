#include "DCMotor.hpp"
#include <esp_check.h>

static const char* TAG = "DCMotor";
DCMotor::DCMotor(TimerPWM* pwmTimer, Gpio* directionPin, bool turnClockwise) : 
    Motor(pwmTimer), directionPin_(directionPin), direction_(!turnClockwise)
{
    ESP_ERROR_CHECK(configureDirection(direction_));
}

void DCMotor::setSpeed(const int16_t speed){
    directionPin_->setState(speed < 0? !direction_ : direction_);
    setPwm(static_cast<uint16_t>((abs(speed) << 1) - static_cast<int16_t>(speed < 0)));
}
esp_err_t DCMotor::configureDirection(bool direction){
    ESP_RETURN_ON_FALSE(directionPin_->isOutput(),ESP_ERR_INVALID_ARG,TAG, "DCMotor: gpio pin should be an output pin");
    directionPin_->setState(direction);
    direction_ = direction;
    return ESP_OK;
}

// void DCMotor::syncSelf(){
//     EnableableSmart::syncSelf();
//     if (DCMotor* motor = dynamic_cast<DCMotor*>(parent_))
//         setPwm(motor->currentPwm_);
// }
