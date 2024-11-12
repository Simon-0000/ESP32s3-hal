#pragma once
#include "Task.hpp"
#include "MCPWM.hpp"
#include "Gpio.hpp"
#include "DCMotor.hpp"

class TestTaskMotor : public Task{
public:

    TestTaskMotor() : Task("testMotor"),
        mcPWM_(0,mcpwm_timer_count_mode_t::MCPWM_TIMER_COUNT_MODE_UP,10000,20000),
        directionPin_(gpio_num_t::GPIO_NUM_8,gpio_mode_t::GPIO_MODE_OUTPUT),
        motor_(&mcPWM_,&directionPin_,true) 
        {}
    void run() override;
    void onInit() override;
    void onStop() override;
    void onSuspend() override;
    void onResume() override;

private:
    // Motor Tests
    MCPWM<MCPWM_TIMER_CLK_SRC_DEFAULT,McpwmConfigs::TimerGroup::GROUP_0> mcPWM_;
    Gpio directionPin_;
    DCMotor motor_;
    // 
};