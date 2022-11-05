ESE 5190: Intro to Embedded Systems

#### Lab repos
1. [`firefly`](https://github.com/ese-detkin-lab/ese5190-2022-lab1-firefly)
2. [`into the (void *)`](https://github.com/ese-detkin-lab/ese5190-2022-lab2-into-the-void-star)

#### Class wiki
[`RP2040 setup guides`](https://github.com/ese-detkin-lab/ese5190-2022/blob/main/guides/RP2040-C-SDK-setup.md)


# Lab-2B-Submission-Dashboard

## Blinking the LED ##

As you can see here we are using a Breadboard, Adafruit QT Py RP2040, one resistor, RED LED, and Jumper wires. They are connected as shown in the picture below: <br>

<p align = "center">

<img width="466" alt="23435" src="https://user-images.githubusercontent.com/114259992/197166327-e9269731-d65f-478a-b7ae-c55757e642a2.png">

</p>

<br>

*LED Circuit*
<br>

After running our LED code with the same procedure as mentioned in the setup guide for Hello World <br>

https://github.com/AkshayaBhati/ESE-519-Lab-2-Setup-Guide/blob/main/README.md <br>

We can see the LED Blinking <br>

<p align = "center">

![LED Blinking (1)](https://user-images.githubusercontent.com/114259992/197149426-1547e072-1e63-4e48-97d8-a94ba02519f4.gif)

</p>

## Lab 2B Proposal ##

Here we are using a Push Button to on and off the LEDs operation. <br>

![Push Button GIF](https://user-images.githubusercontent.com/114259992/200097343-c4a57d90-a3b3-448c-83c6-eda3447c35b2.gif)

Then we are using a slider button. If it's in the right direction, then the right arrow will glow and similarly left arrow will glow for left direction. <br>

![Slider Button GIF](https://user-images.githubusercontent.com/114259992/200097311-2f6c758d-8df1-47ec-a82e-45455a65f793.gif)

The LED will glow in the shape of an arrow in the direction the slider button is moved. If in the right direction then 8 LEDs will glow, making a pattern of an arrow in the right direction and similarly for the left. It resembles the car's rear indicators. <br>

https://user-images.githubusercontent.com/114259992/200098455-5a24a71c-7320-4264-82a9-03bc9482b5e8.mp4

Block Diagram: <br>
<p align = "center">

<img width="328" alt="Block Diagram" src="https://user-images.githubusercontent.com/114259992/200098293-33d66632-55d5-4839-a8c8-d1333058cfc8.png">  

</p>

## Components Required ##

10 LEDs <br>
10 330 ohms resistors (for LEDs)<br>
2 10 kilo-ohms resistors (pull up resistors for the buttons) <br>
Jumper wires <br>
Breadboard <br>
1 Push Button <br>
1 Slider Button <br>
1 Protoboard <br>
