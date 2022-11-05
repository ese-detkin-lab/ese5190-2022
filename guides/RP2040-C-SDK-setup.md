# Setup guide -- Rongqian Chen

E-mail: willchan@seas.upenn.edu

Test on:

Alienware m15 R2   
Intel(R) Core(TM) i7-9750H CPU @ 2.60GHz   2.59 GHz  
Windows 10  

## Step 1: install GNU tool chain  
Download and install the ARM GNU toolchain, download here: https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
If you are windows x64 system, use this:

![1665800333329](https://user-images.githubusercontent.com/43904091/195964503-3bb852b1-44f0-45d8-9e14-0cbe46bae658.png)

 After completing the setup, make sure you tick the box to add the path to environment variable.
 
 ![image](https://user-images.githubusercontent.com/43904091/195964550-079335bd-dc29-4d3e-8510-912cbf1df8bb.png)

## step 2: Install the CMake
Link: https://cmake.org/download/
![1665800807955](https://user-images.githubusercontent.com/43904091/195964883-3478ed89-802e-427f-bc92-5a031692ca34.png)
In the installation, tick this:
![1665800961727](https://user-images.githubusercontent.com/43904091/195964927-1e52671f-7e51-45fe-91f1-d8e16eeeee8a.png)

## step 3: install Visual Studio Build Tools
Link: https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022  
![1665801067926](https://user-images.githubusercontent.com/43904091/195964980-dcb1a59c-b5e9-4e0d-aa9b-5b48919eb54b.png)

## step 4: install Python 3.10
Link: https://www.python.org/downloads/
![1665801754273](https://user-images.githubusercontent.com/43904091/195965316-2d28e15b-c7b2-4ec1-8bd2-9a8cf14f25e4.png)
At the beginning of installation tick the following options:  
![1665801967134](https://user-images.githubusercontent.com/43904091/195965452-6d6106c8-4403-465e-b9a7-74624a0c9cbb.png)
And after installation compeleted, disable the MAX_PATH length limit.

## step 5: install Git
Link: https://git-scm.com/download/win  
![1665802293212](https://user-images.githubusercontent.com/43904091/195965650-27e8e272-5e03-4c67-9d0c-742045f7d590.png)

Choose the Notepad as default editor:  

![1665802355194](https://user-images.githubusercontent.com/43904091/195965766-6113685b-31eb-4a9d-a213-d7d2572e9153.png)


## step 6: Getting the SDK and examples
```
C:\Users\Xuanang Chen\pico\Downloads> git clone -b master https://github.com/raspberrypi/pico-sdk.git  
C:\Users\Xuanang Chen\pico\Downloads> cd pico-sdk  
C:\Users\Xuanang Chen\pico\Downloads\pico-sdk> git submodule update --init   
C:\Users\Xuanang Chen\pico\Downloads\pico-sdk> cd ..  
C:\Users\Xuanang Chen\pico\Downloads> git clone -b master https://github.com/raspberrypi/pico-examples.git  

```

# step 7: Building "Hello World" from Developer Command Prompt Window

Open the Developer Command Prompt window from the Windows Menu:

![1665803271184](https://user-images.githubusercontent.com/43904091/195966245-b974009a-8ecd-4c97-802d-6327fb443087.png)

Then set the path：

```
C:\Users\pico\Downloads> setx PICO_SDK_PATH "..\..\pico-sdk"
```

Then close the current one and open a new window, navigate to pico-examples folder, and build all the template code as follows:

```
C:\Users\pico\Downloads> cd pico-examples
C:\Users\pico\Downloads\pico-examples> mkdir build
C:\Users\pico\Downloads\pico-examples> cd build
C:\Users\pico\Downloads\pico-examples\build> cmake -G "NMake Makefiles" ..
C:\Users\pico\Downloads\pico-examples\build> nmake
```
Then in the build folder, you will find a lot of files, e.g. bin, hex, uf2... We only need uf2 for QT PY 2040 running. Here let's go to hello_world usb example folder. Hold the boot botton on the board, then pull the uf2 file into the directory, then the program would run automatically. Use Putty to open the corresponding serial port, you will find the board sending "hello world" periodically.

![1665804191099](https://user-images.githubusercontent.com/43904091/195966730-57e034f5-d61d-4206-885d-0ff2cdadbc2a.png)
![1665804164410](https://user-images.githubusercontent.com/43904091/195966706-bceadf65-4a28-426f-8953-10229d1c7c69.png)


# step 7: Building "Hello World" from Visual Studio Code

Another way to build your code is using Visual Studio Code. First install CMake Extension, then open the setting and change the following entry:

![1665804258078](https://user-images.githubusercontent.com/43904091/195966778-202c472e-7c2e-4d7d-8d63-8fc061d83b2e.png)

![1665804332050](https://user-images.githubusercontent.com/43904091/195966793-587f2b96-958d-4d46-9913-250279130a58.png)

Finally, click "build" button in the status bar at the bottom, and choose "GCC for arm-none-eabi" for compiler. The uf2 files will appear after setup progress at 100%.
