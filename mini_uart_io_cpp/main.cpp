#include <memory>
#include <string>
#include <vector>
#include "basic_stream.h"

extern char heap_start;
extern char heap_end;

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

	//static const pointer arena_start = &heap_start;
	//static const size_type arena_size = &heap_end - &heap_start;
	static const size_type block_size = 64;

	struct Block {
		Block(pointer newAddress, size_type newSize)
			: address(newAddress)
			, size(newSize)
			, next(nullptr)
		{}

		Block()
			: next(nullptr)
		{}

		Block* next;
		pointer address;
		size_type size;
	};
	
	struct Arena {
		Arena()
		{}

		Arena(size_type initSize, pointer startAddress)
			: size(initSize)
			, curAddress(startAddress)
			, index(0)
			, freeList(nullptr)
		{}

		std::array<Block, 1024 / block_size> blocks;
		
		size_type size;
		pointer curAddress;
		size_type index; 
		Block* freeList;
	};

	Arena arena;

	ArenaAllocator()
		: arena((&heap_end - &heap_start), &heap_start)
	{
	}

	void deallocate(pointer p, size_type n)
	{
		pointer startAddress = arena.blocks[0].address;
		size_type blockIndex = (p - startAddress) / block_size;
		if (arena.freeList == nullptr)
		{
			arena.freeList = &arena.blocks[blockIndex];
		}
		else
		{
			Block* oldFreeList = arena.freeList;
			arena.freeList = &arena.blocks[blockIndex];
			arena.freeList->next = oldFreeList;
		}

		arena.size += block_size;
	}

	pointer allocate(size_type n, ArenaAllocator<T>::const_pointer hint = 0)
	{
		
		if (n > arena.size)
			return nullptr;

		//the size of freelist block isnt the same as required
		//assume all are equal
		pointer address;
		if (arena.freeList != nullptr)
		{
			Block* newHead = arena.freeList;
			arena.freeList = arena.freeList->next;
			arena.size -= newHead->size;
			address = newHead->address;
		}
		else
		{
			arena.blocks[arena.index].address = arena.curAddress;
			address = arena.curAddress;
			arena.blocks[arena.index].size = block_size;
			++arena.index;
			arena.size -= block_size;
			arena.curAddress += block_size;
		}

		cout << "allocate\n";
		return address;
	}

};

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
