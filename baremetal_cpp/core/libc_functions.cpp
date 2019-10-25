#include <cstddef>
#include <cstdint>

extern "C"
int memcmp( const void* lhs, const void* rhs, std::size_t n )
{
    const unsigned char* lhsC = static_cast<const unsigned char*>(lhs);
    const unsigned char* rhsC = static_cast<const unsigned char*>(rhs);

    for ( ; n--; lhsC++, rhsC++) {
	if ( *lhsC != *rhsC) {
	    return (*lhsC-*rhsC);
	}
    }
    return 0;
}

extern "C"
void* memcpy(void* dst, const void* src, std::size_t n)
{
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
	char* dst = static_cast<char*>(ptr);
	for (std::size_t i = 0; i < n; ++i, ++dst)
	{
		*dst = static_cast<char>(value);
	}

	return ptr;
}

extern "C"
std::size_t strlen(const char* str)
{
        int len = 0;
        for (; *str != '\0'; ++str, ++len) {}
        return len;
}

extern "C"
void *memchr (const void *arr, int c, size_t n)
{
        unsigned char *p = (unsigned char*)arr;
        while( n-- )
        {
            if( *p != (unsigned char)c )
                p++;
            else
                return p;
         }
         return 0;
}

extern "C"
void* memmove (void* dest, const void* src, unsigned int len)
{
    char *d = (char*)dest;
    const char *s = (const char*)src;
    if (d < s)
        while (len--)
            *d++ = *s++;
    else
    {
        const char *lasts = s + (len-1);
        char *lastd = d + (len-1);
        while (len--)
            *lastd-- = *lasts--;
    }
    return dest;
}



