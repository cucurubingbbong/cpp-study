# 포인터 / 주소 / nullptr / 변수 수명

## 변수와 메모리 주소

변수는 실제로 메모리 어딘가에 저장된다.

```cpp
int number = 10;
```

`number`라는 변수는 값 `10`을 가지고 있고, 메모리 안의 특정 위치에 존재한다.

개념적으로 보면:

```text
메모리 주소      값
-------------------
0x1000          ...
0x1004          10   ← number
0x1008          ...
```

실제 주소값은 실행할 때마다 달라질 수 있다.

---

# 주소값

변수 앞에 `&`를 붙이면 해당 변수의 주소를 가져올 수 있다.

```cpp
int number = 10;

std::cout << number << '\n';
std::cout << &number << '\n';
```

예:

```text
10
0x000000123456
```

정리:

```text
number
└─ number에 저장된 값

&number
└─ number가 존재하는 메모리 주소
```

---

# 포인터

포인터는 **메모리 주소를 저장하는 변수**이다.

```cpp
int number = 10;

int* ptr = &number;
```

여기서:

```cpp
int* ptr
```

은 `int`형 변수를 가리킬 수 있는 포인터이다.

```cpp
ptr = &number;
```

을 통해 `number`의 주소를 `ptr`에 저장한다.

구조:

```text
number

주소 : 0x1000
값   : 10

        ▲
        │
        │ 가리킴
        │

ptr

값 : 0x1000
```

즉:

```text
number
└─ 10

&number
└─ number의 주소

ptr
└─ number의 주소
```

따라서:

```cpp
std::cout << &number << '\n';
std::cout << ptr << '\n';
```

두 값은 같은 주소가 나온다.

---

# 포인터 자신의 주소

포인터도 하나의 변수이기 때문에 자기 자신의 주소를 가지고 있다.

```cpp
int number = 10;
int* ptr = &number;

std::cout << &number << '\n';
std::cout << ptr << '\n';
std::cout << &ptr << '\n';
```

개념적으로:

```text
number

주소 : 0x1000
값   : 10


ptr

주소 : 0x2000
값   : 0x1000
```

따라서:

```text
&number
= 0x1000

ptr
= 0x1000

&ptr
= 0x2000
```

이다.

즉:

```text
ptr
└─ ptr 안에 저장된 주소

&ptr
└─ ptr 변수 자체의 주소
```

는 서로 다른 개념이다.

---

# 역참조

포인터가 가리키는 주소에 저장된 실제 값에 접근하려면 `*`를 사용한다.

```cpp
int number = 10;
int* ptr = &number;

std::cout << *ptr;
```

결과:

```text
10
```

`*ptr`은:

> ptr에 저장된 주소로 이동해서 그곳에 저장된 값을 가져온다.

라는 의미이다.

정리:

```text
number
└─ 10

&number
└─ number의 주소

ptr
└─ number의 주소

*ptr
└─ ptr이 가리키는 곳의 실제 값
└─ 10

&ptr
└─ ptr 변수 자신의 주소
```

---

# 포인터를 이용한 원본 수정

포인터를 역참조하면 원본 값을 수정할 수도 있다.

```cpp
int number = 10;

int* ptr = &number;

*ptr = 50;

std::cout << number;
```

결과:

```text
50
```

왜냐하면:

```cpp
*ptr = 50;
```

은:

> ptr이 가리키는 주소에 `50`을 저장해라.

라는 뜻이기 때문이다.

구조:

```text
변경 전

ptr
 │
 ▼
number = 10
```

```text
*ptr = 50
```

```text
변경 후

ptr
 │
 ▼
number = 50
```

---

# `*`의 두 가지 의미

`*`는 위치에 따라 의미가 다르다.

## 포인터 선언

```cpp
int* ptr;
```

여기서 `*`는:

> ptr은 `int`를 가리키는 포인터이다.

라는 의미이다.

## 역참조

```cpp
*ptr
```

여기서 `*`는:

> ptr이 가리키는 주소의 실제 값에 접근한다.

라는 의미이다.

정리:

