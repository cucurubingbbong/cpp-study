# 상속 · virtual · 다형성 · 가상 소멸자

> 학습 범위: **C++03 / C++11 / C++14 / C++17**  
> 실행 코드: `main.cpp` (C++11 이상, C++17 권장)  
> 키워드: **Inheritance / Virtual / Polymorphism / Virtual Destructor / Override / Final / Abstract Class**

---

# 1. 상속(Inheritance)이란?

기존 **부모 클래스(Base Class)**의 기능을 **자식 클래스(Derived Class)**가 이어받는 기능이다.

```cpp
class Character
{
public:
    void PrintInfo() const { /* 공통 동작 */ }
};

class Warrior : public Character
{
public:
    void Attack() const { /* 자식 동작 */ }
};
```

```text
Character (부모)
   ├── Warrior (자식)
   └── Mage    (자식)
```

- `class Warrior : public Character`: `Character`를 **public 상속**한다.
- 자식 객체에는 **부모 클래스 부분(Base Subobject)**이 포함된다.
- 일반적인 public 상속은 **IS-A 관계**를 나타낼 때 적합하다. 예: Warrior는 Character의 한 종류.
- 단순히 다른 객체를 *가지고 있다*면 상속보다 멤버 변수 등 **합성(Composition)**이 적절할 수 있다.

---

# 2. public / protected / private

부모 멤버의 접근 수준은 다음과 같다.

| 부모 멤버의 접근 지정자 | 부모 클래스 내부 | 자식 클래스 내부(파생 멤버 함수) | 외부 코드 |
| --- | :---: | :---: | :---: |
| `public` | O | O | O |
| `protected` | O | O | X |
| `private` | O | X | X |

위 표의 외부 접근은 **public 상속** 기준이다. 부모의 `private` 멤버는 자식 객체의 부모 부분에 여전히 존재하지만 자식 클래스가 **직접 접근**할 수 없다.

```cpp
class Character
{
private:
    int secret = 0;    // C++11부터 멤버 기본 초기화 가능
protected:
    int hp = 100;
public:
    void Print() const { /* ... */ }
};

class Warrior : public Character
{
public:
    void Damage() { hp -= 20; } // 가능
    // void Change() { secret = 1; } // 오류: private에 직접 접근 불가
};
```

## 상속 방식 자체에 따른 차이

| 상속 방식 | 부모의 public 멤버 | 부모의 protected 멤버 |
| --- | --- | --- |
| `public` | public으로 유지 | protected로 유지 |
| `protected` | protected가 됨 | protected로 유지 |
| `private` | private가 됨 | private가 됨 |

세 경우 모두 부모 `private` 멤버에 대한 자식의 **직접 접근은 불가능**하다.

실무에서는 데이터를 무조건 `protected`로 만들기보다 `private` 상태를 유지하고 적절한 접근 함수를 제공하는 것도 많이 사용한다.

---

# 3. 부모와 자식의 생성자·소멸자 호출 순서

```cpp
#include <iostream>

class A
{
public:
    A()  { std::cout << "A+\n"; }
    ~A() { std::cout << "A-\n"; }
};

class B : public A
{
public:
    B()  { std::cout << "B+\n"; }
    ~B() { std::cout << "B-\n"; }
};

int main()
{
    B obj;
}
```

출력:

```text
A+
B+
B-
A-
```

```text
생성: 부모 → 자식
소멸: 자식 → 부모
```

부모 생성자에 매개변수가 있다면 **자식 생성자 초기화 리스트**에서 호출한다.

```cpp
class Character
{
public:
    explicit Character(int hp) { /* ... */ }
};

class Warrior : public Character
{
public:
    explicit Warrior(int hp) : Character(hp) { }
};
```

`explicit`은 단일 인수 생성자로 인한 의도하지 않은 암시적 변환을 방지하는 데 사용할 수 있다.

---

# 4. virtual — 가상 함수

부모 포인터나 부모 참조로 함수를 호출할 때 **실제 객체 타입의 재정의된 함수**를 사용하려면 `virtual`을 선언한다.

## virtual이 없다면

```cpp
class Character
{
public:
    void Attack() { std::cout << "Character\n"; }
};

class Warrior : public Character
{
public:
    void Attack() { std::cout << "Warrior\n"; }
};

Warrior warrior;
Character& ref = warrior;
ref.Attack(); // Character
warrior.Attack(); // Warrior
```

부모 참조로 호출한 비가상 함수는 **정적 타입**을 기준으로 선택된다. 자식에 같은 이름의 함수를 정의할 수는 있지만, 이 경우 부모 함수를 숨기는 동작(Name Hiding)이 발생한다.

## virtual이 있다면

```cpp
class Character
{
public:
    virtual void Attack() { std::cout << "Character\n"; }
};

class Warrior : public Character
{
public:
    void Attack() override { std::cout << "Warrior\n"; }
};

Warrior warrior;
Character& ref = warrior;
ref.Attack(); // Warrior
```

