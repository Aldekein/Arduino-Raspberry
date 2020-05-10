# Arduino and Raspberry Pi sources

## Setup

Remember to add the following line in VS Code settings:

`"C_Cpp.intelliSenseEngine": "Tag Parser",`

## Code inside

### PIR-to-air

Is using a Arduino/ARM/MCU Transmitter & Receiver Kit RF Wireless 433Mhz Module + PIR motion sensor.
When motion is detected -> sends an alert over the air. Alert is received by RPi in another room.
Will be used to deploy alarm sensors in attic and other places of housing cooperative.