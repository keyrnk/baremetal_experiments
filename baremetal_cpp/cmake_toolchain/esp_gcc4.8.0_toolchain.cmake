set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR "ESP8266")

set(ARDUINO_ESP8266_PATH "C:/Users/Dorozhkina/AppData/Local/Arduino15/packages/esp8266")
set(TOOLCHAIN_PATH "${ARDUINO_ESP8266_PATH}/tools/xtensa-lx106-elf-gcc/2.5.0-3-20ed2b9")
set(ESPTOOL "${ARDUINO_ESP8266_PATH}/hardware/esp8266/2.5.2/tools/esptool/esptool.py")

set(CMAKE_C_COMPILER "${TOOLCHAIN_PATH}/bin/xtensa-lx106-elf-gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}/bin/xtensa-lx106-elf-g++")
set(READELF "${TOOLCHAIN_PATH}/bin/xtensa-lx106-elf-readelf")

set(CMAKE_FIND_ROOT_PATH "${TOOLCHAIN_PATH}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -nostdlib")

add_compile_options(-Wall
                    -Wextra
                    -Wno-unused-parameter
                    -mlongcalls
                    -fno-exceptions
                    -fno-unwind-tables
                    -fno-rtti 
                    -g3
                    -std=c++11)



