#pragma once
#include "nvs_flash.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"
#include "esp_bt.h"
#include "esp_spp_api.h"
#include <esp_gap_bt_api.h>
#include "esp_random.h"
#include <stdio.h>

class BluetoothService {
public:
    BluetoothService(uint8_t priority);
    void registerToGatt(esp_gatt_if_t gattIf);
    bool handleEvent(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param);

private:
    static constexpr uint8_t UUID_LENGTH_BYTES = 16;
    uint8_t uuid_[UUID_LENGTH_BYTES];
    esp_gatt_if_t gattIf_;
    uint8_t priority_;
    uint16_t serviceHandle_;
};