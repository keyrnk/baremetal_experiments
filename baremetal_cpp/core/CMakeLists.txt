set(SOURCES 
	libc_functions.cpp
	mock_exceptions.cpp
	global_objects.cpp)

add_library(core STATIC ${SOURCES})
