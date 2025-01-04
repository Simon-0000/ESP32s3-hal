#pragma once
#include <cstdint>
#include <esp_log.h>
#include "Enableable.hpp"

class TimerPWM : public EnableableSmart{
public:
    TimerPWM(std::shared_ptr<bool> isEnabled) : EnableableSmart(isEnabled) {}

    virtual ~TimerPWM() = default;
    virtual void setPwmTicks(const uint16_t pwmTicks) = 0;
    virtual void setPwm(const uint16_t pwm) = 0;
    virtual inline uint16_t ticksToPwm(const uint16_t pwmTicks) = 0;
    virtual inline uint16_t pwmToTicks(const uint16_t pwm) = 0;

    virtual inline uint32_t getFrequency() const = 0;
    virtual inline uint32_t getDutyResolution() const = 0;
};


template<uint8_t id = 1>//to allow multiple instance to inherit from the same timer's attributes ex: 2 mcpwm from the same timer will share the same frequency/dutycycle
class TimerPWMAbs : public TimerPWM{
public:
    TimerPWMAbs() : TimerPWM(isEnabled_) {}
    
    TimerPWMAbs(const uint32_t dutyResolution, const uint32_t frequency) : TimerPWMAbs() {
        ESP_LOGI("TIMERPWM","HERE id: %d, res: %d, freq: %d",static_cast<int>(id),static_cast<int>(dutyResolution),static_cast<int>(frequency));
        dutyResolution_ = dutyResolution;
        frequency_ = frequency;
    }
    
    void setPwm(const uint16_t pwm) override{
        if(!(*isEnabled_))
            ESP_LOGW("TimerPWMAbs","Setting a pwm when the timer isnt enabled");

        setPwmTicks(pwmToTicks(pwm));
    }

    inline uint16_t pwmToTicks(const uint16_t pwm) override {
        return pwm / static_cast<float>(UINT16_MAX) * dutyResolution_;
    }
    inline uint16_t ticksToPwm(const uint16_t pwmTicks) override {
        return pwmTicks / static_cast<float>(dutyResolution_) * UINT16_MAX;
    }


    uint32_t inline getFrequency() const override{
        return frequency_;
    }
    uint32_t inline getDutyResolution() const override{
        return dutyResolution_;
    }
protected:

    static inline uint32_t dutyResolution_ = UINT32_MAX;
    static inline uint32_t frequency_ = 1;
    
private:
    static inline std::shared_ptr<bool> isEnabled_ = std::make_shared<bool>(false);
};