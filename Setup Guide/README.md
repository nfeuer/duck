# Setup Guide
### Arduino
* Download and Install the [Arduino IDE](https://www.arduino.cc/en/main/software)
* Download [USB to UART Bridge VCP Driver](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)
  * Once it is finished installing, go to Mac System Preferences -> Security and Privacy -> General. Make sure Silicon Labs is allowed.
* Open Arduino
* Follow these [instructions](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md) to install the specific board that is being used
* In Arduino, go to Tools -> Board -> (Select from Dropdown Menu) “Heltic_WIFI_LoRa_32“
* In Arduino, go to Tools -> Port -> (Select from Dropdown Menu) USB UART Port
* In Arduino folder that located in Documents folder of your environment, add the contents of the Arduino folder provided

### Get the Code
Download the code from the [Ducks Repo](https://github.com/Project-Owl/duck/) and open it in Arduino
