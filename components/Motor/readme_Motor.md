# Motor Component Overview
Abstract class that defines how a motor should behave



# Functional overview

# API Reference

## Header File
```
#include "Motor.hpp"
```

## Functions


## Build and Flash the esp32s3
Before flashing, confirm that the [ESP-IDF](vscode:extension/espressif.esp-idf-extension) extension is installed in vscode. The <b>idf.py</b> command should work in your terminal if you are using the devcontainer<b> (you will need to interact with the idf via the cli when using the devcontainer)</b>. The most frequently used commands are: 
```bash
idf.py build #To build the project
idf.py flash #To build and flash the project
idf.py monitor #To monitor the logs, errors and warnings from the esp
```
<b style="color:grey">
If the idf is unable to open the esp32s3's port, make sure that you dont have a background terminal that is monitoring the esp32s3, if that is not the case then rebuilding the container usually works (Dev Containers: Rebuild Container)
</b>

## Support
Espressif's site for the esp32s3 : https://docs.espressif.com/projects/esp-idf/en/v5.3.1/esp32s3/index.html
<br>
Peripherals Api(v5.3.1): https://docs.espressif.com/projects/esp-idf/en/v5.3.1/esp32s3/api-reference/peripherals/index.html


## Authors 
Simon Asmar
<br>MachinePM, Organization
## License
This project is not to be shared unless you have received the approbation of its contributors.
