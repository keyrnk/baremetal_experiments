#ifndef __UART_OUPUT_H_
#define __UART_OUPUT_H_

void InitMiniUart();
char GetChar() ;
void PutChar(const char ch) noexcept;
void PutStr(const char* s) noexcept;
void PutInt(const int i) noexcept;

#endif
