#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_intr_alloc.h"
#include "usb/usb_host.h"
#include "UsbDaemon.hpp"
#include "UsbClient.hpp"
#include "Controller.hpp"
// #include "Bateau2025.hpp"

extern "C" void app_main(void)
{
    //Bateau code commented to protect the competition code of it
    Controller controller;
    // Bateau2025 bateau(&controller);

    UsbDaemon daemon;
    UsbClient client(&controller);
    
    // bateau.linkChild(&daemon);
    client.linkTo(&daemon);

    daemon.addClient(client);

    // bateau.start();

    while(true){
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}