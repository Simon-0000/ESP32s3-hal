#pragma once
#include "UsbDevice.hpp"
#include <mutex>


class Controller;
static void printInput(usb_transfer_t* transfer);

class Controller : public UsbDevice {
public: 
    Controller() : UsbDevice("Controller") {}

    void run() override;
    void onInit() override;
    void onStop() override;


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

    static constexpr size_t BUFFER_SIZE = 32;
    friend void printInput(usb_transfer_t* transfer);
private:
    inline const std::scoped_lock<std::mutex> createLock() const;
    uint8_t buffer_[32];
    mutable std::mutex bufferMutex_;

    static constexpr uint8_t INTERFACE_NUMBER = 0;
    static constexpr uint16_t STICK_DRIFT = 1000;

};

