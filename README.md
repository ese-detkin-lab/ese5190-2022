
Shuhan Qian  
  &nbsp;https://www.linkedin.com/in/shuhan-qian-53014524a/  
  &nbsp;email:qiansh@seas.upenn.edu  
  &nbsp;Tested on: XiaoXinPro16 Lenovo, AMD Ryzen 7 5800H(3.2GHZ)  

  
Part1: Installing Toolchain
1.Get a exe ending with -arm-none-eabi.exe.   
&nbsp;&nbsp;Note: tick the Add to Path choice during the installment so that use complier directly.  

<img width="416" alt="image" src="https://user-images.githubusercontent.com/64452307/194979586-8907cf9f-073b-4196-b197-095b9ea448b5.png">

2.Cmake installment: Also, remember to choose add to path during your installment.  

<img width="358" alt="image" src="https://user-images.githubusercontent.com/64452307/194979606-bec01abd-977a-4d14-a321-f27b5d51841f.png">

3.Installing build tools in Visual Studio 2022, following components are necessary under desktop C++ development:  
&nbsp;&nbsp;-Windows 10 SDK  
&nbsp;&nbsp;-MSVC 143  
&nbsp;&nbsp;-Testing tools for core features  
&nbsp;&nbsp;-C++ Address sanitizer  
&nbsp;&nbsp;-C++ make tools for CMake  

<img width="416" alt="image" src="https://user-images.githubusercontent.com/64452307/194979631-e92b2a5e-bf05-47fb-acde-a16aad4f289f.png">

4. Python 3.10 install  
&nbsp;During the installation, ensure that it’s installed 'for all users' and add Python 3.10 to the system PATH when prompted by the installer. You &nbsp;should additionally disable the MAX_PATH length limit when prompted at the end of the Python installation

<img width="383" alt="image" src="https://user-images.githubusercontent.com/64452307/194979668-19bb029b-3d76-4ff7-ac2d-fb9132eff199.png">

5. Installing Git:
&nbsp;Note!!!: Remember to tick the checkbox to allow Git to be used from 3rd-party software and, unless you have a strong reason otherwise, when &nbsp;installing Git you should also check the box "Checkout as is, commit as-is", select "Use Windows' default console window", and "Enable &nbsp;experimental support for pseudo consoles" during the installation process.  
<img width="347" alt="image" src="https://user-images.githubusercontent.com/64452307/194979696-fa169b86-b05a-4f1c-9316-6c69bfd393c7.png">
<img width="347" alt="image" src="https://user-images.githubusercontent.com/64452307/194979724-7654a640-f26a-459a-8cd7-d6ebfadd37fd.png">

Part2: SDK Environment Setup  
&nbsp;1.Enter these command on the terminal to fetch pico-sdk and pico examples files from Github Repository: 
&nbsp;&nbsp;C:\Users\pico\Downloads> git clone -b master https://github.com/raspberrypi/pico-sdk.git   
&nbsp;&nbsp;C:\Users\pico\Downloads> cd pico-sdk C:\Users\pico\Downloads\pico-sdk> git submodule update --init   
&nbsp;&nbsp;C:\Users\pico\Downloads\pico-sdk> cd ..   
&nbsp;&nbsp;C:\Users\pico\Downloads> git clone-b master https://github.com/raspberrypi/pico-examples.git  

2.Use Visual Studio Developer command to open the VScode: then it is time for setting environment for SDK and build hello.c by CMake tools. 
&nbsp;Firstly, you need to enter a code in the terminal to open VScode. Then you should install necessary extensions in VS market space: Cmake tools, &nbsp;before modifying its settings. 
&nbsp;-scroll down to "Cmake: Configure Environment". Click on "Add Item" and set the PICO_SDK_PATH to be ..\..\pico-sd
&nbsp;-scroll down to "Cmake: Generator" and enter "NMake Makefiles" into the box.

<img width="416" alt="image" src="https://user-images.githubusercontent.com/64452307/194979759-b4e5c3c4-1542-4b6a-bb45-d902efd0bf68.png">

<img width="1267" alt="image" src="https://user-images.githubusercontent.com/64452307/194980200-12dcf3b6-1074-4600-8ca8-d77be9d9c471.png">

3.Finally, its time for building the hello world target: Click Files at left top and choose open folders to open the pico-examples folder, and choose &nbsp;the complier as GCC for arm-none-eabi12.2. Then you can click the build button at bottom to generate uf2 files. Drag uf2 to your board, then you &nbsp;can find the hello world is output on your terminal!

<img width="881" alt="image" src="https://user-images.githubusercontent.com/64452307/194980115-7653be16-1aed-4abb-8ab8-1e36ed141a7a.png">

<img width="416" alt="image" src="https://user-images.githubusercontent.com/64452307/194979770-2aecdddd-5c06-440b-bd43-800b97a11b61.png">
