ESE 5190: Intro to Embedded Systems

#### Lab repos
1. [`firefly`](https://github.com/ese-detkin-lab/ese5190-2022-lab1-firefly)
2. [`into the (void *)`](https://github.com/ese-detkin-lab/ese5190-2022-lab2-into-the-void-star)

#### Class wiki
[`RP2040 setup guides`](https://github.com/ese-detkin-lab/ese5190-2022/blob/main/guides/RP2040-C-SDK-setup.md)


# Part 2:
## 2.1 Setup
|  | Environment|
|---    |---|
| OS    |    Windows 11 21H2|
|Laptop |  |
***
## 2.2 Installing the Toolchain
To build you will need to install some extra tools:<br/>
• [ARM GNU Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)<br/>
• [CMake](https://cmake.org/download/)<br/>
• [Build Tools for Visal Studio 2022](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022)<br/>
• [Python 3.10](https://www.python.org/downloads/windows/)<br/>
• [Git](https://git-scm.com/download/win)<br/>

## 2.3 Setup SDK
        
              C:\Users\pico\Downloads> git clone -b master https://github.com/raspberrypi/pico-sdk.git
              C:\Users\pico\Downloads> cd pico-sdk
              C:\Users\pico\Downloads\pico-sdk> git submodule update --init
              C:\Users\pico\Downloads\pico-sdk> cd ..
              C:\Users\pico\Downloads> git clone -b master https://github.com/raspberrypi/pico-examples.git
