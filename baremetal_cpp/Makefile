INC_PATH = -I/Users/karina/Projects/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/aarch64-elf/include/c++/8.3.0 -I/Users/karina/Projects/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/aarch64-elf/include/c++/8.3.0/aarch64-elf -I/Users/karina/Projects/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/aarch64-elf/include -I/Users/karina/Projects/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/lib/gcc/aarch64-elf/8.3.0/include

PATH = /usr/local/Cellar/llvm/8.0.0_1/bin/
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nodefaultlibs -fno-cxx-exceptions $(INC_PATH)

all: clean kernel8.img

start.o: start.S
	$(PATH)clang++ --target=aarch64-elf $(CFLAGS) -c start.S -o start.o

%.o: %.cpp
	$(PATH)clang++ --target=aarch64-elf $(CFLAGS) -c $< -o $@

kernel8.img: start.o $(OBJS)
	$(PATH)ld.lld -m aarch64elf -nostdlib start.o $(OBJS) -T load.ld -o kernel8.elf
	$(PATH)llvm-objcopy -O binary kernel8.elf kernel8.img

clean:
	rm kernel8.elf *.o >/dev/null 2>/dev/null || true

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio