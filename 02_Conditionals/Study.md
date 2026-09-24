# 조건문

## 종류

C++ 조건문은 크게 `if문`과 `switch문`이 있다.

### if문

조건식이 참이면 실행한다.

```cpp
if (조건식)
{
    // 실행할 코드
}
```

조건을 여러 개 나눌 때는 `else if`, `else`를 사용한다.

```cpp
if (조건식1)
{
    
}
else if (조건식2)
{
    
}
else
{
    
}
```

---

### switch문

하나의 값을 여러 경우와 비교할 때 사용한다.

```cpp
switch (값)
{
case 1:
    break;

case 2:
    break;

default:
    break;
}
```

`switch`문에는 `std::string`을 바로 넣을 수 없다.

보통 다음과 같은 값들을 비교할 때 사용한다.

* 정수형
* `char`
* `enum`

```cpp
char input = 'A';

switch (input)
{
case 'A':
    break;

case 'B':
    break;
}
```

`break`를 안 쓰면 다음 `case`까지 계속 실행된다.

```cpp
switch (value)
{
case 1:
    // 실행

case 2:
    // case 1이면 여기도 실행됨
    break;
}
```

---

# 비교 연산자

| 연산자  | 의미     |
| ---- | ------ |
| `==` | 같다     |
| `!=` | 다르다    |
| `<`  | 작다     |
| `>`  | 크다     |
| `<=` | 작거나 같다 |
| `>=` | 크거나 같다 |

예:

```cpp
if (hp == 100)
{
    
}

if (age >= 20)
{
    
}
```

주의:

```cpp
=
```

은 대입 연산자이고

```cpp
==
```

은 비교 연산자이다.

---

# 논리 연산자

## &&

AND 연산자.

앞뒤 조건이 **둘 다 참**이어야 `true`.

```cpp
if (age >= 20 && money >= 10000)
{
    
}
```

```text
true && true   → true
true && false  → false
false && true  → false
false && false → false
```

---

## ||

OR 연산자.

앞뒤 조건 중 **하나라도 참**이면 `true`.

```cpp
if (job == 1 || job == 2)
{
    
}
```

```text
true || true   → true
true || false  → true
false || true  → true
false || false → false
```

---

## !

NOT 연산자.

참과 거짓을 뒤집는다.

```cpp
bool isDead = false;

if (!isDead)
{
    
}
```

```text
!true  → false
!false → true
```

---

# 정리

```text
조건문

if
 └─ 조건식으로 분기

switch
 └─ 하나의 값을 여러 case와 비교
 └─ string 직접 사용 불가능
 └─ 정수형, char, enum 등에 사용


비교 연산자

==   같다
!=   다르다
<    작다
>    크다
<=   작거나 같다
>=   크거나 같다


논리 연산자

&&   둘 다 참
||   하나라도 참
!    참 / 거짓 반전
```
