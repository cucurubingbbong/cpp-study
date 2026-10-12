# 1. 시간 복잡도(Big-O)

## 시간 복잡도란?

입력 데이터의 개수 `n`이 커질 때 **연산량이 얼마나 증가하는지** 나타내는 척도이다.

실제 실행 시간을 초 단위로 알려주는 것이 아니고, 데이터 증가에 따른 **연산량의 증가 추세**를 나타낸다.

| 복잡도 | 의미 | 대표적인 예 |
| --- | --- | --- |
| `O(1)` | 입력 크기와 관계없이 일정 | `vector[index]` |
| `O(log n)` | 크기가 커져도 느리게 증가 | 정렬된 배열의 이진 탐색, `set.find()` |
| `O(n)` | 원소 개수에 비례 | 모든 요소 순회, 순차 검색 |
| `O(n log n)` | 정렬에서 자주 등장 | `std::sort()` |
| `O(n²)` | n × n에 비례 | 모든 원소 쌍 검사 |

**주의:** Big-O가 더 작다고 실제 모든 입력에서 반드시 더 빠른 것은 아니다. 상수 비용, 캐시 효율, 해시 계산 비용 등에 따라 실제 시간은 달라진다.

## O(1) — 인덱스 접근

```cpp
std::vector<int> numbers = {10, 20, 30};
std::cout << numbers[1]; // 20
```

유효한 인덱스를 알고 있다면 요소 개수와 무관하게 접근 가능하다.

## O(n) — 순차 검색

```cpp
bool found = false;
for (int number : numbers)
{
    if (number == 30)
    {
        found = true;
        break;
    }
}
```

최악의 경우 모든 원소를 한 번씩 확인한다.

## O(log n) — 이진 탐색

```cpp
std::vector<int> numbers = {10, 20, 30, 40}; // 정렬된 상태

auto it = std::lower_bound(numbers.begin(), numbers.end(), 30);
if (it != numbers.end() && *it == 30)
{
    std::cout << "찾음\n";
}
```

`lower_bound()`는 **정렬된 vector**에서 탐색할 때 비교 횟수가 `O(log n)`이며, vector는 Random Access Iterator를 제공하므로 위치 이동까지 효율적으로 수행할 수 있다.

> `lower_bound()`는 **값이 같다는 것을 직접 보장하는 함수가 아니다.** 처음으로 `찾는 값 이상`이 되는 위치를 반환하므로 실제 존재 여부는 `*it == 찾는 값`으로 확인한다.

## O(n log n) — 정렬

```cpp
std::sort(numbers.begin(), numbers.end());
```

`std::sort()`는 범위 안의 **원본 요소를 직접 정렬**한다. vector 같은 Random Access Iterator가 필요하다.

## O(n²) — 중첩 반복문

```cpp
for (int i = 0; i < n; ++i)
{
    for (int j = 0; j < n; ++j)
    {
        std::cout << i << ' ' << j << '\n';
    }
}
```

바깥 n번 × 안쪽 n번 = `O(n²)`이다. 단, 반복문이 중첩되어 있다고 언제나 `O(n²)`인 것은 아니므로 실제 반복 횟수를 계산해야 한다.

---

# 2. unordered_map

## unordered_map이란?

`std::unordered_map`은 **Key(키)와 Value(값)**를 한 쌍으로 저장하는 해시 기반 컨테이너이다.

- Key 중복을 허용하지 않는다.
- Key로 값을 검색할 때 **평균 `O(1)`**, 최악 `O(n)`이다.
- 원소의 **삽입 순서 또는 정렬 순서는 보장되지 않는다.**
- **C++11부터** 표준 라이브러리에 포함되었다.

```cpp
#include <string>
#include <unordered_map>

std::unordered_map<std::string, int> players;
players["Knight"] = 100;
players["Mage"] = 80;
```

구조:

```text
Key        Value
Knight --> 100
Mage   -->  80
```

## operator[] — 접근과 삽입

```cpp
players["Knight"] += 20; // 기존 값 수정
players["Ghost"] += 1;   // 없는 키라면 0으로 초기화 후 1 추가
```

`operator[]`로 없는 키에 접근하면 요소가 **새로 삽입**될 수 있다.

존재 여부만 알고 싶을 때는 `find()` 또는 `count()`를 사용한다.

## find() — 키 검색

```cpp
auto it = players.find("Knight");

if (it != players.end())
{
    std::cout << it->first << ' ' << it->second << '\n';
}
```

- `it->first`: Key
- `it->second`: Value
- 찾지 못하면 `players.end()` 반환
- **`end()`는 역참조하면 안 된다.**

