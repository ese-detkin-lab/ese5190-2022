# TODO: #
Create a REPL to let you read and write RP2040 registers from a console. You should be able to:

* select any 32-bit address to read/write (even if not a valid RP2020 address)
* read/write any 32-bit value to this address
* read/write using any of the atomic bit-setting aliases and a 32-bit mask

# REPL Video #

Reading from and Writing to a register directly is shown in the following demonstration video. We can also implement an Atomic-bit setting.

https://user-images.githubusercontent.com/73771085/202280796-6efb041b-b64c-434b-af71-99299a92152d.mp4

Here, when "r" input is given by the user followed by the register address (e.g. d00000004 for address 0xd00000004), the program fetches the value of that register.

When "w" input is given by the user to select write to register operation.The user will then have to input the address of the register (e.g. d00000010 for address 0xd00000010) followed by the value to be written into the register.
