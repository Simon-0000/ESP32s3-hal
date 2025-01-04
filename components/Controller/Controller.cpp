#include "Controller.hpp"
#include "esp_log.h"
#include <cstring>


static void handleRawBuffer(usb_transfer_t* transfer){
    Controller* controller = static_cast<Controller*>(transfer->context);

    // const auto lock = controller->createLock();

    switch(transfer->actual_num_bytes)
    {
        case 0:
            controller->status_ = ControllerStatus::NOT_RECEIVING;
            return;
        case Controller::BUFFER_SIZE:
            controller->status_ = ControllerStatus::RECEIVING_VALID;
            break;
        default:
            controller->status_ = ControllerStatus::RECEIVING_INVALID;
            return;
    }
    // memcpy(controller->buffer_,transfer->data_buffer,Controller::BUFFER_SIZE);
    ESP_ERROR_CHECK(esp_async_memcpy(controller->memcpyDriver_, controller->buffer_, transfer->data_buffer, Controller::BUFFER_SIZE, NULL, NULL));

    controller->processedData_ = true;
    // printf("SIZE: %d",transfer->actual_num_bytes);

    // char log_buffer[512]; // Adjust size as needed based on expected transfer sizes
    // int pos = 0;
    // printf("\033[H\033[J");
    // // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "Transferred bytes: ");

    // // for (int i = 0; i < transfer->actual_num_bytes && pos < sizeof(log_buffer) - 4; i++) {
    // //     pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "0x%02X ", controller->buffer_[i]);
    // // }

    // // printf("Transfer status: %d, actual number of bytes transferred: %d\n%s",
    // //         transfer->status, transfer->actual_num_bytes, log_buffer);
    // pos = 0;

    // //CHATGPT CODE to print 
    // // Printing button values
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "\nButtons: ");
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "A: %d, ", controller->getButtonA());
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "B: %d, ", controller->getButtonB());
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "X: %d, ", controller->getButtonX());
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "Y: %d, ", controller->getButtonY());
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "Left: %d, ", controller->getLeftButton());
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "Right: %d, ", controller->getRightButton());
    
    // // Printing axis buttons
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "\nAxis Buttons: ");
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "U: %d, ", controller->getAxisButtonUp());
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "D: %d, ", controller->getAxisButtonDown());
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "L: %d, ", controller->getAxisButtonLeft());
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "R: %d, ", controller->getAxisButtonRight());
    
    // // Printing joystick axis values
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "\nJoysticks: ");
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "L-X: %d, ", controller->getLeftAxisX());
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "L-Y: %d, ", controller->getLeftAxisY());
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "R-X: %d, ", controller->getRightAxisX());
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "R-Y: %d, ", controller->getRightAxisY());

    // // Printing triggers
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "\nTriggers: ");
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "L: %d, ", controller->getLeftTrigger());
    // pos += snprintf(log_buffer + pos, sizeof(log_buffer) - pos, "R: %d", controller->getRightTrigger());

    // // Print the updated log to the terminal
    // printf("%s\n", log_buffer);

}



void Controller::onInit(){
    #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
    static async_memcpy_config_t memcpyConfig = ASYNC_MEMCPY_DEFAULT_CONFIG();
    status_ = ControllerStatus::NOT_RECEIVING;
    processedData_ = true;
    ESP_ERROR_CHECK(esp_async_memcpy_install(&memcpyConfig, &memcpyDriver_));

    ESP_LOGI("CONTROLLER", "init:");
    usb_host_interface_claim( driver_->client_hdl, driver_->dev_hdl, INTERFACE_NUMBER,INTERFACE_NUMBER);
    // responseWatchdogTimer_ = xTimerCreate("responseWatchdogTimer", pdMS_TO_TICKS(TIMEOUT_MS), pdTRUE, NULL, vTimeoutCallback);

}
void Controller::onStop(){
    status_ = ControllerStatus::DISCONNECTED;
    ESP_LOGI("CONTROLLER", "stop:");
    usb_host_interface_release( driver_->client_hdl, driver_->dev_hdl, INTERFACE_NUMBER);
    esp_async_memcpy_uninstall(memcpyDriver_);
}

