#include <functional>
#include <iostream>
#include <set>

int main()
{
    std::set<int> numbers = {30, 10, 20, 10};

    // insert
    auto inserted = numbers.insert(15);

    std::cout << std::boolalpha;
    std::cout << inserted.second << '\n'; // true

    // 중복 삽입
    auto duplicate = numbers.insert(20);

    std::cout << duplicate.second << '\n'; // false

    // find
    auto it = numbers.find(20);

    if (it != numbers.end())
    {
        std::cout << *it << '\n';
    }

    // count
    std::cout << numbers.count(10) << '\n';

    // lower_bound: 18 이상인 첫 번째 요소
    auto lower = numbers.lower_bound(18);

    if (lower != numbers.end())
    {
        std::cout << *lower << '\n';
    }

    // erase
    numbers.erase(10);

    // 기본 오름차순
    for (int number : numbers)
    {
        std::cout << number << ' ';
    }
    std::cout << '\n';

    // 내림차순
    std::set<int, std::greater<int>> descending = {
        30, 10, 20, 10
    };

    for (int number : descending)
    {
        std::cout << number << ' ';
    }

    std::cout << '\n';

    return 0;
}