```text
int* ptr
└─ 포인터 선언

*ptr
└─ 역참조
```

---

# `&`의 두 가지 의미

`&`도 위치에 따라 의미가 다르다.

## 주소 가져오기

```cpp
&number
```

의미:

> number의 주소를 가져온다.

## 참조 선언

```cpp
int& ref = number;
```

의미:

> ref를 number의 참조로 만든다.

즉:

```text
&number
└─ 주소 연산자

int& ref
└─ 참조 타입 선언
```

같은 기호지만 문맥에 따라 의미가 다르다.

---

# 포인터 타입

포인터에도 어떤 자료형을 가리키는지 타입이 존재한다.

```cpp
int number = 10;
int* intPtr = &number;
```

```cpp
double value = 3.14;
double* doublePtr = &value;
```

```cpp
char letter = 'A';
char* charPtr = &letter;
```

정리:

```text
int*
└─ int를 가리키는 포인터

double*
└─ double을 가리키는 포인터

char*
└─ char를 가리키는 포인터
```

---

# 초기화되지 않은 포인터

다음처럼 포인터를 선언만 하고 사용하면 위험하다.

```cpp
int* ptr;

*ptr = 100;
```

`ptr`에 어떤 주소가 들어있는지 알 수 없기 때문이다.

개념적으로:

```text
ptr = 알 수 없는 주소
```

상태에서:

```cpp
*ptr
```

을 사용하면 알 수 없는 메모리 위치에 접근하게 된다.

따라서 포인터는 선언할 때 가능한 한 초기화하는 것이 좋다.

---

# nullptr

포인터가 현재 아무것도 가리키지 않을 때 `nullptr`을 사용한다.

```cpp
int* ptr = nullptr;
```

의미:

```text
ptr
└─ 현재 유효한 객체를 가리키고 있지 않음
```

개념적으로:

```text
ptr
┌───────────┐
│ nullptr   │
└───────────┘
```

현대 C++에서는 포인터가 비어있는 상태를 표현할 때 `nullptr`을 사용한다.

예전 코드에서는:

```cpp
NULL
```

또는:

```cpp
0
```

을 사용하기도 했지만 현재는 `nullptr`을 사용하는 것이 좋다.

---

# nullptr 역참조

`nullptr`은 아무것도 가리키지 않기 때문에 역참조하면 안 된다.

잘못된 코드:

```cpp
int* ptr = nullptr;

std::cout << *ptr;
```

현재 상태:

```text
ptr
└─ 아무것도 가리키지 않음

*ptr
└─ 가리키는 곳의 값을 가져오려고 함

하지만 가리키는 곳이 없음
```

잘못된 메모리 접근이 발생할 수 있다.

---

# nullptr 검사

포인터를 사용하기 전에 `nullptr`인지 확인할 수 있다.

```cpp
int* ptr = nullptr;

if (ptr != nullptr)
{
    std::cout << *ptr;
}
```

또는:

```cpp
if (ptr)
{
    std::cout << *ptr;
}
```

처럼 사용할 수도 있다.

조건문에서는:

```text
nullptr
└─ false

유효한 주소
└─ true
```

처럼 처리된다.

처음에는 의미가 명확한:

```cpp
if (ptr != nullptr)
```

형태를 사용해도 된다.

---

# 참조와 포인터 비교

참조:

```cpp
int number = 10;

int& ref = number;

ref = 20;
```

결과:

```text
number = 20
```

포인터:

```cpp
int number = 10;

int* ptr = &number;

*ptr = 20;
```

결과:

```text
number = 20
```

둘 다 원본에 접근할 수 있지만 사용 방식이 다르다.

| 참조 | 포인터 |
| --- | --- |
| 원본의 별명 같은 개념 | 주소를 저장하는 변수 |
| `int& ref` | `int* ptr` |
| `ref = 10` | `*ptr = 10` |
| 일반 변수처럼 사용 | 역참조가 필요함 |
| 보통 유효한 대상이 필요함 | `nullptr`일 수 있음 |
| 다른 대상을 다시 참조하는 용도로 사용하지 않음 | 다른 주소로 변경 가능 |

