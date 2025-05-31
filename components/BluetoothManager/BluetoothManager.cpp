#include "BluetoothManager.hpp"
#include "esp_log.h"
#include "esp_bt_device.h"

// static const char *TAG = "BluetoothManager";

void BluetoothManager::run()
{

}

void BluetoothManager::onSuspend()
{
    ESP_ERROR_CHECK(esp_bluedroid_disable());
    
}
void BluetoothManager::onResume()
{
    ESP_ERROR_CHECK(esp_bluedroid_enable());
}

void BluetoothManager::onStop(){
    ESP_ERROR_CHECK(esp_bluedroid_disable());
    ESP_ERROR_CHECK(esp_bluedroid_deinit());
}

void BluetoothManager::onInit(){
    esp_bluedroid_config_t config = {ssp_en: USE_SSP};
    ESP_ERROR_CHECK(esp_bluedroid_init_with_cfg(&config));//use ssp(secure simple pairing)
    ESP_ERROR_CHECK(esp_bluedroid_enable());
}