set(TARGET_NAME esp)

set(SOURCES 
	karina_main.cpp)

add_executable(${TARGET_NAME} ${SOURCES})

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
		COMMAND ${CMAKE_READELF} -a ${TARGET_NAME} > ${TARGET_NAME}.elf
		COMMAND python ${ESPTOOL} elf2image ${TARGET_NAME}.elf)

#add_custom_target(run COMMAND qemu-system-aarch64 -M raspi3 -kernel ${IMAGE_NAME} -serial null -serial stdio)
