#include "leds.h"
#include "uart.h"
#include "karina_arena.h"
#include "karina_main.h"
#include <basic_stream.h>
#include <static_objects.h>
#include <string>

//void __cxa_guard_acquire()
//{
//}

using Stream = BasicStream<char, std::char_traits<char>, Uart>;
Stream cout;

class StaticExample
{
public:
    StaticExample()
    {
	cout << "static ctor\n";
    }
};

StaticExample ex;

void testAllocator(void)
{
    ArenaAllocator<char> charAllocator;

    {
        arena_string s(16, 's', charAllocator);
        arena_string t = std::move(s);
        t.append("ddd");
        cout << s.c_str() << '\n';
        cout << t.c_str() << '\n';
    }

    arena_string s(8, 'r', charAllocator);
    s.find('g');
    cout << s.c_str() << '\n';
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
