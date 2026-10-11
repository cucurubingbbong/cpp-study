# vector

`std::vector`는 **같은 자료형의 값을 연속된 메모리 공간에 저장하면서 요소 개수를 동적으로 변경할 수 있는 STL 컨테이너**이다.

일반 배열과 비슷하게 인덱스로 접근할 수 있지만, 필요한 만큼 요소를 추가하거나 삭제할 수 있다.

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
int 값을 여러 개 저장하는 vector 생성
처음에는 요소가 없는 상태: []
```

**학습 기준:** C++11/14/17을 중심으로 하며, C++11부터 추가된 문법은 따로 표시한다.

---

# 배열과 vector 비교

```cpp
int arr[3] = {10, 20, 30};

std::vector<int> numbers = {10, 20, 30};
```

| 배열 | vector |
| --- | --- |
| 크기가 고정됨 | 요소 개수를 늘리거나 줄일 수 있음 |
| `arr[0]` | `numbers[0]` |
| 크기를 직접 관리해야 할 수 있음 | `size()`로 요소 개수 확인 |
| 원소가 연속된 메모리에 저장됨 | 원소가 연속된 메모리에 저장됨 |
| 추가·삭제를 직접 구현해야 함 | `push_back()`, `erase()` 등 제공 |

**주의:** vector도 무한히 커질 수 있는 것은 아니며, 요소가 늘어날 때 메모리 재할당이 발생할 수 있다.

---

# vector 선언과 초기화

```cpp
std::vector<int> a;              // []
std::vector<int> b(3);           // [0, 0, 0]
std::vector<int> c(3, 10);       // [10, 10, 10]
std::vector<int> d{3};           // [3]
std::vector<int> e{3, 10};       // [3, 10]
std::vector<int> f = {10, 20};   // [10, 20]
```

`()`와 `{}`는 같은 의미가 아니다.

```text
vector<int> c(3, 10)
└─ 10이라는 값을 3개 생성

vector<int> e{3, 10}
└─ 3과 10을 각각 요소로 저장
```

`{}`를 이용한 초기화 목록은 C++11부터 사용할 수 있다.

저장할 타입도 바꿀 수 있다.

```cpp
std::vector<int> scores;
std::vector<double> prices;
std::vector<std::string> names; // <string>도 필요
```

---

# push_back() / pop_back()

`push_back()`은 맨 뒤에 요소를 추가한다.

```cpp
std::vector<int> numbers;

numbers.push_back(10);
numbers.push_back(20);
numbers.push_back(30);
```

결과:

```text
[10, 20, 30]
```

`pop_back()`은 **마지막 요소를 제거**한다.

```cpp
numbers.pop_back();
```

결과:

```text
[10, 20]
```

`pop_back()`은 제거한 값을 반환하지 않는다.

vector가 비어 있을 때 `pop_back()`을 호출하면 안 된다.

```cpp
if (!numbers.empty())
{
    numbers.pop_back();
}
```

---

# size() / capacity()

두 함수는 의미가 다르다.

| 함수 | 의미 |
| --- | --- |
| `size()` | 현재 실제로 존재하는 요소 개수 |
| `capacity()` | 재할당 없이 저장할 수 있는 요소의 최대 개수 |

예를 들어:

```text
size = 3
capacity = 5

index     0     1     2     3     4
        ┌────┬────┬────┬────┬────┐
        │ 10 │ 20 │ 30 │    │    │
        └────┴────┴────┴────┴────┘
        └─ 실제 요소 ─┘└─ 여유 공간 ─┘
```

이 경우 **인덱스 0~2만 접근 가능**하다.

`capacity()`가 5라고 해서 `numbers[4]`가 유효한 것은 아니다.

---

# reserve() / resize()

## reserve()

`reserve(n)`은 최소 n개의 요소를 담을 수 있도록 **저장 용량**을 확보한다.

```cpp
std::vector<int> numbers;

numbers.reserve(10);

std::cout << numbers.size();     // 0
std::cout << numbers.capacity(); // 10 이상
```

`reserve()`는 요소를 생성하지 않으므로 다음 코드는 잘못됐다.

```cpp
numbers[5] = 100; // Undefined Behavior
```

## resize()

`resize(n)`은 실제 **요소 개수**를 n개로 변경한다.

```cpp
std::vector<int> numbers;

numbers.resize(5);

numbers[3] = 100; // 정상
```

새로 추가된 `int` 요소는 0으로 초기화된다.

결과:

```text
[0, 0, 0, 100, 0]
```

비교:

| 함수 | size 변경 | capacity 변경 가능 | 새 요소 생성 |
| --- | --- | --- | --- |
| `reserve(n)` | X | O | X |
| `resize(n)` | O | O | 크기가 늘어날 때 O |

**실무 사용 예:** 나중에 `push_back()`으로 데이터를 여러 개 추가할 것이고 개수를 미리 안다면 `reserve()`로 재할당 횟수를 줄일 수 있다.

```cpp
std::vector<int> scores;
scores.reserve(100);

