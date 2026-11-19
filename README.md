# Preparation

1. Insert the SD card reader into a USB slot on your computer
1. Insert the SD card into the SD card reader
1. The SD card should automatically appear as a new drive on your computer
1. Right-click and "Format"
1. After formatting is complete, right-click on the SD card drive and select "Eject"
1. Remove the SD card from the SD card reader

You can unplug the SD card reader now.

# Assembly

1. Cut a ca. 15 cm (6") strip of Kapton tape off the roll. Kapton is very prone to tearing, so be careful
1. Put the battery in the orange mounting frame such that the battery cable is passing through the little gap on the side
1. Wrap the Kapton tape around the battery and mounting frame 
1. Insert the SD card into the datalogger
1. Attach the datalogger board to the mounting frame using three plastic screws. The USB connector should be facing outward. Do not put a screw in the hole nearest to the jumper pins
1. Attach the sensor board to the mounting frame using as many screws as needed (some boards use 2, some use 4). Orientation does not matter
1. Connect the datalogger and the sensor using the provided cable

Do not connect the battery yet.

# Programming

Make sure you have the [Arduino IDE](https://www.arduino.cc/en/software/#ide) installed. 

## Setting up the Arduino IDE

1. Open the Arduino IDE
1. In the menu, select File > Preferences and the "Settings" tab
1. Add "https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json" (without the quotes) to the "Additional Boards Manager URLs" field. If it already contains a value, add a comma between the existing value and the new URL
1. Click OK
1. In the menu, select Tools > Board > Boards Manager
1. In the text field, enter "RP2040"
1. One of the options should be "Raspberry Pi Pico/RP2040/RP2350 by Earle F [...]". Click on "Install" next to the version number. This may take a while
1. In the menu, select Tools > Board > Raspberry Pi Pico RP2040/RP2350 > Adafruit Feather RP2040 Adalogger
1. Connect your computer and the datalogger board with the USB-C cable
1. After a moment, an option should appear in the menu under Tools > Port. On Windows, this will be COM1 or so. Select that option
1. In the menu, select File > Examples > 01.Basics > Blink
1. Click the "Verify" (checkmark symbol) button in the top left. You should see some output in the black "Output" section at the bottom of the window. Check that there are no error messages.
1. Click the "Upload" (arrow pointing right) button in the top left. You should see some more output, and your datalogger should start blinking an LED
1. Feel free to change the values in the lines that say `delay(1000);` and click "Upload" again. See how the LED's behavior changes.

Leave the USB cable plugged in and connect the battery to the datalogger.
The battery will charge automatically when the logger is connected to a power source via USB.

## Reading and Recording Sensor Values

1. In the Arduino IDE menu, select File > New Sketch
1. In the file list above this readme file, select the folder containing the code for your sensor
1. Open the `.ino` file inside that folder
1. 

# Use

Format SD card and insert into SD card reader.
Connect AdaLogger and sensor board with wire.
Connect battery to AdaLogger.
See status LED for status (see below).
Once the logger is ready for recording (solid green light), put a jumper across the D5 and D6 pins.
The logger will start recording data.
After recovering the payload, remove the jumper from D5/D6.
Once the LED goes back to a solid green, you can remove the power supply.
Logger and sensor can stay connected.

## Status LED

- Red: Failed to initialize SD card.
- Orange: Failed to open root directory on SD card.
- Yellow: Failed to find/connect to sensor.
- Green (solid): Ready to record data.
- Green (blinking on/off every 0.5 s): Recording data.

## Charging the battery

Charge the battery by connecting it to the logger and connecting the logger to a USB power source.
It will automatically run off USB power and charge the battery.