포인터는 가리키는 대상을 바꿀 수 있다.

```cpp
int a = 10;
int b = 20;

int* ptr = &a;

ptr = &b;
```

처음:

```text
ptr → a
```

변경 후:

```text
ptr → b
```

---

# 포인터를 함수에 전달하기

포인터를 함수의 매개변수로 사용할 수도 있다.

```cpp
void Change(int* ptr)
{
    *ptr = 100;
}

int main()
{
    int number = 10;

    Change(&number);

    std::cout << number;
}
```

결과:

```text
100
```

실행 과정:

```text
number = 10
```

```cpp
Change(&number);
```

`number`의 주소를 함수에 전달한다.

```cpp
void Change(int* ptr)
```

포인터가 주소를 받는다.

```cpp
*ptr = 100;
```

해당 주소의 값을 수정한다.

결과:

```text
number = 100
```

---

# 참조 전달과 포인터 전달 비교

참조 전달:

```cpp
void Change(int& number)
{
    number = 100;
}

int number = 10;

Change(number);
```

포인터 전달:

```cpp
void Change(int* number)
{
    *number = 100;
}

int number = 10;

Change(&number);
```

정리:

```text
참조 전달

Change(number)
└─ 함수에서 int&로 받음
└─ 일반 변수처럼 사용
```

```text
포인터 전달

Change(&number)
└─ 주소를 전달
└─ 함수에서 int*로 받음
└─ *를 사용해 원본 접근
```

---

# 변수 수명

변수는 항상 프로그램 시작부터 끝까지 존재하는 것이 아니다.

변수가 실제로 존재하는 기간을 **수명(Lifetime)**이라고 한다.

예:

```cpp
void Test()
{
    int number = 10;
}
```

실행 과정:

```text
Test 함수 호출
    ↓
number 생성
    ↓
함수 실행
    ↓
Test 함수 종료
    ↓
number 소멸
```

즉 `number`는 `Test()` 함수가 실행되는 동안만 존재한다.

---

# 지역 변수의 수명

지역 변수는 자신이 선언된 블록을 벗어나면 소멸한다.

```cpp
int main()
{
    int a = 10;

    {
        int b = 20;
    }

    return 0;
}
```

실행 과정:

```text
main 시작

a 생성
│
├─ 내부 블록 시작
│
│  b 생성
│
│  b 사용
│
│  b 소멸
│
└─ 내부 블록 종료

a 계속 사용 가능

a 소멸

main 종료
```

`b`는 내부 `{ }`가 끝나는 순간 소멸한다.

---

# Scope와 Lifetime

`Scope`와 `Lifetime`은 비슷해 보이지만 다른 개념이다.

## Scope

```text
변수 이름을 어디에서 사용할 수 있는가?
```

## Lifetime

```text
변수가 실제로 언제부터 언제까지 존재하는가?
```

일반 지역 변수의 경우에는 대부분 둘이 비슷하게 움직인다.

```cpp
{
    int number = 10;
}
```

블록 밖에서는:

```text
number라는 이름 사용 불가능
+
number 객체도 이미 소멸
```

상태가 된다.

---

# Dangling Pointer

포인터가 가리키던 객체의 수명이 끝났는데 포인터에는 예전 주소가 남아있는 상태를 **Dangling Pointer**라고 한다.

예:

```cpp
int* ptr = nullptr;

{
    int number = 10;

    ptr = &number;
}
```

블록 안에서는:

```text
ptr
 ↓
number = 10
```

으로 정상이다.

하지만 블록이 끝나면:

```text
number 소멸
```

한다.

그런데 `ptr`에는 예전에 `number`가 존재했던 주소가 남아 있을 수 있다.

```text
ptr
 ↓
예전 number의 주소

하지만 number는 이미 존재하지 않음
```

이 상태가 dangling pointer이다.

---

# Dangling Pointer 사용

잘못된 코드:

```cpp
int* ptr = nullptr;

{
    int number = 10;

    ptr = &number;

    std::cout << *ptr << '\n';
}

std::cout << *ptr << '\n';
```

첫 번째:

```cpp
std::cout << *ptr;
```

