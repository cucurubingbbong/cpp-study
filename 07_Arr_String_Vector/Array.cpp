#include <iostream>

int main()
{
    int scores[5];

    // 점수 입력
    for (int i = 0; i < 5; i++)
    {
        std::cin >> scores[i];
    }

    int sum = 0;
    int maxScore = scores[0];
    int minScore = scores[0];

    for (int i = 0; i < 5; i++)
    {
        sum += scores[i];

        if (scores[i] > maxScore)
        {
            maxScore = scores[i];
        }

        if (scores[i] < minScore)
        {
            minScore = scores[i];
        }
    }

    int average = sum / 5;

    std::cout << "총합: " << sum << '\n';
    std::cout << "평균: " << average << '\n';
    std::cout << "최고 점수: " << maxScore << '\n';
    std::cout << "최저 점수: " << minScore << '\n';

    return 0;
}