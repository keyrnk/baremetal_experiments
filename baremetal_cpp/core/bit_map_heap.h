#ifndef __BIT_MAP_HEAP_H_
#define __BIT_MAP_HEAP_H_

#include <array>
#include <cstddef>
#include <cstdint>

#include "basic_stream.h"
#include "mock_exceptions.h"


extern std::uintptr_t heap_start;
extern std::uintptr_t heap_end;


class BitMapHeap
{
public:
    using pointer = void*;
    using size_type = std::size_t;

    static const size_type BlockSize = 256;
    static const size_type MaxHeapSize = 1024 * 1024;

    BitMapHeap()
        : m_startAddress(&heap_start)
        , m_blocksNum((&heap_end - &heap_start) / BlockSize)
        , m_startSearchIndex(0)
    {
        m_bitMap.fill(false);
    }

    pointer allocate(size_type n)
    {
        if (n > BlockSize)
            std::__throw_bad_alloc("bad_alloc");

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

#endif // __BIT_MAP_HEAP_H_
