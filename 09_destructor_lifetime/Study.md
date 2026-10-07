# 소멸자 / new / delete / 객체 수명

## 객체 수명

객체는 생성된 순간부터 소멸되는 순간까지 존재한다.

이 기간을 **객체의 수명(Lifetime)**이라고 한다.

예:

```cpp
{
    Player player;
}
```

실행 흐름:

```text
블록 진입
↓
Player 객체 생성
↓
객체 사용
↓
블록 종료
↓
Player 객체 소멸
```

일반적인 지역 객체는 자신이 선언된 블록을 벗어나면 자동으로 소멸한다.

---

# 생성자와 객체 수명의 시작

객체가 생성될 때 생성자가 자동으로 호출된다.

```cpp
class Player
{
public:
    Player()
    {
        std::cout << "Player 생성\n";
    }
};
```

사용:

```cpp
Player player;
```

출력:

```text
Player 생성
```

실행 흐름:

```text
객체 생성
↓
생성자 호출
↓
객체 사용 가능
```

---

# 소멸자

소멸자(Destructor)는 **객체의 수명이 끝날 때 자동으로 호출되는 특별한 함수**이다.

형태:

```cpp
class Player
{
public:
    ~Player()
    {
    }
};
```

생성자:

```cpp
Player()
```

소멸자:

```cpp
~Player()
```

클래스 이름 앞에 `~`를 붙인다.

---

# 생성자와 소멸자

예:

```cpp
#include <iostream>

class Player
{
public:
    Player()
    {
        std::cout << "생성\n";
    }

    ~Player()
    {
        std::cout << "소멸\n";
    }
};

int main()
{
    {
        Player player;
    }

    return 0;
}
```

출력:

```text
생성
소멸
```

흐름:

```text
블록 진입
↓
Player 객체 생성
↓
Player() 생성자 실행
↓
객체 사용
↓
블록 종료
↓
~Player() 소멸자 실행
↓
객체 수명 종료
```

---

# 소멸자의 특징

소멸자는 다음 특징을 가진다.

```text
클래스 이름 앞에 ~를 붙임

반환형 없음

매개변수 없음

객체의 수명이 끝날 때 자동 실행

클래스당 하나만 존재
```

예:

```cpp
~Player()
{
}
```

생성자는 여러 개 만들 수 있지만:

```cpp
Player()
Player(int hp)
Player(std::string name, int hp)
```

소멸자는 하나만 존재한다.

---

# 소멸자를 사용하는 이유

객체가 사용하던 자원을 정리해야 할 때 사용한다.

예:

```text
동적으로 할당한 메모리
파일
네트워크 연결
운영체제 핸들
기타 외부 자원
```

개념적으로:

```cpp
class Resource
{
public:
    Resource()
    {
        // 자원 획득
    }

    ~Resource()
    {
        // 자원 정리
    }
};
```

즉:

```text
생성자
└─ 필요한 자원 획득

소멸자
└─ 사용한 자원 정리
```

와 같이 사용할 수 있다.

---

# new

`new`는 객체를 **동적으로 생성**할 때 사용하는 연산자이다.

예:

```cpp
int* ptr = new int;
```

실행 과정:

```text
int 객체를 위한 저장공간 확보
↓
int 객체 생성
↓
생성된 객체의 주소 반환
↓
ptr에 주소 저장
```

구조:

```text
ptr
 │
 ▼
┌─────┐
│ int │
└─────┘
```

---

# new로 값 초기화

객체를 생성하면서 값을 넣을 수도 있다.

```cpp
int* ptr = new int(10);
```

구조:

```text
ptr
 │
 ▼
┌────┐
│ 10 │
└────┘
```

값 읽기:

```cpp
std::cout << *ptr;
```

결과:

```text
10
```

값 변경:

```cpp
*ptr = 50;
```

결과:

```text
50
```

---

# 지역 변수와 new의 차이

일반 지역 변수:

```cpp
{
    int number = 10;
}
```

블록이 끝나면 자동으로 소멸한다.

```text
블록 진입
↓
number 생성
↓
블록 종료
↓
number 소멸
```

`new`로 만든 객체:

```cpp
int* ptr = new int(10);
```

은 포인터 변수의 블록이 끝난다고 해서 같은 방식으로 자동 정리되는 것이 아니다.

동적으로 생성한 객체는 별도의 수명 관리가 필요하다.

---

# delete

