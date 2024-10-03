#include "driver/mcpwm_prelude.h"


template<mcpwm_timer_clock_source_t clkSrc, uint32_t groupId>
class MotorControlPWM{
public:
    MotorControlPWM(int pwmGpio, const uint32_t timerResolutionHz,const uint32_t ticksPeriod, const mcpwm_timer_count_mode_t countMode);

    void setPwm();
    void toggle();
    void enable();
    void disable();
private:
    void generateComparator();
    static void generateTimerAndOperator(const uint32_t timerResolutionHz,const uint32_t ticksPeriod, const mcpwm_timer_count_mode_t countMode);

    int pwmGpio_; 
    mcpwm_cmpr_handle_t comparator_ = NULL;
    mcpwm_gen_handle_t generator_ = NULL;
    static inline mcpwm_timer_handle_t timer_ = NULL;
    static inline mcpwm_oper_handle_t operator_ = NULL;


    
};