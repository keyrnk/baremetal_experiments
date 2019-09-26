#ifndef __BIT_MAP_ARENA_H_
#define __BIT_MAP_ARENA_H_

#include <array>
#include <cstddef>

#include "basic_stream.h"

extern char heap_start;
extern char heap_end;  

template <class T>
class BitMapArena
{
public:
	using value_type = T;
	using pointer = T*;
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
        }

public:
	pointer allocate(size_type n)
	{
		cout <<  "allocate index " << (int)m_startSearchIndex << "\n" ;
		if (n > BlockSize)
			return nullptr;

		pointer address = nullptr;
		for (size_t i = m_startSearchIndex; i < m_blocksNum; ++i)
                {
                    if(!m_bitMap[i])
                    {
                        address = m_startAddress + i * BlockSize;
                        m_bitMap[i] = true;
                        m_startSearchIndex = ++i;
                        break;
                    }
                }
		return address;
	}

	void deallocate(pointer p, size_type n)
	{
                cout <<  "deallocate \n";
		size_t index = (p - m_startAddress) / BlockSize;
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

