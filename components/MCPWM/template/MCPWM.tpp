#pragma once
#include "MCPWM.hpp"
#include "esp_log.h"

template<TimerGroup groupId>
MCPWM<groupId>::MCPWM(const gpio_num_t pwmGpio, const uint32_t pwmFrequencyHz, const uint32_t dutyResolution):
    TimerPWMAbs<groupId>(dutyResolution, pwmFrequencyHz), pwmGpio_(pwmGpio)
{
    if(timer_ != NULL)
        ESP_LOGW("MCPWM", "Redifinition of timer from groupeId: %d", static_cast<int>(groupId));

    createTimer(dutyResolution*pwmFrequencyHz, dutyResolution);
    createOperatorComparatorGenerator();
}

template<TimerGroup groupId>
MCPWM<groupId>::MCPWM(const gpio_num_t pwmGpio) : pwmGpio_(pwmGpio)
{
    if(timer_ == NULL)
        ESP_LOGE("MCPWM", "Undefined timer for groupeId: %d", static_cast<int>(groupId));
    else
        createOperatorComparatorGenerator();
}


template<TimerGroup groupId>
void MCPWM<groupId>::createTimer(const uint32_t timerResolutionHz,const uint32_t ticksPeriod)
{
    
    mcpwm_timer_config_t timerConfig = {
        .group_id = groupId,
        .clk_src = DEFAULT_CLK_SRC,
        .resolution_hz = timerResolutionHz,
        .count_mode = DEFAULT_COUNT_MODE,
        .period_ticks = ticksPeriod,
        .intr_priority = 0,
        .flags = {}
    };

    ESP_ERROR_CHECK(mcpwm_new_timer(&timerConfig, &timer_));
}

template<TimerGroup groupId>
void MCPWM<groupId>::createOperatorComparatorGenerator(){
    if(mcpwmCounter_ == MAX_OPERATORS_PER_GROUP - 1)
        ESP_LOGE("MCPWM", "Too many pwm are initialized in group %d (the max is %d)", static_cast<int>(groupId),static_cast<int>(MAX_OPERATORS_PER_GROUP));

    mcpwm_operator_config_t operatorConfig = {
        .group_id = groupId,
        .intr_priority = {},
        .flags = {}
    };    
    ESP_ERROR_CHECK(mcpwm_new_operator(&operatorConfig,&operator_));

    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(operator_, timer_));

    mcpwm_comparator_config_t comparatorConfig = {
        .intr_priority{},
        .flags = {1,0,0}
    };

    ESP_ERROR_CHECK(mcpwm_new_comparator(operator_, &comparatorConfig, &comparator_));

    mcpwm_generator_config_t generatorConfig = {
        .gen_gpio_num = pwmGpio_,
        .flags = {}
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(operator_, &generatorConfig, &generator_));
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(generator_,
            MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(generator_,
        MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comparator_, MCPWM_GEN_ACTION_LOW)));

    ++mcpwmCounter_;
}

template<TimerGroup groupId>
void MCPWM<groupId>::setPwmTicks(const uint16_t pwmTicks)
{
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator_, pwmTicks));
}

template<TimerGroup groupId>
esp_err_t MCPWM<groupId>::enableOnce(){
    esp_err_t err = mcpwm_timer_enable(timer_);
    if (err == ESP_OK)
        err = mcpwm_timer_start_stop(timer_, MCPWM_TIMER_START_NO_STOP);
    return err;
}
template<TimerGroup groupId>
esp_err_t MCPWM<groupId>::disableOnce(){
    return mcpwm_timer_disable(timer_);
}