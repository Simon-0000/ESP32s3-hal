#include "ServoMotor.hpp"

static const char* TAG = "ServoMotor";


ServoMotor::ServoMotor(TimerPWM* pwmTimer):ServoMotor(pwmTimer, DEFAULT_MIN_ANGLE, DEFAULT_MAX_ANGLE){}
ServoMotor::ServoMotor(TimerPWM* pwmTimer, const int16_t minAngle, const int16_t maxAngle):
    Motor(pwmTimer), MIN_ANGLE(minAngle), MAX_ANGLE(maxAngle), ANGLE_SCALER((SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / (MAX_ANGLE - MIN_ANGLE))
{    
    if(pwmTimer->getFrequency() != FREQUENCY_REQUIREMENT)
        ESP_LOGE(TAG,"Timer used for Servo, should be at %dHz. This class wasnt build for servos with a different frequency requirements",static_cast<int>(FREQUENCY_REQUIREMENT));
    
    
}

void ServoMotor::setAngle(int16_t angle){
    if (angle > MAX_ANGLE)
        angle = MAX_ANGLE;
    else if (angle < MIN_ANGLE)
        angle = MIN_ANGLE;

    setPwmTicks(SERVO_MIN_PULSEWIDTH_US + ANGLE_SCALER * (angle-MIN_ANGLE));
}
