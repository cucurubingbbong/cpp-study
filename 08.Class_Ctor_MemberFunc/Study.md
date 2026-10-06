# 클래스 / 생성자 / 멤버 함수

## 클래스

클래스는 **관련된 데이터와 기능을 하나로 묶어서 관리하기 위한 설계도**이다.

예를 들어 플레이어의 정보를 클래스 없이 관리하면:

```cpp
std::string playerName = "Knight";
int playerHp = 100;
int playerAttack = 20;
```

기능도 따로 만들어야 한다.

```cpp
void Heal(int& hp)
{
    hp += 10;
}
```

하지만 이 데이터와 기능은 모두 `Player`와 관련되어 있다.

클래스를 사용하면 하나로 묶을 수 있다.

```cpp
class Player
{
public:
    std::string name;
    int hp;
    int attack;

    void Heal()
    {
        hp += 10;
    }
};
```

구조:

```text
Player
├─ name
├─ hp
├─ attack
└─ Heal()
```

---

# 클래스와 객체

클래스는 설계도이고 실제로 만들어진 데이터를 **객체(Object)**라고 한다.

클래스:

```cpp
class Player
{
};
```

객체 생성:

```cpp
Player player;
```

정리:

```text
class Player
└─ 설계도

Player player;
└─ 실제 객체
```

하나의 클래스로 여러 객체를 만들 수 있다.

```cpp
Player player1;
Player player2;
Player player3;
```

각 객체는 자신의 데이터를 따로 가진다.

```cpp
player1.hp = 100;
player2.hp = 50;
player3.hp = 30;
```

구조:

```text
Player 클래스

├─ player1
│  └─ hp = 100
│
├─ player2
│  └─ hp = 50
│
└─ player3
   └─ hp = 30
```

---

# 멤버 변수

클래스 안에 선언된 변수를 **멤버 변수(Member Variable)**라고 한다.

```cpp
class Player
{
public:
    std::string name;
    int hp;
    int attack;
};
```

여기서:

```text
name
hp
attack
```

은 모두 `Player`의 멤버 변수이다.

객체의 멤버에 접근할 때 `.`을 사용한다.

```cpp
Player player;

player.name = "Knight";
player.hp = 100;
player.attack = 20;
```

형태:

```text
객체.멤버
```

예:

```cpp
player.hp
player.name
```

---

# 멤버 함수

클래스 안에 선언된 함수를 **멤버 함수(Member Function)**라고 한다.

```cpp
class Player
{
public:
    int hp;

    void Heal()
    {
        hp += 10;
    }
};
```

`Heal()`은 `Player`의 멤버 함수이다.

사용:

```cpp
Player player;

player.hp = 50;

player.Heal();

std::cout << player.hp;
```

결과:

```text
60
```

멤버 함수도 `.`을 사용해서 호출한다.

```cpp
player.Heal();
```

---

# 멤버 함수와 멤버 변수

멤버 함수는 자신이 속한 객체의 멤버 변수에 바로 접근할 수 있다.

일반 함수라면:

```cpp
void Heal(int& hp)
{
    hp += 10;
}
```

처럼 값을 전달해야 한다.

하지만 클래스에서는:

```cpp
class Player
{
public:
    int hp;

    void Heal()
    {
        hp += 10;
    }
};
```

처럼 바로 `hp`를 사용할 수 있다.

`Heal()`은 현재 자신을 호출한 `Player` 객체의 `hp`를 사용한다.

예:

```cpp
Player player1;
Player player2;

player1.hp = 100;
player2.hp = 50;

player2.Heal();
```

결과:

```text
player1.hp = 100
player2.hp = 60
```

---

# 멤버 함수의 매개변수

멤버 함수도 일반 함수처럼 매개변수를 받을 수 있다.

```cpp
class Player
{
public:
    int hp;

    void TakeDamage(int damage)
    {
        hp -= damage;
    }
};
```

사용:

```cpp
Player player;

player.hp = 100;

player.TakeDamage(30);
```

결과:

```text
hp = 70
```

실행 과정:

```text
player.TakeDamage(30)

damage = 30

hp = hp - damage

100 - 30

hp = 70
```

---

# 멤버 함수의 반환값

멤버 함수도 값을 반환할 수 있다.

