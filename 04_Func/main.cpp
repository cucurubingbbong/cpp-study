#include <iostream>

void PrintMenu()
{
    std::cout << "===== 메뉴 =====\n";
    std::cout << "1. 공격\n";
    std::cout << "2. 회복\n";
    std::cout << "0. 종료\n";
}

void Attack()
{
    std::cout << "공격했습니다!\n";
}

void Heal(int& hp)
{
    hp += 10;

    std::cout << "회복했습니다.\n";
    std::cout << "현재 HP: " << hp << '\n';
}

int main()
{
    int hp = 100;

    while (true)
    {
        PrintMenu();

        int input;
        std::cin >> input;

        if (input == 1)
        {
            Attack();
        }
        else if (input == 2)
        {
            Heal(hp);
        }
        else if (input == 0)
        {
            break;
        }
        else
        {
            std::cout << "잘못된 입력입니다.\n";
        }
    }

    return 0;
}