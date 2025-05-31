#pragma once
#include "Task.hpp"
#include "nvs_flash.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"
#include "esp_bt.h"
#include "esp_spp_api.h"
#include <esp_gap_bt_api.h>

#pragma once


class BluetoothManager : public Task{
public:
    BluetoothManager() : Task("BluetoothManager"){}
protected:
    void run() override;
    void onInit() override;
    void onStop() override;
    void onSuspend() override;
    void onResume() override;
private:
    static constexpr bool USE_SSP = true;
    
};