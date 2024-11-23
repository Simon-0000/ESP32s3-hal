#pragma once
#include "Task.hpp"
#include "ClientDriver.hpp"
class UsbDevice : public Task{
public:
    UsbDevice(const char* name = "UsbDevice") : Task(name){}
    friend class UsbClient;
protected:
    client_driver_t* driver_;
    usb_device_handle_t deviceHandle_;
};