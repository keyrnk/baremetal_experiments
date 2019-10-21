set(TOOLCHAIN_PATH "/usr/local/Cellar/llvm/8.0.0_1/bin/")
set(INC_ROOT "/Users/karina/Projects/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/")

set(INC_PATH "-I${INC_ROOT}aarch64-elf/include/c++/8.3.0 -I${INC_ROOT}aarch64-elf/include/c++/8.3.0/aarch64-elf -I${INC_ROOT}aarch64-elf/include -I${INC_ROOT}lib/gcc/aarch64-elf/8.3.0/include")

set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}clang)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}clang++)
set(CMAKE_ASM_COMPILER ${CMAKE_CXX_COMPILER})


set(CMAKE_OBJCOPY ${TOOLCHAIN_PATH}llvm-objcopy CACHE INTERNAL "objcopy tool")
set(CMAKE_LINKER ${TOOLCHAIN_PATH}ld.lld CACHE INTERNAL "linker tool" )

set(CMAKE_C_FLAGS "--target=aarch64-elf -Wall -O2 -ffreestanding" CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS "--target=aarch64-elf -Wall -O2 -ffreestanding -nostdinc -nostdlib -nodefaultlibs -fno-cxx-exceptions -fno-threadsafe-statics ${INC_PATH}" CACHE STRING "" FORCE)

set(CMAKE_EXE_LINKER_FLAGS "--target=aarch64-elf -nostdlib -T load.ld" CACHE STRING "" FORCE)


