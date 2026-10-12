#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

void PrintVector(const std::vector<int>& values)
{
    for (int value : values)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

void BasicIterator()
{
    std::cout << "[1] begin, end, const_iterator\n";

    std::vector<int> numbers = {10, 20, 30};

    // [begin, end): end()는 실제 요소가 아니므로 역참조하면 안 된다.
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    // 반복자로 가리키는 요소의 원본 값을 수정할 수 있다.
    auto it = numbers.begin();
    ++it;
    *it = 99;
    PrintVector(numbers); // 10 99 30

    // 읽기 전용 반복자. *cit = 100; 은 컴파일 오류이다.
    for (auto cit = numbers.cbegin(); cit != numbers.cend(); ++cit)
    {
        std::cout << *cit << ' ';
    }
    std::cout << '\n';

    // string도 반복자로 순회할 수 있다.
    std::string text = "CAT";
    for (auto ch = text.cbegin(); ch != text.cend(); ++ch)
    {
        std::cout << *ch << ' ';
    }
    std::cout << "\n\n";
}

void ReverseIterator()
{
    std::cout << "[2] rbegin, rend\n";

    std::vector<int> numbers = {10, 20, 30, 40};

    // 역방향 반복자에서 ++it은 논리적으로 이전 요소로 이동한다.
    for (auto it = numbers.crbegin(); it != numbers.crend(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::cout << '\n'; // 40 30 20 10

    // reverse_iterator::base()는 대응하는 정방향 반복자를 반환한다.
    // rbegin().base() == end(), rend().base() == begin()
    std::cout << std::boolalpha;
    std::cout << (numbers.rbegin().base() == numbers.end()) << '\n';
    std::cout << (numbers.rend().base() == numbers.begin()) << "\n\n";
}

void InsertAndErase()
{
    std::cout << "[3] insert, erase, 반복자 무효화\n";

    std::vector<int> numbers = {10, 20, 30, 40};

    // insert는 새로 삽입한 요소를 가리키는 반복자를 반환한다.
    auto inserted = numbers.insert(numbers.begin() + 1, 15);
    std::cout << *inserted << '\n'; // 15
    PrintVector(numbers);           // 10 15 20 30 40

    // erase는 삭제된 요소 바로 뒤에 남은 요소의 반복자를 반환한다.
    auto next = numbers.erase(numbers.begin() + 2); // 20 삭제
    if (next != numbers.end())
    {
        std::cout << *next << '\n'; // 30
    }
    PrintVector(numbers); // 10 15 30 40

    // 주의: 삽입/삭제 전의 반복자는 무효화됐을 수 있다.
    // 사용하려면 반환된 반복자 또는 begin() 등을 통해 새로 얻어야 한다.

    // 순회 중 안전하게 삭제: erase 반환값을 it에 다시 저장한다.
    std::vector<int> values = {1, 2, 3, 4, 5, 6};
    auto it = values.begin();
    while (it != values.end())
    {
        if (*it % 2 == 0)
        {
            it = values.erase(it);
        }
        else
        {
            ++it;
        }
    }
    PrintVector(values); // 1 3 5
    std::cout << '\n';
}

void StandardAlgorithms()
{
    std::cout << "[4] find, find_if, sort, remove_if\n";

    std::vector<int> numbers = {8, 3, 5, 3};

    // sort는 원본 요소들의 순서를 변경한다.
    std::sort(numbers.begin(), numbers.end());
    PrintVector(numbers); // 3 3 5 8

    auto found = std::find(numbers.begin(), numbers.end(), 5);
    if (found != numbers.end())
    {
        std::cout << "5의 인덱스: "
                  << std::distance(numbers.begin(), found) << '\n'; // 2
    }

    // find_if는 조건이 true인 첫 요소의 반복자를 반환한다.
    auto greaterThanFive = std::find_if(
        numbers.begin(), numbers.end(),
        [](int number) { return number > 5; });

    if (greaterThanFive != numbers.end())
    {
        std::cout << "5보다 큰 첫 값: " << *greaterThanFive << '\n'; // 8
    }

    // remove_if는 남길 요소를 앞으로 옮길 뿐 size()는 바꾸지 않는다.
    std::vector<int> values = {1, 2, 3, 4, 5, 6};
    auto logicalEnd = std::remove_if(
        values.begin(), values.end(),
        [](int number) { return number % 2 == 0; });

    std::cout << "실제 size: " << values.size() << '\n';                // 6
    std::cout << "논리적 size: "
              << std::distance(values.begin(), logicalEnd) << '\n'; // 3

    // [logicalEnd, end()) 구간은 출력하거나 의미를 가정하지 않는다.
    values.erase(logicalEnd, values.end()); // Erase-Remove Idiom
    PrintVector(values); // 1 3 5
    std::cout << '\n';
}

void IteratorCategories()
{
    std::cout << "[5] list와 iterator 범주\n";

    std::list<int> values = {10, 20, 30};
    auto it = values.begin();
    ++it;
    std::cout << *it << '\n'; // 20
    --it;
    std::cout << *it << '\n'; // 10

    // list는 양방향 반복자를 제공하므로 it += 2는 사용할 수 없다.
    // 대신 std::advance()는 C++03부터 사용할 수 있다.
    std::advance(it, 2);
    std::cout << *it << '\n'; // 30
}

int main()
{
    BasicIterator();
    ReverseIterator();
    InsertAndErase();
    StandardAlgorithms();
    IteratorCategories();
    return 0;
}
