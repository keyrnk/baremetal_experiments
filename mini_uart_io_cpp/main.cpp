#include <memory>
#include <string>
#include <vector>
#include "uart_output.h"

extern char heap_start;
extern char heap_end;

extern "C"
void* memcpy(void* dst, const void* src, std::size_t n)
{
	PutStr("memcpy\n");
	char* dstC = (char*)dst;
	const char* srcC = (const char*)src;

	for (std::size_t i = 0; i < n; ++i, ++dstC, ++srcC)
	{
		*dstC = *srcC;
	}
	return dst;
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
		: arena(1024, &heap_start)
	{
		PutStr("Allocator ctor\n");
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
			++ arena.index;
			arena.size -= block_size;
		}

		PutStr("allocate\n");
		return address;
	}
};



int main()
{
	InitMiniUart();
	PutStr("Hello fucking world!\n");

	std::basic_string<char, std::char_traits<char>, ArenaAllocator<char> > s(15, 's');

	PutStr(s.c_str());
	

	return 0;
}
