#pragma once
#include "UsbDevice.hpp"
class Controller : public UsbDevice {
public: 
    Controller() : UsbDevice("Controller") {}

    void run() override;
    void onInit() override;
private:
};