for (int i = 0; i < 100; ++i)
{
    scores.push_back(i);
}
```

반대로 인덱스로 바로 값을 대입하려면 먼저 실제 요소가 생성되어 있어야 한다.

---

# 요소 접근: [] / at() / front() / back()

```cpp
std::vector<int> numbers = {10, 20, 30};

std::cout << numbers[0];     // 10
std::cout << numbers.at(1);  // 20
std::cout << numbers.front(); // 10
std::cout << numbers.back();  // 30
```

| 방법 | 기능 | 주의사항 |
| --- | --- | --- |
| `numbers[i]` | 인덱스로 접근 | 범위를 검사하지 않음 |
| `numbers.at(i)` | 인덱스로 접근 | 범위를 벗어나면 `std::out_of_range` 예외 |
| `numbers.front()` | 첫 요소 | 비어 있으면 사용하면 안 됨 |
| `numbers.back()` | 마지막 요소 | 비어 있으면 사용하면 안 됨 |

```cpp
if (!numbers.empty())
{
    std::cout << numbers.back() << '\n';
}
```

범위를 벗어난 `[]` 접근은 Undefined Behavior이다.

---

# vector 반복문과 참조

## 값 복사

```cpp
std::vector<int> numbers = {10, 20, 30};

for (int number : numbers)
{
    number = 100;
}
```

`number`는 복사본이므로 원본 vector는 그대로다.

```text
[10, 20, 30]
```

## 원본 참조

```cpp
for (int& number : numbers)
{
    number = 100;
}
```

결과:

```text
[100, 100, 100]
```

## const 참조

```cpp
for (const int& number : numbers)
{
    std::cout << number << '\n';
}
```

읽기만 하고 원본을 수정하지 않을 때 사용한다.

`int`처럼 작은 타입은 값 복사도 간단하지만, `std::string`이나 클래스 객체처럼 복사 비용이 있는 요소는 `const T&` 순회가 유용하다.

범위 기반 `for`문은 C++11부터 사용할 수 있다.

---

# insert(): 원하는 위치에 삽입

`insert()`는 지정한 위치 **앞에** 요소를 추가한다.

```cpp
std::vector<int> numbers = {10, 20, 30};

numbers.insert(numbers.begin() + 1, 15);
```

결과:

```text
[10, 15, 20, 30]
```

`begin()`은 첫 번째 요소를 가리키는 반복자를 반환한다.

```text
begin()     → 인덱스 0 위치
begin() + 1 → 인덱스 1 위치
end()       → 마지막 요소 다음 위치
```

동일한 값을 여러 개 삽입할 수도 있다.

```cpp
numbers.insert(numbers.begin() + 1, 2, 99);
```

이 코드는 인덱스 1 위치 앞에 99를 2개 삽입한다.

중간 삽입은 뒤의 요소들을 이동시킬 수 있으므로 일반적으로 O(n) 시간이 걸린다.

---

# erase(): 요소 또는 범위 삭제

## 요소 하나 삭제

```cpp
std::vector<int> numbers = {10, 20, 30, 40};

numbers.erase(numbers.begin() + 1);
```

결과:

```text
[10, 30, 40]
```

## 범위 삭제

```cpp
std::vector<int> numbers = {10, 20, 30, 40, 50};

numbers.erase(numbers.begin() + 1,
              numbers.begin() + 4);
```

결과:

```text
[10, 50]
```

삭제 범위는 **시작 위치 포함, 끝 위치 제외**이다.

```text
[begin() + 1, begin() + 4)
   인덱스 1, 2, 3 삭제
```

`erase()`는 삭제한 위치 다음 요소를 가리키는 반복자를 반환한다. 삭제한 요소가 마지막이었다면 `end()`를 반환한다.

중간 삭제 역시 뒤 요소를 이동시킬 수 있어 일반적으로 O(n) 시간이 걸린다.

---

# 반복자(iterator) 맛보기

`insert()`와 `erase()`에서 사용한 `begin()`과 `end()`는 반복자와 관련된다.

```cpp
std::vector<int> numbers = {10, 20, 30};

auto it = numbers.begin();