- 정적 바인딩: 비가상 함수 호출의 대표적 동작. 호출식에서 보이는 타입 기준.
- 동적 바인딩: 가상 함수 호출에서 실제 객체 타입에 맞는 최종 재정의 함수가 선택됨.
- `virtual`은 C++03에서도 지원한다.
- `override`는 C++11부터 지원한다.

---

# 5. 다형성(Polymorphism)

서로 다른 자식 객체를 **공통 부모 인터페이스**로 다루는 기능이다.

```cpp
void PerformAttack(Character& character)
{
    character.Attack();
}

Warrior warrior;
Mage mage;
PerformAttack(warrior); // Warrior::Attack()
PerformAttack(mage);    // Mage::Attack()
```

부모 포인터나 참조로 다형성을 유지할 수 있다.

**객체 슬라이싱(Object Slicing) 주의**:

```cpp
void Wrong(Character character)
{
    character.Attack();
}
```

부모 타입으로 **값 전달**하면 자식 객체의 부모 부분만 복사되는 슬라이싱이 일어날 수 있다. 다형적 동작에는 보통 `Character&`, `const Character&`, `Character*` 등을 사용한다.

단, `Character`가 추상 클래스면 위처럼 값으로 매개변수를 선언할 수 없다.

---

# 6. 가상 소멸자(Virtual Destructor)

부모 포인터를 통해 자식 객체를 삭제할 수 있도록 설계했다면 부모 소멸자를 `virtual`로 선언한다.

```cpp
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

Character* ptr = new Warrior();
delete ptr;
```

출력:

```text
Warrior 소멸
Character 소멸
```

**주의:** 부모 소멸자가 비가상인 상황에서 부모 포인터로 자식 객체를 `delete`하면 일반적인 C++03~17 규칙상 **정의되지 않은 동작(Undefined Behavior)**이다. 부모 소멸자만 호출된다고 보장되는 상황이 아니고, 메모리 누수는 가능한 증상 중 하나다.

실무에서 다형적 기반 클래스는 **public virtual 소멸자**가 흔한 선택이다. 다형적 삭제를 의도하지 않는다면 다른 설계(예: protected 비가상 소멸자)도 가능하다.

> `main.cpp`는 소멸자 호출을 확인하기 위해 `new`와 `delete`를 직접 사용한다. 이후 RAII 파트에서는 `std::unique_ptr`로 소유권을 자동 관리한다.

---

# 7. override (C++11부터)

`override`는 **실제로 부모의 가상 함수를 재정의하는지 컴파일러에 검사하도록 지시**한다.

```cpp
class Base
{
public:
    virtual void Print() const { }
};

class Derived : public Base
{
public:
    // void Print() override { } // 컴파일 오류: const가 다름
    void Print() const override { } // 정상
};
```

중요한 것은 `const`가 매개변수가 아니라 **멤버 함수 한정자**라는 점이다.

- 함수 이름이 같아도 매개변수 목록, `const` 등의 재정의 조건이 다르면 올바른 재정의가 아닐 수 있다.
- `override`를 생략해도 조건을 만족하면 가상 함수를 재정의할 수 있다.
- 하지만 C++11 이상에서는 실수 방지를 위해 `override` 사용을 권장한다.

---

# 8. final (C++11부터)

`final`은 **가상 함수** 또는 **클래스**에 붙일 수 있으며 역할이 다르다.

## 함수의 final

```cpp
class Base
{
public:
    virtual void Run() { }
};

class Derived : public Base
{
public:
    void Run() override final { }
};

class Child : public Derived
{
public:
    // void Run() override { } // 컴파일 오류: final 함수 재정의 금지
};
```

`Derived`를 상속하는 것 자체는 가능하다. **Run()만 추가 재정의할 수 없다.**

## 클래스의 final

```cpp
class Mage final : public Base
{
};

// class SpecialMage : public Mage {}; // 컴파일 오류: 클래스 상속 금지
```

| 선언 | 의미 |
| --- | --- |
| `void Run() override` | 올바른 가상 함수 재정의인지 검사 |
| `void Run() final` | 해당 가상 함수의 추가 재정의 금지 |
| `void Run() override final` | 재정의 검사 + 추가 재정의 금지 |
| `class Mage final` | Mage 클래스 자체를 더 이상 상속하지 못함 |

---

# 9. 순수 가상 함수와 추상 클래스

순수 가상 함수는 `= 0`으로 선언한다.

```cpp
class Character
{
public:
    virtual void Attack() const = 0;
    virtual ~Character() { }
};
```

- `= 0`은 **0을 반환**한다는 뜻이 아니다.
- 최종적으로 구현되지 않은 순수 가상 함수가 남아 있는 클래스는 **추상 클래스**이다.
- 추상 클래스는 **직접 객체를 생성할 수 없다**.
- 하지만 추상 클래스 타입의 **포인터와 참조**는 만들 수 있다.

