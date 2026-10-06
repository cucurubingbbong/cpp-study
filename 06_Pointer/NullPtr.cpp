#include <iostream>

int main()
{
    int* ptr = nullptr;

    if (ptr == nullptr)
    {
        std::cout << "현재 아무것도 가리키지 않습니다.\n";
    }

    int number = 10;

    ptr = &number;

    if (ptr != nullptr)
    {
        std::cout << *ptr << '\n';
    }

    return 0;
}