은 안전하다.

이 시점에는 `number`가 아직 살아있기 때문이다.

하지만 두 번째:

```cpp
std::cout << *ptr;
```

은 안전하지 않다.

이미:

```text
number 소멸
```

상태이기 때문이다.

이때 `ptr`은:

```text
nullptr X
유효한 포인터 X
dangling pointer O
```

이다.

---

# nullptr과 dangling pointer 차이

## nullptr

```cpp
int* ptr = nullptr;
```

의미:

```text
아무것도 가리키지 않는다고 명확하게 표시된 상태
```

## dangling pointer

```text
주소 값은 가지고 있음

하지만 그 주소에 존재하던 객체의 수명이 이미 끝남
```

즉:

```text
nullptr
└─ 주소 없음

dangling pointer
└─ 주소는 있음
└─ 하지만 유효한 객체가 없음
```

중요한 점:

```cpp
if (ptr != nullptr)
```

검사만으로 dangling pointer를 알아낼 수 있는 것은 아니다.

dangling pointer는 `nullptr`이 아니기 때문이다.

---

# 지역 변수의 주소를 함수에서 반환하면 안 되는 이유

잘못된 예:

```cpp
int* GetNumber()
{
    int number = 10;

    return &number;
}
```

실행 과정:

```text
GetNumber 호출
    ↓
number 생성
    ↓
number 주소 반환
    ↓
GetNumber 종료
    ↓
number 소멸
    ↓
반환된 포인터는 죽은 객체의 주소를 가지고 있음
```

사용:

```cpp
int* ptr = GetNumber();

std::cout << *ptr;
```

`ptr`은 dangling pointer가 된다.

함수 내부의 일반 지역 변수는 함수가 끝나면 소멸하기 때문이다.

---

# Undefined Behavior

수명이 끝난 객체를 포인터로 접근하는 등의 잘못된 메모리 사용은 **Undefined Behavior**를 발생시킬 수 있다.

Undefined Behavior는:

> 프로그램이 어떻게 동작할지 C++에서 보장하지 않는 상태

이다.

예를 들어:

```cpp
std::cout << *danglingPtr;
```

을 실행했을 때:

```text
예전 값이 우연히 출력될 수도 있음

이상한 값이 출력될 수도 있음

프로그램이 종료될 수도 있음

다른 이상 동작이 발생할 수도 있음
```

즉:

```text
에러가 반드시 발생한다
```

는 뜻이 아니다.

오히려 정상처럼 보일 수도 있어서 위험하다.

---

# static 지역 변수의 수명

일반 지역 변수:

```cpp
void Test()
{
    int count = 0;

    count++;

    std::cout << count << '\n';
}
```

호출:

```cpp
Test();
Test();
Test();
```

결과:

```text
1
1
1
```

매번:

```text
count 생성
↓
0
↓
1
↓
함수 종료
↓
count 소멸
```

하기 때문이다.

---

## static 변수

```cpp
void Test()
{
    static int count = 0;

    count++;

    std::cout << count << '\n';
}
```

호출:

```cpp
Test();
Test();
Test();
```

결과:

```text
1
2
3
```

`static` 지역 변수는 함수가 끝나도 소멸하지 않는다.

```text
첫 호출
count 생성
↓
1

함수 종료
↓
count 유지

두 번째 호출
↓
2

세 번째 호출
↓
3
```

정리:

```text
Scope
└─ Test 함수 내부

Lifetime
└─ 프로그램 종료까지
```

즉 `static` 변수는 Scope와 Lifetime이 서로 다를 수 있다는 예이다.

---

# 동적 수명

포인터를 이용해 동적으로 객체를 만들 수도 있다.

```cpp
int* ptr = new int(10);
```

이 경우 `int` 객체가 동적으로 생성된다.

```text
ptr
 ↓
동적으로 생성된 int = 10
```

동적으로 생성한 객체는:

```cpp
delete ptr;
```

을 통해 직접 소멸시킬 수 있다.

```cpp
int* ptr = new int(10);

delete ptr;
ptr = nullptr;
```

`delete`를 실행하면 객체의 수명이 끝난다.

