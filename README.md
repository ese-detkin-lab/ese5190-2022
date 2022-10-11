ESE 5190: Intro to Embedded Systems

#### Lab repos
1. [`firefly`](https://github.com/ese-detkin-lab/ese5190-2022-lab1-firefly)
2. [`into the (void *)`](https://github.com/ese-detkin-lab/ese5190-2022-lab2-into-the-void-star)

#### Class wiki
[`RP2040 setup guides`](https://github.com/ese-detkin-lab/ese5190-2022/blob/main/guides/RP2040-C-SDK-setup.md)
I used Windows 11 OS for setup. What I need to do is to follow the guide and complete following toolchains download and installment
  
Part1: Installing Toolchain
1.Get a exe ending with -arm-none-eabi.exe. 
Note: tick the Add to Path choice during the installment so that use complier directly.

<img width="416" alt="image" src="https://user-images.githubusercontent.com/64452307/194979586-8907cf9f-073b-4196-b197-095b9ea448b5.png">

2.Cmake installment: Also, remember to choose add to path during your installment.

<img width="358" alt="image" src="https://user-images.githubusercontent.com/64452307/194979606-bec01abd-977a-4d14-a321-f27b5d51841f.png">

3.Installing build tools in Visual Studio 2022, following components are necessary under desktop C++ development:
-Windows 10 SDK
-MSVC 143
-Testing tools for core features
-C++ Address sanitizer
-C++ make tools for CMake

<img width="416" alt="image" src="https://user-images.githubusercontent.com/64452307/194979631-e92b2a5e-bf05-47fb-acde-a16aad4f289f.png">

4. Python 3.10 install
During the installation, ensure that it’s installed 'for all users' and add Python 3.10 to the system PATH when prompted by the installer. You should additionally disable the MAX_PATH length limit when prompted at the end of the Python installation

<img width="383" alt="image" src="https://user-images.githubusercontent.com/64452307/194979668-19bb029b-3d76-4ff7-ac2d-fb9132eff199.png">

5. Installing Git:
Note!!!: Remember to tick the checkbox to allow Git to be used from 3rd-party software and, unless you have a strong reason otherwise, when installing Git you should also check the box "Checkout as is, commit as-is", select "Use Windows' default console window", and "Enable experimental support for pseudo consoles" during the installation process.
<img width="347" alt="image" src="https://user-images.githubusercontent.com/64452307/194979696-fa169b86-b05a-4f1c-9316-6c69bfd393c7.png">
<img width="347" alt="image" src="https://user-images.githubusercontent.com/64452307/194979724-7654a640-f26a-459a-8cd7-d6ebfadd37fd.png">

Part2: SDK Environment Setup
1.Enter these command on the terminal to fetch pico-sdk and pico examples files from Github Repository: 
C:\Users\pico\Downloads> git clone -b master https://github.com/raspberrypi/pico-sdk.git 
C:\Users\pico\Downloads> cd pico-sdk C:\Users\pico\Downloads\pico-sdk> git submodule update --init 
C:\Users\pico\Downloads\pico-sdk> cd .. 
C:\Users\pico\Downloads> git clone-b master https://github.com/raspberrypi/pico-examples.git

2.Use Visual Studio Developer command to open the VScode: then it is time for setting environment for SDK and build hello.c by CMake tools. 
Firstly, you need to enter a code in the terminal to open VScode. Then you should install necessary extensions in VS market space: Cmake tools, before modifying its settings. 
-scroll down to "Cmake: Configure Environment". Click on "Add Item" and set the PICO_SDK_PATH to be ..\..\pico-sd
-scroll down to "Cmake: Generator" and enter "NMake Makefiles" into the box.

<img width="416" alt="image" src="https://user-images.githubusercontent.com/64452307/194979759-b4e5c3c4-1542-4b6a-bb45-d902efd0bf68.png">

<img width="1267" alt="image" src="https://user-images.githubusercontent.com/64452307/194980200-12dcf3b6-1074-4600-8ca8-d77be9d9c471.png">

3.Finally, its time for building the hello world target: Click Files at left top and choose open folders to open the pico-examples folder, and choose the complier as GCC for arm-none-eabi12.2. Then you can click the build button at bottom to generate uf2 files. Drag uf2 to your board, then you can find the hello world is output on your terminal!

<img width="881" alt="image" src="https://user-images.githubusercontent.com/64452307/194980115-7653be16-1aed-4abb-8ab8-1e36ed141a7a.png">

<img width="416" alt="image" src="https://user-images.githubusercontent.com/64452307/194979770-2aecdddd-5c06-440b-bd43-800b97a11b61.png">
