#ifndef __ARENA_H_
#define __ARENA_H_

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
	Arena()
        {
             cout <<  "arena ctor\n";
             size_t heapSize = &heap_end - &heap_start;
             char* startAddress = &heap_start;
	     blocksNum = heapSize / BlockSize;
	     startAddress = startAddress;
	     index = 0;
	     freeList = nullptr;
        }

public:
	pointer allocate(size_type n)
	{
		cout <<  "allocate index " << (int)index << "\n" ;
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
                        address = blocks[index].address;
			++index;
                        
		}

		return address;
	}

	void deallocate(pointer p, size_type n)
	{
                cout <<  "deallocate \n";
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
	std::array<Block, MaxHeapSize / BlockSize> blocks;
	size_type blocksNum;
	pointer startAddress;
	size_type index; 
	Block* freeList;
};

#endif

