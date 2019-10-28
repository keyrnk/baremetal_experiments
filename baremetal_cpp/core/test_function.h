#ifndef __TEST_FUNCTION_H_
#define __TEST_FUNCTION_H_

#include <string>
#include <vector>
#include <arena_allocator.h>

using arena_string = std::basic_string<char, std::char_traits<char>, BaremetalAllocator<char> >;

using arena_vector = std::vector<arena_string, BaremetalAllocator<arena_string> >;

template <typename IOStream>
void TestFunction(IOStream& cout)
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
}

#endif