```cpp
class Player
{
public:
    int hp;

    int GetHp()
    {
        return hp;
    }
};
```

사용:

```cpp
Player player;

player.hp = 100;

std::cout << player.GetHp();
```

결과:

```text
100
```

`bool`도 반환할 수 있다.

```cpp
bool IsDead()
{
    return hp <= 0;
}
```

사용:

```cpp
if (player.IsDead())
{
    std::cout << "사망\n";
}
```

---

# 생성자

생성자(Constructor)는 **객체가 생성될 때 자동으로 실행되는 특별한 함수**이다.

예:

```cpp
class Player
{
public:
    std::string name;
    int hp;

    Player()
    {
        name = "Unknown";
        hp = 100;
    }
};
```

여기서:

```cpp
Player()
```

가 생성자이다.

객체를 만들면:

```cpp
Player player;
```

자동으로 생성자가 실행된다.

결과:

```text
player.name = "Unknown"
player.hp = 100
```

---

# 생성자의 특징

생성자는 다음 특징을 가진다.

```text
클래스 이름과 생성자 이름이 같다.

반환형이 없다.

객체가 만들어질 때 자동으로 실행된다.

객체의 초기 상태를 설정할 때 주로 사용한다.
```

일반 함수:

```cpp
void Test()
{
}
```

생성자:

```cpp
Player()
{
}
```

생성자에는 `void`도 작성하지 않는다.

잘못된 형태:

```cpp
void Player()
{
}
```

생성자는:

```cpp
Player()
{
}
```

처럼 작성한다.

---

# 매개변수가 있는 생성자

생성자도 매개변수를 받을 수 있다.

```cpp
class Player
{
public:
    std::string name;
    int hp;

    Player(std::string playerName, int playerHp)
    {
        name = playerName;
        hp = playerHp;
    }
};
```

객체 생성:

```cpp
Player player("Knight", 100);
```

전달되는 값:

```text
playerName = "Knight"
playerHp = 100
```

결과:

```text
player.name = "Knight"
player.hp = 100
```

---

# 객체마다 다른 초기값

```cpp
Player player1("Knight", 100);
Player player2("Wizard", 70);
Player player3("Archer", 80);
```

결과:

```text
player1
├─ name = Knight
└─ hp = 100

player2
├─ name = Wizard
└─ hp = 70

player3
├─ name = Archer
└─ hp = 80
```

---

# 생성자 오버로딩

생성자도 일반 함수처럼 여러 개 만들 수 있다.

단, 매개변수의 개수나 타입이 달라야 한다.

```cpp
class Player
{
public:
    std::string name;
    int hp;

    Player()
    {
        name = "Unknown";
        hp = 100;
    }

    Player(std::string playerName)
    {
        name = playerName;
        hp = 100;
    }

    Player(std::string playerName, int playerHp)
    {
        name = playerName;
        hp = playerHp;
    }
};
```

사용:

```cpp
Player player1;
Player player2("Knight");
Player player3("Wizard", 50);
```

결과:

```text
player1
→ Unknown / 100

player2
→ Knight / 100

player3
→ Wizard / 50
```

전달된 인자를 보고 알맞은 생성자가 자동으로 선택된다.

---

# public

`public`은 **클래스 외부에서도 접근할 수 있는 영역**이다.

```cpp
class Player
{
public:
    int hp;
};
```

사용:

```cpp
Player player;

player.hp = 100;
```

가능하다.

---

# private

`private`는 **클래스 외부에서는 직접 접근할 수 없는 영역**이다.

```cpp
class Player
{
private:
    int hp;
};
```

다음 코드는 사용할 수 없다.

```cpp
Player player;

player.hp = 100;
```

멤버 변수 `hp`가 `private`이기 때문이다.

정리:

```text
public
└─ 클래스 외부 접근 가능

private
└─ 클래스 외부 직접 접근 불가능
└─ 클래스 내부에서는 접근 가능
```

---

# private를 사용하는 이유

다음처럼 `hp`가 public이라면:

```cpp
class Player
{
public:
    int hp;
};
```

외부에서:

```cpp
player.hp = -9999;
player.hp = 999999;
```

처럼 잘못된 값을 마음대로 넣을 수 있다.

