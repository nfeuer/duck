[Join the Project Owl and ClusterDuck and #Help Channel on Slack and ask questions here!](http://project-owl.com/slack)

# Setup Guide
### Environment
* Download and Install the [Arduino IDE](https://www.arduino.cc/en/main/software)
* Download [USB to UART Bridge VCP Driver](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)
  * Once it is finished installing, go to Mac System Preferences -> Security and Privacy -> General. Make sure Silicon Labs is allowed.
* Open Arduino
* Follow these [instructions](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md) to install the specific board that is being used
* In Arduino, go to Tools → Board → (Select from Dropdown Menu) “Heltic_WIFI_LoRa_32“
* In the Arduino folder that's located in Documents folder of your computer's environment, add the contents of the Arduino folder provided

### Hardware
The development board that we recommend, is the [Heltec Esp32 + LoRa](https://www.amazon.com/MakerFocus-Development-Bluetooth-0-96inch-Display/dp/B076MSLFC9/ref=sr_1_1?keywords=heltec+32+lora&qid=1564689711&s=gateway&sr=8-1). But with minor changes, it is possible to setup with other hardware with a similar configuration (ESP32 + LoRa Chip).
* Make sure you are getting the appropriate frequency for your respective country. 
* Use this [link](https://www.thethingsnetwork.org/docs/lorawan/frequencies-by-country.html) as a guide

### Firmware
* Download the code from the [Ducks Repo](https://github.com/Project-Owl/duck/) and open it in Arduino
* Using a data transfer cable, connect the LoRa board to the computer
* In Arduino, go to Tools → Port → (Select from Dropdown Menu) USB UART Port
* The DuckLink, Mama, and Papa, can be individually flashed by toggling just few lines of code in the main Duck.ino file
* Go to the Duck.ino file in Arduino IDE and click on Verify
* If no errors, then click on Upload, to flash the firmware to the board
