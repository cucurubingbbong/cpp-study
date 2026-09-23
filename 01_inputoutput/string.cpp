#include <iostream>
#include <string>

int main()
{
    std::string name;

    std::cout << "이름 입력";

    std::getline(std::cin , name);

    std::cout << "안녕하세요" << name << " 님";

    return 0;
}