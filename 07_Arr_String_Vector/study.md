# 배열 / string / vector

## 배열

배열은 **같은 자료형의 여러 값을 하나의 이름으로 묶어서 저장하는 구조**이다.

예를 들어 정수 5개를 각각 변수로 만들면:

```cpp
int a = 10;
int b = 20;
int c = 30;
int d = 40;
int e = 50;
```

처럼 작성해야 한다.

배열을 사용하면:

```cpp
int numbers[5] = { 10, 20, 30, 40, 50 };
```

처럼 하나의 이름으로 관리할 수 있다.

---

# 배열 선언

기본 형태:

```cpp
자료형 배열이름[크기];
```

예:

```cpp
int numbers[5];
```

의미:

```text
int 값을 저장할 수 있는 공간 5개 생성
```

구조:

```text
index     0     1     2     3     4
        ┌────┬────┬────┬────┬────┐
        │    │    │    │    │    │
        └────┴────┴────┴────┴────┘
```

배열의 크기는 선언할 때 정해지며 일반 배열의 크기는 이후 자동으로 늘어나지 않는다.

---

# 배열 초기화

배열을 만들면서 값을 넣을 수 있다.

```cpp
int numbers[5] = { 10, 20, 30, 40, 50 };
```

구조:

```text
index     0     1     2     3     4
        ┌────┬────┬────┬────┬────┐
value   │ 10 │ 20 │ 30 │ 40 │ 50 │
        └────┴────┴────┴────┴────┘
```

값의 개수가 명확하면 크기를 생략할 수도 있다.

```cpp
int numbers[] = { 10, 20, 30 };
```

컴파일러가 자동으로:

```text
크기 = 3
```

으로 판단한다.

---

# 배열 인덱스

배열의 각 요소에는 번호가 붙는다.

이 번호를 **인덱스(Index)**라고 한다.

중요:

```text
인덱스는 0부터 시작한다.
```

예:

```cpp
int numbers[5] = { 10, 20, 30, 40, 50 };
```

각 요소:

```text
numbers[0] → 10
numbers[1] → 20
numbers[2] → 30
numbers[3] → 40
numbers[4] → 50
```

첫 번째 값:

```cpp
std::cout << numbers[0];
```

결과:

```text
10
```

---

# 배열 값 변경

배열의 요소는 일반 변수처럼 변경할 수 있다.

```cpp
int numbers[3] = { 10, 20, 30 };

numbers[1] = 100;
```

결과:

```text
[10, 100, 30]
```

---

# 배열 범위

다음 배열:

```cpp
int numbers[5];
```

에서 사용할 수 있는 인덱스는:

```text
0
1
2
3
4
```

이다.

따라서:

```cpp
numbers[5] = 100;
```

은 잘못된 접근이다.

```text
numbers[0]
numbers[1]
numbers[2]
numbers[3]
numbers[4] ← 마지막 요소

numbers[5] ← 배열 밖
```

일반 배열은 범위를 자동으로 검사하지 않는다.

배열 범위를 벗어나 접근하면 **Undefined Behavior**가 발생할 수 있다.

```text
이상한 값이 나올 수도 있음
프로그램이 종료될 수도 있음
정상처럼 보일 수도 있음
```

따라서 항상 배열의 크기 안에서 접근해야 한다.

---

# 배열과 반복문

배열은 반복문과 같이 사용하는 경우가 많다.

```cpp
int numbers[5] = { 10, 20, 30, 40, 50 };

for (int i = 0; i < 5; i++)
{
    std::cout << numbers[i] << '\n';
}
```

실행 과정:

```text
i = 0 → numbers[0] → 10
i = 1 → numbers[1] → 20
i = 2 → numbers[2] → 30
i = 3 → numbers[3] → 40
i = 4 → numbers[4] → 50
```

출력:

```text
10
20
30
40
50
```

---

# Range-based for

배열의 모든 값을 하나씩 읽을 때 범위 기반 for문을 사용할 수 있다.

```cpp
int numbers[] = { 10, 20, 30 };

for (int number : numbers)
{
    std::cout << number << '\n';
}
```

실행:

```text
number = 10
number = 20
number = 30
```

결과:

```text
10
20
30
```

형태:

```cpp
for (자료형 변수 : 데이터)
{
}
```

의미:

```text
데이터 안의 요소를 하나씩 꺼내서 반복
```

---

# 배열 특징

