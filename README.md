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
Typing in the terminal:

```
$ brew install cmake

$ brew tap ArmMbed/homebrew-formulae

$ brew install arm-none-eabi-gcc
```
These are the printscreens of terminal
![This is the printscreen of terminal](https://github.com/xcyxcyxcyxcy/ese5190-2022/blob/main/images/install%20cmake.png)
![This is the printscreen of terminal](https://github.com/xcyxcyxcyxcy/ese5190-2022/blob/main/images/tap%20ArmMbed:homebrew-formulae.png)
![This is the printscreen of terminal](https://github.com/xcyxcyxcyxcy/ese5190-2022/blob/main/images/installarm-none-eabi-gcc.png)
- Downloading Visual Studio Code

Choosing the macOS version

## Building with CMake Tools
- Installing the Cmake Tools extension

Click on the Extensions icon in the left-hand toolbar (or type Cmd + Shift + X), and search for "CMake Tools" and click on the entry in the list, and then click on the install button.

The image of Cmake Tools extensions:
<div align=center><img width="500" height="150" src="https://github.com/xcyxcyxcyxcy/ese5190-2022/blob/main/images/install%20cmake%20tools.png"/></div>

- Setting the pico-sdk-path environment variable
1. Installing git on Mac
Typing in the terminal:

```$ brew install git```

2. Creating pico folder and using git to clone pico-examples and pico-sdk
Typing in the terminal:
