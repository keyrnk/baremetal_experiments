ARDUINO_ESP8266_PATH = C:/Users/Dorozhkina/AppData/Local/Arduino15/packages/esp8266
TOOLCHAIN_PATH = $(ARDUINO_ESP8266_PATH)/tools/xtensa-lx106-elf-gcc/2.5.0-3-20ed2b9/bin
ESPTOOL = $(ARDUINO_ESP8266_PATH)/hardware/esp8266/2.5.2/tools/esptool/esptool.py

CC = $(TOOLCHAIN_PATH)/xtensa-lx106-elf-gcc
CXX = $(TOOLCHAIN_PATH)/xtensa-lx106-elf-g++
READELF = $(TOOLCHAIN_PATH)/xtensa-lx106-elf-readelf

INCLUDE_DIR = ../core
CXXFLAGS = -mlongcalls -fno-exceptions -fno-unwind-tables -fno-threadsafe-statics -fno-rtti -Wall -g3 -std=c++11 -I$(INCLUDE_DIR)
LDLIBS = -nostdlib
LDFLAGS = -T./karina_main.ld $(CXXFLAGS)

SRCS = $(wildcard *.cpp) \
       $(wildcard ../core/*.cpp)
OBJS = $(SRCS:.cpp=.o)
	   
.PHONY: clean term

all: karina_main-0x00000.bin flash term

karina_main-0x00000.bin: karina_main
	$(READELF) -a $^ > $^.elf
	python $(ESPTOOL) elf2image $^

karina_main: $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o ./$@


flash: karina_main-0x00000.bin
	python $(ESPTOOL) write_flash 0 karina_main-0x00000.bin

clean:
	rm -f karina_main *.o *.bin *.elf ../core/*.o

term:
	python -m serial.tools.miniterm --dtr=0 --rts=1 COM20 74880
	python -m serial.tools.miniterm --dtr=0 --rts=0 COM20 74880
#	python -m serial.tools.miniterm --dtr=0 --rts=0 /dev/ttyUSB0 74880
