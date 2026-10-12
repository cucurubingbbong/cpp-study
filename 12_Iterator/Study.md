# Iterator (반복자) — C++03 / C++11 / C++14 / C++17

> 이 노트는 `vector`, `string` 학습 이후의 **반복자 1~4강**을 정리한 문서이다.  
> 예제는 별도로 표시하지 않으면 C++11 이상(권장 C++17) 기준이다. C++03 전용 코드는 구분해서 작성한다.

## 1. Iterator란?

Iterator(반복자)는 **컨테이너의 요소를 가리키고, 순서대로 이동하면서 요소를 읽거나 수정하는 데 사용하는 객체**이다.

컨테이너의 예:

- `std::vector` : 요소를 연속된 공간에 저장
- `std::string` : 문자 데이터를 저장
- `std::list` : 양방향 연결 리스트
- `std::forward_list` : 단방향 연결 리스트(C++11)

반복자는 포인터와 비슷하게 `*`, `++` 등의 연산을 제공하지만, **모든 반복자가 실제 포인터인 것은 아니다.**

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numbers = {10, 20, 30};

    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        std::cout << *it << ' ';
    }
}
```

출력:

```text
10 20 30
```

---

## 2. begin()과 end()

```cpp
std::vector<int> numbers = {10, 20, 30};

auto first = numbers.begin(); // 첫 번째 요소 10
auto last = numbers.end();    // 마지막 요소 바로 다음의 종료 위치
```

구조:

```text
인덱스   0     1     2       (종료 위치)
       ┌────┬────┬────┐
값     │ 10 │ 20 │ 30 │    end()
       └────┴────┴────┘
         ↑
       begin()
```

- `begin()` : 첫 요소를 가리키는 반복자를 반환한다.
- `end()` : **마지막 요소 다음의 종료 위치**를 나타내는 반복자를 반환한다.
- 범위 표기는 `[first, last)`이다. **first는 포함, last는 제외**한다.
- 빈 컨테이너는 `begin() == end()`이다.

`end()`는 반복자 비교에 사용할 수 있지만, 역참조해서는 안 된다.

```cpp
std::cout << *numbers.end(); // 잘못됨: Undefined Behavior
```

마지막 요소가 필요한 경우:

```cpp
if (!numbers.empty())
{
    std::cout << numbers.back() << '\n';

    auto it = numbers.end();
    --it; // 비어 있지 않은 vector이므로 유효
    std::cout << *it << '\n';
}
```

---

## 3. *it, ++it, --it

```cpp
std::vector<int> numbers = {10, 20, 30};

auto it = numbers.begin();

std::cout << *it << '\n'; // 10
++it;
std::cout << *it << '\n'; // 20

*it = 99; // 반복자가 가리키는 실제 요소 수정
```

최종 vector:

```text
[10, 99, 30]
```

주요 연산:

| 연산 | 의미 |
| --- | --- |
| `*it` | 현재 가리키는 요소에 접근 |
| `++it` | 다음 요소로 이동 |
| `--it` | 이전 요소로 이동(지원되는 반복자에서만) |
| `it1 == it2` | 같은 위치인지 비교 |
| `it1 != it2` | 다른 위치인지 비교 |
| `it + n` | n칸 이동(Random Access Iterator에서 가능) |

범위를 벗어나 이동하거나 `end()`를 역참조하는 것은 잘못된 동작이다.

### 포인터와 반복자 비교

```cpp
int array[3] = {10, 20, 30};
int* ptr = array;
std::cout << *ptr; // 10

std::vector<int> numbers = {10, 20, 30};
std::vector<int>::iterator it = numbers.begin();
std::cout << *it; // 10
```

포인터는 주소를 다루는 언어 기능이고, 반복자는 **컨테이너 요소에 접근하는 공통 인터페이스** 역할을 한다.

---

## 4. iterator / const_iterator

일반 반복자는 요소를 수정할 수 있다.

```cpp
std::vector<int> numbers = {10, 20, 30};

