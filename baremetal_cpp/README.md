###Cross compiler

Firstly you need to download and install cross compiler
[Raspberry cross compiler](docs/raspberrypi3_cross_compiler.md)
[ESP8266 cross compiler](docs/esp8266_cross_compiler.md)

###ESP connection
For ESP connection I use TODO: com port model
Note that for MacOS and Windows you need to download and install additionally driver for your virtual COM port    
For Linux this driver is already included to distributive.
After ESP connection you'll see the proper serial port name in /dev directory or in device manager for Windows. 
In esp/Makefile, term target, change COM port name to COM port assigned to device in your system

In my systems:
- Linux /dev/ttyUSB0  
- MacOs  
- Windows COM20  

###Make build
Change cross compiler path in esp/Makefile to path in your system. 
From current directory:
 
'''
make esp
'''

This will build and flash image, then via pyserial will give you access to console  

'''
make clean_esp
'''

This will clean build directory

###CMake build
Change cross compiler path in cmake_toolchain/esp_gcc4.8.0_toolchain.cmake to path in your system. 
'''
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake_toolchain/esp_gcc4.8.0_toolchain.cmake
make
make flash
make term
'''

CMake build works fine under Linux and MacOS but I still can't build image under Windows. Gcc linker wants some standard libraries. I set CMAKE_EXE_LINKER_FLAGS_INIT to -nostdlib, this helps under MacOs and Linux, but not for Windows. I will continue researh 

###Raspi Make build
Change cross compiler path in raspi/Makefile to path in your system. 
From current directory:
 
'''
make raspi
'''

This will build image

'''
make clean_raspi
'''

This will clean build directory

'''
make qemu_raspi
'''
This will run emulator with image compiled

###CMake build
Change cross compiler path in cmake_toolchain/raspi_gcc8.3.0_toolchain.cmake to path in your system. 
'''
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake_toolchain/raspi_gcc8.3.0_toolchain.cmake
make
make run
'''

CMake build works fine under Linux and Windows. For Clang I have another toolchain file cmake_toolchain/raspi_clang8_toolchain.cmake but now I still can't build with it. It seems that CMake is more friendly with gcc than with Clang. Clang++ calls linker itself so I need to force its choice. I still can't to pass approperiate flags to linker with aarch64 so it tries to link x86_64 object files and fails.
For Clang build please use Makefile.

###Raspberry connection
Take compiled kernel8.img and boot files from boot_files/ and place all this bunch to SD card as is.
For UART connection I used USB 2 tty adapter. Pin scheme you can see at TODO. 
You will see appropriate COM port under /dev in Linux or MacOS and in device manager in Windows.
Use pyserial or putty under Windows to connect to uart.
Reset board and you'll see output. 
