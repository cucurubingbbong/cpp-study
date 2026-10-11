# string (C++03 / C++11 / C++14 / C++17)

## string이란?

`std::string`은 **문자열을 저장하고 관리하는 C++ 표준 라이브러리 타입**이다.

문자열 길이를 확인하거나, 문자를 추가/삭제하거나, 특정 문자열을 검색하고 교체하는 기능을 제공한다.

사용하려면:

```cpp
#include <string>
```

예:

```cpp
std::string name = "Player";
```

> 이 문서의 기본 예제는 C++03부터 사용 가능한 문법으로 설명한다. C++11/14/17에서 추가된 문법은 별도로 표시한다.

---

# char와 string

문자 **하나**는 `char`, 문자열은 `std::string`으로 다룬다.

```cpp
char grade = 'A';
std::string name = "Alice";
```

```text
'A'     -> char, 작은따옴표
"Alice" -> string으로 다룰 수 있는 문자열 리터럴, 큰따옴표
```

문자열을 구성하는 각 문자에는 인덱스가 붙으며 **0부터 시작**한다.

---

# string 선언 및 기본 사용

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string text = "Hello";

    std::cout << text[0] << '\n'; // H
    std::cout << text.size() << '\n'; // 5

    text[0] = 'Y';
    text += " World";

    std::cout << text << '\n'; // Yello World
    return 0;
}
```

주요 기능:

| 기능 | 코드 | 의미 |
| --- | --- | --- |
| 길이 확인 | `s.size()` / `s.length()` | 저장된 문자 수(바이트 수) |
| 비어 있는지 확인 | `s.empty()` | 비어 있으면 `true` |
| 첫 번째 문자 | `s.front()` | C++11부터, 비어 있지 않을 때 사용 |
| 마지막 문자 | `s.back()` | C++11부터, 비어 있지 않을 때 사용 |
| 전체 삭제 | `s.clear()` | 문자열을 빈 문자열로 만듦 |
| 문자 접근 | `s[index]` | 인덱스로 접근 |
| 범위 검사 접근 | `s.at(index)` | 잘못된 위치면 예외 발생 |

`front()`와 `back()`은 **C++11부터 지원**하며, 빈 문자열에 사용하면 안 된다. C++03에서는 비어 있는지 검사한 후 `s[0]`, `s[s.size() - 1]` 같은 방식으로 접근할 수 있다.

```cpp
// C++11부터
if (!text.empty())
{
    std::cout << text.back() << '\n';
}
```

`std::string`의 길이와 인덱스는 `std::string::size_type`으로 표현할 수 있다.

```cpp
std::string::size_type length = text.size();
```

`size_type`은 부호 없는 정수형이며, C++11부터는 `auto`를 이용해 타입을 추론할 수도 있다.

```cpp
// C++11부터
// auto length = text.size();
```

---

# string 입력 — cin과 getline

`std::cin >>`은 공백을 기준으로 입력을 끊는다.

```cpp
std::string name;
std::cin >> name;
```

입력:

```text
Kim Min Su
```

결과:

```text
name = "Kim"
```

공백이 있는 **한 줄 전체**를 받고 싶으면 `std::getline()`을 사용한다.

```cpp
std::string name;
std::getline(std::cin, name);
```

결과:

```text
name = "Kim Min Su"
```

## cin 다음에 getline을 사용할 때 주의

```cpp
int age;
std::string name;

std::cin >> age;
std::getline(std::cin, name);
```

정수만 입력받은 후 입력 버퍼에 남아 있는 줄바꿈(`'\n'`)을 `getline()`이 읽어서 `name`이 빈 문자열이 될 수 있다.

이런 경우에는 남은 줄을 건너뛰고 다음 줄을 읽는다.

```cpp
#include <iostream>
#include <string>
#include <limits>

