# LED-Cube-8x8x8-RGB
LED-Cube Mikrocontroller Project
[Video of build Cube](https://www.youtube.com/watch?v=Oi0ap_jhWTA)

## Notes
- LED-Cube with 512 RGB-LEDs in 8x8x8
- Controlled by a Microchip Microcontroller PIC18F4420
- Data for LED lighting is read from SD-Card over SPI
- Cube can be accessed from external source over UART.

## Background
Project was created in year 2009. It was my first bigger project i made.
Now it is getting reactivated, so i decided to publish it on github for a better organisation.

Because it was my first project, i had not that much expirience in how to program.
The code works great but it's still less documentated and has a chaotical structure. 
This get changed now!

## Bugs
- FTDI Chip don't work at the moment ( Hardware ) 

## ToDo
- Optimze the coding-style
- Switch microcontroller from PIC18F4420 to PIC18F4520 because of bigger Flash 
- Documentation!
- Support more SD-Cards by adding SDHC-Protocoll
- make API more simple.
- Make Sources independent from Cube x-y-z size
