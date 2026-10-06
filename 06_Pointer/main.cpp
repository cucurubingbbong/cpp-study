#include <iostream>

int main()
{
    int number = 10;
    int* ptr = nullptr;

    std::cout << "number 값 : " << number << "\n";
    std::cout << "number 주소 : " << &number << "\n";

    if (ptr == nullptr)
    {
        std::cout << "현재 가리키고 있는 주소가 없습니다.\n";
    }

    ptr = &number;

    std::cout << "\n===== 포인터 연결 후 =====\n";

    std::cout << "ptr에 저장된 주소 : " << ptr << "\n";
    std::cout << "ptr이 가리키는 값 : " << *ptr << "\n";

    *ptr = 50;

    std::cout << "\n===== 포인터로 값 변경 후 =====\n";

    std::cout << "number 값 : " << number << "\n";
    std::cout << "ptr이 가리키는 값 : " << *ptr << "\n";

    std::cout << "\n===== 주소 확인 =====\n";

    std::cout << "number 주소 : " << &number << "\n";
    std::cout << "ptr에 저장된 주소 : " << ptr << "\n";
    std::cout << "ptr 자신의 주소 : " << &ptr << "\n";

    ptr = nullptr;

    if (ptr == nullptr)
    {
        std::cout << "\nptr 연결 해제\n";
    }

    return 0;
}