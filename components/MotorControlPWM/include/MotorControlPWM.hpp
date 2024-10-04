#pragma once
#include "driver/mcpwm_prelude.h"
#include "McpwmConfigs.hpp"

template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
class MotorControlPWM{
public:
    MotorControlPWM(const int pwmGpio, const mcpwm_timer_count_mode_t countMode, const uint32_t timerResolutionHz, const uint32_t ticksPeriod );
    MotorControlPWM(const int pwmGpio);
    void inline setPwmTicks(const uint32_t pwmTicks);
    void inline setPwmCalibrated(const uint32_t pwm);
    void toggleTimerGroup();//TODO add doc for specifying whats a timer group
    void enableTimerGroup();
    void disableTimerGroup();
private:
    void createComparatorAndGenerator();
    void createTimerAndOperator(const uint32_t timerResolutionHz,const uint32_t ticksPeriod, const mcpwm_timer_count_mode_t countMode);

    int pwmGpio_; 
    static inline bool groupIsEnabled_ = false;
    static inline uint32_t ticksThreshold_ = {};
    mcpwm_cmpr_handle_t comparator_ = NULL;
    mcpwm_gen_handle_t generator_ = NULL;
    mcpwm_timer_handle_t timer_ = NULL;
    mcpwm_oper_handle_t operator_ = NULL;  
};

#include "MotorControlPWM.tpp"
