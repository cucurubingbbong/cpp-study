#include <iostream>

int main()
{
    int hp;

    std::cout << "현재 HP 입력: ";
    std::cin >> hp;

    if (hp <= 0)
    {
        std::cout << "캐릭터가 사망했습니다.\n";
    }
    else if (hp <= 30)
    {
        std::cout << "위험합니다!\n";
    }
    else if (hp <= 70)
    {
        std::cout << "HP가 보통입니다.\n";
    }
    else
    {
        std::cout << "건강합니다.\n";
    }

    return 0;
}