void Controller::run(){

    ESP_LOGI("CONTROLLER", "run:");
    usb_transfer_t *transfer_in ;
    usb_host_transfer_alloc(32, 0, &transfer_in);
    memset(transfer_in->data_buffer, 0xAA, 32);
    transfer_in->num_bytes = 32;
    transfer_in->device_handle = driver_->dev_hdl;
    transfer_in->bEndpointAddress = ENDPOINT_ADDRESS;
    transfer_in->callback = handleRawBuffer;
    transfer_in->context = (void *)this;

    while(true){
        if(processedData_){
            processedData_ = false;
            usb_host_transfer_submit(transfer_in);
        }
        vTaskDelay(TRANSFER_DELAY_MS/portTICK_PERIOD_MS);
    }
}

//ABYX buttons
bool Controller::getButtonA() const {
    const auto lock = createLock();
    return static_cast<bool>(buffer_[3] & 0x10);
}
bool Controller::getButtonB() const {
    const auto lock = createLock();
    return static_cast<bool>(buffer_[3] & 0x20);
}
bool Controller::getButtonY() const {
    const auto lock = createLock();
    return static_cast<bool>(buffer_[3] & 0x80);
}
bool Controller::getButtonX() const {
    const auto lock = createLock();
    return static_cast<bool>(buffer_[3] & 0x40);
}

//Axis buttons
bool Controller::getAxisButtonUp() const {
    const auto lock = createLock();
    return static_cast<bool>(buffer_[2] & 0x01);
}
bool Controller::getAxisButtonDown() const {
    const auto lock = createLock();
    return static_cast<bool>(buffer_[2] & 0x02);
}
bool Controller::getAxisButtonLeft() const {
    const auto lock = createLock();
    return static_cast<bool>(buffer_[2] & 0x04);
}
bool Controller::getAxisButtonRight() const {
    const auto lock = createLock();
    return static_cast<bool>(buffer_[2] & 0x08);
}

//L/R buttons
bool Controller::getLeftButton() const {
    const auto lock = createLock();
    return static_cast<bool>(buffer_[3] & 0x01);
}
bool Controller::getRightButton() const {
    const auto lock = createLock();
    return static_cast<bool>(buffer_[3] & 0x02);
}

//Left joystick
int16_t Controller::getLeftAxisX() const {
    const auto lock = createLock();
    int16_t value = buffer_[7] << 8 | buffer_[6];
    return value < STICK_DRIFT && -value < STICK_DRIFT ? 0 : value;
}
int16_t Controller::getLeftAxisY() const {
    const auto lock = createLock();
    int16_t value = buffer_[9] << 8 | buffer_[8];
    return value < STICK_DRIFT && -value < STICK_DRIFT ? 0 : value;
}
int16_t Controller::getRightAxisX() const {
    const auto lock = createLock();
    int16_t value = buffer_[11] << 8 | buffer_[10];
    return value < STICK_DRIFT && -value < STICK_DRIFT ? 0 : value;
}
int16_t Controller::getRightAxisY() const {
    const auto lock = createLock();
    int16_t value = buffer_[13] << 8 | buffer_[12];
    return value < STICK_DRIFT && -value < STICK_DRIFT ? 0 : value;
}
uint8_t Controller::getLeftTrigger() const {
    const auto lock = createLock();
    return buffer_[4];
}
uint8_t Controller::getRightTrigger() const {
    const auto lock = createLock();
    return buffer_[5];
}

ControllerStatus Controller::getControllerStatus() const{
    return status_;
}

const std::lock_guard<std::recursive_mutex> Controller::createLock() const{
    return std::lock_guard<std::recursive_mutex>(bufferMutex_);
}