int main()
{
    int age;
    std::string name;

    std::cin >> age;
    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(), '\n'
    );
    std::getline(std::cin, name);

    std::cout << age << ' ' << name << '\n';
    return 0;
}
```

`ignore()`는 지정한 개수까지 문자를 버리거나, 줄바꿈 문자를 만나면 그 문자를 버리고 멈춘다.

---

# 문자열 연결 — += / append / push_back

`+=`로 뒤에 문자열을 붙일 수 있다.

```cpp
std::string text = "Hello";
text += " World";
// "Hello World"
```

`append()`도 문자열을 뒤에 붙인다.

```cpp
std::string text = "Hello";
text.append(" World");
// "Hello World"
```

같은 문자를 여러 개 추가할 수도 있다.

```cpp
std::string text = "C++";
text.append(3, '!');
// "C++!!!"
```

문자 한 개만 뒤에 붙이려면 `push_back()`을 쓸 수 있다.

```cpp
text.push_back('?');
// "C++!!!?"
```

```text
+=               -> 문자열 등을 뒤에 추가
append("ABC")    -> 문자열을 뒤에 추가
append(3, 'A')   -> 문자 A를 3개 추가
push_back('A')   -> 문자 A를 1개 추가
```

---

# find() — 문자열 검색

`find()`는 지정한 문자열 또는 문자가 **처음으로 등장하는 시작 인덱스**를 반환한다.

```cpp
std::string text = "Hello World";
std::string::size_type pos = text.find("World");

std::cout << pos; // 6
```

구조:

```text
H e l l o   W o r l d
0 1 2 3 4 5 6 7 8 9 10
            ^
            6
```

문자 하나를 찾을 때는 작은따옴표를 사용해도 된다.

```cpp
text.find('W'); // 6
```

## 시작 위치 지정

```cpp
std::string text = "apple banana apple";

std::cout << text.find("apple") << '\n';    // 0
std::cout << text.find("apple", 3) << '\n'; // 13
```

두 번째 인수는 **그 위치 하나만 확인하라는 뜻이 아니라, 그 위치부터 검색을 시작하라는 뜻**이다.

---

# npos — 검색에 실패했을 때

검색 대상이 존재하지 않으면 `find()`는 `std::string::npos`를 반환한다.

```cpp
std::string text = "Hello";

if (text.find("abc") == std::string::npos)
{
    std::cout << "찾지 못함\n";
}
```

`npos`는 `size_type`으로 표현되는 특수한 큰 값이며, `find()` 결과를 비교할 때 사용한다.

```text
find(...) == std::string::npos -> 못 찾음
find(...) != std::string::npos -> 찾음
```

**중요:** 검색 실패 후 `npos`를 그대로 인덱스나 `substr()`의 시작 위치에 사용하면 범위 오류가 발생할 수 있다.

```cpp
std::string text = "Hello";
std::string::size_type pos = text.find("abc");

if (pos != std::string::npos)
{
    std::cout << text.substr(pos);
}
```

`find()`가 실패하는 것 자체는 오류가 아니다. **실패 결과를 검증하지 않고 위치처럼 사용하는 것**이 문제다.

---

# rfind() — 뒤에서부터 검색

`rfind()`는 뒤쪽에서 검색하여 **마지막으로 일치하는 부분의 시작 인덱스**를 반환한다.

```cpp
std::string text = "apple banana apple";

std::cout << text.find("apple") << '\n';  // 0
std::cout << text.rfind("apple") << '\n'; // 13
```

파일 확장자처럼 마지막 구분자를 찾아야 할 때 유용하다.

```cpp
std::string filename = "player.save.txt";
std::string::size_type pos = filename.rfind('.');

if (pos != std::string::npos)
{
    std::string ext = filename.substr(pos + 1);
    std::cout << ext << '\n'; // txt
}
```

이 예제는 문자열 처리를 설명하기 위한 것으로, 실제 파일 경로 처리에는 숨김 파일이나 경로 구분자 등도 고려해야 한다.

---

# substr() — 부분 문자열 만들기

기본 구조:

```cpp
문자열.substr(시작위치, 가져올_문자개수);
```

```cpp
std::string text = "Hello World";

