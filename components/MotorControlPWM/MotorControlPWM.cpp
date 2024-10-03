#include "MotorControlPWM.hpp"
#include "esp_log.h"
static const char* TAG = "MotorControlPWM";


template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
MotorControlPWM<clkSrc,groupId>::MotorControlPWM(int pwmGpio, const uint32_t timerResolutionHz,const uint32_t ticksPeriod, const mcpwm_timer_count_mode_t countMode):
pwmGpio_(pwmGpio)
{
    if(timer_ == NULL)
        ESP_LOGW(TAG, "Redifinition of timer (and operator) of clkSrc: %d, groupeId: %d",clkSrc,groupId);

    generateTimerAndOperator(timerResolutionHz,ticksPeriod,countMode);
    
    // mcpwm_oper_handle_t oper = NULL;
    // mcpwm_operator_config_t operator_config = {
    //     .group_id = 0, // operator must be in the same group to the timer
    // };

}


template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
void MotorControlPWM<clkSrc,groupId>::generateTimerAndOperator(const uint32_t timerResolutionHz,const uint32_t ticksPeriod, const mcpwm_timer_count_mode_t countMode)
{
    mcpwm_timer_config_t timerConfig = {
        .group_id = groupId,
        .clk_src = clkSrc,
        .resolution_hz = timerResolutionHz,
        .period_ticks = ticksPeriod,
        .count_mode = countMode,
    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&timerConfig, &timer_));

    if(operator_ != NULL)
    {
        mcpwm_operator_config_t operatorConfig = {
            .group_id = groupId,
        };    
        ESP_ERROR_CHECK(mcpwm_new_operator(&operatorConfig,&operator_));
    }

    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(operator_, timer_));


}


template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
void MotorControlPWM<clkSrc,groupId>::generateComparator(){


    mcpwm_comparator_config_t comparatorConfig = {
        .update_cmp_on_tez = true,
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(operator_, &comparatorConfig, &comparator_));

    mcpwm_generator_config_t generatorConfig = {
        .gen_gpio_num = pwmGpio_,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(operator_, &generatorConfig, &generator_));
}