그래서 데이터를 `private`으로 만들고 멤버 함수를 통해 변경할 수 있다.

```cpp
class Player
{
private:
    int hp;

public:
    void TakeDamage(int damage)
    {
        hp -= damage;

        if (hp < 0)
        {
            hp = 0;
        }
    }
};
```

이렇게 하면 `Player` 스스로 자신의 상태를 관리할 수 있다.

---

# Getter

`private` 멤버의 값을 외부에서 읽기 위한 함수를 흔히 **Getter**라고 한다.

```cpp
class Player
{
private:
    int hp;

public:
    int GetHp()
    {
        return hp;
    }
};
```

사용:

```cpp
std::cout << player.GetHp();
```

---

# Setter

`private` 멤버 값을 변경하기 위한 함수를 흔히 **Setter**라고 한다.

```cpp
void SetHp(int value)
{
    if (value < 0)
    {
        value = 0;
    }

    if (value > 100)
    {
        value = 100;
    }

    hp = value;
}
```

사용:

```cpp
player.SetHp(500);
```

함수에서 값을 검사하기 때문에 최종:

```text
hp = 100
```

으로 제한할 수 있다.

---

# 캡슐화

멤버 변수를 `private`으로 숨기고 정해진 멤버 함수를 통해 접근하도록 만드는 것을 **캡슐화(Encapsulation)**와 연결해서 볼 수 있다.

예:

```cpp
class Player
{
private:
    int hp;

public:
    int GetHp()
    {
        return hp;
    }

    void SetHp(int value)
    {
        hp = value;
    }
};
```

핵심:

```text
데이터를 아무 곳에서나 직접 변경하지 못하게 함

객체가 자신의 데이터를 관리하도록 함

잘못된 값이 들어가는 것을 방지할 수 있음
```

---

# 멤버 초기화 리스트

생성자에서는 멤버 변수를 초기화하기 위해 **멤버 초기화 리스트**를 많이 사용한다.

기존 방식:

```cpp
Player(std::string playerName, int playerHp)
{
    name = playerName;
    hp = playerHp;
}
```

초기화 리스트:

```cpp
Player(std::string playerName, int playerHp)
    : name(playerName), hp(playerHp)
{
}
```

의미:

```text
name을 playerName으로 초기화

hp를 playerHp로 초기화
```

C++에서는 생성자에서 멤버를 초기화할 때 초기화 리스트를 자주 사용한다.

---

# this 포인터

멤버 함수 안에서는 `this`라는 특별한 포인터를 사용할 수 있다.

`this`는 **현재 멤버 함수를 실행하고 있는 객체 자신의 주소**를 가리킨다.

예:

```cpp
class Player
{
private:
    int hp;

public:
    Player(int hp)
    {
        this->hp = hp;
    }
};
```

여기서:

```text
this->hp
└─ 현재 객체의 멤버 변수 hp

hp
└─ 생성자의 매개변수 hp
```

따라서:

```cpp
this->hp = hp;
```

의미:

```text
현재 객체의 hp에
매개변수 hp 값을 저장
```

---

# 객체와 포인터의 멤버 접근

객체 자체를 가지고 있다면 `.`을 사용한다.

```cpp
Player player;

player.GetHp();
```

객체를 가리키는 포인터를 가지고 있다면 `->`를 사용한다.

```cpp
Player* ptr = &player;

ptr->GetHp();
```

정리:

```text
객체
└─ .

객체 포인터
└─ ->
```

`->`는 개념적으로:

```cpp
(*ptr).GetHp();
```

와 같은 멤버 접근이다.

---

# const 멤버 함수

멤버 함수 뒤에도 `const`를 붙일 수 있다.

```cpp
int GetHp() const
{
    return hp;
}
```

뒤의 `const`는:

> 이 멤버 함수에서는 객체의 상태를 변경하지 않겠다.

라는 의미이다.

예:

```cpp
class Player
{
private:
    int hp;

public:
    int GetHp() const
    {
        return hp;
    }
};
```

다음 코드는 사용할 수 없다.

```cpp
int GetHp() const
{
    hp = 100;
    return hp;
}
```

`const` 멤버 함수에서는 일반 멤버 변수를 수정할 수 없다.

