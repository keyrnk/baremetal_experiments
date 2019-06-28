#ifndef __UART_OUPUT_H_
#define __UART_OUPUT_H_

void InitMiniUart();
char GetChar() ;
void PutChar(const char ch);
void PutStr(const char* s);

#endif
