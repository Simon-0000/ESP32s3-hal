
idf_component_register(SRCS "BluetoothManager.cpp" "BluetoothService.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES nvs_flash bt Task)
                    