#include <iostream>

int main()
{
    int number = 10;

    int* ptr = &number;

    std::cout << "number 값: " << number << '\n';
    std::cout << "number 주소: " << &number << '\n';

    std::cout << "ptr 값: " << ptr << '\n';
    std::cout << "ptr이 가리키는 값: " << *ptr << '\n';
    std::cout << "ptr 자신의 주소: " << &ptr << '\n';

    *ptr = 50;

    std::cout << "변경 후 number: " << number << '\n';

    return 0;
}