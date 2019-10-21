set(TOOLCHAIN_PATH "/home/user/opt/gcc-arm-8.3-2019.03-x86_64-aarch64-elf")

SET(CMAKE_FIND_ROOT_PATH  ${TOOLCHAIN_PATH})

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM FIRST)

# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/bin/aarch64-elf-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/bin/aarch64-elf-g++)
SET(CMAKE_OBJCOPY ${TOOLCHAIN_PATH}/bin/aarch64-elf-objcopy)

set(CMAKE_C_FLAGS_INIT "-Wall -O2 -nostdlib -fpermissive" CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS_INIT "-Wall -O2 -nostdlib -fno-exceptions -fno-rtti -fno-threadsafe-statics -fpermissive" CACHE STRING "" FORCE)

set(CMAKE_EXE_LINKER_FLAGS_INIT "-T ${PROJECT_SOURCE_DIR}/load.ld" CACHE STRING "" FORCE)


