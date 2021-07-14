# esp-predator
ESP32 Predator for the MacIver Lab at Northwestern

Make sure you have ESP-IDF from https://github.com/espressif/esp-idf --branch release/v4.1

Then go to
cd robot/btstack/port/esp32 
run this line to setup and install the btstack files 
./integrate_btstack.py 

then use idf.py build in the src directory and use ./flash to flash the code to your ESP32 connected robot
