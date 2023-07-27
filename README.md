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


