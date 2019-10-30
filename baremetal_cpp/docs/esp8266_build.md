### Make build
Change cross compiler path in esp/Makefile to path in your system. 
From current directory:
 
```
make esp
```

This will build and flash image, then via pyserial will give you access to console  

```
make clean_esp
```

This will clean build directory

### CMake build
Change cross compiler path in cmake_toolchain/esp_gcc4.8.0_toolchain.cmake to path in your system. 
```
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake_toolchain/esp_gcc4.8.0_toolchain.cmake
make
make flash
make term
```

CMake build works fine under Linux and MacOS but I still can't build image under Windows. Gcc linker wants some standard libraries. I set CMAKE_EXE_LINKER_FLAGS_INIT to -nostdlib, this helps under MacOs and Linux, but not for Windows. I will continue researh 