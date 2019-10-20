1. GNU GCC build   
Download via https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads  
Choose the one for AArch64 ELF bare-metal target (aarch64-elf)  
Just untar it as is for example to /home/user/opt/  
Compiler path is set in Makefile COMPILER_PATH = /home/user/opt/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/bin/    

2. Clang build. 
Compiled GNU GCC for arm A-arch is available only for Windows and Linux hosts. So if you have Mac OS you can either build gcc from sources (not so good idea, believe me) or use Clang (that's more painless).  

For linking and kernel.elf convertation to binary format you'll need ld.lld and llvm-objcopy from llvm project besides clang that you might have.  

```
$ git clone https://github.com/llvm/llvm-project llvm-project
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS=lld -DCMAKE_INSTALL_PREFIX=/usr/local ../llvm-project/llvm
$ make install
```
These commands will build (be prepared for a long build :)) and install both ld.ldd and llvm-objcopy (as other llvm tools) but without any problem.  
Although Clang is a cross-compiler and you can set aarch64-elf target it doesn't have STL headers for this architecture and you build will fail.  
You can get this headers from previously mentioned gcc. Just download
via https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads  
AArch64 ELF bare-metal target (aarch64-elf) and set appropriate include paths in Makefile (see example in repository).  
It will work. 

TODO: see and remove
4. std::basic_string<...> is marked as throw()/noexcept
so if allocator::deallocate calls inside throw-func you'll see compilation error
undefined reference to __cxa_call_unexpected




