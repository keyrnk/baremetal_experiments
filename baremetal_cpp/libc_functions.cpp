#include <cstddef>
#include <cstdint>

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

