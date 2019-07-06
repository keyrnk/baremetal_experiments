#ifndef __UART_OUPUT_H_
#define __UART_OUPUT_H_

#include <array>
#include <cstddef>
#include <ios>
#include <streambuf>

void InitMiniUart();
char GetChar() ;
void PutChar(const char ch) noexcept;
void PutStr(const char* s) noexcept;
void PutInt(const int i) noexcept;

namespace std
{

locale::locale()
{
}

locale::~locale()
{
}

}

template <class T, std::size_t N>
class UartStreamBufBase : public std::streambuf
{
public:
	UartStreamBufBase()
	{
	}

	~UartStreamBufBase()
	{
	}

	int_type overflow(int_type)
	{
		return -1;
	}

	std::streamsize xsputn(const char_type* s, std::streamsize n)
	{
		return -1;
	}

	int_type pbackfail(int_type)
	{
		return -1;
	}

	int_type uflow()
	{
		return -1;
	}

	int_type underflow()
	{
		return -1;
	}

	std::streamsize xsgetn(char_type* s, std::streamsize n)
	{
		return -1;
	}

	std::streamsize showmanyc()
	{
		return 0;
	}

	int sync()
	{
		return 0;
	}

	pos_type seekpos(std::fpos<_mbstate_t>, std::_Ios_Openmode)
	{		
		return pos_type(off_type(-1));
	}

	pos_type seekoff(off_type, std::_Ios_Seekdir, std::_Ios_Openmode)
	{
		return pos_type(off_type(-1));
	}

	basic_streambuf<char_type>* setbuf(char_type* s, std::streamsize n)
	{
		return this;
	} 

	void imbue(std::locale const&)
	{
	}
public:
	UartStreamBufBase(const UartStreamBufBase&) = delete;
	UartStreamBufBase& operator =(const UartStreamBufBase&) = delete;

private:
	std::array<T, N> m_buf;
};

typedef UartStreamBufBase UartStreamBuf;

#endif