std::string result = text.substr(6, 5);
std::cout << result; // World
```

두 번째 인수는 **끝 인덱스가 아니라 문자 개수**다.

```cpp
std::string text = "Programming";
std::cout << text.substr(3, 4); // gram
```

두 번째 인수를 생략하면 시작 위치부터 끝까지 반환한다.

```cpp
std::string text = "Hello World";
std::cout << text.substr(6); // World
```

원본 문자열은 변경되지 않으며, `std::string::substr()`의 결과는 **새로운 문자열을 소유한다.**

주의:

- 시작 위치가 `size()`보다 크면 `std::out_of_range` 예외가 발생한다.
- 시작 위치가 `size()`와 같으면 빈 문자열을 얻는다.
- 지정한 개수가 남은 길이보다 크면 문자열 끝까지만 가져온다.

---

# insert() — 원하는 위치에 문자열 삽입

```cpp
std::string text = "HelloWorld";
text.insert(5, " ");

std::cout << text; // Hello World
```

`insert(위치, 문자열)`은 그 위치의 **앞에** 문자열을 추가한다.

```cpp
std::string text = "Hello";
text.insert(0, 3, '*');

std::cout << text; // ***Hello
```

```text
insert(0, 3, '*')
       |  |    +-- 넣을 문자
       |  +------- 개수
       +---------- 삽입 위치
```

`size()` 위치에 삽입하면 맨 뒤에 추가된다. `size()`보다 큰 위치는 잘못된 위치다.

---

# erase() — 특정 위치의 문자열 삭제

```cpp
std::string text = "Hello World";
text.erase(5, 1);

std::cout << text; // HelloWorld
```

기본 구조:

```cpp
문자열.erase(시작위치, 삭제할_문자개수);
```

```cpp
std::string text = "ABCDEFG";
text.erase(2, 3);

std::cout << text; // ABFG
```

```text
원본:  A B C D E F G
인덱스 0 1 2 3 4 5 6
          [C D E] 삭제
결과:  A B F G
```

시작 위치만 주면 그 위치부터 끝까지 지운다.

```cpp
std::string text = "Hello World";
text.erase(5); // "Hello"
```

인수를 생략하면 전부 삭제한다.

```cpp
text.erase(); // ""
```

- 시작 위치가 `size()`보다 크면 예외가 발생한다.
- 삭제 개수가 남은 길이보다 크면 끝까지만 지운다.

---

# replace() — 문자열 교체

기본 구조:

```cpp
문자열.replace(시작위치, 교체할_문자개수, 새문자열);
```

```cpp
std::string text = "Hello World";
text.replace(6, 5, "C++");

std::cout << text; // Hello C++
```

교체하는 문자열의 길이는 기존 문자열과 달라도 된다.

## find와 replace를 함께 사용

```cpp
std::string text = "I like Java";
std::string::size_type pos = text.find("Java");

if (pos != std::string::npos)
{
    text.replace(pos, 4, "C++");
}

std::cout << text; // I like C++
```

## 모든 일치 항목 교체하기

```cpp
std::string text = "Java and Java";
std::string before = "Java";
std::string after = "C++";

std::string::size_type pos = text.find(before);

while (pos != std::string::npos)
{
    text.replace(pos, before.size(), after);
    pos = text.find(before, pos + after.size());
}

std::cout << text; // C++ and C++
```

이 예제는 **교체할 문자열이 빈 문자열이 아니며**, 교체 결과에 새 `Java`가 생기지 않는 경우를 가정한다.

문자열을 수정하면 뒤쪽 문자의 인덱스가 바뀔 수 있으므로 검색 위치를 주의해야 한다.

---

# 공백 제거 — find_first_not_of / find_last_not_of

문자열 양쪽의 공백만 제거하고, 중간 공백은 유지하고 싶을 수 있다.

```cpp
std::string message = "  Hello World  ";

