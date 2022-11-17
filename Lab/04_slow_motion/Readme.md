## Replay slow motion

https://user-images.githubusercontent.com/73771085/202311864-71f87ab9-826a-4340-b184-c1f875ad52b5.mp4

This program works when the c program present on the QT Py is integrated with a Python program that takes input from the user and writes data into a TXT file. The c program is unable to access a file on the computre.

A C program contains 4 functions to read the data sequence, replay the data sequence with normal speed, replay the data sequence at half of the normal speed, and replay the data sequence at double the of the normal speed which are called when it gets "r", "n" , "s" and "f" as input, respectively.

A Python program reads serial input from the microcontroller (button press sequence) and saves it to a text file. Depending upon the input, the python program write "r", "n" , "s" and "f" onto the com port to select the operations to perform.
