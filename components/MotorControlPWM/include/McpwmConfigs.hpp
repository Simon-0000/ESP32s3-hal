#pragma once
#include "driver/mcpwm_timer.h"

namespace McpwmConfigs{
    enum TimerGroup
    {
        #ifdef CONFIG_IDF_TARGET_ESP32S3 
            GROUP_0,
            GROUP_1,
        #endif

    };
};



