#include <memory>
#include <string>
#include <vector>
#include "uart_output.h"

extern unsigned char heap_start;
extern unsigned char heap_end;

template <class T>
struct ArenaAllocator
{
	using value_type = T;	
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	
	void deallocate(pointer p, size_type n)
	{
	}

	pointer allocate(size_type n, ArenaAllocator<T>::const_pointer hint = 0)
	{
	}
};

void memcpy(unsigned char* dest, const unsigned char* src, std::size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		*dest = *src;
		++dest;
		++src;
	}
}

int main()
{
	InitMiniUart();
	PutStr("Hello fucking world!\n");

	std::basic_string<char, std::char_traits<char>, ArenaAllocator<char> > s = "s";

	

	return 0;
}
