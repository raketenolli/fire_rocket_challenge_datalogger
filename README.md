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
1. Click the "Verify" (checkmark symbol) button in the top left. You should see some output in the black "Output" section at the bottom of the window. Check that there are no error messages
1. Click the "Upload" (arrow pointing right) button in the top left. You should see some more output, and your datalogger should start blinking an LED
1. Feel free to change the values in the lines that say `delay(1000);` and click "Upload" again. See how the LED's behavior changes

## Charging the Battery

Leave the USB cable plugged in and connect the battery to the datalogger.
The battery will charge automatically whenever the logger is connected to a power source via USB.

## Reading and Recording Sensor Values

1. In the Arduino IDE menu, select File > New Sketch. A "sketch" is Arduino-speak for a code file
1. In the file list above this readme file (in your browser), select the folder containing the code for your sensor
1. Open the `.ino` file inside that folder
1. It should show the full code. Click the "Copy raw file" (two overlapping squares) button to the top right of the code
1. Go back to the Arduino IDE and paste the code into the new, empty sketch
1. Click the "Verify" button in the top left. Check that there are no error messages
1. In the menu, select Tools > Serial Monitor. The Serial Monitor displays any data or other messages that the datalogger is sending to your computer
1. Click the "Upload" button in the top left
1. Once the upload is complete, you should see some messages in the Serial Monitor window, such as "<sensor name> found!" and "<sensor name> configured!"
1. The LED should be showing a continuous green light
1. Connect pins D5 and D6 (the two pins) with a jumper
1. The LED should start blinking green every second. It is now recording data
1. Remove the jumper. The LED should go back to continuous green.

You can now disconnect the datalogger from the USB cable and the battery.

Having to connect the two pins to start the recording is used to make sure that the data on the SD card does not get corrupted. If the datalogger is disconnected from power while data is being written to the SD card, the data file may no longer be readable, or even the whole SD card would need reformatting.

### LED Status Indicator and Troubleshooting

The LED color is used to indicate certain issues which may not be immediately apparent, especially if the logger is not connected to a computer and you cannot read messages on the Serial Monitor.

- Red: Failed to initialize SD card. Make sure your SD card is formatted and inserted properly into the SD card slot
- Orange: Failed to open root directory on SD card. Make sure your SD card is formatted and inserted properly into the SD card slot
- Yellow: Failed to find/connect to sensor. Either the cable connecting datalogger and sensor board is damaged or not seated correctly, or you chose the wrong code to program the datalogger. The code needs to match the sensor (this may be made simpler in the future)
- Green (solid): Ready to record data. You are good to go and can connect the jumper
- Green (blinking on/off every 0.5 s): Recording data. Do not remove the power supply while data is being recorded

# Use in Flight

1. Mount the mounting frame to e.g. a balsa board that is cut to the correct length and width of your payload bay (should be 150 mm long and 50 mm in diameter; BT-70 is large enough)
1. Connect the battery to the datalogger
1. Wait for the solid green light to appear. Connect the jumper
1. Insert the board into your payload bay. Close up the payload bay with a nosecone or coupler and make sure it cannot separate (e.g. masking tape). You can do this while on the launch pad
1. Launch and recover the rocket
1. Remove the nosecone and the board holding the datalogger
1. Remove the jumper and wait for the LED to turn solid green again
1. Disconnect the battery from the datalogger

You can now remove the SD card (will require removing the sensor board) from the datalogger and open its contents on a computer.