`std::find(begin, end, value)`는 범위를 순회하는 일반 알고리즘이고, `players.find(key)`는 해시 테이블의 멤버 검색이다.

## insert(), emplace(), try_emplace()

```cpp
players.insert({"Archer", 60});

auto result = players.emplace("Archer", 999);
std::cout << result.second; // 0: 중복 Key로 삽입 실패
```

`insert()`와 `emplace()`는 중복 Key가 존재하면 기존 값을 덮어쓰지 않는다.

`result.first`는 해당 요소의 반복자, `result.second`는 삽입 성공 여부이다.

```cpp
players.try_emplace("Archer", 500);    // C++17, 이미 있으면 값 생성 안 함
players.insert_or_assign("Archer", 70); // C++17, 없으면 삽입 / 있으면 수정
```

`emplace()`는 중복 키가 있어도 임시 요소를 생성할 수 있다. 반면 `try_emplace()`는 중복 키라면 mapped value를 새로 생성하지 않는다.

## count(), at(), erase()

```cpp
std::cout << players.count("Knight") << '\n'; // 0 또는 1

if (players.find("Knight") != players.end())
{
    std::cout << players.at("Knight") << '\n';
}

players.erase("Mage");
```

- `count(key)`: 키가 없으면 0, 있으면 1
- `at(key)`: 없으면 `std::out_of_range` 예외 (삽입하지 않음)
- `erase(key)`: 해당 키의 요소 삭제, 삭제한 원소 수 반환

## 해시(Hash)와 해시 충돌

Key를 해시 함수로 계산하여 버킷(Bucket)에 배치한다.

```text
"Knight" --hash--> Bucket 2
"Mage"   --hash--> Bucket 2  (충돌 예시)
```

서로 다른 키가 같은 버킷에 배치되는 현상을 **해시 충돌**이라고 한다. 충돌해도 서로 다른 키는 구분되지만, 충돌이 심하면 검색 성능이 떨어질 수 있다.

| 연산 | 평균 | 최악 |
| --- | --- | --- |
| 검색 | `O(1)` | `O(n)` |
| 삽입 | `O(1)` (분할 상환) | `O(n)` |
| 키로 삭제 | `O(1)` | `O(n)` |

## reserve(), rehash(), load_factor()

```cpp
std::unordered_map<int, int> data;
data.reserve(1000);

std::cout << data.bucket_count() << '\n';
std::cout << data.load_factor() << '\n';
```

```text
load_factor = 저장된 요소 개수 / 버킷 개수
```

`reserve(n)`은 최대 부하율을 기준으로 요소 n개를 수용하기 위한 버킷 수를 확보한다. `vector.reserve(n)`처럼 요소 n개를 실제 생성하는 기능은 아니다.

`rehash()`가 발생하면 **기존 반복자는 무효화**되지만, 삭제되지 않은 요소에 대한 **포인터·참조는 유지**된다.

```cpp
int& hp = data[1];
data.rehash(1000);
hp = 50; // 정상: 요소 참조는 유지
```

하지만 rehash 전에 얻은 반복자로 `*it`을 실행하면 안 된다.

---

# 3. set

## set이란?

`std::set`은 **중복을 허용하지 않고 정렬 상태를 유지하는 컨테이너**이다.

- 기본 정렬: 오름차순
- 검색·삽입·키 기준 삭제: `O(log n)`
- 일반적으로 균형 이진 탐색 트리로 구현
- C++03에서도 사용 가능

```cpp
#include <set>

std::set<int> numbers = {30, 10, 20, 10};
```

반복자로 순회하면:

```text
10 20 30
```

## insert(), find(), count(), erase()

```cpp
numbers.insert(40);

auto it = numbers.find(20);
if (it != numbers.end())
{
    std::cout << *it << '\n';
}

std::cout << numbers.count(10) << '\n'; // 1
numbers.erase(10);
```

`insert()`는 `std::pair<iterator, bool>`을 반환하고, 중복 값은 새로 삽입하지 않는다.

## 내림차순 set

```cpp
#include <functional>
#include <set>

std::set<int, std::greater<int>> numbers = {30, 10, 20};
```

출력 순서는 `30 20 10`이다.

## lower_bound()

```cpp
std::set<int> numbers = {10, 20, 30, 40};
auto it = numbers.lower_bound(25);

if (it != numbers.end())
{
    std::cout << *it; // 30
}
```

기본 오름차순 `set`에서 `lower_bound(x)`는 **x 이상인 첫 요소**를 가리킨다. `set`의 멤버 `lower_bound()`는 `O(log n)`이다.

## 원소 변경 주의

