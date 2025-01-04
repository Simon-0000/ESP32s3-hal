#pragma once
#include "UsbDevice.hpp"
#include <mutex>
#include "esp_async_memcpy.h"

enum class ControllerStatus {DISCONNECTED, NOT_RECEIVING, RECEIVING_INVALID, RECEIVING_VALID };

class Controller;
static void handleRawBuffer(usb_transfer_t* transfer);

class Controller : public UsbDevice {
public: 
    Controller() : UsbDevice("Controller") {}

	bool getButtonA() const;
	bool getButtonB() const;
	bool getButtonY() const;
	bool getButtonX() const;
    bool getAxisButtonUp() const;
	bool getAxisButtonDown() const;
	bool getAxisButtonLeft() const;
	bool getAxisButtonRight() const;
	bool getLeftButton() const;
	bool getRightButton() const;
	int16_t getLeftAxisX() const;
	int16_t getLeftAxisY() const;
	int16_t getRightAxisX() const;
	int16_t getRightAxisY() const;
	uint8_t getLeftTrigger() const;
	uint8_t getRightTrigger() const;
	ControllerStatus getControllerStatus() const;
    
    #pragma GCC diagnostic ignored "-Wunused-function"
    friend void handleRawBuffer(usb_transfer_t* transfer);

protected:
    void run() override;
    void onInit() override;
    void onStop() override;

private:
    inline const std::lock_guard<std::recursive_mutex> createLock() const;
    

    static constexpr size_t BUFFER_SIZE = 20;
    uint8_t buffer_[BUFFER_SIZE] = {0};
    mutable std::recursive_mutex bufferMutex_;
    bool processedData_ = true;
    ControllerStatus status_ = ControllerStatus::DISCONNECTED;
    async_memcpy_handle_t memcpyDriver_ = NULL;

    static constexpr uint8_t INTERFACE_NUMBER = 0;
    static constexpr uint8_t ENDPOINT_ADDRESS = 0x81;
    static constexpr uint16_t STICK_DRIFT = 1000;
    static constexpr uint8_t TRANSFER_DELAY_MS = 4;
};

