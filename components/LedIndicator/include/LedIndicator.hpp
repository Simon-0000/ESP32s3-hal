#pragma once
#include "led_strip.h"

enum Color{
    NONE = 0,
    RED = 0xFF0000,
    GREEN = 0x00FF00,
    BLUE = 0x0000FF,

    YELLOW = 0xFFFF00,
    CYAN = 0x00FFFF,
    MAGENTA = 0xFF00FF,

    ORANGE = 0xFFA500,

};

class LedIndicator{
public:
    LedIndicator();
    ~LedIndicator();
    void setColor(uint32_t r, uint32_t g, uint32_t b);
    void setColor(Color color);
private:
    // static inline Color color_ = Color::NONE;
    static inline led_strip_handle_t led_ = NULL;
    static constexpr int ONBOARD_LED_GPIO = 48;

};