```cpp
std::set<int> numbers = {10, 20, 30};
auto it = numbers.find(20);

// *it = 99; // 컴파일 오류
numbers.erase(20);
numbers.insert(99);
```

set은 정렬 상태를 유지해야 하므로 반복자를 이용해 원소 값을 직접 수정할 수 없다.

## iterator 무효화

- `insert()`: 기존 요소의 반복자와 참조를 무효화하지 않음
- `erase()`: 삭제한 요소의 반복자·참조만 무효화
- `clear()`: 모든 요소 삭제

---

# 4. 컨테이너 비교

| 컨테이너 | 데이터 | 정렬 | 검색 | 대표 용도 |
| --- | --- | --- | --- | --- |
| `vector` | 값의 시퀀스 | 자동 X | 순차 검색 O(n) | 순서 있는 목록, 인덱스 접근 |
| `map` | Key-Value | Key 기준 O | O(log n) | 정렬된 사전 |
| `set` | 중복 없는 Key | O | O(log n) | 중복 제거 + 정렬 |
| `unordered_map` | Key-Value | X | 평균 O(1) | 이름 → 점수, 빈도수 계산 |
| `unordered_set` | 중복 없는 Key | X | 평균 O(1) | 빠른 중복 검사 |

> `vector[index]`는 O(1) 접근이지만 정렬되지 않은 vector에서 **특정 값을 찾는 검색은 O(n)**이다.

### 어떤 컨테이너를 선택할까?

- 인덱스로 빠르게 접근하고 순회가 많음 → `vector`
- 이름으로 HP를 빠르게 검색 → `unordered_map`
- 중복 없이 항상 정렬된 값 → `set`
- 이름을 정렬한 상태로 Key-Value 저장 → `map`
- 정렬이 필요 없고 중복 여부만 검사 → `unordered_set`

시간 복잡도 외에도 **메모리, 캐시 효율, 순회 순서, 반복자 무효화**를 함께 고려해야 한다.

---

# 5. C++03 / 11 / 14 / 17 차이

| 기능 | C++03 | C++11 | C++14 | C++17 |
| --- | :---: | :---: | :---: | :---: |
| `set`, `map` | O | O | O | O |
| `unordered_map`, `unordered_set` | X | O | O | O |
| `auto` 타입 추론 | X | O | O | O |
| 범위 기반 `for` | X | O | O | O |
| `emplace()` | X | O | O | O |
| 제네릭 람다 | X | X | O | O |
| 구조적 바인딩 | X | X | X | O |
| `try_emplace()` | X | X | X | O |
| `insert_or_assign()` | X | X | X | O |

C++03 표준에는 `std::unordered_map`이 없다. 비슷한 Key-Value 관리에는 `std::map`을 이용할 수 있지만 정렬 특성과 복잡도가 다르다.

C++03 스타일의 set 순회 예:

```cpp
std::set<int> numbers;
numbers.insert(10);
numbers.insert(20);

std::set<int>::const_iterator it;
for (it = numbers.begin(); it != numbers.end(); ++it)
{
    std::cout << *it << '\n';
}
```

C++17 스타일의 unordered_map 순회:

```cpp
for (const auto& [name, count] : inventory)
{
    std::cout << name << ' ' << count << '\n';
}
```

`unordered_map` 순회 순서는 보장되지 않는다.

---

# 6. 자주 헷갈리는 부분

| 잘못 생각하기 쉬운 내용 | 정확한 이해 |
| --- | --- |
| `set<int>`은 내림차순이다 | 기본은 오름차순 |
| `unordered_map`은 삽입 순서로 출력된다 | 순서를 보장하지 않음 |
| `map[key]`는 읽기만 한다 | 없는 키라면 새 요소를 만들 수 있음 |
| `emplace()`는 항상 더 빠르다 | 중복 시 임시 객체를 만들 수 있음 |
| `rehash()`는 참조도 무효화한다 | 반복자는 무효화, 기존 요소 참조는 유지 |
| `set`에 `std::sort()`를 적용한다 | set은 이미 정렬되며 반복자는 Random Access가 아님 |
| `O(1)`이 항상 가장 빠르다 | 실제 성능은 데이터 크기와 상수 비용에도 영향받음 |

---

# 7. 최종 정리

```text
vector
  └─ 연속 저장 / 인덱스 접근 O(1)

set
  └─ 중복 제거 / 자동 정렬 / 검색 O(log n)

unordered_map
  └─ Key-Value / 순서 보장 X / 평균 검색 O(1)

Big-O
  └─ 입력이 증가할 때 연산량이 얼마나 늘어나는지 나타냄
```

```