std::string::size_type first = message.find_first_not_of(' ');

if (first == std::string::npos)
{
    message.clear();
}
else
{
    message.erase(0, first);

    std::string::size_type last = message.find_last_not_of(' ');
    message.erase(last + 1);
}

std::cout << message; // Hello World
```

의미:

```text
find_first_not_of(' ') -> 첫 번째 공백이 아닌 문자 위치
find_last_not_of(' ')  -> 마지막 공백이 아닌 문자 위치
```

`erase(0, 1)`로 앞 공백을 하나씩 반복해서 제거하면 남은 문자열을 매번 이동시킬 수 있으므로 비효율적일 수 있다. 긴 문자열이라면 앞처럼 한 번에 지우는 방식을 고려한다.

---

# stoi() — 문자열을 정수로 (C++11)

`std::stoi()`는 C++11부터 사용할 수 있다.

```cpp
std::string text = "123";
int number = std::stoi(text);

std::cout << number + 10; // 133
```

## 문자열 전체를 꼭 변환하는 것은 아니다

```cpp
std::string text = "250abc";
std::size_t pos = 0;

int number = std::stoi(text, &pos);

std::cout << number << ' ' << pos; // 250 3
```

`250`까지 변환한 후, **변환에 사용된 문자 개수**인 `3`을 `pos`에 기록한다.

여기서 두 번째 인수 `&pos`는 **참조가 아니라 변수의 주소를 전달하는 포인터 인수**다.

관련 함수 형태:

```cpp
int stoi(const std::string& str,
         std::size_t* pos = nullptr,
         int base = 10);
```

- 첫 번째 인수: 변환할 문자열 (`const` 참조)
- 두 번째 인수: 변환한 문자 개수를 저장할 변수의 주소 (`std::size_t*`)
- 세 번째 인수: 진법 (기본값 10)

변환할 숫자가 없으면 `std::invalid_argument`, `int` 범위를 벗어나면 `std::out_of_range` 예외가 발생할 수 있다.

```cpp
#include <iostream>
#include <string>
#include <stdexcept>

int main()
{
    try
    {
        int value = std::stoi("abc");
        std::cout << value;
    }
    catch (const std::invalid_argument&)
    {
        std::cout << "숫자로 변환 불가\n";
    }
    catch (const std::out_of_range&)
    {
        std::cout << "정수 범위 초과\n";
    }
}
```

문자열 전체가 올바른 숫자인지 확인하려면 `pos == text.size()`까지 검사해야 한다.

---

# to_string() — 숫자를 문자열로 (C++11)

```cpp
int hp = 80;
std::string message = "Player HP: " + std::to_string(hp);

std::cout << message; // Player HP: 80
```

실수를 변환할 때는 C++11~17에서 다음과 같이 소수점 이하가 길게 나타날 수 있다.

```cpp
std::to_string(3.5); // 보통 "3.500000"
```

출력 형식을 자세히 조절해야 한다면 `std::ostringstream` 등을 사용할 수 있다.

---

# C++03 문자열과 숫자 변환 — stringstream

C++03에는 `stoi()`와 `to_string()`이 없다.

`<sstream>`을 이용하면 문자열을 스트림처럼 읽거나 쓸 수 있다.

## 문자열 → 정수

```cpp
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::string text = "123";
    std::istringstream iss(text);

    int number = 0;
    if (iss >> number)
    {
        std::cout << number + 10; // 133
    }
}
```

## 정수 → 문자열

```cpp
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    int number = 123;
    std::ostringstream oss;
    oss << number;

    std::string text = oss.str();
    std::cout << text; // 123
}
```

입력 스트림이 숫자를 하나 읽었다고 해서 뒤에 잘못된 문자가 없는 것까지 검증된 것은 아니다. 입력 형식을 엄격히 검사하려면 남은 내용도 확인해야 한다.

---

# C++14 — 문자열 리터럴 접미사 s

C++14부터 `"..."s`를 사용하면 **문자열 리터럴을 바로 `std::string` 객체로 만들 수 있다.**

```cpp
#include <iostream>
#include <string>

