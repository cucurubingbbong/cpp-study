#include <iostream>
#include <string>

// 값 전달
void PassByValue(int number)
{
    number = 100;

    std::cout << "[값 전달 함수 내부] number = "
              << number << '\n';
}

// 참조 전달
void PassByReference(int& number)
{
    number = 200;

    std::cout << "[참조 전달 함수 내부] number = " << number << '\n';
}

// const 참조 전달
void PassByConstReference(const int& number)
{
    std::cout << "[const 참조 함수 내부] number = "<< number << '\n';

    // number = 300;
    // 오류 발생
}

// string 같이 복사 비용이 있을 수 있는 데이터는
// 읽기만 할 경우 const 참조를 많이 사용함
void PrintName(const std::string& name)
{
    std::cout << "Name: " << name << '\n';

    // name = "Changed";
    // const이므로 수정 불가능
}

int main()
{
    int number = 10;

    std::cout << "===== 값 전달 =====\n";

    std::cout << "함수 호출 전: "
              << number << '\n';

    PassByValue(number);

    std::cout << "함수 호출 후: "
              << number << '\n';


    std::cout << "\n===== 참조 전달 =====\n";

    PassByReference(number);

    std::cout << "함수 호출 후: "
              << number << '\n';


    std::cout << "\n===== const 참조 =====\n";

    PassByConstReference(number);

    std::cout << "함수 호출 후: "
              << number << '\n';


    std::cout << "\n===== string const 참조 =====\n";

    std::string name = "Player";

    PrintName(name);


    return 0;
}