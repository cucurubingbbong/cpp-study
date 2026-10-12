#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
    std::unordered_map<std::string, int> inventory;

    inventory.reserve(16);

    // 값 추가 및 수정
    inventory["potion"] += 3;
    inventory["potion"] += 2;

    // insert
    inventory.insert({"sword", 1});

    // emplace
    auto result = inventory.emplace("sword", 999);

    std::cout << std::boolalpha;
    std::cout << result.second << '\n'; // false

    // find
    auto it = inventory.find("potion");

    if (it != inventory.end())
    {
        std::cout << it->first << ": "
                  << it->second << '\n';
    }

    // count
    std::cout << inventory.count("shield") << '\n';

    // C++17: 없으면 삽입
    inventory.try_emplace("shield", 4);

    // C++17: 삽입 또는 수정
    inventory.insert_or_assign("sword", 2);

    std::cout << inventory.at("sword") << '\n';

    // 삭제
    inventory.erase("shield");

    std::cout << inventory.size() << '\n';

    // 바인딩 
    for (const auto& [name, count] : inventory)
    {
        std::cout << name << ": " << count << '\n';
    }

    return 0;
}