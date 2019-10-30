 ### Raspberry connection
Take compiled kernel8.img and boot files from boot_files/ and place all this bunch to SD card as is.
For UART connection I used USB 2 tty adapter. Pin scheme you can see at TODO. 
You will see appropriate COM port under /dev in Linux or MacOS and in device manager in Windows.
Use pyserial or putty under Windows to connect to uart.
Reset board and you'll see output. 