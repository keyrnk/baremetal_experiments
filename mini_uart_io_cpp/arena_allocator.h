#ifndef __ARENA_ALLOCATOR_H_
#define __ARENA_ALLOCATOR_H_

#include <cstddef>
#include "bit_map_arena.h"

template <class T, class AllocationStrategy >
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
		typedef ArenaAllocator<U, AllocationStrategy> other;	
	};

	static AllocationStrategy arena;

public:
	ArenaAllocator() noexcept = default;
	ArenaAllocator(const ArenaAllocator& other) noexcept = default;
	
	template<typename U>
	ArenaAllocator(const ArenaAllocator<U, AllocationStrategy>& other) noexcept {};	
	~ArenaAllocator() noexcept = default;

public:
	static pointer allocate(size_type n, ArenaAllocator<T, AllocationStrategy>::const_pointer hint = 0)
	{
		return arena.allocate(n);
	}

	static void deallocate(pointer p, size_type n)
	{
		arena.deallocate(p, n);
	}

};

template <class T, class AllocationStrategy>
AllocationStrategy ArenaAllocator<T, AllocationStrategy>::arena;

template <class T1, class T2, class AllocationStrategy>
bool operator == (const ArenaAllocator<T1, AllocationStrategy>& first, const ArenaAllocator<T2, AllocationStrategy>& second) noexcept
{
	return true;
}

template <class T1, class T2, class AllocationStrategy>
bool operator != (const ArenaAllocator<T1, AllocationStrategy>& first, const ArenaAllocator<T2, AllocationStrategy>& second) noexcept
{
	return false;
}

template <class T>
using BaremetalAllocator = ArenaAllocator<T, BitMapArena<T> >;
#endif
