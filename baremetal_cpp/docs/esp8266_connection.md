### ESP connection
For ESP connection I use TODO: com port model
Note that for MacOS and Windows you need to download and install additionally driver for your virtual COM port    
For Linux this driver is already included to distributive.
After ESP connection you'll see the proper serial port name in /dev directory or in device manager for Windows. 
In esp/Makefile, term target, change COM port name to COM port assigned to device in your system

In my systems:
- Linux /dev/ttyUSB0  
- MacOs  
- Windows COM20 