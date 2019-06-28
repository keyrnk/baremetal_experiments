#include <memory>
#include <string>
#include <vector>
#include "uart_output.h"

struct custom_delete
{
constexpr custom_delete() noexcept = default;
void
operator()(int* __ptr) const
{
	return;
}
};

class MyObject
{
public:
	void operator delete(void* ptr) noexcept
	{
		//PutStr("Delete my obj\n");
		return;
	}
};


int main()
{
	std::array<char, 5> arr;
	arr[0] = 'a';

	int s = 3;

	std::char_traits<char> traits;
	std::unique_ptr<int, custom_delete> v(&s);
	
	MyObject obj;
	std::unique_ptr<MyObject> ptr(&obj);

	InitMiniUart();

	PutStr("Hello fucking world!\n");
	PutChar(arr[0]);
	//std::cout << "Hello\n";
	//while(1)
	//{
	//	PutChar(GetChar());
	//}

	return 0;
}