```text
같은 자료형 여러 개 저장

크기 고정

인덱스는 0부터 시작

메모리에 연속적으로 저장

반복문과 같이 사용하는 경우가 많음
```

---

# string

`std::string`은 **문자열을 저장하고 쉽게 다루기 위한 C++ 표준 라이브러리 타입**이다.

사용하려면:

```cpp
#include <string>
```

을 포함한다.

예:

```cpp
std::string name = "Player";
```

---

# char와 string

문자 하나는 `char`를 사용한다.

```cpp
char grade = 'A';
```

문자열은 `std::string`을 사용한다.

```cpp
std::string name = "Alice";
```

차이:

```text
'A'
└─ char
└─ 문자 하나
└─ 작은따옴표

"Alice"
└─ string
└─ 문자열
└─ 큰따옴표
```

---

# string 입력

```cpp
std::string name;

std::cin >> name;
```

입력:

```text
Player
```

결과:

```text
name = "Player"
```

하지만:

```text
Kim Min Su
```

처럼 공백이 포함된 값을 입력하면 `std::cin >>`은 첫 번째 공백까지만 읽는다.

결과:

```text
Kim
```

한 줄 전체를 입력받으려면:

```cpp
std::getline(std::cin, name);
```

을 사용한다.

---

# string 인덱스 접근

`string`은 문자들의 묶음이기 때문에 배열처럼 인덱스로 접근할 수 있다.

```cpp
std::string text = "Hello";
```

구조:

```text
index    0    1    2    3    4
        ┌───┬───┬───┬───┬───┐
        │ H │ e │ l │ l │ o │
        └───┴───┴───┴───┴───┘
```

첫 번째 문자:

```cpp
std::cout << text[0];
```

결과:

```text
H
```

두 번째 문자:

```cpp
std::cout << text[1];
```

결과:

```text
e
```

---

# string 문자 변경

```cpp
std::string text = "Hello";

text[0] = 'Y';

std::cout << text;
```

결과:

```text
Yello
```

`text[0]`은 문자 하나이기 때문에:

```cpp
'Y'
```

처럼 작은따옴표를 사용한다.

---

# string 길이

문자열의 길이는:

```cpp
.size()
```

로 구할 수 있다.

```cpp
std::string text = "Hello";

std::cout << text.size();
```

결과:

```text
5
```

또는:

```cpp
text.length();
```

도 사용할 수 있다.

`string`에서는 `size()`와 `length()`가 같은 길이를 반환한다.

---

# 마지막 문자 접근

문자열의 마지막 인덱스는:

```text
문자열 길이 - 1
```

이다.

예:

```cpp
std::string text = "Hello";
```

길이는:

```text
5
```

마지막 인덱스는:

```text
5 - 1 = 4
```

따라서:

```cpp
std::cout << text[text.size() - 1];
```

결과:

```text
o
```

---

# 문자열 합치기

`string`은 `+`를 이용해서 문자열을 합칠 수 있다.

```cpp
std::string first = "Hello";
std::string second = "World";

std::string result = first + " " + second;

std::cout << result;
```

결과:

```text
Hello World
```

---

# 문자열 추가

기존 문자열 뒤에 내용을 추가할 수도 있다.

```cpp
std::string text = "Hello";

text += " World";
```

결과:

```text
Hello World
```

---

# 문자열 비교

`string`은 조건문에서 `==`, `!=` 등을 사용할 수 있다.

```cpp
std::string password;

std::cin >> password;

if (password == "1234")
{
    std::cout << "로그인 성공\n";
}
else
{
    std::cout << "비밀번호 오류\n";
}
```

---

# string 반복문

문자열 안에 있는 문자를 하나씩 확인할 수 있다.

```cpp
std::string text = "Hello";

for (char ch : text)
{
    std::cout << ch << '\n';
}
```

결과:

```text
H
e
l
l
o
```

예를 들어 특정 문자 개수를 구할 수도 있다.

```cpp
std::string text = "banana";

int count = 0;

for (char ch : text)
{
    if (ch == 'a')
    {
        count++;
    }
}

std::cout << count;
```

결과:

```text
3
```

---

# string 특징

```text
문자열을 쉽게 저장하고 관리

인덱스로 문자 접근 가능

size()로 문자열 길이 확인

+ 또는 += 로 문자열 연결 가능

==, != 등으로 문자열 비교 가능

반복문으로 각 문자 순회 가능
```

---

# vector

`std::vector`는 **같은 자료형의 값을 여러 개 저장하면서 크기를 동적으로 변경할 수 있는 STL 컨테이너**이다.

