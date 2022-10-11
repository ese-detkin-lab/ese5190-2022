I used Windows 11 OS for setup. What I need to do is to follow the guide and complete following toolchains download and installment

Part1: Installing Toolchain

1. Get a exe ending with -arm-none-eabi.exe.

Note: tick theAdd to Path choice during the installment so that use complier directly.

![](Aspose.Words.2321b6af-c794-4edc-8138-eb1fd19e1c6c.001.jpeg)

2. Cmake installment:Also, remember to choose add to path during your installment.

![](Aspose.Words.2321b6af-c794-4edc-8138-eb1fd19e1c6c.002.jpeg)

3. Installing build tools in Visual Studio 2022, following components are necessary under desktop C++ development:

-Windows 10 SDK

-MSVC 143

-Testing tools for core features

-C++Address sanitizer

-C++ make tools for CMake

![](Aspose.Words.2321b6af-c794-4edc-8138-eb1fd19e1c6c.003.jpeg)

4. Python 3.10 install

During the installation, ensure that it’s installed 'for all users' and add Python 3.10 to the system PATH when prompted by the installer.You should additionally disable the MAX\_PATH length limit when prompted at the end of the Python installation

![](Aspose.Words.2321b6af-c794-4edc-8138-eb1fd19e1c6c.004.jpeg)

5. Installing Git:

Note!!!: Remember to tick the checkbox to allow Git to be used from 3rd-party software and, unless you have a strong reason otherwise, when installing Git you should also check the box "Checkout as is, commit as-is", select "Use Windows' default console window", and "Enable experimental support for pseudo consoles" during the installation process.

![](Aspose.Words.2321b6af-c794-4edc-8138-eb1fd19e1c6c.005.jpeg)

![](Aspose.Words.2321b6af-c794-4edc-8138-eb1fd19e1c6c.006.jpeg)

Part2: SDK Environment Setup

1. Enter these command on the terminal to fetch pico-sdk and pico examples files from Github Repository:

***C:\Users\pico\Downloads> git clone -b master https://github.com/raspberrypi/pico-sdk.git C:\Users\pico\Downloads> cd pico-sdk C:\Users\pico\Downloads\pico-sdk> git submodule update --init***

***C:\Users\pico\Downloads\pico-sdk> cd ..***

***C:\Users\pico\Downloads> git clone-b master https://github.com/raspberrypi/pico-examples.git***

2. Use Visual Studio Developer command to open the VScode: then it is time for setting environment for SDK and build hello.c by CMake tools.

Firstly, **you need to enter a *code* in the terminal to open VScode**. Then you should install necessary extensions in VS market space: Cmake tools, before modifying its settings.

- scroll down to "Cmake: Configure Environment". Click on "Add Item" and set the PICO\_SDK\_PATH to be ..\..\pico-sd
- scroll down to "Cmake: Generator" and enter "NMake Makefiles" into the box.

![](Aspose.Words.2321b6af-c794-4edc-8138-eb1fd19e1c6c.007.jpeg)

3. Finally, its time for building the hello world target: Click Files at left top and choose open folders to open the pico-examples folder, and choose the complier as GCC for arm-none-eabi12.2. Then you can click the build button at bottom to generate uf2 files. Drag uf2 to your board, then you can find the hello world is output on your terminal!

![](Aspose.Words.2321b6af-c794-4edc-8138-eb1fd19e1c6c.008.jpeg)
