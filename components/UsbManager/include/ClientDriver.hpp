#pragma once
#include <usb/usb_host.h>


enum class USB_EVENTS{
    NONE,
    ON_DEVICE_INIT,
    ON_DEVICE_STOP
};



typedef struct {
    usb_host_client_handle_t client_hdl;
    usb_device_handle_t dev_hdl;
    USB_EVENTS event;
} client_driver_t;