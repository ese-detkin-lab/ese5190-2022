University of Pennsylvania, ESE 5190: Intro to Embedded Systems, Lab 2

    Chenye Xiong
        Email: xcyxcy@seas.upenn.edu
    Tested on: MacBook Pro, 13inch, 2022, macOS Monterey 12.6, Apple M2
# Setup Guide for Pico
1. Installing the Toolchain and Visual Studio Code
3. Building with CMake Tools
4. Connecting to the serial console on Mac
5. Connecting with screen
6. Saying "Hello World"
## Step1 Installing the Toolchain and Visual Studio Code
- Intsalling Homebrew
Typing in the terminal:

```
$ /bin/bash -c "$(curl -fsSL
https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
```

- Installing the toolchain
Typing in the terminal

```
$ brew install cmake

$ brew tap ArmMbed/homebrew-formulae

$ brew install arm-none-eabi-gcc
```

- Downloading the macOS version Visual Studio Code
##
