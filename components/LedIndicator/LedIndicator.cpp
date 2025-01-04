#include "LedIndicator.hpp"
#include "esp_log.h"
static const char* TAG = "LedIndicator";

LedIndicator::LedIndicator(){
    if(led_ == NULL){
        led_strip_config_t stripConfig = {
            .strip_gpio_num = ONBOARD_LED_GPIO,
            .max_leds = 1,
            .led_model = LED_MODEL_WS2812,
            .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_RGB,
            .flags {
                .invert_out = false
            }
        };
        led_strip_rmt_config_t rmtConfig = {
            .clk_src = RMT_CLK_SRC_DEFAULT,
            .resolution_hz = 10*1000*1000,
            .mem_block_symbols = 64,
            .flags = {
                .with_dma = true
            }
        };
        ESP_ERROR_CHECK(led_strip_new_rmt_device(&stripConfig, &rmtConfig, &led_));
    }else{
        ESP_LOGW(TAG, "Tried to reconfigure the led");
    }
    ESP_ERROR_CHECK(led_strip_clear(led_));
}
LedIndicator::~LedIndicator(){
    setColor(Color::NONE);
    ESP_ERROR_CHECK(led_strip_del(led_));
    led_ = NULL;
}


void LedIndicator::setColor(uint32_t r, uint32_t g, uint32_t b){
    ESP_ERROR_CHECK(led_strip_set_pixel(led_,0,g,r,b));
    ESP_ERROR_CHECK(led_strip_refresh(led_));
}
void LedIndicator::setColor(Color color){
    setColor((color & 0xFF0000)>>(8*2),
             (color & 0x00FF00)>>8,
             (color & 0x0000FF));
}