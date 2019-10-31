### ESP connection
For ESP connection I use virtual com port from [ftdi](https://www.ftdichip.com)  
Note that for MacOS and Windows you need to download and install appropriate driver from here https://www.ftdichip.com/Drivers/VCP.htm.    
For Linux this driver is already included to distributive.  


After ESP connection you'll see the proper serial port name in /dev directory or in device manager in Windows. 
In esp/Makefile, term target, change COM port name to COM port assigned to device in your system

In my systems:
- Linux /dev/ttyUSB0  
- MacOs /dev/tty.usbserial-A50285BI 
- Windows COM20 

For binary image upload use ESP tool from downloaded package:  
```
python $(ARDUINO_ESP8266_PATH)/hardware/esp8266/2.5.2/tools/esptool/esptool.py write_flash 0 main-0x00000.bin. 
```

You can connect to serial port directly either from Arduino IDE or via python serial
```
python -m serial.tools.miniterm --dtr=0 --rts=0 /dev/ttyUSB0 74880  
```
For RESET and PROG signal handling serial port terminal lines RTS and DTR are used. 