단, `delete`를 했다고 포인터 변수 자체가 자동으로 `nullptr`이 되는 것은 아니다.

따라서:

```cpp
delete ptr;
ptr = nullptr;
```

처럼 사용하는 경우가 많다.

현대 C++에서는 직접 `new`, `delete`를 남발하기보다:

```text
std::vector
std::string
std::unique_ptr
std::shared_ptr
```

같은 자동 자원 관리 방식을 많이 사용한다.

---

# delete와 일반 변수 주소

다음과 같은 포인터는:

```cpp
int number = 10;

int* ptr = &number;
```

`number`를 가리킬 뿐이다.

이 경우:

```cpp
delete ptr;
```

을 하면 안 된다.

`number`는 `new`를 이용해 생성한 객체가 아니기 때문이다.

즉:

```text
포인터
= 주소를 저장하는 변수

포인터라고 해서
= 무조건 delete 해야 하는 것은 아님
```

이다.

---

# 전체 관계 정리

```cpp
int number = 10;
int* ptr = &number;
```

현재 상태:

```text
number
└─ 10

&number
└─ number의 주소

ptr
└─ number의 주소

*ptr
└─ ptr이 가리키는 곳의 값
└─ 10

&ptr
└─ ptr 변수 자신의 주소
```

그림:

```text
주소 0x1000                      주소 0x2000

number                           ptr
┌──────────┐                    ┌──────────┐
│    10    │ ◀───────────────── │  0x1000  │
└──────────┘                    └──────────┘
```

따라서:

```text
number  = 10

&number = 0x1000

ptr     = 0x1000

*ptr    = 10

&ptr    = 0x2000
```

이다.

---

# 핵심 문법 정리

```cpp
int number = 10;
```

일반 변수 선언.

```cpp
&number
```

`number`의 주소를 가져온다.

```cpp
int* ptr;
```

`int`를 가리키는 포인터를 선언한다.

```cpp
ptr = &number;
```

`number`의 주소를 `ptr`에 저장한다.

```cpp
*ptr
```

`ptr`이 가리키는 곳의 값을 읽는다.

```cpp
*ptr = 50;
```

`ptr`이 가리키는 원본의 값을 변경한다.

```cpp
&ptr
```

포인터 변수 `ptr` 자체의 주소를 가져온다.

```cpp
int* ptr = nullptr;
```

현재 아무것도 가리키지 않는 포인터를 만든다.

---

# 최종 정리

```text
변수

int number = 10;

number
└─ 값

&number
└─ 변수의 주소
```

```text
포인터

int* ptr = &number;

ptr
└─ 저장된 주소

*ptr
└─ 그 주소에 있는 값

&ptr
└─ 포인터 변수 자체의 주소
```

```text
nullptr

int* ptr = nullptr;

└─ 아무것도 가리키지 않는 상태
└─ 역참조하면 안 됨
```

```text
Dangling Pointer

└─ 주소는 가지고 있음
└─ 하지만 가리키던 객체의 수명이 끝남
└─ 역참조하면 안 됨
```

```text
변수 수명

일반 지역 변수
└─ 선언된 블록을 빠져나가면 소멸

static 지역 변수
└─ 프로그램 종료까지 유지

동적 객체
└─ new로 생성
└─ delete할 때 수명 종료
```

---

# 가장 중요한 안전 규칙

```text
1. 초기화되지 않은 포인터를 사용하지 않는다.

2. nullptr을 역참조하지 않는다.

3. 수명이 끝난 객체를 가리키는 포인터를 사용하지 않는다.

4. 일반 지역 변수의 주소를 함수 밖에서 계속 사용하지 않는다.

5. 포인터가 nullptr이 아니라고 해서 항상 안전한 것은 아니다.

6. 포인터가 가리키는 객체가 아직 살아있는지 확인해야 한다.

7. new로 만들지 않은 객체에 delete를 사용하지 않는다.
```

가장 핵심적으로 기억할 것:

```text
ptr
= 주소

*ptr
= 그 주소의 값

&ptr
= 포인터 변수 자신의 주소
```