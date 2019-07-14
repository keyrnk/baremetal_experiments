#ifndef __UART_OUPUT_H_
#define __UART_OUPUT_H_

#include <string>

template <class CharT>
class MiniUartIO
{
public:
	MiniUartIO()
	{
		InitMiniUart();
	}
public:
	char GetChar() ;
	void PutChar(const CharT ch) noexcept;
	void PutStr(const CharT* s) noexcept;
	void PutInt(const int i) noexcept;
private:
	void InitMiniUart();
	void WriteToRegister(volatile unsigned int* reg, const unsigned int val);
	void ReadFromRegister(volatile unsigned int* reg, unsigned int* val);
	void SetUpGPIO(void);
	void WaitForRegisterReady() noexcept;
};

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
		m_uart.PutChar(ch);
		return *this;
	}
	stream_type& operator << (const char* s) noexcept
	{
		m_uart.PutStr(s);
		return *this;
	}
	stream_type& operator << (const int n) noexcept
	{	
		m_uart.PutInt(n);
		return *this;
	}

private:
	MiniUartIO<CharT> m_uart;
}; 


typedef BasicStream<char, std::char_traits<char>> IOStream;

#endif
