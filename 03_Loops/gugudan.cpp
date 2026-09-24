#include <iostream>

int main()
{
    int dan;

    std::cout << "단 입력: ";
    std::cin >> dan;

    for (int i = 1; i <= 9; i++)
    {
        std::cout
            << dan
            << " x "
            << i
            << " = "
            << dan * i
            << '\n';
    }

    return 0;
}