cmake_minimum_required(VERSION 3.8)
project(baremetal_cpp)

include_directories(core)

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "ESP8266")
    set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/esp/load.ld")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")
    add_subdirectory(esp)
else()
    add_subdirectory(raspi)
endif()

add_subdirectory(core)
