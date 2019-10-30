#ifndef _ESP8266_UART_H_
#define _ESP8266_UART_H_

#define UART_TX_FIFO     (*((volatile unsigned char *)0x60000000))
#define UART_TXFIFO_LOAD (*((volatile unsigned char *)0x6000001E))

#define UART_RX_FIFO     (*((volatile unsigned char *)0x60000000))
#define UART_RXFIFO_LOAD (*((volatile unsigned char *)0x6000001C))

#define ENTER_KEYCODE 0x0d

class Uart
{
public:
    void PutChar(const unsigned char c) noexcept
    {
        while (UART_TXFIFO_LOAD > 125); // Wait, do nothing
        UART_TX_FIFO = c;
    }

    void PutStr(const char* s) noexcept
    {
        while(*s != '\0')
        {
            if (*s == '\n')
                PutChar('\r');

            PutChar(*s);
            s++;
        }
    }

    void PutInt(int i)
    {
    }

    int CharsAvailable()
    {
        return UART_RXFIFO_LOAD;
    }

    inline static char GetChar()
    {
        return UART_RX_FIFO;
    }
};

#endif // _ESP8266_UART_H_