int main()
{
    using namespace std::string_literals;

    std::string text = "Hello"s;
    std::cout << text + " World";
}
```

일반적인 `"Hello"`는 문자열 리터럴이고, `"Hello"s`는 `std::string` 객체가 된다.

> 문자열 리터럴에 `s` 접미사를 쓰는 문법은 C++03/C++11에서는 사용할 수 없다.

---

# C++17 — string_view란?

`std::string_view`는 **문자열을 소유하지 않고, 기존 문자 데이터의 구간을 읽기 전용으로 바라보는 타입**이다.

```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string text = "Hello World";
    std::string_view view = text;

    std::cout << view << '\n';
}
```

주요 차이:

```text
std::string
  -> 문자열 데이터를 소유
  -> 수정 가능
  -> 복사하면 별도의 문자열을 소유

std::string_view
  -> 문자열 데이터를 소유하지 않음
  -> 읽기 전용으로 바라봄
  -> 복사해도 문자 데이터 자체는 복사하지 않음
```

`string_view`는 일반적으로 **문자 위치 + 길이**를 나타내는 작은 객체로 구현된다. 실제 구현 세부 사항에 의존하는 코드는 작성하지 않는 게 좋다.

---

# string.substr와 string_view.substr의 차이

## string: 문자열 내용 복사

```cpp
std::string text = "Hello World";
std::string first = text.substr(0, 5);
// first = "Hello" (별도 소유)
```

## string_view: 같은 데이터의 구간 참조

```cpp
std::string text = "Hello World";
std::string_view view = text;
std::string_view first = view.substr(0, 5);
// first = "Hello"를 참조 (문자 내용 복사 없음)
```

| 항목 | `std::string::substr()` | `std::string_view::substr()` |
| --- | --- | --- |
| 문자 데이터 복사 | O | X |
| 결과가 문자 데이터를 소유 | O | X |
| 일반적인 시간 복잡도 | O(k) | O(1) |
| 원본 수명과 독립적 | O | X |

`k`는 추출한 문자열의 길이다.

---

# string_view 범위 변경 — remove_prefix / remove_suffix

`remove_prefix(n)`은 앞에서 n개를, `remove_suffix(n)`은 뒤에서 n개를 **참조 범위에서 제외한다.**

```cpp
std::string_view text = "Hello World";
text.remove_prefix(6);

std::cout << text; // World
```

```cpp
std::string_view text = "Hello World";
text.remove_suffix(6);

std::cout << text; // Hello
```

실제 원본 문자열을 삭제하는 게 아니다.

주의: 제외할 개수 `n`은 현재 `view.size()` 이하이어야 한다.

---

# Dangling View — string_view 사용 시 가장 중요한 주의사항

`string_view`는 데이터를 **소유하지 않기 때문에** 원본 데이터가 소멸하면 무효한 뷰가 될 수 있다.

## 잘못된 예제 1: 원본이 먼저 소멸

```cpp
std::string_view view;

{
    std::string name = "Knight";
    view = name;
}

std::cout << view; // Undefined Behavior
```

`name`은 블록이 끝나면서 소멸한다. 따라서 `view`가 참조하던 문자는 더 이상 유효하지 않다.

## 잘못된 예제 2: 임시 string 참조

```cpp
std::string_view view = std::string("Hello");
// 이 문장이 끝나면 임시 string이 소멸함
// 이후 view를 읽으면 Undefined Behavior
```

## 잘못된 예제 3: string의 substr 결과를 바로 view로 받음

```cpp
std::string text = "Hello World";
std::string_view view = text.substr(0, 5); // 위험
```

`text.substr()`는 임시 `std::string`을 반환하고, 그 임시 객체는 문장이 끝나면 소멸한다.

## 올바른 예제

```cpp
std::string text = "Hello World";

