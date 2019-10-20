# The ARM toolchain prefix
#ARMGNU = /home/user/opt/gcc-arm-none-eabi-6-2017-q2-update/bin/arm-none-eabi
ARMGNU = /home/user/opt/cross-compiler-aarch64/bin/aarch64-elf


#COPS = -mthumb -Wall -O2 -nostdlib -nostartfiles -ffreestanding
COPS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles

# Directory to put the intermediate build files
BUILD = build/

# Directory where the source files are
SOURCE = src/

# Name of the target
TARGET_NAME = kernel

# Name of the file to output
TARGET = kernel8.img

# Name of the listing file to output
LIST = kernel.list

# Name of the linker script to use
LINK_SCRIPT = load.ld

# Rule to build everything (creates the target image and listing)
all: $(TARGET) $(LIST)

# Rule to create the image file
$(TARGET): $(BUILD)kernel.elf
	$(ARMGNU)-objcopy $(BUILD)kernel.elf -O binary $(BUILD)$(TARGET) 

# Rule to make the ELF file
$(BUILD)kernel.elf: $(BUILD)start.o $(BUILD)main.o $(LINK_SCRIPT)
	$(ARMGNU)-ld $(BUILD)start.o $(BUILD)main.o -o $(BUILD)kernel.elf -T $(LINK_SCRIPT)

# Rule to make the object files
$(BUILD)start.o: $(SOURCE)start.s $(BUILD)
	$(ARMGNU)-as $(SOURCE)start.s -o $@

$(BUILD)main.o: $(SOURCE)main.c $(BUILD)
	$(ARMGNU)-gcc $(COPS) -c $(SOURCE)main.c -o $@

# Rule to make the listing file.
$(LIST): $(BUILD)kernel.elf
	$(ARMGNU)-objdump -D $(BUILD)kernel.elf > $(LIST)

# Create the build directory
$(BUILD):
	mkdir $@

# Clean all the intermediate and output files
clean:
	rm -rf build/
	rm -f $(LIST)
	rm -f $(TARGET)
