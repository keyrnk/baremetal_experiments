INCLUDE(CMakeForceCompiler)

set(ARDUINO_ESP8266_PATH C:/Users/Dorozhkina/AppData/Local/Arduino15/packages/esp8266)
set(TOOLCHAIN_PATH ${ARDUINO_ESP8266_PATH}/tools/xtensa-lx106-elf-gcc/2.5.0-3-20ed2b9)
set (ESPTOOL ${ARDUINO_ESP8266_PATH}/hardware/esp8266/2.5.2/tools/esptool/esptool.py)

# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(CMAKE_AR ${TOOLCHAIN_PATH}/bin/xtensa-lx106-elf-ar)
SET(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/bin/xtensa-lx106-elf-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/bin/xtensa-lx106-elf-g++)
SET(CMAKE_READELF ${TOOLCHAIN_PATH}/bin/xtensa-lx106-elf-readelf)
SET(CMAKE_C_LINK_EXECUTABLE ${TOOLCHAIN_PATH}/bin/xtensa-lx106-elf-ld)

set(CMAKE_C_FLAGS_INIT "-Wall -O2 -nostdlib" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_INIT "-nostdlib -mlongcalls -fno-exceptions -fno-unwind-tables -fno-rtti -Wall -g3 -std=c++11" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_INIT "-nostdlib -T ${PROJECT_SOURCE_DIR}/esp/karina_main.ld" CACHE STRING "" FORCE)


