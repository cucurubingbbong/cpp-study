#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string name;

    std::cout << "이름: ";
    std::cin >> name;

    std::vector<int> scores;

    scores.push_back(90);
    scores.push_back(80);
    scores.push_back(100);

    std::cout << "\n학생: " << name << '\n';

    for (int score : scores)
    {
        std::cout << "점수: " << score << '\n';
    }

    std::cout << "점수 개수: "<< scores.size()<< '\n';
    return 0;
}