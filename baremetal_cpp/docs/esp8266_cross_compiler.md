### GNU GCC build   

The easiest way is to download Arduino IDE and then instal esp8266 tools which include gcc 4.8.0 compiler and python tools for software flash. 
- [Install Arduino IDE](https://www.arduino.cc/en/Main/Software)
- Add references to ESP8266 SDK in Arduino IDE:  
File->Settings->Additional Boards Manager URLs  
Insert http://arduino.esp8266.com/stable/package_esp8266com_index.json
- Install ESP SDK:
Tools->Board->Board Manager  
Filter by esp8266, then install
- Choose esp8266 in Tools with following settings:  
Upload speed 460800  
CPU Frequency 80 MHz  
Crystal Frequency 26MHz  
Flash size 4M (no SPIFFS)  
Flash mode QIO(fast)
- ESP8266 cross compiler will bestored somewhere in /Users/karina/Library/Arduino15/packages/esp8266.  
So you can use it independently with Makefile or Cmake