Getter나 상태 출력 함수처럼 **읽기만 하는 멤버 함수**에 많이 사용한다.

---

# 전체 예제

```cpp
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

    void Attack() const
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

    std::cout << "\n데미지를 받은 후\n";
    player.PrintStatus();

    player.Heal(10);

    std::cout << "\n회복 후\n";
    player.PrintStatus();

    return 0;
}
```

실행 결과:

```text
Name: Knight
HP: 100
Attack: 20

데미지를 받은 후
Name: Knight
HP: 70
Attack: 20

회복 후
Name: Knight
HP: 80
Attack: 20
```

---

# 클래스의 기본 구조

보통 다음과 같은 형태를 많이 사용한다.

```cpp
class 클래스이름
{
private:
    // 멤버 변수

public:
    // 생성자

    // 멤버 함수
};
```

예:

```cpp
class Player
{
private:
    int hp;

public:
    Player(int startHp)
        : hp(startHp)
    {
    }

    void Heal(int amount)
    {
        hp += amount;
    }

    int GetHp() const
    {
        return hp;
    }
};
```

---

# 클래스 끝의 세미콜론

클래스를 정의한 뒤에는 반드시 `;`을 붙인다.

```cpp
class Player
{
};
```

함수:

```cpp
void Test()
{
}
```

는 마지막에 `;`이 필요하지 않지만 클래스는 필요하다.

---

# 객체의 수명

객체도 일반 변수와 마찬가지로 수명이 있다.

```cpp
{
    Player player("Knight", 100, 20);

    player.Attack();
}
```

실행:

```text
블록 진입
↓
Player 객체 생성
↓
생성자 실행
↓
객체 사용
↓
블록 종료
↓
Player 객체의 수명 종료
```

클래스 객체도 선언된 블록을 벗어나면 일반적으로 소멸한다.

---

# 용어 정리

```text
class
└─ 객체를 만들기 위한 설계도

object
└─ 클래스를 이용해 만든 실제 객체

member variable
└─ 클래스 내부의 변수

member function
└─ 클래스 내부의 함수

constructor
└─ 객체 생성 시 자동 실행되는 특별한 함수
└─ 주로 초기값 설정

public
└─ 외부 접근 가능

private
└─ 외부 직접 접근 불가능

Getter
└─ 값을 읽는 멤버 함수

Setter
└─ 값을 설정하는 멤버 함수
```

---

# 접근 방법 정리

일반 객체:

```cpp
Player player;

player.Attack();
```

```text
.
└─ 객체의 멤버 접근
```

포인터:

```cpp
Player* ptr = &player;

ptr->Attack();
```

```text
->
└─ 객체 포인터의 멤버 접근
```

---

# 최종 정리

```text
클래스

class Player
{
};

└─ 데이터와 기능을 묶는 설계도
```

```text
객체

Player player;

└─ 클래스로 만든 실제 데이터
```

```text
멤버 변수

int hp;

└─ 객체가 가지고 있는 데이터
```

```text
멤버 함수

void Heal()
{
}

└─ 객체가 수행하는 기능
```

```text
생성자

Player()
{
}

└─ 객체 생성 시 자동 실행
└─ 초기 상태 설정
└─ 반환형 없음
```

```text
private

└─ 클래스 외부 직접 접근 X
```

```text
public

└─ 클래스 외부 접근 O
```

```text
const 멤버 함수

int GetHp() const

└─ 객체의 상태를 변경하지 않는 함수
```

---

# 핵심 문법

```cpp
class Player
{
private:
    int hp;

public:
    Player(int hp)
        : hp(hp)
    {
    }

    void TakeDamage(int damage)
    {
        hp -= damage;
    }

    int GetHp() const
    {
        return hp;
    }
};
```

해석:

```text
Player
└─ 클래스 이름

hp
└─ private 멤버 변수

Player(int hp)
└─ 생성자

: hp(hp)
└─ 멤버 변수 초기화

TakeDamage()
└─ hp를 수정하는 멤버 함수

GetHp() const
└─ hp를 반환하는 멤버 함수
└─ 객체 상태를 변경하지 않음
```

사용:

```cpp
Player player(100);

player.TakeDamage(30);

std::cout << player.GetHp();
```

결과:

```text
70
```