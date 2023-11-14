#include <iostream>

#include "q.h"

int main()
{
	MyStruct* a = CreateMyStruct(1);
    std::cout << GetMyStruct(a);
}
