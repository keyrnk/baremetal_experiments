#ifndef __ARENA_ALLOCATOR_H_
#define __ARENA_ALLOCATOR_H_

#include <array>
#include <cstddef>

#include "basic_stream.h"

extern char heap_start;
extern char heap_end;

template <class T>
class Arena
{
public:
	using value_type = T;
	using pointer = T*;
	using size_type = std::size_t;

	static const size_type BlockSize = 64;
	static const size_type MaxHeapSize = 1024;
public:
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

public:
	Arena() = default;

	void Init(size_type heapSize, pointer startAddress)
	{
		if (!isInited)
		{
			blocksNum = heapSize / BlockSize;
			startAddress = startAddress;
			index = 0;
			freeList = nullptr;
		}
	}

public:
	pointer allocate(size_type n)
	{
		cout << "allocate\n";
		if (n > BlockSize)
			return nullptr;

		pointer address;
		if (freeList != nullptr)
		{
			Block* oldHead = freeList;
			oldHead->next = nullptr;
			address = oldHead->address;
			freeList = freeList->next;
		}
		else
		{
			if (index >= blocksNum)
			{
				return nullptr;
			}
			blocks[index].address = startAddress + index * BlockSize;
			blocks[index].size = BlockSize;
			++index;
		}

		return address;
	}

	void deallocate(pointer p, size_type n)
	{
		size_type blockIndex = (p - startAddress) / BlockSize;
		if (freeList == nullptr)
		{
			freeList = &blocks[blockIndex];
		}
		else
		{
			Block* oldFreeList = freeList;
			freeList = &blocks[blockIndex];
			freeList->next = oldFreeList;
		}
	}

private:
	bool isInited = false;
	std::array<Block, MaxHeapSize / BlockSize> blocks;
	size_type blocksNum;
	pointer startAddress;
	size_type index; 
	Block* freeList;
};

template <class T>
class ArenaAllocator
{
public:
	using value_type = T;	
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

	using propagate_on_container_copy_assignment = std::true_type;
	using propagate_on_container_move_assignment = std::true_type;
	using propagate_on_container_swap = std::true_type;

	template <class U>
	struct rebind {
		typedef ArenaAllocator<U> other;	
	};

	static Arena<T> arena;

	ArenaAllocator()
	{
		arena.Init((&heap_end - &heap_start), &heap_start);
	}

	pointer allocate(size_type n, ArenaAllocator<T>::const_pointer hint = 0)
	{
		return arena.allocate(n);
	}

	void deallocate(pointer p, size_type n)
	{
		arena.deallocate(p, n);
	}

};

template <class T>
Arena<T> ArenaAllocator<T>::arena;

template <class T1, class T2>
bool operator == (const ArenaAllocator<T1>& first, const ArenaAllocator<T2>& second) noexcept
{
	return true;
}

template <class T1, class T2>
bool operator != (const ArenaAllocator<T1>& first, const ArenaAllocator<T2>& second) noexcept
{
	return false;
}

#endif
