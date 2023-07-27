# switchpager
This sketch transforms a Heltec LORA 32 (v2) into a pager with GPIO output

## Background
This sketch has been written for the Heltec LORA 32 (v2) 433 MHz. It transforms the board into a pager (as described by [Manoel](https://github.com/pe2kmv/ESP32-Pocsag-Pager/tree/main/Arduino%20Sketch/ESP32_Pager_ProofOfConcept)).
- match the Heltec board
- switch GPIO pins depending on the message
- choose between a latching and non latching switch

## Libraries
The libraries needed for this project are:
- U8g2lib.h
- RadioLib.h

The U8g2 library is needed to get visual output from the onboard display. RadioLib has everything on board to convert the Heltec module into a pager.

## Configuration
All configuration is done via the config.h file. Change the settings mentioned below to your convenience:
+ POCSAG_QRG: this is the pager receiver frequency in MHz. Default this is set to the European amateur radio pager frequency 439.9875 MHz, which is commonly used by DAPNET;
+ POCSAG_BAUD: set the baudrate for the pager system (512, 1200 or 2400 Bd). Default is 1200 (also commonly used by DAPNET);
+ POCSAG_OFFSET: some boards are slightly off frequency. A correctional factor in MHz can be entered here.

The object 'RICNUMBER' defines how the pager reacts to any message. The first number is the RIC the pager reacts to. The second item is a string representing a self defined label. The next integer defines the number of the GPIO pin. Then an integer defines how long the GPIO pin changes state. The last integer is the keyword to call the GPIO action.

Latched switching can be done by setting the timer to 0 (switching from low to high) or -1 (switching from high to low).

Example in plain words:
{123456, "TX Reset",12,5,1010} -> 'When the keyword 1010 is received via RIC 123456 GPIO 12 is set high for 5 secons while the display shows "TX Reset"'

{123456, "Light on",32,0,3031} -> 'when the keyword 3031 is received via RIC 123456 GPIO 32 is set to high for an indefinite time while the display shows "Light on"'.

## To Do:
+ configure 2 GPIO pins to output a tone and PTT signal which can be coupled to a transmitter to facilitate a test message by audible feedback;
+ create a more secure way of communication to avoid pseudo funny replay attacks.
