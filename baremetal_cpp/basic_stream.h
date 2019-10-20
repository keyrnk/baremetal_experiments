#ifndef __BASIC_STREAM_H_
#define __BASIC_STREAM_H_

#include <string>
#include "mini_uart.h"

template <class UartImpl>
UartImpl& GetInstance()
{
	static UartImpl uart;
	return uart;
}

template <class CharT, class Traits, class UartImpl>
class BasicStream
{
public:
	using stream_type = BasicStream<CharT, Traits, UartImpl>;

public:
	BasicStream() = default;

public:
	stream_type& operator << (const char ch) noexcept
	{
		GetInstance<UartImpl>().PutChar(ch);
		return *this;
	}
	stream_type& operator << (const char* s) noexcept
	{
		GetInstance<UartImpl>().PutStr(s);
		return *this;
	}
	stream_type& operator << (const int n) noexcept
	{	
		GetInstance<UartImpl>().PutInt(n);
		return *this;
	}
}; 


typedef BasicStream<char, std::char_traits<char>, MiniUartIO> IOStream;
IOStream cout;

#endif
