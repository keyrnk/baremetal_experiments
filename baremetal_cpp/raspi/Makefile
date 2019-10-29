INC_ROOT = /Users/karina/Projects/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/

STL_INC_PATH = -I$(INC_ROOT)aarch64-elf/include/c++/8.3.0 -I$(INC_ROOT)aarch64-elf/include/c++/8.3.0/aarch64-elf -I$(INC_ROOT)aarch64-elf/include -I$(INC_ROOT)lib/gcc/aarch64-elf/8.3.0/include

PROJECT_INC_PATH = -I../core

PATH = /usr/local/Cellar/llvm/8.0.0_1/bin/

CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nodefaultlibs -fno-cxx-exceptions -fno-threadsafe-statics $(STL_INC_PATH) $(PROJECT_INC_PATH)

RASPI_FOLDER = src
CORE_FOLDER = ../core

RASPI_SRC = $(wildcard $(RASPI_FOLDER)/*.cpp)
CORE_SRC = $(wildcard $(CORE_FOLDER)/*.cpp)
	   
ODIR=build
RASPI_OBJS_ = $(RASPI_SRC:.cpp=.o)
CORE_OBJS_ = $(CORE_SRC:.cpp=.o)

RASPI_OBJS= $(patsubst %,$(ODIR)/%,$(notdir $(RASPI_OBJS_))) 
CORE_OBJS= $(patsubst %,$(ODIR)/%,$(notdir $(CORE_OBJS_)))

all: directories $(ODIR)/kernel8.img

MKDIR_P = mkdir -p

directories: ${ODIR}
${ODIR}: 
	${MKDIR_P} ${ODIR}

$(ODIR)/start.o: src/start.S
	$(PATH)clang++ --target=aarch64-elf $(CFLAGS) -c $(RASPI_FOLDER)/start.S -o $(ODIR)/start.o

$(ODIR)/%.o: $(RASPI_FOLDER)/%.cpp
	$(PATH)clang++ --target=aarch64-elf $(CFLAGS) -c $< -o $@

$(ODIR)/%.o: $(CORE_FOLDER)/%.cpp
	$(PATH)clang++ --target=aarch64-elf $(CFLAGS) -c $< -o $@

$(ODIR)/kernel8.img: $(ODIR)/start.o $(RASPI_OBJS) $(CORE_OBJS)
	$(PATH)ld.lld -m aarch64elf -nostdlib $(ODIR)/start.o $(RASPI_OBJS) $(CORE_OBJS) -T load.ld -o $(ODIR)/kernel8.elf
	$(PATH)llvm-objcopy -O binary $(ODIR)/kernel8.elf $(ODIR)/kernel8.img

clean: 
	rm -r ${ODIR}

run:
	qemu-system-aarch64 -M raspi3 -kernel $(ODIR)/kernel8.img -serial null -serial stdio