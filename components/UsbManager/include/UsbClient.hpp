#pragma once
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "usb/usb_host.h"
#include "Task.hpp"
#include "UsbDevice.hpp"
#include "ClientDriver.hpp"

class UsbClient : public Task {
public:
    UsbClient(UsbDevice* device) :  Task("UsbClient"), device_(device) {device->driver_ = &driver_;}
    virtual ~UsbClient() = default;

    friend class UsbDaemon;
    friend class UsbDevice;
protected:
    void run() override;
    void onStop() override;
    client_driver_t driver_ = {NULL,NULL, USB_EVENTS::NONE};

private:
    SemaphoreHandle_t* signalingSemaphore_ = nullptr;
    UsbDevice* device_;
};