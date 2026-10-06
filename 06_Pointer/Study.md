# 값 전달 / 참조 전달 / const

## 값 전달

값 전달은 함수에 변수를 넘길 때 **원본 변수가 아니라 값의 복사본을 전달하는 방식**이다.

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

출력:

```text
10
```

`Change(value)`를 호출하면 `value` 자체가 넘어가는 것이 아니라 현재 값인 `10`이 복사된다.

```text
main

value
┌──────┐
│  10  │
└──────┘
    │
    │ 값 복사
    ▼

Change

number
┌──────┐
│  10  │
└──────┘
```

따라서 함수 내부에서:

```cpp
number = 100;
```

을 실행해도:

```text
value = 10
number = 100
```

으로 서로 다른 변수가 된다.

함수가 끝나면 함수 내부의 `number`는 사라진다.

### 값 전달 특징

- 원본의 값이 복사된다.
- 함수 내부에서 값을 수정해도 원본에는 영향을 주지 않는다.
- `int`, `float`, `double`, `char`, `bool` 같은 작은 자료형에서 자주 사용한다.

예:

```cpp
int Add(int a, int b)
{
    return a + b;
}
```

`a`, `b`는 각각 전달받은 값의 복사본이다.

---

## 참조 전달

참조 전달은 함수가 **복사본이 아니라 원본 변수를 직접 참조하는 방식**이다.

자료형 뒤에 `&`를 붙인다.

```cpp
void Change(int& number)
{
    number = 100;
}
```

사용:

```cpp
int main()
{
    int value = 10;

    Change(value);

    std::cout << value;
}
```

출력:

```text
100
```

참조 전달에서는 새로운 복사본을 만들지 않는다.

```text
        ┌───────┐
value → │  10   │
        └───────┘
            ▲
            │
number ─────┘
```

`value`와 함수의 `number`가 같은 데이터를 바라보는 형태이다.

따라서:

```cpp
number = 100;
```

을 실행하면 원본인:

```cpp
value
```

도 `100`으로 변경된다.

### 참조 전달 특징

- 값을 복사하지 않는다.
- 함수 내부에서 원본을 직접 수정할 수 있다.
- 원본 데이터를 변경해야 하는 함수에서 사용한다.

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

출력:

```text
110
```

`Heal()`에서 `hp`를 참조로 받았기 때문에 원본 체력이 변경된다.

---

## 값 전달과 참조 전달 비교

값 전달:

```cpp
void Test(int value)
```

```text
원본
 ↓
값 복사
 ↓
함수의 별도 변수
```

특징:

```text
복사 O
원본 수정 X
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

특징:

```text
복사 X
원본 수정 O
```

정리:

| 방식 | 코드 | 복사 | 원본 수정 |
|---|---|---|---|
| 값 전달 | `int value` | O | X |
| 참조 전달 | `int& value` | X | O |

---

## const

`const`는 **값을 변경할 수 없도록 만드는 키워드**이다.

```cpp
const int MAX_HP = 100;
```

이후에:

```cpp
MAX_HP = 200;
```

을 작성하면 컴파일 오류가 발생한다.

일반 변수는:

```cpp
int hp = 100;

hp = 50;
```

처럼 값을 변경할 수 있다.

하지만:

```cpp
const int hp = 100;

hp = 50;
```

은 불가능하다.

### const를 사용하는 이유

변경되면 안 되는 값을 실수로 수정하지 못하게 막기 위해 사용한다.

예:

```cpp
const int MAX_HP = 100;
const double PI = 3.141592;
```

---

## const 참조

`const`와 참조 `&`를 같이 사용할 수도 있다.

```cpp
void Print(const int& number)
{
    std::cout << number;
}
```

여기서:

```cpp
const int& number
```

을 나눠서 보면:

```text
int
→ 정수 자료형

&
→ 원본을 참조

const
→ 참조한 값을 수정하지 못함
```

즉:

> 원본을 복사하지 않고 참조하지만 함수 안에서는 원본을 수정하지 않겠다.

라는 의미이다.

다음 코드는 오류가 발생한다.

```cpp
void Print(const int& number)
{
    number = 100;
}
```

`number`가 `const`이기 때문에 수정할 수 없다.

---

## const 참조를 사용하는 이유

문자열을 함수에 전달한다고 해보자.

```cpp
void PrintName(std::string name)
{
    std::cout << name;
}
```

이 방식은 값 전달이기 때문에 `string` 전체가 복사된다.

```text
원본 문자열
      ↓
   전체 복사
      ↓
