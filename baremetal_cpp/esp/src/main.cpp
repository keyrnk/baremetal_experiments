#include "leds.h"
#include "uart.h"
#include <arena_allocator.h>
#include "main.h"
#include <basic_stream.h>
#include <static_objects.h>
#include <string>
#include <test_function.h>

extern "C"
void karina_main(void)
{
    mem_clr_bss();
    init_leds();
    StaticInitialize();

    using IOStream = BasicStream<char, std::char_traits<char>, Uart>;
    IOStream cout;
    cout << "\n[Karina C++ version 0.1]\n\n";
    
    TestFunction<IOStream>(cout);
    
    SET_LED_STATUS(GREEN_LED, false);
    SET_LED_STATUS(RED_LED, true);

    while(1)
    {
        SWITCH_LEDS
    }
}