```cpp
// Character character; // 컴파일 오류

class Warrior : public Character
{
public:
    void Attack() const override { }
};

Warrior warrior;         // 가능
Character& ref = warrior; // 가능
```

자식 클래스에서 순수 가상 함수를 구현하지 않으면 그 자식도 추상 클래스다.

```cpp
class Archer : public Character
{
};

// Archer archer; // 컴파일 오류
```

순수 가상 소멸자를 선언한 경우에는 **별도의 소멸자 정의가 필요**하다. 순수 가상 함수에 정의를 제공하는 것이 가능하더라도 순수 가상 선언 자체가 만드는 추상성은 별개다.

---

# 10. 실습 정답 코드 요약

`main.cpp`에는 다음 요구사항을 모두 구현했다.

| 요구사항 | 구현 요소 |
| --- | --- |
| 부모 추상 클래스 | `Character`, `virtual Attack() const = 0` |
| 공통 이름 | `protected std::string name` |
| 부모 생성자 | `Character(newName)` |
| 자식 전사 | `Warrior`, `Attack() const override final` |
| 자식 마법사 | `class Mage final`, `Attack() const override` |
| 다형성 | `std::vector<Character*>` |
| 공격 실행 | 부모 포인터의 `character->Attack()` |
| 가상 소멸자 | `virtual ~Character()` |
| 역순 삭제 | `rbegin()` ~ `rend()` 반복자와 `delete` |

## 예제 입력

```text
3
W Knight
M Merlin
W Archer
```

## 예상 출력

```text
Warrior Knight: Sword Attack
Mage Merlin: Magic Attack
Warrior Archer: Sword Attack
Destroy Warrior Archer
Destroy Character Archer
Destroy Mage Merlin
Destroy Character Merlin
Destroy Warrior Knight
Destroy Character Knight
```

### 왜 `new`와 `delete`를 사용했을까?

가상 소멸자가 실제로 작동하는지 확인하는 학습 문제이기 때문이다.

```cpp
Character* ptr = new Warrior("Knight");
ptr->Attack(); // 동적 바인딩
delete ptr;    // 자식 소멸자 → 부모 소멸자
```

이 경우 `std::vector<Character*>`는 **포인터를 저장할 뿐, 가리키는 객체를 자동 삭제하지 않는다.** `delete`를 하지 않으면 동적 할당한 객체가 해제되지 않는다. 반대로 같은 포인터를 두 번 `delete`해도 안 된다.

실제 코드에서는 수동 메모리 관리가 예외 안전성 문제를 일으킬 수 있으므로 이후 `std::unique_ptr`와 `std::make_unique`를 학습한다.

---

# 11. C++03 / C++11 / C++14 / C++17 차이

| 기능 | C++03 | C++11 | C++14 | C++17 |
| --- | :---: | :---: | :---: | :---: |
| `class`, 상속, `virtual` | O | O | O | O |
| 추상 클래스와 순수 가상 함수 | O | O | O | O |
| 가상 소멸자 | O | O | O | O |
| `override` / `final` | X | O | O | O |
| `std::unique_ptr` | X | O | O | O |
| `std::make_unique` | X | X | O | O |
| 범위 기반 `for` / `auto` 타입 추론 | X | O | O | O |

## C++03에서도 가능한 가상 함수 코드

```cpp
#include <iostream>

class Base
{
public:
    virtual void Speak() const = 0;
    virtual ~Base() { }
};

class Derived : public Base
{
public:
    virtual void Speak() const
    {
        std::cout << "Hello\n";
    }
};

int main()
{
    Derived derived;
    Base& ref = derived;
    ref.Speak();
}
```

C++03에서는 `override`와 `final`을 쓸 수 없으므로 함수 서명을 직접 정확하게 맞춰야 한다.

### 빌드 예시

```bash
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp -o oop_study
g++ -std=c++14 -Wall -Wextra -pedantic main.cpp -o oop_study
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o oop_study
./oop_study
```

---

# 12. 핵심 요약

```text
상속
  └─ 자식 객체는 부모 클래스 부분을 포함

접근 지정자
  └─ public: 외부 접근 가능
  └─ protected: 자식 멤버 함수에서 접근 가능
  └─ private: 자식이 직접 접근 불가

생성/소멸 순서
  └─ 생성: 부모 → 자식
  └─ 소멸: 자식 → 부모

virtual
  └─ 부모 참조·포인터를 통한 동적 바인딩

override (C++11)
  └─ 가상 함수 재정의를 컴파일러가 검증

final (C++11)
  └─ 함수: 추가 재정의 금지
  └─ 클래스: 추가 상속 금지

순수 가상 함수 (= 0)
  └─ 구체적인 파생 클래스에서 구현해야 할 인터페이스

추상 클래스
  └─ 직접 객체 생성 불가 / 부모 포인터·참조로 사용 가능

가상 소멸자
  └─ 부모 포인터로 자식 객체를 안전하게 삭제
```

