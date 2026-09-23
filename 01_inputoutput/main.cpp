// c++ 프로그래밍에서 입출력을 쓰기 위해 사용되는 표준 헤더 파일
#include <iostream>

int main()
{
    int num_a = 0;

    int num_b = 0;

    int result = 0;

    char sign;

    bool isSign = true;

    std::cout << "첫번째 숫자를 입력해주세요 :";
    std::cin >> num_a;
    std::cout << "두번째 숫자를 입력해주세요 :";
    std::cin >> num_b;

    std::cout << "기호를 입력해주세요 :";

    std::cin >> sign;

    switch (sign)
    {
    case '+':
        result = num_a + num_b;
        break;
    case '-':
        result = num_a - num_b;
        break;
    case '*':
        result = num_a * num_b;
        break;
    case '/':
        result = num_a / num_b;
        break;

    default:
        isSign = false;
        break;
    }

    if(!isSign) {std::cout << "유효한 기호가 아닙니다"; return 0;}

    std::cout << result;
    return 0;
}