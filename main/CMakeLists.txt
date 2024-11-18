idf_component_register(SRCS "usb_host_lib_main.cpp" "class_driver.cpp"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES usb UsbDaemon
                    )