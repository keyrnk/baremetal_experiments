cmake_minimum_required(VERSION 3.8)

set(SOURCES 
	main.cpp
	libc_functions.cpp
	mini_uart.cpp
	mock_exceptions.cpp
	static_objects.cpp
	start.S)

add_executable(kernel8.elf ${SOURCES})