#include "leds.h"
#include "uart.h"
#include "main.h"
#include <basic_stream.h>
#include <global_objects.h>
#include <string>
#include <test_function.h>

extern "C"
void my_main(void)
{
    mem_clr_bss();
    init_leds();
    GlobalInitialize();

    using IOStream = BasicStream<char, std::char_traits<char>, Uart>;
    IOStream cout;
    cout << "\n[ESP8266 C++ version 0.1]\n\n";

    TestFunction<IOStream>(cout);

    SET_LED_STATUS(GREEN_LED, false);
    SET_LED_STATUS(RED_LED, true);

    while(1)
    {
        SWITCH_LEDS
    }
}
