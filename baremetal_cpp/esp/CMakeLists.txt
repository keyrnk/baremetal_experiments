set(TARGET_NAME esp)

add_executable(${TARGET_NAME}
               src/main.cpp)

target_link_libraries(${TARGET_NAME} core)

set_target_properties(${TARGET_NAME} PROPERTIES LINK_DEPENDS "${LINKER_SCRIPT}")

add_custom_target(${TARGET_NAME}-0x00000.bin
                  COMMAND python ${ESPTOOL} elf2image ${TARGET_NAME}
                  COMMAND ${READELF} -a ${TARGET_NAME} > ${TARGET_NAME}.elf
                  DEPENDS ${TARGET_NAME})

add_custom_target(flash
                  COMMAND python ${ESPTOOL} write_flash 0 ${TARGET_NAME}-0x00000.bin
                  DEPENDS ${TARGET_NAME}-0x00000.bin)

add_custom_target(term
                  COMMAND python -m serial.tools.miniterm --dtr=0 --rts=0 /dev/tty.usbserial-A50285BI 74880)