std::vector<int>::iterator it = numbers.begin();
*it = 100; // 가능
```

`const_iterator`는 가리키는 요소를 수정할 수 없다.

```cpp
std::vector<int>::const_iterator cit = numbers.begin();
std::cout << *cit; // 가능
// *cit = 100;     // 컴파일 오류
```

C++11부터는 `cbegin()`, `cend()`가 제공된다.

```cpp
for (auto it = numbers.cbegin(); it != numbers.cend(); ++it)
{
    std::cout << *it << ' ';
}
```

| 구분 | 읽기 | 수정 | 도입 |
| --- | --- | --- | --- |
| `iterator` | O | O | C++98 |
| `const_iterator` | O | X | C++98 |
| 컨테이너 멤버 `cbegin()` | O | X | C++11 |
| 컨테이너 멤버 `cend()` | O | X | C++11 |

`const std::vector<int>`의 `begin()`도 `const_iterator`를 반환한다.

```cpp
const std::vector<int> values = {1, 2, 3};
auto it = values.begin(); // const_iterator
```

**C++03**에서는 `auto` 타입 추론을 사용할 수 없으므로 반복자 타입을 직접 적는다.

---

## 5. 역방향 반복자 — rbegin(), rend()

`rbegin()`은 역방향으로 보았을 때 첫 번째 요소(정방향 마지막 요소)를 가리킨다.  
`rend()`는 역방향 순회의 종료 위치를 나타내며 **역참조하면 안 된다.**

```cpp
std::vector<int> numbers = {10, 20, 30};

for (auto it = numbers.rbegin(); it != numbers.rend(); ++it)
{
    std::cout << *it << ' ';
}
```

출력:

```text
30 20 10
```

역방향 반복자에서도 `++it`을 사용하지만, **논리적인 다음 요소가 정방향 순서의 왼쪽**에 있다.

```cpp
auto it = numbers.rbegin();
*it = 99; // 마지막 요소 수정 → [10, 20, 99]
```

C++11부터는 `crbegin()`, `crend()`로 읽기 전용 역방향 순회를 할 수 있다.

```cpp
for (auto it = numbers.crbegin(); it != numbers.crend(); ++it)
{
    std::cout << *it << ' ';
}
```

### reverse_iterator의 base()

역방향 반복자는 대응하는 정방향 반복자를 `base()`로 반환할 수 있다.

```cpp
auto r = numbers.rbegin();

std::cout << (r.base() == numbers.end()); // 1
```

```text
[10] [20] [30] [end]
           ↑     ↑
          *r   r.base()
```

`rbegin().base() == end()`, `rend().base() == begin()`이다.  
**`base()`가 나타내는 위치와 역참조한 역방향 반복자의 요소 사이에는 한 칸 차이가 있다.**

---

## 6. 반복자 종류(기본 5가지)

C++03/11/14/17 학습에서 기억할 주요 종류는 다음과 같다.

| 종류 | 기본 기능 | 대표 예 |
| --- | --- | --- |
| Input Iterator | 읽으면서 앞으로 진행 | `istream_iterator` |
| Output Iterator | 쓰면서 앞으로 진행 | `ostream_iterator` |
| Forward Iterator | 정방향으로 여러 번 순회 | `forward_list`(C++11) |
| Bidirectional Iterator | `++`, `--` | `list`, `map` |
| Random Access Iterator | `++`, `--`, `+n`, `-n`, 비교 | `vector`, `string`, `deque` |

### vector는 `it + 2` 가능

```cpp
std::vector<int> values = {10, 20, 30};
auto it = values.begin();
it += 2;
std::cout << *it; // 30
```

### list는 `it + 2` 불가능

```cpp
#include <list>
#include <iterator>

std::list<int> values = {10, 20, 30};
std::list<int>::iterator it = values.begin();

