#ifndef __BIT_MAP_ARENA_H_
#define __BIT_MAP_ARENA_H_

#include <array>
#include <cstddef>
#include <cstdint>

#include "basic_stream.h"

extern std::uintptr_t heap_start;
extern std::uintptr_t heap_end;  

class BitMapArena
{
public:
	using pointer = void*;
	using size_type = std::size_t;

	static const size_type BlockSize = 64;
	static const size_type MaxHeapSize = 1024;
public:
	BitMapArena()
            : m_startAddress(&heap_start)
            , m_blocksNum((&heap_end - &heap_start) / BlockSize)
            , m_startSearchIndex(0)
        {
             cout <<  "bit map arena ctor\n";
             m_bitMap.fill(false);
        }

public:
	pointer allocate(size_type n)
	{
		cout <<  "allocate index " << (int)m_startSearchIndex << "\n" ;
		if (n > BlockSize)
			return nullptr;

		pointer address = (pointer)nullptr;
		for (size_t i = m_startSearchIndex; i < m_blocksNum; ++i)
                {
                    if(!m_bitMap[i])
                    {
                        address = (pointer)((std::uintptr_t)m_startAddress + i * BlockSize);
                        m_bitMap[i] = true;
                        m_startSearchIndex = ++i;
                        break;
                    }
                }
		return (pointer)address;
	}

	void deallocate(pointer p, size_type n)
	{
                cout <<  "deallocate \n";
		size_t index = ((std::uintptr_t)p - (std::uintptr_t)m_startAddress) / BlockSize;
                m_bitMap[index] = false;
                m_startSearchIndex = index;
	}

private:
	std::array<bool, MaxHeapSize / BlockSize> m_bitMap;
	pointer m_startAddress;
        size_type m_blocksNum;
	size_type m_startSearchIndex;
};

#endif

