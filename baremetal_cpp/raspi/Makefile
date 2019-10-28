#
# Copyright (C) 2018 bzt (bztsrc@github)
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use, copy,
# modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
#

COMPILER_PATH = /home/user/opt/gcc-arm-8.3-2019.03-x86_64-aarch64-elf/bin/

INCLUDE_DIR = ../core/
CFLAGS = -Wall -O2 -nostdlib -fno-exceptions -fno-rtti -fno-threadsafe-statics -fpermissive -I$(INCLUDE_DIR)

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
	$(COMPILER_PATH)aarch64-elf-g++ $(CFLAGS) -c src/start.S -o $(ODIR)/start.o

$(ODIR)/%.o: $(RASPI_FOLDER)/%.cpp
	$(COMPILER_PATH)aarch64-elf-g++ $(CFLAGS) -c $< -o $@

$(ODIR)/%.o: $(CORE_FOLDER)/%.cpp
	$(COMPILER_PATH)aarch64-elf-g++ $(CFLAGS) -c $< -o $@

$(ODIR)/kernel8.img: $(ODIR)/start.o $(RASPI_OBJS) $(CORE_OBJS)
	$(COMPILER_PATH)aarch64-elf-ld -nostdlib -nostartfiles $(ODIR)/start.o $(RASPI_OBJS) $(CORE_OBJS) -T load.ld -o $(ODIR)/kernel8.elf
	$(COMPILER_PATH)aarch64-elf-objcopy -O binary $(ODIR)/kernel8.elf $(ODIR)/kernel8.img

clean:
	rm -r ${ODIR}

run:
	qemu-system-aarch64 -M raspi3 -kernel $(ODIR)/kernel8.img -serial null -serial stdio
