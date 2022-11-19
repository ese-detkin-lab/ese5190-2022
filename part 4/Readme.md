# TODO: #
* Update your sequencer to be able to slow down and speed up recordings/replay. On the input side, the goal is ultimately to be able to handle the full 4 Gbps "firehose" from the PIO logic analyzer example in the SDK manual, which would fill up 256Kb of RAM in only 31 µs at a system clock speed of 125000 MHz if captured 'raw'! On the output side, the goal is to be able to output precisely timed sequences from the PIO at system clock resolution based on a handful of control points.

* update your sequencer to be able to record just the timestamped transitions between input values, and to be able to play data in this format
give your sequencer the ability to select a range of output rates for both live and recorded input

# Slow Motion #

This program works, When the c program present on the QT Py is integrated with a Python program that takes input from the user and writes data into a TXT file. The text file as below:

<img width="598" alt="3b" src="https://user-images.githubusercontent.com/114259992/202715759-08279e08-b46b-48aa-9722-e1ae270d089e.png">

The C program contains four functions which are called by inputs "r", "n", "s" and "f". Input "r" is to read the data sequence, input "n" is to replay the data sequence with normal speed, input "s" is to replay the data sequence at half of the normal speed, and input "f" is to replay the data sequence at double the of the normal speed.

The Python program reads serial input from the microcontroller (button press sequence) and saves it to a text file. The python program writes "r", "n", "s" and "f" onto the com port to select the operations to perform depending upon the input. The output video:

https://user-images.githubusercontent.com/73771085/202311864-71f87ab9-826a-4340-b184-c1f875ad52b5.mp4