std::cout << *it; // 10
++it;
std::cout << *it; // 20
```

| 표현 | 의미 |
| --- | --- |
| `begin()` | 첫 번째 요소의 반복자 |
| `end()` | 마지막 요소 **다음** 위치의 반복자 |
| `*it` | 반복자가 가리키는 요소 |
| `++it` | 다음 요소로 이동 |
| `auto` | 변수 타입을 컴파일러가 추론 (C++11) |

**중요:** `end()`는 실제 요소를 가리키지 않으므로 역참조하면 안 된다.

반복자의 종류와 안전한 순회는 뒤의 `iterator` 파트에서 자세히 배운다.

---

# push_back() / emplace_back()

`push_back()`은 이미 존재하는 객체 또는 임시 객체를 추가한다.

`emplace_back()`은 전달받은 생성자 인수로 vector 내부에 객체를 직접 생성한다. (`emplace_back()`은 C++11부터 지원)

```cpp
#include <iostream>
#include <string>
#include <vector>

struct Player
{
    std::string name;
    int hp;

    Player(const std::string& newName, int newHp)
        : name(newName), hp(newHp)
    {
    }
};

int main()
{
    std::vector<Player> players;
    players.reserve(2);

    players.push_back(Player("Knight", 100));
    players.emplace_back("Mage", 80);

    for (const Player& player : players)
    {
        std::cout << player.name << ' ' << player.hp << '\n';
    }
}
```

출력:

```text
Knight 100
Mage 80
```

```text
push_back(Player("Knight", 100))
└─ 임시 Player 객체를 만든 후 vector에 추가

emplace_back("Mage", 80)
└─ 생성자 인수를 받아 vector 저장 공간에서 Player 객체 직접 생성
```

**주의:** `emplace_back()`이 무조건 더 빠른 것은 아니다. 이미 만들어진 객체를 추가할 때는 `push_back()`도 자연스럽고, vector가 재할당되면 기존 요소의 이동·복사 비용은 발생할 수 있다.

---

# 메모리 재할당(Reallocation)

vector는 요소를 연속된 메모리에 저장한다.

새 요소를 추가하려는데 남은 용량이 부족하면 다음과 같은 과정이 발생할 수 있다.

```text
기존 공간
[10][20][30]  size = 3, capacity = 3
       ↓ 공간 부족
새로운 더 큰 메모리 공간 확보
       ↓
기존 요소를 새 공간으로 이동 또는 복사
       ↓
기존 저장 공간 해제
       ↓
새 공간을 사용
```

재할당 후 capacity가 몇 배로 커지는지는 표준이 정해 놓지 않았고 구현마다 다르다.

`push_back()`은 보통 빠르지만 재할당이 발생하는 순간에는 요소를 옮기는 작업 때문에 비용이 커질 수 있다.

---

# 포인터·참조·반복자 무효화

전에 배운 포인터와 참조가 여기서 연결된다.

```cpp
std::vector<int> numbers = {10, 20, 30};

int& first = numbers[0];
int* ptr = &numbers[0];

numbers.reserve(numbers.capacity() + 1); // 반드시 재할당 발생
```

재할당 후 기존 요소를 가리키던 `first`와 `ptr`은 무효화된다.

```cpp
// std::cout << first; // Undefined Behavior
// std::cout << *ptr;  // Undefined Behavior

std::cout << numbers[0]; // 새 저장 공간의 요소에 정상 접근
```

| 동작 | 기존 요소의 참조·포인터에 미치는 영향 |
| --- | --- |
| `push_back()` + 재할당 | 모든 기존 요소의 참조·포인터 무효화 |
| `push_back()` + 재할당 없음 | 기존 요소의 참조·포인터는 유지 |
| `reserve()` + 재할당 | 모두 무효화 |
| `reserve()` + 재할당 없음 | 유지 |
| `insert()` + 재할당 없음 | 삽입 위치부터 뒤쪽 요소의 참조·반복자 무효화 |
| `erase()` | 삭제 위치부터 뒤쪽 요소의 참조·반복자 무효화 |

재할당이 없는 `push_back()`이라도 기존 `end()` 반복자는 무효화된다.

**핵심:** vector의 요소를 가리키는 주소나 참조를 오래 보관한 채 요소를 추가·삭제하는 코드는 주의해야 한다.

---

# vector와 함수 전달

## 값 전달

```cpp
void Print(std::vector<int> numbers)
{
    // vector 복사본을 사용
}
```

원본 vector를 복사하므로 불필요한 비용이 발생할 수 있다.

## 참조 전달

```cpp
void AddNumber(std::vector<int>& numbers)
{
    numbers.push_back(100);
}
```

원본 vector를 직접 수정한다.

## const 참조 전달

```cpp
void PrintNumbers(const std::vector<int>& numbers)
{
    for (int number : numbers)
    {
        std::cout << number << '\n';
    }
}
```

원본을 복사하지 않고 읽기만 한다.

| 전달 방식 | vector 복사 | 원본 수정 가능 |
| --- | --- | --- |
| `std::vector<int> v` | O | X |
| `const std::vector<int> v` | O | X |
| `std::vector<int>& v` | X | O |
| `const std::vector<int>& v` | X | X |

**정리:** `const`는 수정을 제한하고, `&`는 참조를 나타낸다. `const`만 붙인 값 전달도 복사는 발생한다.

---

# vector 복사와 객체 수명

```cpp
std::vector<int> original = {10, 20, 30};
std::vector<int> copied = original;

