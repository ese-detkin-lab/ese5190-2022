# TODO: #

Toggle the Qt Py's Neopixel LED when the BOOT button is pressed, using only direct register reads to access the boot button status. You may use the SDK to initialize the board and the pins, and the WS2812 example code to toggle the Neopixel.

# Registers Output Video

We can see reading from a register directly from the following demonstration video. In this program, if the onboard BOOT button is pressed then the neopixel LED blinks.

https://user-images.githubusercontent.com/73771085/202279728-a92b1488-7bbe-4a02-b180-5d9fb22b9f88.mp4

Here, we are reading the register with address the 0xd0000004. The reading from the boot pin will be the bit value present at the 21st location. We are turning the LED on only when the Boot Pin is pressed and masked the other bits. 