++it;              // 가능
--it;              // 가능
// it += 2;         // 컴파일 오류
std::advance(it, 2); // 유효한 범위 내 이동. list는 선형 시간
```

`std::advance()`는 C++03에서도 사용 가능하다. 실제 이동 거리는 컨테이너의 반복자 종류에 따라 시간이 달라진다.

**모든 컨테이너에서 `std::sort()`가 가능한 것은 아니다.** `std::sort()`에는 Random Access Iterator가 필요하므로 `std::list`에서는 `values.sort()`를 사용한다.

---

## 7. insert()와 erase() 반환값

### insert()

```cpp
std::vector<int> numbers = {10, 20, 30};

auto it = numbers.insert(numbers.begin() + 1, 15);

std::cout << *it; // 15
```

결과:

```text
[10, 15, 20, 30]
```

`insert()`는 **새로 삽입한 요소를 가리키는 유효한 반복자**를 반환한다.

`insert(numbers.end(), 40)`처럼 끝 위치에 삽입하는 것은 가능하다.

### erase()

```cpp
std::vector<int> numbers = {10, 20, 30, 40};

auto it = numbers.erase(numbers.begin() + 1);

std::cout << *it; // 30
```

결과:

```text
[10, 30, 40]
```

`erase()`는 **삭제한 자리의 다음에 남는 요소를 가리키는 반복자**를 반환한다. 마지막 요소를 삭제하면 `end()`를 반환한다.

```cpp
auto it = numbers.erase(numbers.end() - 1);

if (it != numbers.end())
{
    std::cout << *it;
}
```

`erase(numbers.end())`는 잘못된 호출이다. `end()`는 삭제할 실제 요소가 아니기 때문이다.

### 구간 삭제

```cpp
std::vector<int> numbers = {10, 20, 30, 40, 50};

numbers.erase(numbers.begin() + 1, numbers.begin() + 4);
```

결과:

```text
[10, 50]
```

범위 `[first, last)`의 `last`는 **삭제하지 않는다.**

---

## 8. 반복자 무효화(Invalidation)

반복자 무효화는 기존 반복자가 더 이상 유효하게 사용될 수 없게 되는 현상이다.

### 재할당 때문에 무효화

```cpp
std::vector<int> numbers = {10, 20, 30};
auto it = numbers.begin();

numbers.reserve(numbers.capacity() + 1); // 반드시 용량 증가

// std::cout << *it; // 잘못됨: 기존 요소의 반복자가 무효화됨
```

`vector`의 저장 공간이 재할당되면 기존 요소의 포인터·참조·반복자가 모두 무효화된다.

### 재할당이 없어도 무효화

```cpp
std::vector<int> numbers = {10, 20, 30};
numbers.reserve(10);

auto it = numbers.begin() + 2; // 30
numbers.insert(numbers.begin() + 1, 99);

// std::cout << *it; // 잘못됨: 중간 삽입으로 it 무효화
```

재할당이 없어도 **삽입 위치부터 뒤쪽의 반복자와 참조**가 무효화될 수 있다.

### vector의 주요 무효화 규칙

| 연산 | 무효화 대상 |
| --- | --- |
| `push_back()` / `emplace_back()`, 재할당 O | 기존 반복자·참조 전부 |
| `push_back()` / `emplace_back()`, 재할당 X | 기존 `end()` 반복자 |
| `insert()`, 재할당 O | 기존 반복자·참조 전부 |
| `insert()`, 재할당 X | 삽입 위치부터 기존 `end()`의 반복자, 그 위치 이후 요소 참조 |
| `erase()` | 삭제 위치부터 기존 `end()`까지 반복자·참조 |
| `reserve()`, 용량 변경 | 전부 |
| `pop_back()` | 지워진 마지막 요소와 기존 `end()` |
| `clear()` | 모든 요소의 반복자·참조, 기존 `end()` |

이 표는 `std::vector` 기준이다. **다른 컨테이너에 그대로 적용하면 안 된다.**

`std::list`는 중간 삽입 시 기존 요소의 반복자가 유지되며, 요소 삭제 시 **삭제된 요소를 가리키던 반복자만** 무효화된다.

### 순회하면서 안전하게 삭제

```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
auto it = numbers.begin();

