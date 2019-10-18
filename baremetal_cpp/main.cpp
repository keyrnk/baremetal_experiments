#include <memory>
#include <string>
#include <vector>

#include <string_view>
#include "arena_allocator.h"
#include "basic_stream.h"
#include "mini_uart.h"

typedef BasicStream<char, std::char_traits<char>, MiniUartIO> IOStream;
IOStream cout;

using arena_string = std::basic_string<char, std::char_traits<char>, BaremetalAllocator<char> >;

using arena_vector = std::vector<arena_string, BaremetalAllocator<arena_string> >;

int main()
{
	arena_string greeting("Why should I stay");
	greeting.append(" here?");
        cout << greeting.c_str() << "\n";

        std::size_t pos = greeting.rfind("h");
        arena_string part(greeting.begin(), greeting.begin() + pos);
        cout << part.c_str() << "\n"; 

        arena_vector phrase {"I'd be crazy not to follow", "Follow where you lead"};  
        phrase.push_back("Your eyes");      
        for (const auto& word : phrase)
        {
           cout << word.c_str() << "\n";
        }
       
	return 0;
}
