# ESP-PM 2025 Overview (incomplete code)
Project for the boat that is required in the 2025 jeu de genie. <b>NOTE THAT THIS ISNT THE FULL CODE AND DOESNT CONTAIN THE "Bateau2025" COMPONENT</b>

## Description
The code is designed to receive inputs from a controller in order to control a boat's rudder and propeller. The onboard addressable led is used to show the state of the controller connection:

<ul>
<li><span style="color:Grey">No Color</span><span>, The esp didnt power up properly, simply press the reset button on it</span></li>

<li><span style="color:red">Red: DISCONNECTED</span><span>, no usb device is currently detected by the board</span></li>

<li><span style="color:yellow">Yellow: NOT_RECEIVING</span><span>, a usb device is connected but it's not receiving data (<i>The controller's logitech/center button needs to be pressed to wake up the controller</i>)</span></li>

<li><span style="color:green">Green: RECEIVING_VALID</span><span>, the board is receiving the 20 bytes that it expects, (<i>The mapping of the controller may not work if the "mode" button is pressed/activated</i>)</span></li>

<li><span style="color:magenta">Magenta: RECEIVING_INVALID</span><span>,  The board is receiving data at an unexpected size<i>(Likely because the controller's X/O switch isnt in the correct position)</i></span></li>

</ul>


## Prerequisite
Install <a href="https://docs.docker.com/engine/install/">Docker</a> on your system
<br>
Install the [Dev Containter](vscode:extension/ms-vscode-remote.remote-containers)
 extension for vscode
<br><i style="color:grey">The project works in ubuntu, but it is not tested on other OS. According to espressif, it is not currently possible to <a href="https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-guides/tools/idf-docker-image.html#using-the-image-interactively">pass serial ports</a> with Docker Windows.</i>

## Setup the devcontainer (or Toolchain)
The <a href="https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-guides/tools/idf-docker-image.html">docker image</a> comes from the template project provided by espressif for the esp32s3 and it was modifed to contain less layers (ex: the qemu emulator was removed). If you wish to build/flash the project without using the devcontainer, ensure that the <a href="https://docs.espressif.com/projects/esp-idf/en/v5.3.1/esp32s3/get-started/linux-macos-setup.html">standard toolchain</a> is setup <b>(This project is built on version 5.3.1 of the idf)</b>.

To build the container, press ctrl + shift + P to open vscode's command palette and search for the <b>Dev Containers: Reopen in Container</b> command

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
