#ifndef __BASIC_STREAM_H_
#define __BASIC_STREAM_H_

#include <string>
#include "mini_uart.h"

template <class CharT, class Traits>
class BasicStream
{
public:
	using stream_type = BasicStream<CharT, Traits>;

public:
	BasicStream() = default;

public:
	stream_type& operator << (const char ch) noexcept
	{
		MiniUartIO::GetInstance().PutChar(ch);
		return *this;
	}
	stream_type& operator << (const char* s) noexcept
	{
		MiniUartIO::GetInstance().PutStr(s);
		return *this;
	}
	stream_type& operator << (const int n) noexcept
	{	
		MiniUartIO::GetInstance().PutInt(n);
		return *this;
	}
}; 


typedef BasicStream<char, std::char_traits<char>> IOStream;
IOStream cout;

#endif
