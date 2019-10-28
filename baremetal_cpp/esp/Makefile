ARDUINO_ESP8266_PATH = C:/Users/Dorozhkina/AppData/Local/Arduino15/packages/esp8266
TOOLCHAIN_PATH = $(ARDUINO_ESP8266_PATH)/tools/xtensa-lx106-elf-gcc/2.5.0-3-20ed2b9/bin
ESPTOOL = $(ARDUINO_ESP8266_PATH)/hardware/esp8266/2.5.2/tools/esptool/esptool.py

CC = $(TOOLCHAIN_PATH)/xtensa-lx106-elf-gcc
CXX = $(TOOLCHAIN_PATH)/xtensa-lx106-elf-g++
READELF = $(TOOLCHAIN_PATH)/xtensa-lx106-elf-readelf

INCLUDE_DIR = ../core
CXXFLAGS = -mlongcalls -fno-exceptions -fno-unwind-tables -fno-threadsafe-statics -fno-rtti -Wall -g3 -std=c++11 -I$(INCLUDE_DIR)
LDLIBS = -nostdlib
LDFLAGS = -T./load.ld $(CXXFLAGS)

ESP_FOLDER = src
CORE_FOLDER = ../core

ESP_SRC = $(wildcard $(ESP_FOLDER)/*.cpp)
CORE_SRC = $(wildcard $(CORE_FOLDER)/*.cpp)
	   
ODIR=build
ESP_OBJS_ = $(ESP_SRC:.cpp=.o)
CORE_OBJS_ = $(CORE_SRC:.cpp=.o)

ESP_OBJS= $(patsubst %,$(ODIR)/%,$(notdir $(ESP_OBJS_))) 
CORE_OBJS= $(patsubst %,$(ODIR)/%,$(notdir $(CORE_OBJS_))) 

.PHONY: clean term directories

all: directories main-0x00000.bin flash term

MKDIR_P = mkdir -p

directories: ${ODIR}

${ODIR}:
		${MKDIR_P} ${ODIR}
		
main-0x00000.bin: $(ODIR)/main
	$(READELF) -a $^ > $^.elf
	python $(ESPTOOL) elf2image $^

$(ODIR)/main: $(ESP_OBJS) $(CORE_OBJS)

$(ODIR)/%.o: $(ESP_FOLDER)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $(ODIR)/$(notdir $@)

$(ODIR)/%.o: $(CORE_FOLDER)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $(ODIR)/$(notdir $@)
	
flash: main-0x00000.bin
	python $(ESPTOOL) write_flash 0 $(ODIR)/main-0x00000.bin

clean:
	rm -r build/

term:
	python -m serial.tools.miniterm --dtr=0 --rts=1 COM20 74880
	python -m serial.tools.miniterm --dtr=0 --rts=0 COM20 74880
#	python -m serial.tools.miniterm --dtr=0 --rts=0 /dev/ttyUSB0 74880
