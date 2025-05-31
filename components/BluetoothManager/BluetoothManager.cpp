#include "BluetoothManager.hpp"
#include "esp_log.h"
#define TAG  "BluetoothManager"


static esp_ble_adv_params_t adv_params = {
    .adv_int_min        = 0x20,                      // 20 ms
    .adv_int_max        = 0x40,                      // 40 ms
    .adv_type           = ADV_TYPE_IND,              // Connectable undirected advertising
    .own_addr_type      = BLE_ADDR_TYPE_PUBLIC,      // Use the public address
    .channel_map        = ADV_CHNL_ALL,              // All 3 channels: 37, 38, 39
    .adv_filter_policy  = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY // Allow any device to scan/connect
};

static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    esp_err_t err;
    ESP_LOGI(TAG, "GAP_EVT, event %d", event);

    switch (event) {
    case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT:
        esp_ble_gap_start_advertising(&adv_params);
        break;
    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
        //advertising start complete event to indicate advertising start successfully or failed
        if((err = param->adv_start_cmpl.status) != ESP_BT_STATUS_SUCCESS) {
            ESP_LOGE(TAG, "Advertising start failed: %s", esp_err_to_name(err));
        }
        break;
    default:
        break;
    }
}


static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param)
{
    ESP_LOGI(TAG, "EVT %d, gatts if %d", event, gatts_if);

    // /* If event is register event, store the gatts_if for each profile */
    // if (event == ESP_GATTS_REG_EVT) {
    //     if (param->reg.status == ESP_GATT_OK) {
    //         spp_profile_tab[SPP_PROFILE_APP_IDX].gatts_if = gatts_if;
    //     } else {
    //         ESP_LOGI(GATTS_TABLE_TAG, "Reg app failed, app_id %04x, status %d",param->reg.app_id, param->reg.status);
    //         return;
    //     }
    // }

    // do {
    //     int idx;
    //     for (idx = 0; idx < SPP_PROFILE_NUM; idx++) {
    //         if (gatts_if == ESP_GATT_IF_NONE || /* ESP_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
    //                 gatts_if == spp_profile_tab[idx].gatts_if) {
    //             if (spp_profile_tab[idx].gatts_cb) {
    //                 spp_profile_tab[idx].gatts_cb(event, gatts_if, param);
    //             }
    //         }
    //     }
    // } while (0);
}

void BluetoothManager::run()
{
    while(true){
        vTaskDelay(pdMS_TO_TICKS(100));
    }
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
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));


    esp_bt_controller_config_t controllerConfig = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_bt_controller_init(&controllerConfig));
    ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_BLE));

    ESP_ERROR_CHECK(esp_bluedroid_init());
    ESP_ERROR_CHECK(esp_bluedroid_enable());

    ESP_ERROR_CHECK(esp_ble_gatts_register_callback(gatts_event_handler));
    ESP_ERROR_CHECK(esp_ble_gap_register_callback(gap_event_handler));

    uint8_t adv_data[] = {
        0x02, 0x01, 0x06,                         // Flags: LE General Discoverable
        0x03, 0x03, 0xAB, 0xCD,                   // 16-bit Service UUID (dummy)
        0x0A, 0x09, 'E','S','P','3','2','-','S','3','B','L'  // Local name
    };
    ESP_ERROR_CHECK(esp_ble_gap_config_adv_data_raw(adv_data, sizeof(adv_data)));

    esp_ble_gatts_app_register(0);
    // spp_uart_init();
    esp_ble_gatt_set_local_mtu(500);
    // ESP_ERROR_CHECK(esp_ble_gatts_register_callback(gatts_event_handler));
    // ESP_ERROR_CHECK(esp_ble_gatt_set_local_mtu(500));
    // //init controller
    // esp_bt_controller_config_t controllerConfig = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    // ESP_ERROR_CHECK(esp_bt_controller_init(&controllerConfig));
    // ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT));

    // //init bluedroid
    // esp_bluedroid_config_t bluedroidConfig = {ssp_en: USE_SSP};
    // ESP_ERROR_CHECK(esp_bluedroid_init_with_cfg(&bluedroidConfig));//use ssp(secure simple pairing)
    // ESP_ERROR_CHECK(esp_bluedroid_enable());

    // // //init ssp
    // esp_spp_register_callback(spp_callback);
    // // esp_spp_cfg_t spp_cfg = {
    // //     .mode = ESP_SPP_MODE_CB,
    // //     .enable_l2cap_ertm = true,
    // //     .tx_buffer_size = 0
    // // };
    // // esp_spp_enhanced_init(&spp_cfg);

}

