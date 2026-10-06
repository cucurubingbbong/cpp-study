#include <iostream>
#include <string>

int main()
{
    std::string text;

    std::cin >> text;

    int aCount = 0;

    for (char ch : text)
    {
        if (ch == 'a')
        {
            aCount++;
        }
    }

    std::cout << "길이: " << text.size() << '\n';
    std::cout << "a의 개수: " << aCount << '\n';
    std::cout << "첫 번째 문자: " << text[0] << '\n';
    std::cout << "마지막 문자: " << text[text.size() - 1] << '\n';

    return 0;
}