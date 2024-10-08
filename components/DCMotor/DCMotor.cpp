#include "DCMotor.hpp"

DCMotor::DCMotor(TimerPWM* pwmTimer, Gpio* directionPin, bool turnClockwise) : 
        timer_(pwmTimer), directionPin_(directionPin), direction_(!turnClockwise) 
{
    setSpeedDirection(direction_);
    setSpeed(0);
}

void DCMotor::setSpeed(const int speed){
    timer_->setPwm(static_cast<uint32_t>(abs(speed)));
    directionPin_->setState(speed >= 0? direction_ : !direction_);
}
void DCMotor::setSpeedDirection(bool direction){
    directionPin_->setState(direction);
    direction_ = direction;
}

void DCMotor::enable(){timer_->enable();}
void DCMotor::disable(){timer_->disable();}
void DCMotor::toggle(){timer_->toggle();}




