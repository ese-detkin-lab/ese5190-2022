### TODO:

Create a 'sequencer' that allows you to record BOOT button presses and play them on the Neopixel, and also play a sequence of read/write commands. You should be able to:
- record at a least a few seconds of button input to your RP2040 (in RAM)
- replay a recorded sequence on your NeoPixel
- loop a recording
- save a recording to your laptop (the Python Serial library is one way to do this)
- play a recording from your laptop
- record 'macros' (a sequence of console commands) based on keystrokes in your serial console
- hand-edit a list of register read/write commands on your laptop, and play them on the RP2040
- include multiple I/O sources in a recording, and remap among the following:
    - inputs: BOOT button, console commands, register read/write commands
    - outputs: neopixel color, neopixel brightness, data over serial, register read/write commands
### Result:
![image](https://github.com/IndigoQuadratic/ese5190-2022-lab2b-esp/blob/a201918b396d4b9cb6f8f680e95015c6f98e0121/flashlight/p3/part3(1).gif)
