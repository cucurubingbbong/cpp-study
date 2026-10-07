#include <iostream>
#include <string>

class Player
{
private:
    std::string name;

public:
    Player(const std::string& name)
        : name(name)
    {
        std::cout << name << " 생성\n";
    }

    ~Player()
    {
        std::cout << name << " 소멸\n";
    }

    void PrintName() 
    {
        std::cout << "Player: " << name << '\n';
    }
};

int main()
{
    std::cout << "===== 지역 객체 =====\n";

    {
        Player player("Knight");

        player.PrintName();
    }

    std::cout << "\n===== 동적 객체 =====\n";

    Player* player = new Player("Wizard");

    player->PrintName();

    delete player;
    player = nullptr;

    return 0;
}