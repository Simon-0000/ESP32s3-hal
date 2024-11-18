#pragma once
#include "Task.hpp"
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include <usb/usb_host.h>
#include "UsbClient.hpp"

class UsbDaemon : public Task{
public:
    UsbDaemon() : Task("UsbDaemon"){}

    void linkClient(UsbClient& client);
    void run() override;
    void onInit() override;
    void onStop() override;
private:
    SemaphoreHandle_t signalingSemaphore_ = NULL;
    
};