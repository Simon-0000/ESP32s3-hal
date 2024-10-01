#include "driver/mcpwm_timer.h"

class MotorControlPWM{

public:
    MotorControlPWM();
    void setPwm();
    void toggle();
    void enable();
    void disable();
};