일반 배열과 비슷하지만 크기를 늘리거나 줄일 수 있다는 차이가 있다.

사용하려면:

```cpp
#include <vector>
```

를 포함한다.

기본 선언:

```cpp
std::vector<int> numbers;
```

의미:

```text
int를 여러 개 저장할 수 있는 vector
```

처음에는:

```text
[]
```

처럼 비어있다.

---

# vector 타입

`vector`의 `< >` 안에는 저장할 자료형을 넣는다.

정수:

```cpp
std::vector<int> numbers;
```

문자열:

```cpp
std::vector<std::string> names;
```

실수:

```cpp
std::vector<double> values;
```

정리:

```text
vector<int>
└─ int 여러 개 저장

vector<string>
└─ string 여러 개 저장

vector<double>
└─ double 여러 개 저장
```

---

# vector 초기화

```cpp
std::vector<int> numbers = { 10, 20, 30 };
```

구조:

```text
index     0     1     2
        ┌────┬────┬────┐
value   │ 10 │ 20 │ 30 │
        └────┴────┴────┘
```

배열과 마찬가지로 인덱스는 0부터 시작한다.

---

# push_back()

vector 맨 뒤에 값을 추가한다.

```cpp
std::vector<int> numbers;

numbers.push_back(10);
```

결과:

```text
[10]
```

추가:

```cpp
numbers.push_back(20);
numbers.push_back(30);
```

결과:

```text
[10, 20, 30]
```

---

# vector 인덱스 접근

배열처럼 인덱스를 사용할 수 있다.

```cpp
std::vector<int> numbers = { 10, 20, 30 };

std::cout << numbers[0];
```

결과:

```text
10
```

값 변경:

```cpp
numbers[1] = 100;
```

결과:

```text
[10, 100, 30]
```

---

# vector size()

vector에 현재 몇 개의 요소가 있는지 확인한다.

```cpp
std::vector<int> numbers = { 10, 20, 30 };

std::cout << numbers.size();
```

결과:

```text
3
```

반복문과 같이 사용할 수 있다.

```cpp
for (int i = 0; i < numbers.size(); i++)
{
    std::cout << numbers[i] << '\n';
}
```

---

# vector 반복문

범위 기반 for문을 사용할 수 있다.

```cpp
std::vector<int> numbers = { 10, 20, 30 };

for (int number : numbers)
{
    std::cout << number << '\n';
}
```

결과:

```text
10
20
30
```

---

# vector와 값 전달

다음 코드를 보면:

```cpp
std::vector<int> numbers = { 10, 20, 30 };

for (int number : numbers)
{
    number = 100;
}
```

`number`는 각 요소의 복사본이다.

따라서 원본 vector는 변경되지 않는다.

결과:

```text
[10, 20, 30]
```

---

# vector와 참조

원본 요소를 수정하려면 참조를 사용한다.

```cpp
std::vector<int> numbers = { 10, 20, 30 };

for (int& number : numbers)
{
    number = 100;
}
```

결과:

```text
[100, 100, 100]
```

이유:

```text
int number
└─ 복사본

int& number
└─ 원본 요소 참조
```

---

# const 참조 반복

값을 수정하지 않고 읽기만 할 경우:

```cpp
for (const int& number : numbers)
{
    std::cout << number << '\n';
}
```

처럼 사용할 수 있다.

특히 `string`, `class`, `struct`처럼 큰 데이터를 담는 vector에서 많이 사용한다.

예:

```cpp
std::vector<std::string> names = { "Kim", "Lee", "Park" };

for (const std::string& name : names)
{
    std::cout << name << '\n';
}
```

의미:

```text
복사 X
원본 참조 O
원본 수정 X
```

---

# pop_back()

vector의 마지막 요소를 삭제한다.

```cpp
std::vector<int> numbers = { 10, 20, 30 };

numbers.pop_back();
```

결과:

```text
[10, 20]
```

`pop_back()`은 마지막 요소를 삭제할 뿐 값을 반환하지 않는다.

---

# empty()

vector가 비어있는지 확인한다.

```cpp
std::vector<int> numbers;

if (numbers.empty())
{
    std::cout << "비어있음\n";
}
```

결과:

```text
비어있음
```

`empty()`는 `bool` 값을 반환한다.

```text
비어있음
→ true

요소가 있음
→ false
```

특히:

```cpp
pop_back()
```

을 사용하기 전에 vector가 비어있는지 검사하는 용도로 사용할 수 있다.

