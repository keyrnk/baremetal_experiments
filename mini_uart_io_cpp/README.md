1. Clang is used for compiling  
For linking and kernel.elf convertation to binary format you'll need ld.lld and llvm-objcopy from llvm project  

```
$ git clone https://github.com/llvm/llvm-project llvm-project
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS=lld -DCMAKE_INSTALL_PREFIX=/usr/local ../llvm-project/llvm
$ make install
```
These commands will build (be prepared for a long build :)) and install both ld.ldd and llvm-objcopy (as other llvm tools)

2. --relocatable flag is needed for ld.lld otherwise the following error is possible:  
ld.lld: error: start.o:(.text.boot+0x34): has non-ABS relocation R_AARCH64_CALL26 against symbol 'main'  
because bl instruction needs relocation mode

