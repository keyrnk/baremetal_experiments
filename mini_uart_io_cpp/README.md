1. Clang is used for compiling and linking

2. --relocatable flag is needed for ld.lld otherwise the following error is possible:
ld.lld: error: start.o:(.text.boot+0x34): has non-ABS relocation R_AARCH64_CALL26 against symbol 'main'
because bl instruction needs relocation mode

