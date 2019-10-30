#ifndef __BAREMETAL_ALLOCATOR_H_
#define __BAREMETAL_ALLOCATOR_H_

#include <cstddef>
#include "bit_map_heap.h"


class Base
{
protected:
    static BitMapHeap m_heap;
};


BitMapHeap Base::m_heap;


template <class T>
class BaremetalAllocator : public Base
{
public:
    using value_type = T;

//gcc 4.8 for esp8266 doesn't have full support for C++11 allocator
//and requires all using below and rebind
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using difference_type = std::ptrdiff_t;

    template <typename U>
    struct rebind
    {
        typedef BaremetalAllocator<U> other;
    };

public:
    BaremetalAllocator() noexcept = default;

    template<typename U>
    BaremetalAllocator(const BaremetalAllocator<U>& other) noexcept {};

public:
    static pointer allocate(size_type n, const_pointer hint = 0)
    {
        return static_cast<pointer>(m_heap.allocate(n * sizeof(T)));
    }

    static void deallocate(pointer p, size_type n)
    {
        m_heap.deallocate(p, n * sizeof(T));
    }
};

template <class T1, class T2>
bool operator == (const BaremetalAllocator<T1>& first, const BaremetalAllocator<T2>& second) noexcept
{
    return true;
}

template <class T1, class T2>
bool operator != (const BaremetalAllocator<T1>& first, const BaremetalAllocator<T2>& second) noexcept
{
    return false;
}

#endif // __BAREMETAL_ALLOCATOR_H_
