#pragma once
#include "Task.hpp"
#include "esp_bt_main.h"
// #include "esp_gap_bt_api.h"

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