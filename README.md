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
|Laptop | Mi Notebook Pro 15.6 |
|Processor | Intel(R) Core(TM) i7-9750H CPU @ 2.60GHz   2.59 GHz |

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

## 2.4 Building "Hello World" from Visual Studio Code
              
Download the Visual Studio Code from: <br/>
https://code.visualstudio.com/download
<br/>
Install the CMake Tools extension:<br/>
Type (Ctrl + Shift + X), and search for "CMake Tools". Install CMake Tools and configure Cmake : Configure Environment as follow:
![s1](https://user-images.githubusercontent.com/113371324/195964834-e23c2a29-9e0c-475b-9e44-85c534594ee9.png)
Also scroll down to "Cmake: Generator" and enter "NMake Makefiles" into the box:<br/>
![s2](https://user-images.githubusercontent.com/113371324/195964868-ddceed44-f49c-486e-bac1-310280c0c62b.png)
<br/>
Go to the File menu and click on "Open Folder" and navigate to pico-examples and select folder. Select "GCC for arm-none-eabi" for the
compiler and click on the "Build" button in the blue bottom bar. <br/>
Build successful like follow: <br/>
![s6](https://user-images.githubusercontent.com/113371324/195965875-2d09dd65-88bc-4d70-afaf-592845df5d13.png)


## 2.5 Running "Hello World"
Dragged-and-dropped hello_usb.uf2 from C:\Users\pico-examples\build\hello_world\usb onto a RP2040 board. <br/>
Install PuTTY. Run it, and select "Serial", enter 115,200 as the baud ratein the "Speed" box as follow:
![s4](https://user-images.githubusercontent.com/113371324/195965252-77794e74-b7e7-499a-9c25-9cb135a26b05.png)
<br/>
and the serial port that the UART converter is using, which can be found as follow:<br/>
![s3](https://user-images.githubusercontent.com/113371324/195965219-f6cb7619-9947-4da6-89ba-cf7beae56727.png)
<br/>
Then click open. The UART output from the Raspberry Pi Pico will appear Terminal window:<br/>
![s5](https://user-images.githubusercontent.com/113371324/195965279-be67b4db-6c18-4354-8073-65ce5e54747e.png)