while (it != numbers.end())
{
    if (*it % 2 == 0)
    {
        it = numbers.erase(it); // 새 유효한 반복자를 받는다.
    }
    else
    {
        ++it;
    }
}
```

결과:

```text
[1, 3, 5]
```

삭제 직후 무조건 `++it`을 실행하면 안 된다. 반환된 반복자가 이미 다음에 검사할 요소를 가리키기 때문이다.

vector에서 여러 번 중간 `erase()`를 하면 최악 O(n²)이 될 수 있으므로, 조건에 따른 대량 삭제에는 뒤에서 배우는 Erase-Remove Idiom이 적합할 수 있다.

---

## 9. STL 알고리즘과 반복자

알고리즘은 `<algorithm>` 헤더에 선언되어 있다.

많은 알고리즘은 **`[begin, end)` 범위**를 인수로 받는다.

### std::find() — 값 검색

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> numbers = {10, 20, 30};

auto it = std::find(numbers.begin(), numbers.end(), 20);

if (it != numbers.end())
{
    std::cout << *it; // 20
}
```

찾지 못하면 **전달한 범위의 끝 반복자**를 반환한다. `std::string::find()`의 `npos`와 구분해야 한다.

| 검색 함수 | 성공 시 | 실패 시 |
| --- | --- | --- |
| `std::string::find()` | 시작 인덱스 | `std::string::npos` |
| `std::find()` | 요소 반복자 | 범위의 끝 반복자 |

### std::find_if() — 조건 검색

```cpp
std::vector<int> numbers = {10, 15, 21, 30};

auto it = std::find_if(numbers.begin(), numbers.end(),
                       [](int n) { return n > 20; });

if (it != numbers.end())
{
    std::cout << *it; // 21
}
```

람다(`[](...) {...}`)는 **C++11부터** 사용 가능하다.

### std::sort() — 정렬

```cpp
std::vector<int> numbers = {8, 3, 5, 3};

std::sort(numbers.begin(), numbers.end());

// numbers = [3, 3, 5, 8]
```

`sort()`는 **원본 범위의 요소들을 직접 재정렬**한다.

```cpp
auto it = std::find(numbers.begin(), numbers.end(), 5);

if (it != numbers.end())
{
    std::cout << (it - numbers.begin()); // 2
}
```

`it - numbers.begin()`은 두 Random Access Iterator 사이의 거리다. 정렬된 `[3, 3, 5, 8]`에서 5의 인덱스는 2이다.

내림차순 정렬:

```cpp
#include <functional>

std::sort(numbers.begin(), numbers.end(), std::greater<int>());
```

또는 C++11 람다:

```cpp
std::sort(numbers.begin(), numbers.end(),
          [](int a, int b) { return a > b; });
```

비교 함수는 일관된 엄격 약순서(strict weak ordering)를 만족해야 한다. 예를 들어 `a <= b`처럼 값이 같아도 참을 반환하는 비교는 사용하면 안 된다.

`std::sort()`는 Random Access Iterator가 필요하므로 `std::list`에는 직접 사용할 수 없다. list에서는 `list.sort()`를 사용한다.

---

## 10. remove() / remove_if()와 Erase-Remove Idiom

**`std::remove()`와 `std::remove_if()`는 vector의 `size()`를 줄이지 않는다.**

### 특정 값 제거 대상으로 지정

```cpp
std::vector<int> numbers = {1, 2, 3, 2, 4};

auto newEnd = std::remove(numbers.begin(), numbers.end(), 2);
```

### 조건에 맞는 값 제거 대상으로 지정

```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5, 6};

auto newEnd = std::remove_if(numbers.begin(), numbers.end(),
                             [](int n) { return n % 2 == 0; });
```

