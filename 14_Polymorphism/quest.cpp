#include <iostream>
#include <string>
#include <vector>
#include <cstddef>

// 부모 추상 클래스
class Character
{
protected:
    std::string name;

public:
    // 부모 생성자
    explicit Character(const std::string& newName)
        : name(newName)
    {
    }

    // 순수 가상 함수
    // 자식 클래스가 구체적인 공격 방식을 구현해야 함
    virtual void Attack() const = 0;

    // 가상 소멸자
    // 부모 포인터로 자식 객체를 삭제할 때 필요
    virtual ~Character()
    {
        std::cout << "Destroy Character "
                  << name << '\n';
    }
};

// Character 상속
class Warrior : public Character
{
public:
    explicit Warrior(const std::string& newName)
        : Character(newName)
    {
    }

    // override: 부모 가상 함수 재정의 검사
    // final: 하위 클래스에서 Attack 재정의 금지
    void Attack() const override final
    {
        std::cout << "Warrior " << name
                  << ": Sword Attack\n";
    }

    ~Warrior() override
    {
        std::cout << "Destroy Warrior "
                  << name << '\n';
    }
};

// 클래스에 final을 붙였으므로 추가 상속 불가능
class Mage final : public Character
{
public:
    explicit Mage(const std::string& newName)
        : Character(newName)
    {
    }

    void Attack() const override
    {
        std::cout << "Mage " << name
                  << ": Magic Attack\n";
    }

    ~Mage() override
    {
        std::cout << "Destroy Mage "
                  << name << '\n';
    }
};

int main()
{
    int n = 0;
    std::cin >> n;

    // 부모 포인터를 이용해 서로 다른 자식 객체 관리
    std::vector<Character*> characters;

    characters.reserve(static_cast<std::size_t>(n));

    // 캐릭터 생성
    for (int i = 0; i < n; ++i)
    {
        char type;
        std::string name;

        std::cin >> type >> name;

        if (type == 'W')
        {
            characters.push_back(new Warrior(name));
        }
        else if (type == 'M')
        {
            characters.push_back(new Mage(name));
        }
    }

    // 다형성
    // Character 포인터이지만 실제 객체 타입에 따라
    // Warrior 또는 Mage의 Attack이 실행됨
    for (const Character* character : characters)
    {
        character->Attack();
    }

    // 생성 역순으로 객체 삭제
    // 가상 소멸자 덕분에
    // 자식 소멸자 -> 부모 소멸자 순으로 호출됨
    for (auto it = characters.rbegin();
         it != characters.rend();
         ++it)
    {
        delete *it;
    }

    // 포인터 요소 제거
    characters.clear();

    return 0;
}