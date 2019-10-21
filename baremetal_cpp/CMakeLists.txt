cmake_minimum_required(VERSION 3.8)
project(kernel8.elf)

set(IMAGE_NAME kernel8.img)

enable_language(C ASM)

set(SOURCES 
	start.S
	main.cpp
	libc_functions.cpp
	mini_uart.cpp
	mock_exceptions.cpp
	static_objects.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME} ${IMAGE_NAME})

add_custom_target(run COMMAND qemu-system-aarch64 -M raspi3 -kernel ${IMAGE_NAME} -serial null -serial stdio)
