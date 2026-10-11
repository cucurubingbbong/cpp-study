#include <iostream>
#include <vector>
#include <string>

int main()
{
    int n = 0;
    std::cin >> n;

    std::vector<int> numbers;

    for (int i = 0; i < n; ++i)
    {
        std::string command;
        std::cin >> command;

        if (command == "PUSH")
        {
            int x = 0;
            std::cin >> x;
            numbers.push_back(x);
        }
        else if (command == "INSERT")
        {
            int index = 0, x = 0;
            std::cin >> index >> x;

            if (index < 0 || index > (int)numbers.size())
            {
                std::cout << "INVALID" << "\n";
            }
            else
            {
                numbers.insert(numbers.begin() + index, x);
            }
        }
        else if (command == "ERASE")
        {
            int index = 0;
            std::cin >> index;

            if (index < 0 || index >= (int)numbers.size())
            {
                std::cout << "INVALID" << "\n";
            }
            else
            {
                numbers.erase(numbers.begin() + index);
            }
        }
        else if (command == "SET")
        {
            int index = 0, x = 0;
            std::cin >> index >> x;

            if (index < 0 || index >= (int)numbers.size())
            {
                std::cout << "INVALID" << "\n";
            }
            else
            {
                numbers[index] = x;
            }
        }
        else if (command == "PRINT")
        {
            if (numbers.empty())
            {
                std::cout << "EMPTY" << "\n";
            }
            else
            {
                for (int j = 0; j < (int)numbers.size(); ++j)
                {
                    std::cout << numbers[j];
                    if (j < (int)numbers.size() - 1)
                    {
                        std::cout << " "; 
                    }
                }
                std::cout << std::endl;
            }
        }
        else if (command == "SIZE")
        {
            std::cout << numbers.size() << std::endl;
        }
    }

    return 0;
}
