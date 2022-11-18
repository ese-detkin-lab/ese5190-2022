      Sahil Mahendra Mangaonkar
      LinkedIn: https://www.linkedin.com/in/sahil-m-39a2671b0
      Tested on:  HP Probook 650 G1 (15.6-inch, 2014), Window 10

### Registers Video

The following demonstration video shows reading from a register directly. In this program the neopixel LED blinks, if the on-board BOOT button is pressed.

https://user-images.githubusercontent.com/73771085/202279728-a92b1488-7bbe-4a02-b180-5d9fb22b9f88.mp4

Here, we are reading the register with address 0xd0000004. The bit value present at 21st location will be the reading from the boot pin. We have masked the other bits and turning the LED on when boot pin is pressed.


