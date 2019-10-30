//#include <memory>
#include <string>
#include <vector>

#include <string_view>
#include <test_function.h>
#include "mini_uart.h"

typedef BasicStream<char, std::char_traits<char>, MiniUartIO> IOStream;

extern "C"
int main()
{
    IOStream cout;
    TestFunction(cout);

    return 0;
}
