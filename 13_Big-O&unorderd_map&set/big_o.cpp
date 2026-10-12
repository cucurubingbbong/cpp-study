#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numbers = {9, 3, 7, 1, 5};

    // O(1): 인덱스로 접근
    std::cout << "O(1): " << numbers[2] << '\n';

    // O(n): 순차 검색
    bool found = false;

    for (int number : numbers)
    {
        if (number == 5)
        {
            found = true;
            break;
        }
    }

    std::cout << "O(n): " << found << '\n';

    // O(n log n): 정렬
    std::sort(numbers.begin(), numbers.end());

    for (int number : numbers)
    {
        std::cout << number << ' ';
    }
    std::cout << '\n';

    // O(log n): 정렬된 vector에서 이진 탐색
    auto it = std::lower_bound(
        numbers.begin(),
        numbers.end(),
        7
    );

    if (it != numbers.end() && *it == 7)
    {
        std::cout << "7 found\n";
    }

    // O(n^2): 중첩 반복문
    std::size_t count = 0;

    for (std::size_t i = 0; i < numbers.size(); ++i)
    {
        for (std::size_t j = 0; j < numbers.size(); ++j)
        {
            ++count;
        }
    }

    std::cout << "O(n^2): " << count << '\n';

    return 0;
}