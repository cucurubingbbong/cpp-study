#include <iostream>
#include <vector>

class Character
{
public:
    virtual void Attack() const = 0;

    virtual ~Character()
    {
        std::cout << "Character 소멸\n";
    }
};

class Warrior : public Character
{
public:
    void Attack() const override
    {
        std::cout << "검 공격\n";
    }

    ~Warrior() override
    {
        std::cout << "Warrior 소멸\n";
    }
};

class Mage final : public Character
{
public:
    void Attack() const override
    {
        std::cout << "마법 공격\n";
    }

    ~Mage() override
    {
        std::cout << "Mage 소멸\n";
    }
};

void PerformAttack(const Character& character)
{
    character.Attack();
}

int main()
{
    Warrior warrior;
    Mage mage;

    std::vector<const Character*> characters;

    characters.push_back(&warrior);
    characters.push_back(&mage);

    for (const Character* character : characters)
    {
        PerformAttack(*character);
    }

    return 0;
}