`delete`는 `new`로 동적으로 생성한 객체의 수명을 끝내고 저장공간을 해제한다.

```cpp
int* ptr = new int(10);

delete ptr;
```

흐름:

```text
new
↓
동적 객체 생성
↓
객체 사용
↓
delete
↓
객체 수명 종료
↓
저장공간 해제
```

기초적으로는:

```text
new
↔ delete
```

를 한 쌍으로 생각하면 된다.

---

# 클래스와 new

클래스 객체도 `new`로 생성할 수 있다.

```cpp
class Player
{
public:
    Player()
    {
        std::cout << "생성자\n";
    }

    ~Player()
    {
        std::cout << "소멸자\n";
    }
};
```

사용:

```cpp
Player* player = new Player();

delete player;
```

출력:

```text
생성자
소멸자
```

---

# new와 생성자

다음 코드:

```cpp
Player* player = new Player();
```

실행 과정:

```text
저장공간 확보
↓
Player 객체 생성
↓
Player() 생성자 호출
↓
객체 주소 반환
↓
player 포인터가 주소 저장
```

---

# delete와 소멸자

다음 코드:

```cpp
delete player;
```

은 단순히 메모리만 지우는 것이 아니다.

클래스 객체인 경우:

```text
delete
↓
소멸자 호출
↓
객체 수명 종료
↓
저장공간 해제
```

과정이 일어난다.

즉:

```cpp
delete player;
```

을 하면:

```cpp
~Player()
```

가 호출된다.

---

# delete 후 포인터

```cpp
int* ptr = new int(10);

delete ptr;
```

`delete` 이후에는 `ptr` 변수가 자동으로 사라지지 않는다.

또한 자동으로 `nullptr`이 되는 것도 아니다.

개념적으로:

```text
ptr
↓
예전 주소

하지만
그 주소에 있던 객체는 이미 소멸
```

이 상태는 **Dangling Pointer**가 된다.

---

# delete 후 nullptr

학습 단계에서는 다음처럼 사용하는 경우가 많다.

```cpp
delete ptr;
ptr = nullptr;
```

의미:

```text
delete ptr
└─ 동적 객체 삭제

ptr = nullptr
└─ 현재 아무 객체도 가리키지 않는 상태로 변경
```

이렇게 하면 이미 삭제된 객체의 주소를 계속 들고 있는 실수를 줄일 수 있다.

---

# delete 후 역참조

다음 코드는 잘못된 코드이다.

```cpp
int* ptr = new int(10);

delete ptr;

std::cout << *ptr;
```

`delete` 이후에는 객체의 수명이 끝났기 때문이다.

따라서:

```cpp
*ptr
```

로 접근하면 Undefined Behavior가 발생할 수 있다.

---

# nullptr delete

`nullptr`에 `delete`를 사용하는 것은 안전하다.

```cpp
int* ptr = nullptr;

delete ptr;
```

아무 일도 일어나지 않는다.

따라서:

```cpp
delete ptr;
ptr = nullptr;
```

와 같은 형태를 사용할 수 있다.

---

# 아무 포인터에 delete를 사용하면 안 됨

포인터라고 해서 무조건 `delete`를 사용하면 안 된다.

잘못된 코드:

```cpp
int number = 10;

int* ptr = &number;

delete ptr;
```

`number`는 `new`를 이용해서 만든 객체가 아니다.

따라서 `delete`하면 안 된다.

정리:

```text
포인터
≠ 무조건 delete

new로 생성한 객체
→ 그에 맞는 delete 필요
```

---

# Double Delete

이미 삭제한 객체를 다시 삭제하는 것을 Double Delete라고 한다.

잘못된 코드:

```cpp
int* ptr = new int(10);

delete ptr;
delete ptr;
```

첫 번째 `delete`에서 이미 객체가 소멸했다.

두 번째 `delete`는 이미 수명이 끝난 객체를 다시 삭제하려는 것이므로 Undefined Behavior이다.

학습 단계에서는:

```cpp
delete ptr;
ptr = nullptr;
```

처럼 처리할 수 있다.

`delete nullptr;`은 안전하다.

---

# 메모리 누수

`new`로 메모리를 할당한 뒤 `delete`하지 않으면 메모리 누수(Memory Leak)가 발생할 수 있다.

예:

```cpp
void Test()
{
    int* ptr = new int(10);
}
```

함수가 끝나면:

