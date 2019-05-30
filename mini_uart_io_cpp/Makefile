SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib

all: clean kernel8.img

start.o: start.S
	clang --target=aarch64-elf $(CFLAGS) -c start.S -o start.o

%.o: %.cpp
	clang --target=aarch64-elf $(CFLAGS) -c $< -o $@

kernel8.img: start.o $(OBJS)
	ld.lld -m aarch64elf -nostdlib --relocatable start.o $(OBJS) -T load.ld -o kernel8.elf
	llvm-objcopy -O binary kernel8.elf kernel8.img

clean:
	rm kernel8.img kernel8.elf *.o >/dev/null 2>/dev/null || true
