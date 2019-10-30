### Raspi Make build
Change cross compiler path in raspi/Makefile to path in your system. 
From current directory:
 
```
make raspi
```

This will build image

```
make clean_raspi
```

This will clean build directory

```
make qemu_raspi
```
This will run emulator with image compiled

### CMake build
Change cross compiler path in cmake_toolchain/raspi_gcc8.3.0_toolchain.cmake to path in your system. 
```
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake_toolchain/raspi_gcc8.3.0_toolchain.cmake
make
make run
```

CMake build works fine under Linux and Windows. For Clang I have another toolchain file cmake_toolchain/raspi_clang8_toolchain.cmake but now I still can't build with it. It seems that CMake is more friendly with gcc than with Clang. Clang++ calls linker itself so I need to force its choice. I still can't to pass approperiate flags to linker with aarch64 so it tries to link x86_64 object files and fails.
For Clang build please use Makefile.