idf_component_register(SRCS "main.cpp"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES UsbManager Controller ServoMotor MCPWM DCMotor Gpio LedCPWM BluetoothManager
                    )