std::string_view view = text;
std::string_view first = view.substr(0, 5);

std::cout << first; // Hello
```

`text`가 살아 있고 데이터가 유효한 동안만 view를 사용해야 한다.

문자열을 수정하여 재할당 등이 발생하면 기존 포인터나 뷰가 무효화될 수도 있다.

문자열 리터럴은 정적 저장 기간을 가지므로 다음은 안전하다.

```cpp
std::string_view view = "Hello";
```

---

# string_view를 함수 매개변수로 활용

문자열을 **읽기만 하고 보관하지 않는 함수**에 유용하다.

```cpp
#include <iostream>
#include <string>
#include <string_view>

void PrintName(std::string_view name)
{
    std::cout << name << '\n';
}

int main()
{
    std::string player = "Warrior";

    PrintName(player);
    PrintName("Mage");
}
```

`string_view` 매개변수를 함수 밖에 보관하지 않는다면 수명을 관리하기가 비교적 쉽다.

C++03/11/14에서는 읽기 전용 `std::string`을 받는 함수에 보통 `const std::string&`를 사용할 수 있다.

```cpp
void PrintName(const std::string& name)
{
    std::cout << name << '\n';
}
```

두 방식은 목적이 조금 다르다. `string_view`는 문자열 내용을 복사하지 않고 **일부 구간이나 문자열 리터럴도 효율적으로** 받을 수 있지만 소유권이 없다.

---

# string_view.data() 주의

`string_view`는 반드시 널 문자(`'\0'`)로 끝나는 문자열을 가리킨다는 보장이 없다.

```cpp
std::string text = "Hello World";
std::string_view view = text;
std::string_view part = view.substr(0, 5);
```

`part`는 다섯 글자 `Hello`만 나타낸다. 하지만 `part.data()` 뒤에는 원본의 나머지 문자 ` World`가 있을 수 있다.

따라서 `part.data()`를 그대로 C 스타일 널 종료 문자열이 필요한 함수에 전달하면 안 된다.

반면 다음 코드는 길이를 고려해서 출력하므로 안전하다.

```cpp
std::cout << part; // Hello
```

---

# string의 메모리와 수명

`std::string`은 문자열 데이터를 자동으로 관리한다. 범위를 벗어나 객체가 소멸하면 해당 문자열이 소유한 자원도 정리된다.

```cpp
void Test()
{
    std::string text = "Hello";
}
// text의 수명 종료
```

이런 자원 관리 방식은 이전에 배운 **RAII**와 연결된다.

`std::string` 구현은 짧은 문자열을 별도의 동적 할당 없이 객체 내부에 저장하는 **SSO(Small String Optimization)**를 사용할 수 있지만, 구체적인 크기와 동작은 구현마다 다르다.

- `size()`는 현재 문자열의 길이를 반환한다.
- `capacity()`는 재할당 없이 담을 수 있는 용량과 관련된다.
- `reserve()`는 용량 확보를 요청할 수 있다.
- 문자열이 늘어나 재할당되면 기존 문자 포인터나 참조가 무효화될 수 있다.

문자열을 반복적으로 앞에서 지우는 작업은 비용이 커질 수 있으므로 필요하면 인덱스로 먼저 위치를 찾고 한 번에 삭제한다.

---

# []와 at(), 문자 인덱스 안전성

```cpp
std::string text = "Hello";

