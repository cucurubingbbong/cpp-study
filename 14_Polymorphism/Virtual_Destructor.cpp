#include <iostream>

class Character
{
public:
    virtual ~Character()
    {
        std::cout << "Character 소멸\n";
    }
};

class Warrior : public Character
{
public:
    ~Warrior() override
    {
        std::cout << "Warrior 소멸\n";
    }
};

int main()
{
    Character *ptr = new Warrior();

    delete ptr;
}