```cpp
if (!numbers.empty())
{
    numbers.pop_back();
}
```

---

# clear()

vector의 모든 요소를 삭제한다.

```cpp
std::vector<int> numbers = { 10, 20, 30 };

numbers.clear();
```

이후:

```cpp
numbers.size();
```

결과:

```text
0
```

---

# front() / back()

첫 번째 요소:

```cpp
numbers.front();
```

마지막 요소:

```cpp
numbers.back();
```

예:

```cpp
std::vector<int> numbers = { 10, 20, 30 };

std::cout << numbers.front() << '\n';
std::cout << numbers.back() << '\n';
```

결과:

```text
10
30
```

vector가 비어있는 상태에서는 `front()`나 `back()`을 사용하면 안 된다.

---

# []와 at()

vector 요소 접근:

```cpp
numbers[0];
```

또는:

```cpp
numbers.at(0);
```

사용 가능.

차이:

```text
[]
└─ 범위를 자동으로 검사하지 않음

at()
└─ 범위를 검사함
└─ 잘못된 인덱스면 예외 발생
```

예:

```cpp
numbers.at(100);
```

vector 범위를 벗어나면 예외가 발생한다.

---

# 배열과 vector 비교

| 배열 | vector |
| --- | --- |
| 크기 고정 | 크기 변경 가능 |
| `int arr[5]` | `std::vector<int>` |
| 기본적인 배열 기능 | STL 컨테이너 |
| 자동 확장 X | `push_back()`으로 확장 |
| 기능이 비교적 적음 | 다양한 함수 제공 |
| 크기를 직접 알고 있어야 함 | `size()` 사용 가능 |

예:

```cpp
int numbers[5];
```

```text
크기 = 5
고정
```

vector:

```cpp
std::vector<int> numbers;
```

```text
[]
↓ push_back(10)

[10]
↓ push_back(20)

[10, 20]
↓ push_back(30)

[10, 20, 30]
```

---

# 배열 / string / vector 비교

## 배열

```cpp
int numbers[5];
```

```text
같은 타입 여러 개 저장
크기 고정
인덱스 0부터
```

---

## string

```cpp
std::string text = "Hello";
```

```text
문자열 관리
문자 단위 인덱스 접근 가능
size() 사용 가능
```

---

## vector

```cpp
std::vector<int> numbers;
```

```text
같은 타입 여러 개 저장
크기 변경 가능
STL 컨테이너
```

---

# 주요 vector 함수 정리

| 기능 | 코드 |
| --- | --- |
| 값 추가 | `push_back()` |
| 마지막 값 삭제 | `pop_back()` |
| 크기 확인 | `size()` |
| 비어있는지 확인 | `empty()` |
| 전체 삭제 | `clear()` |
| 첫 번째 값 | `front()` |
| 마지막 값 | `back()` |
| 요소 접근 | `[]`, `at()` |

---

# 최종 정리

```text
배열

int arr[5];

└─ 같은 자료형 여러 개 저장
└─ 크기 고정
└─ 인덱스 0부터
```

```text
string

std::string text;

└─ 문자열 저장
└─ text[index]로 문자 접근
└─ size()로 길이 확인
└─ + 또는 += 로 문자열 연결
```

```text
vector

std::vector<int> values;

└─ 같은 자료형 여러 개 저장
└─ 크기 변경 가능
└─ push_back()으로 추가
└─ pop_back()으로 마지막 요소 삭제
└─ size()로 크기 확인
└─ empty()로 비어있는지 확인
```

---

# 핵심 문법

```cpp
int arr[5];
```

고정 크기 배열.

```cpp
arr[0];
```

배열 첫 번째 요소.

```cpp
std::string text = "Hello";
```

문자열.

```cpp
text[0];
```

첫 번째 문자.

```cpp
text.size();
```

문자열 길이.

```cpp
std::vector<int> numbers;
```

정수를 저장하는 vector.

```cpp
numbers.push_back(10);
```

맨 뒤에 값 추가.

```cpp
numbers.pop_back();
```

맨 뒤 값 삭제.

```cpp
numbers.size();
```

현재 요소 개수.

```cpp
numbers.empty();
```

비어있는지 검사.

```cpp
for (int number : numbers)
{
}
```

값을 복사해서 순회.

```cpp
for (int& number : numbers)
{
}
```

원본 요소를 참조해서 순회.

```cpp
for (const int& number : numbers)
{
}
```

복사하지 않고 원본을 읽기만 함.