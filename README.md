# BLEMIDI

Use an Adafruit Arduino Feather as a BLE MIDI device.

This simple sketch passes data straight through to h/w serial. Use it to bring BLE MIDI to your ancient sythesisers.

## Prerequisites.

###Hardware
For the BLE MIDI to 'standard' MIDI requires you build interface hardware similar to this:
![alt tag](https://www.arduino.cc/en/uploads/Tutorial/MIDI_schem.png)

###Firmware
Requires the nRF51 module has the 0.70 firmware (currently beta). Get it [here] (https://github.com/adafruit/Adafruit_BluefruitLE_Firmware/tree/master/beta/0.7.0/blespifriend).

Use the Adafruit Bluefruit LE iOS app to install it.

###Libraries
Requires the Adafruit BLE MIDI library. Currently BLE MIDI is only available under the development branch so clone it into your Arduion libraries folder:

```
cd path/to/ardunio/libraries
git clone -b development https://github.com/adafruit/Adafruit_BluefruitLE_nRF51.git
```




