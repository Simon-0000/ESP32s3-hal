#include "UsbClient.hpp"
#include "esp_log.h"
static const char *TAG = "Client";

#define CLIENT_NUM_EVENT_MSG        5

#define ACTION_OPEN_DEV             0x01
#define ACTION_GET_DEV_INFO         0x02
#define ACTION_GET_DEV_DESC         0x04
#define ACTION_GET_CONFIG_DESC      0x08
#define ACTION_GET_STR_DESC         0x10
#define ACTION_CLOSE_DEV            0x20
#define ACTION_EXIT                 0x40

static void client_event_cb(const usb_host_client_event_msg_t *event_msg, void *arg)
{
    client_driver_t *driver_obj = (client_driver_t *)arg;
    switch (event_msg->event) {
    case USB_HOST_CLIENT_EVENT_NEW_DEV:
        if (driver_obj->dev_hdl == NULL) {
            ESP_LOGI(TAG, "OPENING DEVICE");
            uint8_t address = event_msg->new_dev.address;
            ESP_ERROR_CHECK(usb_host_device_open(driver_obj->client_hdl, address, &driver_obj->dev_hdl));
            
            ESP_LOGI(TAG, "Getting device information");
            usb_device_info_t dev_info;
            ESP_ERROR_CHECK(usb_host_device_info(driver_obj->dev_hdl, &dev_info));
            ESP_LOGI(TAG, "\t%s speed", (dev_info.speed == USB_SPEED_LOW) ? "Low" : "Full");
            ESP_LOGI(TAG, "\tbConfigurationValue %d", dev_info.bConfigurationValue);

            driver_obj->event = USB_EVENTS::ON_DEVICE_INIT;
        }
        break;
    case USB_HOST_CLIENT_EVENT_DEV_GONE:
        if (driver_obj->dev_hdl != NULL) {
            //Cancel any other actions and close the device next
            ESP_LOGI(TAG, "CLOSING DEVICE");
            //TODO call device.stop before closing
            driver_obj->event = USB_EVENTS::ON_DEVICE_STOP;
        }
        break;
    default:
        //Should never occur
        abort();
    }
}


void UsbClient::run()
{

    //Wait until daemon task has installed USB Host Library
    xSemaphoreTake(*signalingSemaphore_, portMAX_DELAY);

    ESP_LOGI(TAG, "Registering Client");
    usb_host_client_config_t client_config = {
        .is_synchronous = false,    //Synchronous clients currently not supported. Set this to false
        .max_num_event_msg = CLIENT_NUM_EVENT_MSG,
        .async = {
            .client_event_callback = client_event_cb,
            .callback_arg = (void *) &driver_,
        },
    };
    ESP_ERROR_CHECK(usb_host_client_register(&client_config, &driver_.client_hdl));

    //handle connected device on boot up
    const uint8_t MAX_DEVICE = 1;//TODO modify this to allow more than 1 connected device in the futur
    int nbrOfDevice;
    uint8_t deviceList[MAX_DEVICE];
    usb_host_device_addr_list_fill(MAX_DEVICE, deviceList, &nbrOfDevice);
    if(nbrOfDevice == 1){
        ESP_LOGI(TAG, "Device is connected on boot up");
        ESP_ERROR_CHECK(usb_host_device_open(driver_.client_hdl, deviceList[0], &driver_.dev_hdl));
        driver_.event = USB_EVENTS::ON_DEVICE_INIT;
    }
    //handle client/device connections
    while (true) {
        switch(driver_.event)  
        {
            case USB_EVENTS::ON_DEVICE_INIT:
                device_->start();
                ESP_LOGI(TAG, "done init");
                break;
            case USB_EVENTS::ON_DEVICE_STOP:
                device_->stop();
                ESP_ERROR_CHECK(usb_host_device_close(driver_.client_hdl, driver_.dev_hdl));
                driver_.dev_hdl = NULL;
                ESP_LOGI(TAG, "done stop");
                break;           
            default:
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(4));
        driver_.event = USB_EVENTS::NONE;
        usb_host_client_handle_events(driver_.client_hdl, portMAX_DELAY);
    }
}


void UsbClient::onStop(){
    ESP_LOGI(TAG, "Deregistering Client");
    ESP_ERROR_CHECK(usb_host_client_deregister(driver_.client_hdl));

    //Wait to be deleted
    xSemaphoreGive(*signalingSemaphore_);
    vTaskSuspend(NULL);
}