std::cout << text[1];    // e
std::cout << text.at(1); // e
```

`at()`은 범위를 검사하고, 범위를 벗어나면 `std::out_of_range` 예외를 던진다.

일반적인 문자 접근에 사용할 수 있는 인덱스는 `0`부터 `size() - 1`까지다. 특히 빈 문자열의 첫/마지막 문자 접근을 주의한다.

```cpp
// C++11부터 사용 가능
if (!text.empty())
{
    char last = text.back();
    std::cout << last << '\n';
}
```

---

# 한글과 UTF-8 주의

`std::string`은 일반적으로 **바이트 기반 문자열**을 다룬다.

```cpp
std::string text = "안녕";
std::cout << text.size();
```

UTF-8로 인코딩된 환경에서는 한글 글자 한 개가 보통 3바이트이므로 `size()`가 사람이 세는 글자 수와 다를 수 있다.

또한 `substr()`, `erase()` 등의 인덱스도 바이트 기준이라서 한글 문자의 중간 바이트를 잘라 잘못된 UTF-8 문자열을 만들 수 있다.

**문자열 인코딩과 글자 단위 처리는 별도의 주제**이므로, 기본 문자열 실습에서는 영문/ASCII를 기준으로 연습한다.

---

# C++ 버전별 string 기능 정리

| 버전 | 관련 기능 | 비고 |
| --- | --- | --- |
| C++03 | `string`, `find`, `rfind`, `npos`, `substr` | 기본 문자열 처리 |
| C++03 | `insert`, `erase`, `replace`, `append`, `getline` | 삽입·수정·입력 |
| C++03 | `istringstream`, `ostringstream` | 숫자/문자열 변환 |
| C++11 | `stoi`, `to_string` | 숫자 변환 기능 추가 |
| C++11 | `auto` 타입 추론, `string::front()`, `string::back()` | 타입 선언 간소화 및 문자 접근 |
| C++14 | `"text"s` | `std::string` 리터럴 |
| C++17 | `std::string_view` | 데이터를 소유하지 않는 읽기 전용 뷰 |

컴파일 예:

```bash
g++ -std=c++03 main.cpp -o main
# C++11 기능을 쓰면 -std=c++11
g++ -std=c++11 main.cpp -o main
# C++14 기능을 쓰면 -std=c++14
g++ -std=c++14 main.cpp -o main
# string_view 예제는 C++17 필요
g++ -std=c++17 main.cpp -o main
```

---

# 핵심 문법 최종 정리

```cpp
std::string text = "Hello World";

text.size();                 // 길이
text.empty();                // 빈 문자열인지 검사
text.find("World");         // 처음 발견한 위치
text.rfind('o');             // 마지막으로 발견한 위치
text.substr(6, 5);          // 부분 문자열 복사: World
text.insert(5, "!");        // 지정 위치에 삽입
text.erase(5, 1);           // 지정 위치에서 1개 삭제
text.replace(0, 5, "Hi");   // 지정 부분 교체
text.append("!");           // 뒤에 추가
```

```cpp
// C++11
int number = std::stoi("250");
std::string str = std::to_string(number);
```

```cpp
// C++17
std::string original = "Hello World";
std::string_view view = original;
std::string_view first = view.substr(0, 5); // 데이터 복사 없음
```

## 반드시 기억할 것

1. `find()`가 실패하면 `npos`를 반환한다. 검색 결과는 사용 전에 확인한다.
2. `substr()`, `erase()`, `replace()`의 개수 인수는 **끝 인덱스가 아니다.**
3. `getline()`은 공백까지 입력받고, `cin >>` 다음에 쓸 때 남은 줄바꿈을 주의한다.
4. `stoi()`의 두 번째 인수는 **포인터**이며, 변환한 문자 수를 기록한다.
5. `std::string`은 문자열을 소유하고, `std::string_view`는 **소유하지 않는다.**
6. `string_view`가 참조한 원본이 소멸하면 **Dangling View**가 될 수 있다.
7. C++03/11/14/17에서 쓸 수 있는 기능을 구분한다.

---

# 이번 파트 학습 완료

```text
vector 기본/심화 -> 완료
string 기본/심화 -> 완료

다음 학습 -> iterator (반복자)

begin() / end()
*it / ++it
iterator / const_iterator
rbegin() / rend()
반복자 무효화
STL 알고리즘과의 연결
```
