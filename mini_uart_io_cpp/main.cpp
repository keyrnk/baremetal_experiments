#include <memory>
#include <string>
#include <vector>


#include "arena_allocator.h"
#include "basic_stream.h"

extern "C"
void* memcpy(void* dst, const void* src, std::size_t n)
{
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

	void __throw_logic_error(char const* s)
	{
                //throw std::length_error(s);
		while(true)
		{}
	}

}
using arena_string = std::basic_string<char, std::char_traits<char>, BaremetalAllocator<char> >;

using arena_vector = std::vector<arena_string, BaremetalAllocator<arena_string> >;

int main()
{
        arena_vector v;
        v.push_back("hello");

        for (size_t i = 0; i < v.size(); ++i)
        {
           cout << v[i].c_str() << "\n";
        }
	arena_string h("hello this fucking worldsjdkkkkkkkkkkkkkk\n");
	cout << h.c_str();

	cout << "Hello fucking world!\n";
	{
		arena_string s(20, 's');
		arena_string t = std::move(s);
		t.append("ddd");
                cout << h.c_str();
		cout << s.c_str() << '\n' << t.c_str() << '\n';
	}

	arena_string s(8, 'r');
	s.find('g');

	cout << s.c_str() << '\n' << 1023 << "\n";
        cout << h.c_str();
	return 0;
}