람다가 참을 반환하는 **짝수는 제거 대상**이다. `remove_if()`는 **남겨야 할 홀수 `[1, 3, 5]`를 앞쪽에 모은다.**

```text
원본:                    [1, 2, 3, 4, 5, 6]
remove_if 이후 앞부분:   [1, 3, 5 | ?, ?, ?]
                        ↑       ↑
                      begin   newEnd
```

`?`는 해당 요소가 사라졌다는 뜻이 아니다. **요소는 여전히 존재하고 유효하지만 그 값은 지정되지 않는다.**

```cpp
std::cout << numbers.size();                    // 6
std::cout << std::distance(numbers.begin(), newEnd); // 3
```

실제 삭제하려면 vector 멤버 함수 `erase()`를 이어서 호출한다.

```cpp
numbers.erase(newEnd, numbers.end());

// numbers = [1, 3, 5], size() = 3
```

### Erase-Remove Idiom — 실무 패턴

```cpp
numbers.erase(
    std::remove_if(numbers.begin(), numbers.end(),
                   [](int n) { return n % 2 == 0; }),
    numbers.end()
);
```

이 패턴은 C++03에서도 사용 가능하지만, C++03에서는 람다 대신 별도의 함수 또는 함수 객체를 전달해야 한다.

```cpp
// C++03용 조건 함수
bool IsEven(int n)
{
    return n % 2 == 0;
}

// numbers가 std::vector<int>라고 가정
numbers.erase(
    std::remove_if(numbers.begin(), numbers.end(), IsEven),
    numbers.end()
);
```

- `std::remove_if` 자체: O(n)
- 뒤의 `vector::erase`: 지워지는 뒷부분에 대한 처리
- 전체적으로 선형 시간 O(n)으로 조건 삭제 가능
- 순회 중 여러 번 중간 `vector::erase`를 하는 방법은 최악 O(n²)

`std::list`에는 별도의 `list::remove_if()` 멤버 함수가 있어 실제 노드를 삭제하므로 `std::remove_if`와 혼동하지 말자.

---

## 11. iterator 관련 유틸리티

`<iterator>` 헤더를 포함한다.

### std::distance() — 반복자 거리

```cpp
std::vector<int> values = {10, 20, 30, 40};

auto it = values.begin() + 2;
std::cout << std::distance(values.begin(), it); // 2
```

### std::advance() — 반복자 이동(C++03부터)

```cpp
std::list<int> values = {10, 20, 30};
auto it = values.begin();
std::advance(it, 2);
std::cout << *it; // 30
```

### std::next() / std::prev() — 새로운 위치 반환(C++11부터)

```cpp
std::vector<int> values = {10, 20, 30};

auto it = values.begin();
auto second = std::next(it); // it 자체는 그대로

std::cout << *second; // 20
```

주의: `advance`, `next`, `prev`에도 범위를 벗어나는 이동을 지시해서는 안 된다.

| 반복자 | 거리/이동 비용 |
| --- | --- |
| vector의 Random Access Iterator | 보통 O(1) |
| list의 Bidirectional Iterator | 거리 n에 비례, O(n) |

---

## 12. C++03 / 11 / 14 / 17 차이 정리

| 기능 | 도입 버전 |
| --- | --- |
| 기본 반복자, `begin()`, `end()`, `rbegin()`, `rend()` | C++98, C++03에서 사용 가능 |
| `std::find`, `std::sort`, `std::remove_if`, `std::advance` | C++98, C++03에서 사용 가능 |
| `auto` 타입 추론 | C++11 |
| 범위 기반 `for` | C++11 |
| 람다식 | C++11 |
| 컨테이너 멤버 `cbegin/cend/crbegin/crend` | C++11 |
| `std::next`, `std::prev` | C++11 |
| 제네릭 람다(`[](auto x)`) | C++14 |
| `std::make_reverse_iterator()` | C++14 |
| 비멤버 `std::cbegin()`, `std::cend()` | C++14 |
| `std::size()`, `std::data()` | C++17 |
| 일부 STL 알고리즘의 병렬 실행 정책 | C++17 |

