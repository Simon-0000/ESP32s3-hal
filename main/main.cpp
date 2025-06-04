#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_intr_alloc.h"
#include "usb/usb_host.h"
#include "UsbDaemon.hpp"
#include "UsbClient.hpp"
#include "Controller.hpp"
#include "DCMotor.hpp"
#include "MCPWM.hpp"
#include <esp_log.h>
#include "Gpio.hpp"
#include "LedCPWM.hpp"
#include "ServoMotor.hpp"
#include "BluetoothManager.hpp"
// #include "Bateau2025.hpp"

extern "C" void app_main(void)
{
    //Bateau code commented to protect the competition code of it
    // Controller controller;
    // Bateau2025 bateau(&controller);

    // UsbDaemon daemon;
    // UsbClient client(&controller);
    
    // // bateau.linkChild(&daemon);
    // client.linkTo(&daemon);

    // daemon.addClient(client);
    
    // bateau.start();
    
    // MCPWM<McpwmConfigs::TimerGroup::GROUP_0> pwm(GPIO_NUM_14, 50, 20000);
    // Gpio directionPin_(gpio_num_t::GPIO_NUM_8,gpio_mode_t::GPIO_MODE_OUTPUT);

    // DCMotor servoMotor(&mcPWM_,&directionPin_);
    // ServoMotor rudderMotor_(&pwm);
    // servoMotor.start();
    // int16_t angle = 0;
    // pwm.start();
    // rudderMotor_.start();
    BluetoothManager manager = BluetoothManager::getInstance();
    BluetoothService service(4);
    manager.services.push_back(&service);

    manager.start();
    while(true){
        vTaskDelay(pdMS_TO_TICKS(100));

        // ESP_LOGW("main","SET %d",static_cast<int>(angle));

        // vTaskDelay(500/portTICK_PERIOD_MS);
        // ESP_LOGW("main", "Ticks: %d", pwm.pwmToTicks(UINT16_MAX/4));

        // // pwm.setPwm(UINT16_MAX/4);
        // rudderMotor_.setAngle(0);
        // servoMotor.setSpeed(INT16_MAX/4);
        // if(angle >= INT16_MAX)
        //     angle = 0;
    }
}