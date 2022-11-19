### `/lab2b/part01/link`
https://github.com/ZhijingY/ese5190-2022-lab2b-esp/blob/main/lab/01_registers/README.md
### `/lab2b/part01/status`
Completed
### `/lab2b/part02/link`
https://github.com/ZhijingY/ese5190-2022-lab2b-esp/blob/main/lab/02_repl/README.md
### `/lab2b/part02/status`
Completed
### `/lab2b/part03/link`
https://github.com/ZhijingY/ese5190-2022-lab2b-esp/blob/main/lab/04_slow_motion/README.md
### `/lab2b/part03/status`
Completed. Part 3 and 4 are updated, and are combined into one.
### `/lab2b/part04/link`
https://github.com/ZhijingY/ese5190-2022-lab2b-esp/blob/main/lab/04_slow_motion/README.md
### `/lab2b/part04/status`
Completed
### `/lab2b/part05/link`
https://github.com/ZhijingY/ese5190-2022-lab2b-esp/blob/main/lab/05_i2c_traffic/README.md
### `/lab2b/part05/status`
complete
### `/lab2b/part06/link`
https://github.com/ZhijingY/ese5190-2022-lab2b-esp/tree/main/lab/06_pioscope
### `/lab2b/part06/status`
Completed
### `/lab2b/part07/link`
https://github.com/ZhijingY/ese5190-2022-lab2b-esp/tree/main/lab/07_pio_sequencer
### `/lab2b/part07/status`
Completed
### `/lab2b/part08/link`
https://github.com/ZhijingY/ese5190-2022-lab2b-esp/blob/main/lab/08_adps_protocol/README.md
### `/lab2b/part08/status`
Completed.
### `/lab2b/part09/link`
https://github.com/ZhijingY/ese5190-2022-lab2b-esp/blob/main/lab/09_lab_on_a_chip/README.md
### `/lab2b/part09/status`
Completed.
### `/lab2b/part10/link`
https://github.com/ZhijingY/ese5190-2022-lab2b-esp/blob/main/lab/10_protoboard/README.md
### `/lab2b/part10/status`
Completed.
### `/lab2b/status`
Done.
### Friday Submission Answers

1. I found the description of part 3 requirements the most confusing. In the description it is stated that:

        record 'macros' (a sequence of console commands) based on keystrokes in your serial console
        hand-edit a list of register read/write commands on your laptop, and play them on the RP2040
        include multiple I/O sources in a recording, and remap among the following:
        inputs: BOOT button, console commands, register read/write commands
        outputs: neopixel color, neopixel brightness, data over serial, register read/write commands

    It is not quite clear how to play the register read/write commands on the RP2040. Many questions occured to me: do we need to handle the registers that do not allow reading? Shall we explicitly demonstrates the register reading/writing on the RP2040 by flashing the lights/tranferring data on specific bus, or just send a success/failure notice after the reading/writing attempt? How do we make the MCU interpret the literal commands?
    
2. Progamming the PIO files, especially the assembly part is the modt confusing part to me. It requires many efforts on reading the documentations and datasheets regarding the PIO techniques.

3. C/Python co-design for sequencer is the most challenging part to me, especially the "serial" library utilized in the Python code. 

4. I discussed with my teammates and seeked for help online by searching for documentations and posts on forum. For the difficult problem that I could not find any relevant information online, I would check my peer classmates' solutions for inspirations.