### C++03 방식

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values;
    values.push_back(10);
    values.push_back(20);

    std::vector<int>::iterator it;
    for (it = values.begin(); it != values.end(); ++it)
    {
        std::cout << *it << ' ';
    }
}
```

### C++11/14/17 방식

```cpp
std::vector<int> values = {10, 20};

for (auto it = values.cbegin(); it != values.cend(); ++it)
{
    std::cout << *it << ' ';
}
```

---

## 13. 실무에서 주의할 점

1. `end()` / `rend()`를 역참조하지 않는다.
2. `find()`의 반환값은 먼저 범위의 끝 반복자와 비교한다.
3. `sort()`는 원본 순서를 변경한다.
4. `remove_if()`의 조건이 **true인 요소는 제거 대상**이며, **false인 요소가 앞으로 모인다.**
5. vector에서 `insert`, `erase`, `reserve`, `push_back` 등으로 반복자가 무효화될 수 있다.
6. `erase()` 후에는 이전 반복자를 계속 쓰지 말고 반환된 반복자를 사용한다.
7. `std::list`에는 `it + 2`나 `std::sort`를 사용할 수 없다.
8. `std::string`을 바이트 단위로 순회할 때 UTF-8 한글 문자 하나가 반드시 요소 하나인 것은 아니다.
9. 범위 기반 `for`는 단순한 전체 순회에 좋지만, **순회 중 삭제하는 경우**에는 명시적인 반복자와 반환값을 사용하는 방식이 필요할 수 있다.

---

## 14. main.cpp 복습 파일

같이 제공한 `main.cpp`는 다음 항목을 함수 단위로 실행한다.

| 함수 | 복습 내용 |
| --- | --- |
| `BasicIterator()` | `begin`, `end`, 수정, `cbegin`, string 반복자 |
| `ReverseIterator()` | `rbegin`, `rend`, `base()` |
| `InsertAndErase()` | `insert`, `erase`, 반복 중 안전한 삭제 |
| `StandardAlgorithms()` | `find`, `find_if`, `sort`, `remove_if`, erase-remove |
| `IteratorCategories()` | list의 양방향 이동, `std::advance` |

컴파일 및 실행(C++17):

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o iterator_study
./iterator_study
```

실행 결과에서 확인할 핵심:

```text
정렬된 요소: 3 3 5 8
5의 인덱스: 2
실제 size: 6
논리적 size: 3
실제 erase 후: 1 3 5
```

이 파일은 실행 가능한 **개념 복습 예제**이며 최종 실습 문제의 정답 코드가 아니다.

---

## 15. 최종 정리

```text
Iterator
└─ 컨테이너 요소의 위치를 다루는 공통 인터페이스

begin() / end()
└─ [시작, 끝) 범위, 끝 위치는 역참조 금지

*it / ++it
└─ 현재 요소 접근 / 다음 요소로 이동

const_iterator
└─ 읽기 가능, 요소 수정 불가

rbegin() / rend()
└─ 역방향 순회

insert()
└─ 삽입된 요소의 유효한 반복자 반환

erase()
└─ 삭제 위치 다음에 남은 요소의 반복자 반환

std::find()
└─ 성공: 찾은 요소의 반복자 / 실패: end()

std::sort()
└─ 원본 범위 정렬, Random Access Iterator 필요

std::remove_if()
└─ 남길 요소를 앞으로 모음, vector의 size는 그대로

Erase-Remove Idiom
└─ remove_if 결과를 vector.erase()에 전달해 실제 삭제
```

**핵심 한 줄:** 반복자는 요소의 위치를 표현하는 도구이지만, 컨테이너를 수정하면 그 위치가 무효화될 수 있으므로 항상 연산의 반환값과 무효화 규칙을 확인해야 한다.

