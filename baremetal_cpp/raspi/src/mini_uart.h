#ifndef __UART_OUPUT_H_
#define __UART_OUPUT_H_

#include <string>


bool __cxa_guard_acquire();
bool __cxa_guard_release();

class MiniUartIO
{
public:
    MiniUartIO()
    {
        InitMiniUart();
    }
public:
    char GetChar() ;
    void PutChar(const char ch) noexcept;
    void PutStr(const char* s) noexcept;
    void PutInt(const int i) noexcept;
private:
    static void InitMiniUart();
    static void SetUpGPIO(void);

    static void WriteToRegister(volatile unsigned int* reg, const unsigned int val);
    static void ReadFromRegister(volatile unsigned int* reg, unsigned int* val);
    static void WaitForRegisterReady() noexcept;

private:
    MiniUartIO(const MiniUartIO&) = delete;
    MiniUartIO& operator = (const MiniUartIO&) = delete;
};

#endif // __UART_OUPUT_H_
