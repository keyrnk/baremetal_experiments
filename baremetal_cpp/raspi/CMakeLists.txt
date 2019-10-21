cmake_minimum_required(VERSION 3.8)

set(TARGET_NAME kernel8.elf)
set(IMAGE_NAME kernel8.img)

enable_language(C ASM)

set(SOURCES 
	src/start.S
	src/main.cpp
	src/mini_uart.cpp)

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME} core)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
		COMMAND ${CMAKE_OBJCOPY} -O binary ${TARGET_NAME} ${IMAGE_NAME})

add_custom_target(run COMMAND qemu-system-aarch64 -M raspi3 -kernel ${IMAGE_NAME} -serial null -serial stdio)
