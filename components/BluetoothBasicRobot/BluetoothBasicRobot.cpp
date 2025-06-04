#include "BluetoothBasicRobot.hpp"
#include "esp_log.h"
#include <cstring> 

#define TAG_BT_BASIC_ROBOT "BluetoothBasicRobot"
BluetoothBasicRobot::BluetoothBasicRobot(uint8_t priority) : BluetoothService(priority) {}


void BluetoothBasicRobot::onServiceCreate(esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) {
    esp_bt_uuid_t char_uuid = {};
    char_uuid.len = ESP_UUID_LEN_16;
    char_uuid.uuid.uuid16 = 0xBEEF;

    esp_gatt_char_prop_t prop = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE_NR;

    static uint8_t val[] = {'1', '2', '3', '4'};
    esp_attr_value_t attr_val = {
        .attr_max_len = sizeof(val),
        .attr_len     = sizeof(val),
        .attr_value   = val
    };

    ESP_ERROR_CHECK(esp_ble_gatts_add_char(serviceHandle_, &char_uuid,
        ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE, prop, &attr_val, nullptr));
}

void BluetoothBasicRobot::onReadRequest(esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) {
    esp_gatt_rsp_t rsp = {};
    rsp.attr_value.handle = param->read.handle;
    rsp.attr_value.len = sizeof("Tres beau habibi") - 1;
    memcpy(rsp.attr_value.value, "Tres beau habibi", sizeof("Tres beau habibi")-1);

    ESP_ERROR_CHECK(esp_ble_gatts_send_response(
        gatts_if, param->read.conn_id, param->read.trans_id,
        ESP_GATT_OK, &rsp
    ));
    
}

void BluetoothBasicRobot::onWriteRequest(esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t* param) {
    ESP_LOG_BUFFER_HEX(TAG_BT_BASIC_ROBOT, param->write.value, param->write.len);
}
