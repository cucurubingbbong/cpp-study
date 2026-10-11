#include <iostream>
#include <vector>

void PrintScores(const std::vector<int>& scores)
{
    for (int score : scores)
    {
        std::cout << score << ' ';
    }

    std::cout << '\n';
}

int main()
{
    std::vector<int> scores;

    scores.reserve(3);

    scores.push_back(90);
    scores.push_back(80);
    scores.push_back(100);

    PrintScores(scores);

    if (!scores.empty())
    {
        std::cout << scores.back() << '\n';
    }

    return 0;
}