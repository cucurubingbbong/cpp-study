# 값 전달 / 참조 전달 / const

## 값 전달

값 전달은 함수에 값을 넘길 때 **원본이 아니라 값의 복사본을 전달하는 방식**이다.

```cpp
void Change(int number)
{
    number = 100;
}

int main()
{
    int value = 10;

    Change(value);

    std::cout << value;
}
```

결과:

```text
10
```

함수를 호출하면:

```cpp
Change(value);
```

`value` 자체가 넘어가는 것이 아니라 현재 값인 `10`이 복사된다.

```text
value = 10
    ↓ 복사
number = 10
```

따라서 함수 내부에서:

```cpp
number = 100;
```

으로 값을 변경해도:

```text
value = 10
number = 100
```

처럼 원본 `value`는 변하지 않는다.

보통 `int`, `float`, `double`, `char`, `bool`처럼 작은 값을 함수에 전달할 때 많이 사용한다.

---

# 참조 전달

참조 전달은 함수에 값을 넘길 때 **복사본을 만들지 않고 원본 변수를 직접 참조하는 방식**이다.

자료형 뒤에 `&`를 붙인다.

```cpp
void Change(int& number)
{
    number = 100;
}

int main()
{
    int value = 10;

    Change(value);

    std::cout << value;
}
```

결과:

```text
100
```

참조 전달에서는 `number`가 새로운 변수가 아니라 원본 `value`를 참조한다.

```text
        ┌───────┐
value → │  10   │
        └───────┘
           ↑
           │
number ────┘
```

따라서:

```cpp
number = 100;
```

을 실행하면 원본인 `value`도 같이 변경된다.

```text
value = 100
```

보통 **함수 안에서 원본 데이터를 직접 수정해야 할 때** 사용한다.

예:

```cpp
void Heal(int& hp)
{
    hp += 10;
}

int main()
{
    int hp = 100;

    Heal(hp);

    std::cout << hp;
}
```

결과:

```text
110
```

---

# 값 전달과 참조 전달 비교

| 방식 | 코드 | 값 복사 | 원본 수정 |
| --- | --- | --- | --- |
| 값 전달 | `int value` | O | X |
| 참조 전달 | `int& value` | X | O |

값 전달:

```cpp
void Test(int value)
```

```text
원본
 ↓
복사본 생성
 ↓
함수에서 복사본 사용
```

참조 전달:

```cpp
void Test(int& value)
```

```text
원본
 ↑
함수에서 직접 참조
```

---

# const

`const`는 **값을 변경할 수 없도록 만드는 키워드**이다.

```cpp
const int MAX_HP = 100;
```

`const`로 선언한 변수는 이후 값을 변경할 수 없다.

```cpp
MAX_HP = 200;
```

위 코드는 컴파일 오류가 발생한다.

일반 변수:

```cpp
int hp = 100;

hp = 50;
```

값 변경 가능.

`const` 변수:

```cpp
const int hp = 100;

hp = 50;
```

값 변경 불가능.

보통 **변경되면 안 되는 값을 실수로 수정하는 것을 막기 위해** 사용한다.

예:

```cpp
const int MAX_HP = 100;
const double PI = 3.141592;
```

---

# const 참조

`const`와 참조 `&`를 같이 사용할 수도 있다.

```cpp
void Print(const int& number)
{
    std::cout << number;
}
```

`const int&`를 나눠서 보면:

```text
int
 └─ 정수 자료형

&
 └─ 원본을 참조

const
 └─ 참조한 값을 수정할 수 없음
```

즉:

```text
복사하지 않고 원본을 참조하지만
함수 내부에서 원본을 수정할 수 없다.
```

다음 코드는 오류가 발생한다.

```cpp
void Print(const int& number)
{
    number = 100;
}
```

`number`가 `const`이기 때문에 값을 변경할 수 없다.

---

# const 참조를 사용하는 이유

문자열을 함수에 값으로 전달하면:

```cpp
void PrintName(std::string name)
{
    std::cout << name;
}
```

`name`에 원본 문자열의 복사본이 만들어진다.

```text
원본 문자열
    ↓ 복사
함수의 문자열
```

문자열이나 객체의 크기가 크다면 불필요한 복사가 발생할 수 있다.

복사를 피하려면 참조를 사용할 수 있다.

```cpp
void PrintName(std::string& name)
{
    std::cout << name;
}
```

하지만 일반 참조는 원본을 수정할 수 있다.

```cpp
name = "Changed";
```

따라서 **원본을 수정할 필요 없이 읽기만 할 경우** `const` 참조를 사용한다.

```cpp
void PrintName(const std::string& name)
{
    std::cout << name;
}
```

이 경우:

```text
복사 X
원본 참조 O
원본 수정 X
```

가 된다.

---

# 작은 자료형과 큰 자료형

`int`, `float`, `double`, `char`, `bool`처럼 작은 자료형은 보통 값 전달을 사용한다.

```cpp
int Add(int a, int b)
{
    return a + b;
}
```

반대로 `string`, `vector`, `struct`, `class`처럼 크기가 커질 수 있는 데이터는 읽기만 할 경우 `const` 참조를 많이 사용한다.

```cpp
void PrintName(const std::string& name)
{
    std::cout << name;
}
```

나중에 STL에서는 다음과 같은 코드도 많이 사용한다.

```cpp
void PrintNumbers(const std::vector<int>& numbers)
{
}
```

의미:

```text
vector 복사 X
원본 vector 참조 O
원본 vector 수정 X
```

---

# struct / class에서의 사용

예:

```cpp
struct Player
{
    std::string name;
    int hp;
};
```

원본 Player를 수정해야 한다면 참조 전달을 사용한다.

```cpp
void Heal(Player& player)
{
    player.hp += 10;
}
```

```text
Player&
 └─ 원본 Player를 직접 수정 가능
```

반대로 Player 정보를 읽기만 한다면 `const` 참조를 사용한다.

```cpp
void PrintPlayer(const Player& player)
{
    std::cout << player.name << '\n';
    std::cout << player.hp << '\n';
}
```

```text
const Player&
 └─ Player 복사 X
 └─ 원본 참조 O
 └─ 원본 수정 X
```

---

# 언제 무엇을 사용할까?

## 값 전달

```cpp
void Test(int value)
```

보통 작은 데이터를 단순히 전달할 때 사용한다.

```text
복사 O
원본 수정 X
```

---

## 참조 전달

```cpp
void Test(int& value)
```

함수에서 원본 값을 직접 수정해야 할 때 사용한다.

```text
복사 X
원본 수정 O
```

---

## const 참조

```cpp
void Test(const std::string& value)
```

큰 데이터를 복사하지 않고 읽기만 할 때 사용한다.

```text
복사 X
원본 수정 X
```

---

# 정리

```text
값 전달

T value
 └─ 원본 값을 복사해서 사용
 └─ 원본 수정 X
```

```text
참조 전달

T& value
 └─ 원본을 직접 참조
 └─ 복사 X
 └─ 원본 수정 O
```

```text
const 참조

const T& value
 └─ 원본을 직접 참조
 └─ 복사 X
 └─ 원본 수정 X
```

선택 기준:

```text
작은 값을 단순히 전달
 └─ T

원본을 직접 수정해야 함
 └─ T&

큰 데이터를 복사하지 않고 읽기만 함
 └─ const T&
```