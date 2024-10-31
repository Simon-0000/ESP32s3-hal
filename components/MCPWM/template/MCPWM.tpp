#pragma once
#include "MCPWM.hpp"
#include "esp_log.h"

template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
MCPWM<clkSrc,groupId>::MCPWM(const int pwmGpio,const mcpwm_timer_count_mode_t countMode, const uint32_t timerResolutionHz,const uint32_t ticksPeriod):
    TimerPWM(timerResolutionHz), pwmGpio_(pwmGpio)
{
    if(timer_ == NULL)
        ESP_LOGW("MCPWM", "Redifinition of timer (and operator) of clkSrc: %d, groupeId: %d",static_cast<int>(clkSrc),static_cast<int>(groupId));

    createTimerAndOperator(timerResolutionHz,ticksPeriod,countMode);
    createComparatorAndGenerator();

}
template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
MCPWM<clkSrc,groupId>::MCPWM(const int pwmGpio) : pwmGpio_(pwmGpio)
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
        .flags = {}
    };

    ESP_ERROR_CHECK(mcpwm_new_timer(&timerConfig, &timer_));

    if(operator_ == NULL)
    {
        mcpwm_operator_config_t operatorConfig = {
            .group_id = groupId,
        };    
        ESP_ERROR_CHECK(mcpwm_new_operator(&operatorConfig,&operator_));
    }

    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(operator_, timer_));
}

template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
void MCPWM<clkSrc,groupId>::createComparatorAndGenerator(){


    mcpwm_comparator_config_t comparatorConfig = {
        .flags = {1,0,0}
    };
    // ESP_LOGI(TAG,"operator_ is :%d", static_cast<int>(operator_));
    ESP_ERROR_CHECK(mcpwm_new_comparator(operator_, &comparatorConfig, &comparator_));

    mcpwm_generator_config_t generatorConfig = {
        .gen_gpio_num = pwmGpio_,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(operator_, &generatorConfig, &generator_));
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(generator_,
            MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(generator_,
        MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comparator_, MCPWM_GEN_ACTION_LOW)));
}

template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupeId>
void MCPWM<clkSrc,groupeId>::setPwmTicks(const uint32_t pwmTicks)
{
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator_, pwmTicks));
}





template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
void MCPWM<clkSrc,groupId>::enableTimer(){
    ESP_LOGI("MCPWM", "ENABLE TIMER");
    ESP_ERROR_CHECK(mcpwm_timer_enable(timer_));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(timer_, MCPWM_TIMER_START_NO_STOP));

}
template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
void MCPWM<clkSrc,groupId>::disableTimer(){
    ESP_ERROR_CHECK(mcpwm_timer_disable(timer_));
}