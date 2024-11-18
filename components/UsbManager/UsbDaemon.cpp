#include "UsbDaemon.hpp"
#include "esp_log.h"
static const char *TAG = "DAEMON";

void UsbDaemon::linkClient(UsbClient& client){
    client.signalingSemaphore_ = &signalingSemaphore_;
}

void UsbDaemon::run(){

    ESP_LOGI(TAG, "Installing USB Host Library");
    usb_host_config_t host_config = {
        .skip_phy_setup = false,
        .intr_flags = ESP_INTR_FLAG_LEVEL1,
        .enum_filter_cb = NULL
    };
    ESP_ERROR_CHECK(usb_host_install(&host_config));

    //Signal to the class driver task that the host library is installed
    xSemaphoreGive(signalingSemaphore_);

    bool has_clients = true;
    bool has_devices = true;
    while(true){
        while (has_clients || has_devices) {
            uint32_t event_flags;
            ESP_ERROR_CHECK(usb_host_lib_handle_events(portMAX_DELAY, &event_flags));
            if (event_flags & USB_HOST_LIB_EVENT_FLAGS_NO_CLIENTS) {
                has_clients = false;
            }
            if (event_flags & USB_HOST_LIB_EVENT_FLAGS_ALL_FREE) {
                has_devices = false;
            }
        }
        ESP_LOGI(TAG, "No clients and devices");
        vTaskDelay(pdMS_TO_TICKS(200)); 
    }

}

void UsbDaemon::onInit(){
    signalingSemaphore_ = xSemaphoreCreateBinary();
}

void UsbDaemon::onStop(){
    ESP_ERROR_CHECK(usb_host_uninstall());
    //Wait to be deleted
    xSemaphoreGive(signalingSemaphore_);
}