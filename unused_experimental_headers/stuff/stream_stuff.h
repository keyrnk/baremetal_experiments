#ifndef __UART_OUPUT_H_
#define __UART_OUPUT_H_

#include <array>
#include <cstddef>
#include <ios>
#include <streambuf>
#include <ostream>

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
class UartStreamBufBase : public std::basic_streambuf<char, std::char_traits<char>>
{
public:
    explicit UartStreamBufBase() noexcept
    {
        setp(&m_buf.front(), &m_buf.front() + m_buf.max_size());
    }

//see arobenko explanation
    void operator delete(void*, unsigned long)
    {}

    virtual ~UartStreamBufBase()
    {
    }

    int_type overflow(int_type ch)
    {
        if (ch != traits_type::eof())
        {
            *pptr() = ch;
            pbump(1);
            do_flush();
        }

        return traits_type::eof();
    }

    void do_flush()
    {
        std::ptrdiff_t n = pptr() - pbase();
        PutInt(n);
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
        do_flush();
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

typedef UartStreamBufBase<char, 256> UartStreamBuf;
typedef std::basic_ostream<char, std::char_traits<char>> cout_type;

class uart_ostream : virtual public std::basic_ostream<char, std::char_traits<char>>
{
public:
    uart_ostream()
    {
    }

    virtual ~uart_ostream() {}
};


#endif
