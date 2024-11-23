#include "Controller.hpp"
#include "esp_log.h"
#include <string.h>


static void printInput(usb_transfer_t* transfer){
    char log_buffer[512]; // Adjust size as needed based on expected transfer sizes
    int pos = 0;

    pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "Transferred bytes: ");

    for (int i = 0; i < transfer->actual_num_bytes && pos < sizeof(log_buffer) - 4; i++) {
        pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "0x%02X ", transfer->data_buffer[i]);
    }

    ESP_LOGI("CONTROLLER", "Transfer status: %d, actual number of bytes transferred: %d\n%s",
            transfer->status, transfer->actual_num_bytes, log_buffer);

}

void Controller::onInit(){
    ESP_LOGI("CONTROLLER", "init:");
    usb_host_interface_claim( driver_->client_hdl, driver_->dev_hdl, 0, 0);
}
void Controller::run(){
    ESP_LOGI("CONTROLLER", "run:");
    uint8_t buffer[32]; // Max packet size
    usb_transfer_t *transfer_in ;
    usb_host_transfer_alloc(1024, 0, &transfer_in);
    memset(transfer_in->data_buffer, 0xAA, 1024);
    // transfer_in->data_buffer_size = sizeof(buffer);
    transfer_in->num_bytes = sizeof(buffer);
    transfer_in->device_handle = driver_->dev_hdl;
    transfer_in->bEndpointAddress = 0x81;
    transfer_in->callback = printInput;
    transfer_in->context = (void *)this;

    while(true){
        usb_host_transfer_submit(transfer_in);
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}
        
