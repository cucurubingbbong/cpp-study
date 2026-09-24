#include <iostream>

int main()
{
    for (int i = 1; i <= 20; i++)
    {
        if (i % 2 == 0)
        {
            std::cout << i << " : 짝수\n";
        }
        else
        {
            std::cout << i << " : 홀수\n";
        }
    }

    return 0;
}