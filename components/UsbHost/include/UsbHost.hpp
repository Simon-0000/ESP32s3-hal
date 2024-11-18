#pragma once
#include "Task.hpp"
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include <usb/usb_host.h>

typedef struct {
    usb_host_client_handle_t client_hdl;
    uint8_t dev_addr;
    usb_device_handle_t dev_hdl;
    uint32_t actions;
} class_driver_t;

class UsbHost : public Task{
public:
    UsbHost() : Task("UsbHost"){}
    void run() override;
    void onInit() override;
private:
    SemaphoreHandle_t signaling_sem_;
};