함수 내부 문자열
```

문자열이나 객체가 크다면 불필요한 복사가 발생할 수 있다.

복사를 피하기 위해 참조를 사용할 수 있다.

```cpp
void PrintName(std::string& name)
{
    std::cout << name;
}
```

이 경우 복사는 발생하지 않는다.

하지만 함수 내부에서:

```cpp
name = "Changed";
```

처럼 원본을 수정할 수 있다는 문제가 있다.

단순히 값을 읽기만 할 목적이라면 `const`를 추가한다.

```cpp
void PrintName(const std::string& name)
{
    std::cout << name;
}
```

그러면:

```text
복사 X
원본 참조 O
원본 수정 X
```

가 된다.

즉 `const T&`는:

> 큰 데이터를 복사하지 않고 효율적으로 전달하면서 원본이 수정되는 것도 막고 싶을 때 사용한다.

---

## 작은 자료형과 큰 자료형

`int`, `float`, `double`, `char`, `bool` 같은 작은 자료형은 보통 그냥 값으로 전달한다.

```cpp
int Add(int a, int b)
{
    return a + b;
}
```

굳이:

```cpp
int Add(const int& a, const int& b)
```

처럼 사용할 필요가 거의 없다.

반대로:

```cpp
std::string
std::vector
struct
class
```

같은 데이터는 크기가 커질 수 있기 때문에 읽기만 할 경우 `const` 참조를 많이 사용한다.

예:

```cpp
void PrintName(const std::string& name)
{
    std::cout << name;
}
```

나중에 STL을 배우면 다음과 같은 코드도 자주 보게 된다.

```cpp
void PrintNumbers(const std::vector<int>& numbers)
{
}
```

의미:

```text
vector를 복사하지 않음
원본 vector를 참조함
함수 안에서 vector를 수정하지 못함
```

---

## struct / class에서의 사용 예시

```cpp
struct Player
{
    std::string name;
    int hp;
};
```

Player의 체력을 수정해야 한다면:

```cpp
void Heal(Player& player)
{
    player.hp += 10;
}
```

`Player&`를 사용한다.

이유:

```text
원본 Player를 수정해야 하기 때문
```

반대로 Player 정보를 출력만 한다면:

```cpp
void PrintPlayer(const Player& player)
{
    std::cout << player.name << '\n';
    std::cout << player.hp << '\n';
}
```

`const Player&`를 사용한다.

이유:

```text
Player 전체를 복사하지 않음
+
원본 Player를 수정하지 않음
```

---

## 세 가지 최종 비교

### 값 전달

```cpp
void Test(int value)
```

의미:

> 원본의 값을 복사해서 받는다.

```text
복사 O
원본 수정 X
```

예:

```cpp
void Change(int value)
{
    value = 100;
}
```

원본에는 영향을 주지 않는다.

---

### 참조 전달

```cpp
void Test(int& value)
```

의미:

> 원본 변수를 직접 참조한다.

```text
복사 X
원본 수정 O
```

예:

```cpp
void Change(int& value)
{
    value = 100;
}
```

원본 값도 변경된다.

---

### const 참조

```cpp
void Test(const int& value)
```

의미:

> 원본 변수를 직접 참조하지만 수정할 수 없다.

```text
복사 X
원본 수정 X
```

큰 데이터를 읽기만 할 경우 자주 사용한다.

예:

```cpp
void Print(const std::string& text)
{
    std::cout << text;
}
```

---

## 매개변수를 정하는 기준

함수에서 원본을 수정해야 한다면:

```cpp
T&
```

예:

```cpp
void Heal(Player& player)
```

원본을 수정하지 않지만 큰 데이터를 복사하고 싶지 않다면:

```cpp
const T&
```

예:

```cpp
void PrintPlayer(const Player& player)
```

`int`, `float`, `bool` 같은 작은 값을 단순히 전달한다면:

```cpp
T
```

예:

```cpp
int Add(int a, int b)
```

정리:

```text
원본을 수정해야 하는가?

YES
→ T&

NO
↓
복사하기 부담스러운 큰 데이터인가?

YES
→ const T&

NO
→ T
```

---

# 핵심 정리

```cpp
void Test(int value)
```

값 전달

> 원본의 복사본

```cpp
void Test(int& value)
```

참조 전달

> 원본 자체를 참조하며 수정 가능

```cpp
void Test(const int& value)
```

const 참조

> 원본 자체를 참조하지만 수정 불가능

가장 중요하게 기억할 것:

```text
T
= 값 복사

T&
= 원본 참조 + 수정 가능

const T&
= 원본 참조 + 수정 불가능
```