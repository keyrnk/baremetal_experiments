#include <memory>
#include <string>
#include <vector>

#include "arena_allocator.h"
#include "basic_stream.h"

extern "C"
void* memcpy(void* dst, const void* src, std::size_t n)
{
	//PutStr("memcpy\n");
	char* dstC = static_cast<char*>(dst);
	const char* srcC = static_cast<const char*>(src);
	for (std::size_t i = 0; i < n; ++i, ++dstC, ++srcC)
	{
		*dstC = *srcC;
	}
	return dst;
}

extern "C"
void* memset(void* ptr, int value, std::size_t n)
{
	//PutStr("memset\n");
	char* dst = static_cast<char*>(ptr);
	for (std::size_t i = 0; i < n; ++i, ++dst)
	{
		*dst = static_cast<char>(value);
	}

	return ptr;
}

namespace std {
	void __throw_length_error(char const*)
	{
		while(true)
		{}
	}

	void __throw_logic_error(char const*)
	{
		while(true)
		{}
	}
}

typedef std::basic_string<char, std::char_traits<char>, ArenaAllocator<char> > arena_string;

int main()
{
	cout << "Hello fucking world!\n";
	{
		arena_string s(16, 's');
		arena_string t = std::move(s);
		t.append("ddd");
		cout << s.c_str() << '\n' << t.c_str() << '\n';
	}

	arena_string s(8, 'r');
	s.find('g');

	cout << s.c_str() << '\n' << 1023;

	return 0;
}
