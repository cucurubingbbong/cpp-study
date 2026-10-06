#include <iostream>
#include <string>

class Player
{
    private:
        std::string name;
        int hp;
        int attack;

    public:
        Player(std::string playerName, int playerHp, int playerAttack)
            : name(playerName), hp(playerHp), attack(playerAttack)
        {
        }

    void Attack()
    {
        std::cout
            << name
            << "이 공격합니다. 공격력: "
            << attack
            << '\n';
    }

    void TakeDamage(int damage)
    {
        hp -= damage;

        if (hp < 0)
        {
            hp = 0;
        }
    }

    void Heal(int amount)
    {
        hp += amount;

        if (hp > 100)
        {
            hp = 100;
        }
    }

    bool IsDead() const
    {
        return hp <= 0;
    }

    int GetHp() const
    {
        return hp;
    }

    void PrintStatus() const
    {
        std::cout << "Name: " << name << '\n';
        std::cout << "HP: " << hp << '\n';
        std::cout << "Attack: " << attack << '\n';
    }
};

int main()
{
    Player player("Knight", 100, 20);

    player.PrintStatus();

    player.TakeDamage(30);

    std::cout << "\n데미지 받은 후\n";

    player.PrintStatus();

    player.Heal(10);

    std::cout << "\n회복 후\n";

    player.PrintStatus();

    return 0;
}