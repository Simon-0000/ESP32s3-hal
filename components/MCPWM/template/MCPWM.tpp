#pragma once
#include "MCPWM.hpp"
#include "esp_log.h"


template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
MCPWM<clkSrc,groupId>::MCPWM(const int pwmGpio,const mcpwm_timer_count_mode_t countMode, const uint32_t timerResolutionHz,const uint32_t ticksPeriod):
    pwmGpio_(pwmGpio)
{
    ticksThreshold_ = ticksPeriod;
    // // if(timer_ == NULL)
    // //     ESP_LOGW(TAG, "Redifinition of timer (and operator) of clkSrc: %d, groupeId: %d",clkSrc,groupId);

    createTimerAndOperator(timerResolutionHz,ticksPeriod,countMode);
    createComparatorAndGenerator();
}
template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
MCPWM<clkSrc,groupId>::MCPWM(const int pwmGpio): pwmGpio_(pwmGpio)
{
    createComparatorAndGenerator();
}


template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
void MCPWM<clkSrc,groupId>::createTimerAndOperator(const uint32_t timerResolutionHz,const uint32_t ticksPeriod, const mcpwm_timer_count_mode_t countMode)
{
    
    mcpwm_timer_config_t timerConfig = {
        .group_id = groupId,
        .clk_src = clkSrc,
        .resolution_hz = timerResolutionHz,
        .count_mode = countMode,
        .period_ticks = ticksPeriod,
        .intr_priority = 0,
        .flags = {1,0}
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&timerConfig, &timer_));

    if(operator_ == NULL)
    {
        mcpwm_operator_config_t operatorConfig = {
            groupId,
            0,
            {}
        };    
        ESP_ERROR_CHECK(mcpwm_new_operator(&operatorConfig,&operator_));
    }

    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(operator_, timer_));
}

template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
void MCPWM<clkSrc,groupId>::createComparatorAndGenerator(){


    mcpwm_comparator_config_t comparatorConfig = {
        .intr_priority = 0,
        .flags = {1,0,0}
    };
    // ESP_LOGI(TAG,"operator_ is :%d", static_cast<int>(operator_));
    ESP_ERROR_CHECK(mcpwm_new_comparator(operator_, &comparatorConfig, &comparator_));

    mcpwm_generator_config_t generatorConfig = {
        .gen_gpio_num = pwmGpio_,
        .flags = {}
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(operator_, &generatorConfig, &generator_));
}

template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupeId>
void MCPWM<clkSrc,groupeId>::setPwmTicks(const uint32_t pwmTicks)
{
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator_, pwmTicks));
}
template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupeId>
void MCPWM<clkSrc,groupeId>::setPwm(const uint32_t pwm)
{
    setPwmTicks(pwm / static_cast<float>(UINT32_MAX) * ticksThreshold_);
}




template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
void MCPWM<clkSrc,groupId>::enableTimer(){
    mcpwm_timer_enable(timer_);
}
template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
void MCPWM<clkSrc,groupId>::disableTimer(){
    mcpwm_timer_disable(timer_);
}