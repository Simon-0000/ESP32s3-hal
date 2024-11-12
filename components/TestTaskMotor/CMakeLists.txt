
idf_component_register(SRCS "TestTaskMotor.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES Task MCPWM LedCPWM DCMotor Gpio freertos)
                    