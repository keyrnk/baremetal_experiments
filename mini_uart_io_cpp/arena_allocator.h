#ifndef __ARENA_ALLOCATOR_H_
#define __ARENA_ALLOCATOR_H_

#include <array>
#include <cstddef>

#include "basic_stream.h"

extern char heap_start;
extern char heap_end;

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

	static const size_type BlockSize = 64;
	static const size_type MaxHeapSize = 1024;

	struct Block 
	{
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

		Arena(size_type heapSize, pointer startAddress)
			: blocksNum(heapSize / BlockSize)
			, startAddress(startAddress)
			, index(0)
			, freeList(nullptr)
		{}

		std::array<Block, MaxHeapSize / BlockSize> blocks;
	
		size_type blocksNum;
		pointer startAddress;
		size_type index; 
		Block* freeList;
	};

	static Arena arena;

	ArenaAllocator() = default;

	pointer allocate(size_type n, ArenaAllocator<T>::const_pointer hint = 0)
	{
		cout << "allocate\n";
		if (n > BlockSize)
			return nullptr;

		pointer address;
		if (arena.freeList != nullptr)
		{
			Block* oldHead = arena.freeList;
			oldHead->next = nullptr;
			address = oldHead->address;
			arena.freeList = arena.freeList->next;
		}
		else
		{
			if (arena.index >= arena.blocksNum)
			{
				return nullptr;
			}
			arena.blocks[arena.index].address = arena.startAddress + arena.index * BlockSize;
			arena.blocks[arena.index].size = BlockSize;
			++arena.index;
		}

		return address;
	}

	void deallocate(pointer p, size_type n)
	{
		cout << "deallocate\n";
		size_type blockIndex = (p - arena.startAddress) / BlockSize;
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
	}

};

template <class T>
typename ArenaAllocator<T>::Arena ArenaAllocator<T>::arena((&heap_end - &heap_start), &heap_start);

#endif
