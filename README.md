# LED_Trinket_PIC10F202
<img src="/images/Front_Back.png" alt="image" width="400" height="auto">

## Description
This simple and low-cost project allows students to quickly learn PCB making/etching & soldering while making something more elaborate than just a battery with an LED.
We designed this with simplicity and robustness in mind, choosing through-hole components suitable for soldering novices and an 8-bit Microchip PIC microcontroller for its hardiness. 

We've put this design through the wringer, subjecting it to all sorts of student abuse, including short-circuiting, flipping the IC's orientation, and prolonged burning with a soldering iron. Yet, the components all remained alive after fixing the soldering and PCB mistakes.

The design is powered by a CR2032 coin cell and controlled by a tactile push switch, which drives 2 independent LEDs via a microcontroller. It will cycle through 3 different modes of operation & in its off state; the microcontroller enters deep sleep to extend the battery's life.

## Components Required:
* 1x Pre-programmed PIC10 microcontroller (Refer [here](/src/Blink.c) for the source code)
* 2x 3mm LEDs
* 1x 0.1uF Capacitor
* 1x Tactile Switches
* 1x CR2032 Battery Clip Holder

## Instruction
* For soldering instructions, please refer to the soldering guide [here](docs/Soldering_Guide.pdf).
* After completing the soldering process for the LED Blinker, press the tactile switch to initiate LED blinking. Once blinking has started, continue pressing the switch to adjust the blinking rate.
