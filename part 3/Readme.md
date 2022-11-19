# TODO: #
Create a 'sequencer' that allows you to record BOOT button presses and play them on the Neopixel, and also play a sequence of read/write commands. You should be able to:

* record at a least a few seconds of button input to your RP2040 (in RAM)
* replay a recorded sequence on your NeoPixel
* loop a recording
* save a recording to your laptop (the Python Serial library is one way to do this)
* play a recording from your laptop
* record 'macros' (a sequence of console commands) based on keystrokes in your serial console
* hand-edit a list of register read/write commands on your laptop, and play them on the RP2040
* include multiple I/O sources in a recording, and remap among the following:
           * inputs: BOOT button, console commands, register read/write commands
           * outputs: neopixel color, neopixel brightness, data over serial, register read/write commands

# Sequencer Output #

When the input is "r" and "p" then, the two functions in the C program to read and replay the data sequence are called respectively. You can see the terminal output below:

<img width="595" alt="3" src="https://user-images.githubusercontent.com/114259992/202714440-b7afa0c3-a5a8-46c7-80c0-9746baea4442.png">

This program works when the c program present on the QT Py is integrated with a Python program that takes input from the user and writes data into a TXT file. The c program is unable to access a file on the computer. You can see the Text file below:

<img width="598" alt="3b" src="https://user-images.githubusercontent.com/114259992/202714420-ae4bf3ab-66a1-4124-84cd-b5779499f747.png">

A Python program reads serial input from the microcontroller (button press sequence) and saves it to 
a text file. Depending upon the input, the python program write "r" and "p" onto the com port to select read and replay the data sequence option. As you can see in the output video:


https://user-images.githubusercontent.com/73771085/202282888-2cb7f6b7-0417-4733-afcc-d50153e2119d.mp4


