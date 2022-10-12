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

```
$ brew install git
```

This is the printscreen of terminal:
<div align=center><img width="600" height="550" src="https://github.com/ese-detkin-lab/ese5190-2022/blob/056e000e23355ad776f2dd0adc4371b9cfdfda05/images/install%20git.png"/></div>

2. Creating pico folder and using git to clone pico-examples and pico-sdk

Typing in the terminal:
```
$ mkdir pico
$ cd pico
```
This is the printscreen of terminal:
![This is the printscreen of terminal](https://github.com/ese-detkin-lab/ese5190-2022/blob/056e000e23355ad776f2dd0adc4371b9cfdfda05/images/pico%20folder.png)

Now we have created a pico folder and opened it, then we can clone pico-sdk and pico-examples in it:
```
$ git clone -b master https://github.com/raspberrypi/pico-sdk.git
$ cd pico-sdk
$ git submodule update --init
$ cd ..
$ git clone -b master https://github.com/raspberrypi/pico-examples.git
```
These are the printscreens of terminal:
![This is the printscreen of terminal](https://github.com/ese-detkin-lab/ese5190-2022/blob/056e000e23355ad776f2dd0adc4371b9cfdfda05/images/clone%20sdk.png)
![This is the printscreen of terminal](https://github.com/ese-detkin-lab/ese5190-2022/blob/056e000e23355ad776f2dd0adc4371b9cfdfda05/images/clone%20example.png)

3. Creating a .vscode folder and adding a file called setting.json in it

It's purpose is to tell CMake Tools the location of the SDK:
<div align=center><img width="300" height="150" src="https://github.com/xcyxcyxcyxcy/ese5190-2022/blob/main/images/settingjson.png"/></div>

The code in setting.json is:

```
{
    "cmake.environment": {
        "PICO_SDK_PATH":"../../pico-sdk"
    },
}
```
The image:
<div align=center><img width="500" height="200" src="https://github.com/xcyxcyxcyxcy/ese5190-2022/blob/main/images/code%20in%20settingjson.png"/></div>

4.Setting the generator of Cmake and building environment variable of Cmake

Now click on the Cog Wheel at the bottom of the navigation bar on the left-hand side of the interface and select "Settings". Then in the Settings pane click on "Extensions" and the "CMake Tools". Then click the "Extension Settings" of CMake Tools, scroll down to "Cmake: Generator" and enter "Unix Makefiles" into the box.

The printscreen of VSCode:
<div align=center><img width="700" height="500" src="https://github.com/xcyxcyxcyxcy/ese5190-2022/blob/main/images/generator.png"/></div>

Then scoll up to the "Cmake:Build Environment",and add PICO_SDK_PATH to Item and add ../../pico-sdk to Value.

The printscreen of VSCode:
<div align=center><img width="500" height="200" src="https://github.com/xcyxcyxcyxcy/ese5190-2022/blob/main/images/environment.png"/></div>
