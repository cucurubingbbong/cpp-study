# 함수

## 함수란?

특정 기능을 수행하는 **코드 묶음**.

C++ 프로그램의 기본 시작점은 `main()` 함수이다.

```cpp
int main()
{
    return 0;
}
```

---

# 함수의 기본 구조

```cpp
반환형 함수이름(매개변수)
{
    실행할 코드
}
```

예:

```cpp
int Add(int a, int b)
{
    return a + b;
}
```

각 부분:

```text
int      → 반환형
Add      → 함수명
a, b     → 매개변수
return   → 반환값
```

---

## return

`return`은 값을 **함수를 호출한 곳으로 돌려준다.**

```cpp
int Add(int a, int b)
{
    return a + b;
}
```

```cpp
int result = Add(10, 20);
```

결과:

```text
result = 30
```

반환값을 바로 사용할 수도 있다.

```cpp
std::cout << Add(10, 20);
```

결과:

```text
30
```

`return`을 만나는 순간 해당 함수는 종료된다.

```cpp
int Test()
{
    return 10;

    std::cout << "실행되지 않음";
}
```

반환형은 실제 반환하는 값의 타입과 맞아야 한다.

```cpp
int GetNumber()
{
    return 10;
}
```

---

# void

`void`는 **반환값이 없는 함수**에서 사용한다.

```cpp
void Hello()
{
    std::cout << "Hello\n";
}
```

호출:

```cpp
Hello();
```

---

# 매개변수

매개변수는 함수가 사용할 데이터를 **외부에서 받아오는 공간**이다.

```cpp
void PrintNumber(int number)
{
    std::cout << number;
}
```

```cpp
PrintNumber(10);
```

여러 개를 받을 수도 있다.

```cpp
int Add(int a, int b)
{
    return a + b;
}
```

```cpp
Add(10, 20);
```

---

# 스코프

함수 내부에서 만든 변수는 기본적으로 **해당 함수 내부에서만 사용할 수 있다.**

```cpp
void Test()
{
    int number = 10;
}
```

```cpp
int main()
{
    Test();

    // number 사용 불가능
}
```

이런 변수의 유효 범위를 **스코프(scope)** 라고 한다.

---

# 값 전달

일반적인 매개변수는 값을 **복사해서 전달받는다.**

```cpp
void Change(int number)
{
    number = 100;
}
```

```cpp
int value = 10;

Change(value);
```

`Change()` 내부의 `number`를 수정해도 원본 `value`는 바뀌지 않는다.

```text
value = 10
```

---

# 참조 전달

`&`를 사용하면 참조로 받을 수 있다.

```cpp
void Change(int& number)
{
    number = 100;
}
```

```cpp
int value = 10;

Change(value);
```

결과:

```text
value = 100
```

차이:

```text
int number
 └─ 값을 복사해서 전달

int& number
 └─ 원본 변수를 참조
```

참조는 추후 따로 정리.

---

# const 참조

```cpp
void PrintName(const std::string& name)
{
    std::cout << name << '\n';
}
```

각 부분:

```text
std::string  → 문자열 타입
&            → 참조
const        → 함수 내부에서 수정하지 않음
```

즉:

```cpp
const std::string& name
```

은

> 원본 문자열을 복사하지 않고 참조해서 받아오되, 함수 안에서는 수정하지 않는다.

라는 의미.

특히 `std::string`처럼 데이터가 큰 타입은 값으로 전달하면 복사 비용이 발생할 수 있다.

```cpp
void PrintName(std::string name)
```

```text
원본 string
   ↓
복사
   ↓
매개변수 name
```

반면 참조를 사용하면:

```cpp
void PrintName(const std::string& name)
```

```text
원본 string
   ↑
name이 참조
```

복사 없이 기존 객체를 참조할 수 있다.

---

# 함수의 선언과 정의

예:

```cpp
#include <iostream>

void Hello();

int main()
{
    Hello();

    return 0;
}

void Hello()
{
    std::cout << "Hello\n";
}
```

---

## 전방선언

```cpp
void Hello();
```

컴파일러에게

> `Hello`라는 함수가 존재한다.

라고 미리 알려주는 것.

함수 선언 또는 **함수 원형(Function Prototype)** 이라고 한다.

---

## 정의

```cpp
void Hello()
{
    std::cout << "Hello\n";
}
```

함수가 실제로 무엇을 하는지 작성하는 부분.

정리:

```text
선언
 └─ 함수가 존재한다는 것을 알려줌

정의
 └─ 함수가 실제로 수행할 코드 작성
```

---

# 함수 오버로딩

같은 이름의 함수를 여러 개 만들 수 있다.

단, **매개변수 구성이 달라야 한다.**

```cpp
int Add(int a, int b)
{
    return a + b;
}

double Add(double a, double b)
{
    return a + b;
}
```

호출:

```cpp
Add(10, 20);
```

```text
int Add(int, int)
```

호출:

```cpp
Add(10.5, 20.5);
```

```text
double Add(double, double)
```

컴파일러가 전달된 인자의 타입 등을 보고 어떤 함수를 호출할지 결정한다.

---

## 반환형만 다른 경우

이건 안 된다.

```cpp
int Test()
{
    return 10;
}

double Test()
{
    return 10.0;
}
```

함수 오버로딩은 **반환형이 아니라 매개변수 차이**로 구분한다.

---

# 기본 매개변수

매개변수에 기본값을 지정할 수 있다.

```cpp
void Attack(int damage = 10)
{
    std::cout << damage << " 데미지!\n";
}
```

파라미터 없이 호출:

```cpp
Attack();
```

결과:

```text
10 데미지!
```

값을 직접 넣어서 호출:

```cpp
Attack(50);
```

결과:

```text
50 데미지!
```

즉:

```text
Attack()
 └─ 기본값 사용

Attack(50)
 └─ 전달한 값 사용
```

여러 매개변수에서 기본값을 사용할 경우 기본값이 있는 매개변수는 보통 뒤쪽부터 둔다.

```cpp
void Attack(int damage, int critical = 0)
{
    
}
```

---

# 정리

```text
함수
 └─ 특정 기능을 수행하는 코드 묶음


기본 구조

반환형 함수명(매개변수)
{
    코드
}


return
 └─ 값을 호출한 곳으로 반환
 └─ return 실행 시 함수 종료


void
 └─ 반환값 없음


매개변수
 └─ 함수가 외부에서 데이터를 받는 공간


값 전달
 └─ 값을 복사해서 전달


참조 전달 &
 └─ 원본 변수를 참조


const 참조
 └─ 복사 없이 참조
 └─ 함수 내부에서 수정하지 않음


스코프
 └─ 변수를 사용할 수 있는 범위


함수 선언
 └─ 함수가 존재한다고 미리 알려줌


함수 정의
 └─ 함수의 실제 코드 작성


오버로딩
 └─ 같은 함수명 사용 가능
 └─ 매개변수 구성이 달라야 함


기본 매개변수
 └─ 인자를 생략하면 기본값 사용
 └─ 직접 넣으면 전달한 값 사용
```
