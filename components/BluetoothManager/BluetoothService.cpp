#include "BluetoothService.hpp"
#include "esp_log.h"

#define TAG_BT_SERVICE "BluetoothService"

BluetoothService::BluetoothService(uint8_t priority): priority_(priority) {
    for(int i = 0; i < UUID_LENGTH_BYTES; ++i)
        uuid_[i] = esp_random();//implicit cast from 32 bit to 8 bit

    uuid_[6] = (uuid_[6] & 0x0F) | 0x40;  // Version 4 (randomly generated uuid)
    uuid_[8] = (uuid_[8] & 0x3F) | 0x80;  // Variant 1 (RFC 4122)
}

void BluetoothService::registerToGatt(esp_gatt_if_t gattIf) {
    gattIf_ = gattIf;

    esp_gatt_srvc_id_t service_id = {};
    service_id.is_primary = true;
    service_id.id.inst_id = 0;
    service_id.id.uuid.len = ESP_UUID_LEN_16;
    service_id.id.uuid.uuid.uuid16 = 0xABCD;

    ESP_ERROR_CHECK(esp_ble_gatts_create_service(gattIf_, &service_id, 4));
}

bool BluetoothService::handleEvent(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) {
    switch (event) {
        case ESP_GATTS_REG_EVT:
            if (param->reg.status == ESP_GATT_OK) {
                registerToGatt(gatts_if);
                ESP_LOGI(TAG_BT_SERVICE, "Service registration started");
            } else {
                ESP_LOGE(TAG_BT_SERVICE, "GATT REG failed, status %d", param->reg.status);
            }
            break;

        case ESP_GATTS_CREATE_EVT:
            serviceHandle_ = param->create.service_handle;
            ESP_LOGI(TAG_BT_SERVICE, "Service created, handle = %d", serviceHandle_);
            ESP_ERROR_CHECK(esp_ble_gatts_start_service(serviceHandle_));
            onServiceCreate(gatts_if,param);
            break;

        case ESP_GATTS_ADD_CHAR_EVT:
            ESP_LOGI(TAG_BT_SERVICE, "Characteristic added, handle = %d", param->add_char.attr_handle);
            break;

        case ESP_GATTS_WRITE_EVT:
            ESP_LOGI(TAG_BT_SERVICE, "Write event to handle 0x%04x", param->write.handle);
            ESP_LOGI(TAG_BT_SERVICE, "Write value, len = %d", param->write.len);
            onWriteRequest(gatts_if,param);

            break;
        
        case ESP_GATTS_READ_EVT:
            ESP_LOGI(TAG_BT_SERVICE, "Read request for handle: 0x%04x", param->read.handle);
            onReadRequest(gatts_if,param);
            break;
        default:
            break;
    }

    return true;
}
