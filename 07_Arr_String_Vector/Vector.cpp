#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numbers;

    int N;
    std::cin >> N;

    for (int i = 0; i < N; i++)
    {
        int command;
        std::cin >> command;

        if (command == 1)
        {
            int number;
            std::cin >> number;

            numbers.push_back(number);
        }
        else if (command == 2)
        {
            if (numbers.empty())
            {
                std::cout << "비어있음\n";
            }
            else
            {
                numbers.pop_back();
            }
        }
        else if (command == 3)
        {
            for (int number : numbers)
            {
                std::cout << number << ' ';
            }

            std::cout << '\n';
        }
    }

    return 0;
}