```text
ptr 변수
└─ 소멸
```

하지만:

```text
new int(10)
└─ 할당한 메모리가 해제되지 않음
```

상태가 될 수 있다.

흐름:

```text
new
↓
동적 메모리 확보
↓
ptr이 주소 저장
↓
함수 종료
↓
ptr 소멸
↓
delete 하지 않음
↓
동적 메모리가 남음
↓
Memory Leak
```

---

# 반복문에서 new 사용 주의

다음 코드는 매우 위험하다.

```cpp
while (true)
{
    int* ptr = new int(10);
}
```

반복할 때마다 새로운 메모리를 확보한다.

```text
new
new
new
new
new
...
```

하지만 해제하지 않기 때문에 메모리가 계속 낭비될 수 있다.

---

# 지역 객체와 동적 객체

## 지역 객체

```cpp
{
    Player player;
}
```

수명:

```text
객체 생성
↓
블록 안에서 사용
↓
블록 종료
↓
자동 소멸
```

## 동적 객체

```cpp
Player* player = new Player();
```

수명:

```text
new
↓
객체 생성
↓
사용
↓
delete
↓
객체 소멸
```

---

# 객체 수명과 포인터 수명

포인터의 수명과 포인터가 가리키는 객체의 수명은 서로 다르다.

예:

```cpp
Player* ptr = new Player();

delete ptr;
```

`delete` 이후:

```text
Player 객체
└─ 수명 종료

ptr 변수
└─ 아직 살아있을 수 있음
```

따라서:

```text
포인터가 살아있다
≠
포인터가 가리키는 객체도 살아있다
```

이 차이 때문에 Dangling Pointer가 발생할 수 있다.

---

# new로 생성자 호출

매개변수가 있는 생성자:

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
};
```

일반 객체:

```cpp
Player player(100);
```

동적 객체:

```cpp
Player* player = new Player(100);
```

포인터이기 때문에 멤버에 접근할 때:

```cpp
player->GetHp();
```

처럼 `->`를 사용한다.

---

# 동적 배열

배열도 `new`로 만들 수 있다.

```cpp
int* numbers = new int[5];
```

구조:

```text
numbers
   │
   ▼
[ ][ ][ ][ ][ ]
 0  1  2  3  4
```

사용:

```cpp
numbers[0] = 10;
numbers[1] = 20;
```

---

# new[]와 delete[]

배열을:

```cpp
new[]
```

로 만들었다면:

```cpp
delete[]
```

로 해제해야 한다.

예:

```cpp
int* numbers = new int[5];

delete[] numbers;
numbers = nullptr;
```

정리:

```text
new
↔ delete

new[]
↔ delete[]
```

---

# new와 delete 짝

올바른 코드:

```cpp
int* number = new int(10);

delete number;
```

올바른 배열 코드:

```cpp
int* numbers = new int[5];

delete[] numbers;
```

잘못된 코드:

```cpp
int* numbers = new int[5];

delete numbers;
```

잘못된 코드:

```cpp
int* number = new int(10);

delete[] number;
```

`new`와 `delete`의 형태를 맞춰야 한다.

---

# 여러 객체의 소멸 순서

같은 범위에 여러 지역 객체가 있으면 일반적으로 **생성된 순서의 반대로 소멸**한다.

예:

```cpp
Test a("A");
Test b("B");
Test c("C");
```

생성:

```text
A
B
C
```

소멸:

```text
C
B
A
```

예제:

```cpp
#include <iostream>
#include <string>

class Test
{
private:
    std::string name;

public:
    Test(const std::string& name)
        : name(name)
    {
        std::cout << name << " 생성\n";
    }

    ~Test()
    {
        std::cout << name << " 소멸\n";
    }
};

