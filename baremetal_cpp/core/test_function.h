#ifndef __TEST_FUNCTION_H_
#define __TEST_FUNCTION_H_

#include <string>
#include <vector>
#include <baremetal_allocator.h>

using baremetal_string = std::basic_string<char, std::char_traits<char>, BaremetalAllocator<char> >;

using baremetal_vector = std::vector<baremetal_string, BaremetalAllocator<baremetal_string> >;

template <typename IOStream>
void TestFunction(IOStream& cout)
{
    baremetal_string greeting("Why should I stay");
    greeting.append(" here?");
    cout << greeting.c_str() << "\n";

    std::size_t pos = greeting.rfind("h");
    baremetal_string part(greeting.begin(), greeting.begin() + pos);
    cout << part.c_str() << "\n";

    baremetal_vector phrase {"I'd be crazy not to follow", "Follow where you lead"};
    phrase.push_back("Your eyes");
    for (const auto& word : phrase)
    {
        cout << word.c_str() << "\n";
    }
}

#endif // __TEST_FUNCTION_H_
