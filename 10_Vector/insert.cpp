#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numbers = {10, 20, 30};

    numbers.insert(numbers.begin() + 1, 3 , 15);

    for (int number : numbers)
    {
        std::cout << number << ' ';
    }

    return 0;
}