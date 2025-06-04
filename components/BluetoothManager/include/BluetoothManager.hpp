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
#include "BluetoothService.hpp"


class BluetoothManager : public Task{
public:
    static BluetoothManager& getInstance();
    static inline std::vector<BluetoothService*> services = {};

protected:
    BluetoothManager() : Task("BluetoothManager"){}

    void run() override;
    void onInit() override;
    void onStop() override;
    void onSuspend() override;
    void onResume() override;
private:
    static constexpr bool USE_SSP = true;
};