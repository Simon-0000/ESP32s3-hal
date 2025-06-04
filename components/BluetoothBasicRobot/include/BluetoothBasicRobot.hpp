#pragma once
#include "BluetoothService.hpp"

class BluetoothBasicRobot : public BluetoothService {
public:
    BluetoothBasicRobot(uint8_t priority);
    void onServiceCreate(esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) override;
    void onReadRequest(esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) override;
    void onWriteRequest(esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) override;
private:

};