#include "leds.h"
#include "uart.h"
#include <arena_allocator.h>
#include "main.h"
#include <basic_stream.h>
#include <static_objects.h>
#include <string>

using Stream = BasicStream<char, std::char_traits<char>, Uart>;
Stream cout;

using arena_string = std::basic_string<char, std::char_traits<char>, BaremetalAllocator<char> >;

void testAllocator(void)
{
    BaremetalAllocator<char> charAllocator;

    {
        arena_string s(16, 's', charAllocator);
        //arena_string t = std::move(s);
        //t.append("ddd");
        cout << s.c_str() << '\n';
        //cout << t.c_str() << '\n';
    }

   // arena_string s(8, 'r', charAllocator);
   // s.find('g');
   // cout << s.c_str() << '\n';
}

extern "C"
void karina_main(void)
{
    mem_clr_bss();
    init_leds();
    StaticInitialize();

    cout << "\n[Karina C++ version 0.1]\n\n";
    testAllocator();

    // Задаем начальные значения светодиодов
    SET_LED_STATUS(GREEN_LED, false);
    SET_LED_STATUS(RED_LED, true);

    while(1)
    {
        SWITCH_LEDS
    }
}