int main()
{
    Test a("A");
    Test b("B");
    Test c("C");

    return 0;
}
```

결과:

```text
A 생성
B 생성
C 생성
C 소멸
B 소멸
A 소멸
```

---

# 자동 저장 기간과 동적 저장 기간

일반적인 지역 객체:

```cpp
Player player;
```

은 보통 **자동 저장 기간(Automatic Storage Duration)**을 가진다.

```text
블록 진입
↓
객체 생성
↓
블록 종료
↓
자동 소멸
```

`new`로 생성한 객체:

```cpp
Player* player = new Player();
```

는 **동적 저장 기간(Dynamic Storage Duration)**과 관련된다.

```text
new
↓
객체 생성
↓
delete
↓
객체 수명 종료
```

---

# 현대 C++에서 new/delete

`new`와 `delete`는 C++의 객체 수명과 동적 메모리를 이해하기 위해 반드시 알아야 한다.

하지만 현대 C++에서는 직접:

```cpp
new
delete
```

를 여기저기 사용하는 것을 가능한 한 줄이는 편이다.

대신 다음과 같은 타입을 많이 사용한다.

```text
std::string
std::vector
std::unique_ptr
std::shared_ptr
```

이 타입들이 자원을 자동으로 관리하도록 만드는 것이다.

---

# vector와 자원 관리

예:

```cpp
{
    std::vector<int> numbers;

    numbers.push_back(10);
    numbers.push_back(20);
}
```

`vector` 내부에서는 필요한 메모리를 관리한다.

블록이 끝나면 `vector` 객체의 소멸자가 호출되고 자신이 관리하던 자원을 자동으로 정리한다.

따라서 사용자가 직접:

```cpp
new[]
delete[]
```

를 작성할 필요가 없다.

---

# RAII

RAII는 C++의 중요한 자원 관리 방식이다.

핵심은:

> 객체의 수명과 자원의 수명을 연결한다.

개념:

```text
객체 생성
↓
생성자에서 자원 획득
↓
객체 사용
↓
객체 수명 종료
↓
소멸자 호출
↓
자원 정리
```

즉 객체가 살아있는 동안 자원을 가지고 있고, 객체가 사라질 때 자원도 자동으로 정리하도록 만드는 방식이다.

---

# 전체 예제

```cpp
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

    void PrintName() const
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
```

출력:

```text
===== 지역 객체 =====
Knight 생성
Player: Knight
Knight 소멸

===== 동적 객체 =====
Wizard 생성
Player: Wizard
Wizard 소멸
```

차이:

```text
Knight
└─ 블록이 끝나면서 자동 소멸

Wizard
└─ delete를 실행할 때 소멸
```

---

# 핵심 문법

생성자:

```cpp
Player()
{
}
```

객체가 생성될 때 호출된다.

소멸자:

```cpp
~Player()
{
}
```

객체의 수명이 끝날 때 호출된다.

지역 객체:

```cpp
Player player;
```

블록이 끝나면 자동으로 소멸한다.

동적 객체:

```cpp
Player* player = new Player();
```

`new`로 객체를 생성하고 주소를 반환받는다.

삭제:

```cpp
delete player;
```

동적 객체의 수명을 끝내고 저장공간을 해제한다.

삭제 후:

```cpp
player = nullptr;
```

더 이상 유효한 객체를 가리키지 않는 상태로 만든다.

동적 배열:

```cpp
int* numbers = new int[5];
```

해제:

```cpp
delete[] numbers;
```

---

# 최종 정리

```text
생성자

Player()

└─ 객체 생성 시 자동 호출
└─ 객체 초기화
```

```text
소멸자

~Player()

└─ 객체 수명 종료 시 자동 호출
└─ 자원 정리에 사용
```

```text
지역 객체

Player player;

└─ 블록 종료 시 자동 소멸
```

```text
동적 객체

Player* player = new Player();

└─ new로 생성
└─ 객체 주소 반환
└─ 포인터로 관리
```

```text
delete

delete player;

└─ 소멸자 호출
└─ 객체 수명 종료
└─ 저장공간 해제
```

```text
new / delete

new
↔ delete

new[]
↔ delete[]
```

```text
Dangling Pointer

delete 후에도 포인터 변수에 예전 주소가 남아있을 수 있음

└─ 객체는 이미 소멸
└─ 역참조하면 안 됨
```

```text
Memory Leak

new로 자원 확보
↓
delete하지 않음
↓
사용할 수 없는 메모리가 계속 남을 수 있음
```

---

# 가장 중요한 내용

```text
포인터의 수명
≠
포인터가 가리키는 객체의 수명
```

그리고:

```text
객체를 누가 만들었는가?

객체는 언제 생성되는가?

객체는 언제 사라지는가?

누가 객체를 정리해야 하는가?

현재 포인터가 가리키는 객체는 아직 살아있는가?
```

를 생각하는 것이 중요하다.

현대 C++에서는 직접 `new/delete`를 많이 사용하는 것보다 객체의 수명과 RAII를 이용해 자원을 자동으로 관리하는 방식을 우선한다.