copied[0] = 99;
```

결과:

```text
original = [10, 20, 30]
copied   = [99, 20, 30]
```

vector를 복사하면 일반적으로 별도의 저장 공간과 복사된 요소들이 생긴다.

단, `vector<int*>`처럼 포인터를 요소로 저장했다면 **포인터가 가리키는 대상까지 자동 복제되는 것은 아니다.**

또한 vector는 자신이 관리하는 요소의 수명과 저장 공간을 관리한다.

```cpp
void Test()
{
    std::vector<int> numbers = {10, 20, 30};
} // 지역 vector의 수명 종료 → 요소 정리 및 저장 공간 해제
```

이러한 자동 자원 관리는 RAII와 연결된다. 일반적인 vector 사용에서는 `new[]`와 `delete[]`를 직접 쓸 필요가 없다.

---

# clear() / shrink_to_fit()

```cpp
std::vector<int> numbers = {10, 20, 30};

numbers.clear();
```

`clear()`는 모든 요소를 제거하므로 `size()`는 0이 된다.

하지만 이미 확보된 `capacity()`는 유지된다.

```cpp
numbers.shrink_to_fit();
```

`shrink_to_fit()`은 불필요한 용량을 줄여 달라고 **요청**하는 함수이다. 실제로 용량이 줄어드는 것은 보장되지 않는다. (C++11)

---

# 시간 복잡도

| 연산 | 일반적인 시간 복잡도 |
| --- | --- |
| `numbers[i]` | O(1) |
| `at(i)` | O(1) |
| `size()` / `empty()` | O(1) |
| `push_back()` | 분할 상환 O(1), 재할당이 발생하는 호출은 O(n) 가능 |
| `pop_back()` | O(1) |
| 중간 `insert()` | O(n) |
| 중간 `erase()` | O(n) |
| `clear()` | O(n) |

`vector`는 **뒤에 추가하는 작업과 인덱스 접근**에 특히 적합하다.

중간 삽입·삭제를 매우 자주 한다면 자료구조 선택을 다시 고려할 수 있다.

---

# 실무에서 주의할 점

1. `reserve()`는 size를 늘리지 않는다. 인덱스로 쓰려면 유효한 요소가 먼저 있어야 한다.
2. `pop_back()`, `front()`, `back()`은 비어 있는 vector에 사용하지 않는다.
3. `[]`는 범위를 검사하지 않는다. 외부 입력으로 인덱스를 받는다면 먼저 검증한다.
4. `push_back()` 등으로 재할당이 일어나면 기존 요소의 주소·참조·반복자가 무효화될 수 있다.
5. vector를 읽기만 하는 함수에서는 보통 `const std::vector<T>&`를 사용한다.
6. 반복문에서 `erase()`를 호출했다면 무효화된 반복자를 계속 사용하지 않는다.
7. `emplace_back()`을 모든 상황에서 무조건 `push_back()`보다 좋다고 생각하지 않는다.

---

# 주요 함수 요약

| 기능 | 코드 |
| --- | --- |
| 값 추가 | `push_back(x)` |
| 객체 직접 생성 | `emplace_back(args...)` |
| 맨 뒤 삭제 | `pop_back()` |
| 중간 삽입 | `insert(pos, x)` |
| 요소 삭제 | `erase(pos)` |
| 범위 삭제 | `erase(first, last)` |
| 크기 확인 | `size()` |
| 용량 확인 | `capacity()` |
| 비었는지 확인 | `empty()` |
| 용량 미리 확보 | `reserve(n)` |
| 요소 개수 변경 | `resize(n)` |
| 전체 요소 삭제 | `clear()` |
| 첫 요소 | `front()` |
| 마지막 요소 | `back()` |
| 범위 검사 접근 | `at(i)` |
| 용량 축소 요청 | `shrink_to_fit()` |

---

# 최종 정리

```text
vector
└─ 같은 타입의 요소를 연속된 메모리에 저장
└─ size()는 실제 요소 개수
└─ capacity()는 확보된 저장 용량
└─ reserve()는 용량 확보, resize()는 요소 개수 변경
└─ push_back()은 뒤에 추가
└─ emplace_back()은 생성자 인수로 요소를 직접 생성
└─ insert() / erase()는 중간 삽입·삭제
└─ 재할당이 발생하면 기존 참조·포인터·반복자가 무효화됨
└─ 읽기 전용 함수 전달은 const vector<T>&를 우선 고려
└─ vector가 자원과 요소 수명을 자동으로 관리
```
