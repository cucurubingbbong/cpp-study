#include <iostream>

class Character
{
public:
    virtual void Attack()
    {
        std::cout << "기본 공격\n";
    }

    virtual ~Character() {}
};

class Warrior : public Character
{
public:
    void Attack() override
    {
        std::cout << "검 공격\n";
    }
};

class Mage : public Character
{
public:
    void Attack() override
    {
        std::cout << "마법 공격\n";
    }
};

void PerformAttack(Character& character)
{
    character.Attack();
}

int main()
{
    Warrior warrior;
    Mage mage;

    PerformAttack(warrior);
    PerformAttack(mage);

    return 0;
}