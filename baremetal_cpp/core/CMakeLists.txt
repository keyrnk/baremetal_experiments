set(SOURCES 
	libc_functions.cpp
	mock_exceptions.cpp
	static_objects.cpp)

add_library(core STATIC ${SOURCES})
