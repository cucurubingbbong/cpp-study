#include <iostream>
#include <string>
#include <vector>

struct Player
{
    std::string name;
    int hp;

    Player(const std::string& newName, int newHp)
        : name(newName), hp(newHp)
    {
        std::cout << "생성자 호출\n";
    }
};

int main()
{
    std::vector<Player> players;

    players.reserve(2);

    // 객체를 만들어서 전달
    players.push_back(Player("Warrior", 100));

    // 객체를 직접 생성
    players.emplace_back("Mage", 80);

    return 0;
}