#include <iostream>

int main()
{
    int score;

    std::cout << "점수를 입력하세요: ";
    std::cin >> score;

    if (score < 0 || score > 100)
    {
        std::cout << "잘못된 점수입니다.\n";
    }
    else if (score >= 90)
    {
        std::cout << "A\n";
    }
    else if (score >= 80)
    {
        std::cout << "B\n";
    }
    else if (score >= 70)
    {
        std::cout << "C\n";
    }
    else if (score >= 60)
    {
        std::cout << "D\n";
    }
    else
    {
        std::cout << "F\n";
    }

    return 0;
}