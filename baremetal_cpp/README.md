1. For build gnu-gcc is using   
You can pick it up from https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads  
The one for aarch64-elf  
Compiler path is set in Makefile COMPILER_PATH = /home/user/opt/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/bin/  

2. If you want Clang build  
For linking and kernel.elf convertation to binary format you'll need ld.lld and llvm-objcopy from llvm project  

```
$ git clone https://github.com/llvm/llvm-project llvm-project
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS=lld -DCMAKE_INSTALL_PREFIX=/usr/local ../llvm-project/llvm
$ make install
```
These commands will build (be prepared for a long build :)) and install both ld.ldd and llvm-objcopy (as other llvm tools)

--relocatable flag is needed for ld.lld otherwise the following error is possible:  
ld.lld: error: start.o:(.text.boot+0x34): has non-ABS relocation R_AARCH64_CALL26 against symbol 'main'  
because bl instruction needs relocation mode

3. strange 
requires memset
std::basic_string<char, std::char_traits<char>, ArenaAllocator<char> > s(16, 's');
doesn't require
std::basic_string<char, std::char_traits<char>, ArenaAllocator<char> > s(15, 's');

4. std::basic_string<...> is marked as throw()/noexcept
so if allocator::deallocate calls inside throw-func you'll see compilation error
undefined reference to __cxa_call_unexpected

5. string constructors require memcpy and memset impl
6. string assignment requires std::__throw_logic_error and std::__throw_length_error impl



