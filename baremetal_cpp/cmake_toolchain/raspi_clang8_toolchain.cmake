set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR "arm")

set (INC_ROOT "/Users/karina/Projects/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/")

set (INC_PATH "-I${INC_ROOT}aarch64-elf/include/c++/8.3.0 -I${INC_ROOT}aarch64-elf/include/c++/8.3.0/aarch64-elf -I${INC_ROOT}aarch64-elf/include -I${INC_ROOT}lib/gcc/aarch64-elf/8.3.0/include")

set(TOOLCHAIN_PATH "/usr/local/Cellar/llvm/8.0.0_1/bin")

SET(CMAKE_FIND_ROOT_PATH  "${TOOLCHAIN_PATH}")

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


SET(CMAKE_C_COMPILER "${TOOLCHAIN_PATH}/clang")
SET(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}/clang++")
SET(CMAKE_ASM_COMPILER "${TOOLCHAIN_PATH}/clang++" CACHE FILEPATH "asm" FORCE)
SET(CMAKE_LINKER "${TOOLCHAIN_PATH}/ld.lld" CACHE FILEPATH "Linker" FORCE)
SET(CMAKE_OBJCOPY "${TOOLCHAIN_PATH}/llvm-objcopy" CACHE FILEPATH "objcopy" FORCE)
SET(CMAKE_AR "${TOOLCHAIN_PATH}/llvm-ar" CACHE FILEPATH "ar" FORCE)
SET(CMAKE_RUNLIB "${TOOLCHAIN_PATH}/llvm-runlib" CACHE FILEPATH "runlib" FORCE)
SET(CMAKE_OBJDUMP "${TOOLCHAIN_PATH}/llvm-objdump" CACHE FILEPATH "objdump" FORCE)
SET(CMAKE_RUNLIB "${TOOLCHAIN_PATH}/llvm-nm" CACHE FILEPATH "nm" FORCE)

