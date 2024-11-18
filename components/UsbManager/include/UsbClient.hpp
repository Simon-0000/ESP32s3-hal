#pragma once
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "usb/usb_host.h"
#include "Task.hpp"


enum class USB_EVENTS{
    NONE,
    ON_DEVICE_INIT,
    ON_DEVICE_STOP,
    ON_DEVICE_RUN
};

typedef struct {
    usb_host_client_handle_t client_hdl;
    usb_device_handle_t dev_hdl;
    USB_EVENTS event;
} client_driver_t;

class UsbClient : public Task {
public:
    UsbClient() :  Task("UsbClient") {}
    virtual void onDeviceInit() {}
    virtual void onDeviceStop() {}

    virtual void onDeviceRun() {}

    void run() override;
    void onStop() override;
    friend class UsbDaemon;
private:
    SemaphoreHandle_t* signalingSemaphore_ = nullptr;
    client_driver_t driver_ = {NULL,NULL, USB_EVENTS::NONE};

};