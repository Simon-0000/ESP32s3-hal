#pragma once
#include "driver/mcpwm_prelude.h"
#include "McpwmConfigs.hpp"
#include "TimerPWM.hpp"
#include "driver/gpio.h"

using namespace McpwmConfigs;

template<TimerGroup groupId>
class MCPWM : public TimerPWMAbs<groupId>{
public:
    MCPWM(const gpio_num_t pwmGpio, const uint32_t pwmFrequencyHz, const uint32_t dutyResolution);
    MCPWM(const gpio_num_t pwmGpio);
    void setPwmTicks(const uint16_t pwmTicks) override;
protected:
    esp_err_t enableOnce() override;
    esp_err_t disableOnce() override;
private:
    void createTimer(const uint32_t timerResolutionHz,const uint32_t ticksPeriod);
    void createOperatorComparatorGenerator();

    const gpio_num_t pwmGpio_; 

    static inline mcpwm_timer_handle_t timer_ = NULL;
    static inline uint8_t mcpwmCounter_ = 0;
    mcpwm_cmpr_handle_t comparator_ = NULL;
    mcpwm_gen_handle_t generator_ = NULL;
    mcpwm_oper_handle_t operator_ = NULL;  

    static constexpr mcpwm_timer_count_mode_t DEFAULT_COUNT_MODE = MCPWM_TIMER_COUNT_MODE_UP;
    static constexpr mcpwm_timer_clock_source_t DEFAULT_CLK_SRC = MCPWM_TIMER_CLK_SRC_DEFAULT;
    static constexpr uint8_t MAX_OPERATORS_PER_GROUP = 3;
};

#include "../template/MCPWM.tpp"
