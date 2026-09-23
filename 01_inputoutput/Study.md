# C++ 기초 정리

## 목차

1. [GCC와 G++](#1-gcc와-g)
2. [C++ 컴파일 명령어](#2-c-컴파일-명령어)
3. [VS Code의 tasks.json과 launch.json](#3-vs-code의-tasksjson과-launchjson)
4. [C++ 입출력](#4-c-입출력)
5. [입력 스트림 객체](#5-입력-스트림-객체)
6. [std::cin.ignore()](#6-stdcinignore)
7. [std::cin.get()](#7-stdcinget)
8. [\n과 std::endl의 차이](#8-n과-stdendl의-차이)
9. [Flush](#9-flush)
10. [문자열 std::string](#10-문자열-stdstring)
11. [std::getline()](#11-stdgetline)
12. [cin과 getline을 같이 사용할 때 주의점](#12-cin과-getline을-같이-사용할-때-주의점)

---

# 1. GCC와 G++

GCC와 G++는 작성한 소스 코드를 컴파일하여 **실행 가능한 프로그램을 만드는 데 사용하는 컴파일러 드라이버**이다.

## GCC

```bash
gcc
```

GCC는 일반적으로 C 프로그램을 컴파일할 때 사용한다.

파일 확장자에 따라서 입력 파일의 언어를 판단할 수 있다.

예를 들어:

```text
main.c
```

는 C 소스 코드로 인식하고,

```text
main.cpp
```

는 C++ 소스 코드로 인식한다.

단, C++ 프로그램에서는 C++ 표준 라이브러리 링크 문제 때문에 일반적으로 `gcc`보다 `g++`를 사용하는 것이 편하다.

---

## G++

```bash
g++
```

G++는 C++ 프로그램을 컴파일할 때 주로 사용한다.

C++ 표준 라이브러리도 자동으로 링크해주기 때문에 C++ 코드를 작성할 때 일반적으로 `g++`를 사용한다.

---

# 2. C++ 컴파일 명령어

예제:

```bash
g++ main.cpp -o main.exe
```

각 부분의 의미는 다음과 같다.

| 명령어        | 의미                              |
| ---------- | ------------------------------- |
| `g++`      | C++ 컴파일러 호출                     |
| `main.cpp` | 컴파일할 C++ 소스 코드 파일               |
| `-o`       | Output의 약자로, 출력 파일의 이름을 지정하는 옵션 |
| `main.exe` | 생성할 실행 파일 이름                    |

즉,

```bash
g++ main.cpp -o main.exe
```

는

> `main.cpp`를 컴파일해서 `main.exe`라는 실행 파일을 만들어라.

라는 의미이다.

프로그램의 기본적인 실행 과정은 다음과 같다.

```text
소스 코드
   ↓
컴파일
   ↓
실행 파일(.exe)
   ↓
프로그램 실행
```

---

# 3. VS Code의 tasks.json과 launch.json

VS Code에서 C++ 프로그램을 사용할 때 주로 다음 두 설정 파일을 사용한다.

```text
tasks.json
launch.json
```

## tasks.json

`tasks.json`은 주로 **컴파일 작업**을 담당한다.

예를 들어 내부적으로 다음과 같은 명령어를 실행하도록 설정할 수 있다.

```bash
g++ main.cpp -o main.exe
```

즉,

```text
.cpp
 ↓
tasks.json
 ↓
컴파일
 ↓
.exe
```

와 같은 역할을 한다.

---

## launch.json

`launch.json`은 만들어진 실행 파일을 **디버거를 통해 실행하기 위한 설정**을 담당한다.

```text
.cpp
 ↓
컴파일
 ↓
.exe
 ↓
launch.json
 ↓
디버거 실행
```

`launch.json`의 자세한 내용은 나중에 디버깅을 공부할 때 다시 정리한다.

---

# 4. C++ 입출력

C++에서 콘솔 입출력을 사용하려면 다음 헤더를 사용한다.

```cpp
#include <iostream>
```

`iostream`은 C++에서 기본적인 **입력(Input)과 출력(Output)** 기능을 제공하는 표준 헤더이다.

---

## std

`std`는 C++ 표준 라이브러리가 들어 있는 **네임스페이스(namespace)** 이다.

예를 들어:

```cpp
std::cout
std::cin
std::string
std::endl
```

등이 있다.

C#으로 비유하면 `System` 네임스페이스와 비슷한 개념으로 생각할 수 있다.

---

## cout

`cout`은 **Character Output**의 의미이며 콘솔 출력을 담당하는 객체이다.

출력할 때는 `<<` 연산자를 사용한다.

`<<`를 **삽입 연산자(Insertion Operator)** 라고 부른다.

```cpp
std::cout << "Hello";
```

여러 값을 연속으로 출력할 수도 있다.

```cpp
std::cout << "Hello\n" << "World";
```

결과:

```text
Hello
World
```

변수도 출력할 수 있다.

```cpp
int hp = 100;

std::cout << "HP : " << hp;
```

결과:

```text
HP : 100
```

---

## cin

`cin`은 **Character Input**의 의미이며 콘솔 입력을 담당하는 객체이다.

입력할 때는 `>>` 연산자를 사용한다.

`>>`를 **추출 연산자(Extraction Operator)** 라고 부른다.

```cpp
int age;

std::cin >> age;
```

`age`가 `int` 타입이기 때문에 입력된 내용을 정수 형태로 읽으려고 한다.

예를 들어:

```text
20
```

을 입력하면

```cpp
age == 20
```

이 된다.

---

## 여러 값 입력받기

`>>`를 연속해서 사용하면 여러 개의 값을 한 번에 입력받을 수 있다.

```cpp
int id;
int age;

std::cin >> id >> age;
```

입력:

```text
10 25
```

결과:

```text
id = 10
age = 25
```

공백이나 Enter 등을 기준으로 각각의 값을 구분해서 읽는다.

---

## Enter를 입력하면?

키보드에서 Enter를 누르면 입력 스트림에는 줄바꿈 문자가 들어간다.

일반적으로 줄바꿈 문자는 다음과 같이 표현한다.

```text
\n
```

이 줄바꿈 문자가 입력 버퍼에 남아 있는 상황이 생길 수 있으며, 특히 `std::cin >>`과 `std::getline()`을 함께 사용할 때 주의해야 한다.

---

# 5. 입력 스트림 객체

C++에는 다양한 입력 스트림 객체가 존재한다.

## std::cin

콘솔, 즉 키보드로부터 입력을 받는다.

```cpp
std::cin >> age;
```

---

## std::ifstream

파일로부터 데이터를 읽어오는 **파일 입력 스트림**이다.

사용하려면 다음 헤더가 필요하다.

```cpp
#include <fstream>
```

예:

```cpp
std::ifstream file("data.txt");
```

---

## std::stringstream

문자열을 마치 입력 스트림처럼 사용할 수 있게 해주는 스트림이다.

문자열 파싱 등에 자주 사용된다.

사용하려면 다음 헤더가 필요하다.

```cpp
#include <sstream>
```

예:

```cpp
std::stringstream ss("10 20");

int a;
int b;

ss >> a >> b;
```

결과:

```text
a = 10
b = 20
```

---

# 6. std::cin.ignore()

`ignore()` 함수는 **입력 버퍼에 남아 있는 불필요한 문자를 버리는 함수**이다.

기본 형태:

```cpp
std::cin.ignore(무시할_최대_문자_개수, 종료_문자);
```

예:

```cpp
std::cin.ignore(100, '\n');
```

의미:

> 최대 100개의 문자를 버리되, `\n`을 만나면 거기까지 버린다.

---

## 매개변수

```cpp
std::cin.ignore(100, '\n');
```

### 첫 번째 매개변수

```cpp
100
```

무시할 문자의 **최대 개수**이다.

### 두 번째 매개변수

```cpp
'\n'
```

어떤 문자를 만날 때까지 버릴 것인지 지정한다.

---

# 7. std::cin.get()

`std::cin.get()`은 **문자 하나를 입력받는 함수**이다.

예:

```cpp
char ch;

std::cin.get(ch);
```

입력:

```text
A
```

결과:

```text
ch = 'A'
```

`>>`와 다르게 공백이나 줄바꿈 같은 문자도 읽을 수 있다는 특징이 있다.

---

# 8. \n과 std::endl의 차이

둘 다 줄바꿈을 할 수 있지만 동작에는 차이가 있다.

## \n

```cpp
std::cout << "Hello\n";
```

단순히 **줄바꿈 문자**를 출력한다.

### 특징

* 단순 줄바꿈
* 일반적으로 빠름
* 반복문에서 대량 출력할 때 적합
* 알고리즘 문제에서 자주 사용

예:

```cpp
for (int i = 0; i < 10000; i++)
{
    std::cout << i << '\n';
}
```

---

## std::endl

```cpp
std::cout << "Hello" << std::endl;
```

`std::endl`은 두 가지 작업을 수행한다.

```text
줄바꿈
+
출력 버퍼 Flush
```

따라서 단순히 줄바꿈만 필요한 경우에는 `\n`보다 불필요한 작업이 추가될 수 있다.

### 특징

* 줄바꿈 수행
* 출력 버퍼 Flush 수행
* 반복적으로 사용하면 성능에 영향을 줄 수 있음
* 즉시 출력을 보내야 하는 상황에서 사용할 수 있음

---

## 비교

| 구분        | `\n` | `std::endl` |
| --------- | ---- | ----------- |
| 줄바꿈       | O    | O           |
| Flush     | X    | O           |
| 일반적인 출력   | 권장   | 필요할 때 사용    |
| 반복문 대량 출력 | 적합   | 상대적으로 비효율적  |

---

# 9. Flush

프로그램의 출력은 항상 즉시 화면으로 전달되는 것은 아니다.

성능을 위해 출력 내용을 임시 공간인 **버퍼(Buffer)** 에 저장했다가 한 번에 처리할 수 있다.

```text
프로그램
   ↓
출력 버퍼
   ↓
콘솔
```

**Flush**는 출력 스트림의 내부 버퍼에 쌓여 있는 데이터를 강제로 출력하고 버퍼를 처리하도록 만드는 작업이다.

명시적으로 Flush만 하고 싶다면 다음과 같이 사용할 수 있다.

```cpp
std::cout << std::flush;
```

예:

```cpp
std::cout << "Loading..." << std::flush;
```

---

# 10. 문자열 std::string

C++에서 문자열을 사용하려면 일반적으로 `<string>` 헤더를 포함한다.

```cpp
#include <string>
```

문자열은 다음과 같이 선언한다.

```cpp
std::string name;
```

예:

```cpp
std::string name = "Pupu";
```

---

## cin으로 문자열 입력받기

```cpp
std::string name;

std::cin >> name;
```

`std::cin >>`은 기본적으로 **공백을 기준으로 입력을 구분한다.**

예를 들어 다음처럼 입력했다고 하자.

```text
장 푸푸
```

다음 코드에서는

```cpp
std::cin >> name;
```

`name`에

```text
장
```

만 저장된다.

공백 뒤의 `푸푸`는 같은 문자열에 포함되지 않는다.

---

# 11. std::getline()

공백을 포함해서 **한 줄 전체를 입력받고 싶다면** `std::getline()`을 사용한다.

```cpp
std::getline(std::cin, name);
```

예:

```cpp
std::string name;

std::getline(std::cin, name);
```

입력:

```text
장 푸푸
```

결과:

```text
name = "장 푸푸"
```

---

## getline의 매개변수

```cpp
std::getline(std::cin, name);
```

### 첫 번째 매개변수

```cpp
std::cin
```

데이터를 읽어올 **입력 스트림 객체**이다.

### 두 번째 매개변수

```cpp
name
```

읽어온 문자열을 저장할 `std::string` 변수이다.

---

# 12. cin과 getline을 같이 사용할 때 주의점

다음 코드를 생각해보자.

```cpp
int age;
std::string name;

std::cin >> age;
std::getline(std::cin, name);
```

사용자가 다음과 같이 입력한다.

```text
20 [Enter]
```

`std::cin >> age`는 숫자 `20`을 읽는다.

하지만 Enter로 입력된 줄바꿈 문자 `\n`이 입력 스트림에 남아 있을 수 있다.

개념적으로 보면 다음과 같다.

```text
입력

20\n
```

`std::cin >> age` 실행 후:

```text
age = 20

입력 스트림에 남은 내용:
\n
```

그 다음:

```cpp
std::getline(std::cin, name);
```

을 실행하면 `getline()`은 `\n`을 만나면 한 줄의 입력이 끝났다고 판단한다.

따라서 사용자가 새로운 문자열을 입력하기도 전에 빈 문자열을 읽어버리는 문제가 발생할 수 있다.

---

## 해결 방법

`getline()`을 실행하기 전에 남아 있는 줄바꿈 문자를 제거한다.

```cpp
int age;
std::string name;

std::cin >> age;
std::cin.ignore();

std::getline(std::cin, name);
```

좀 더 안전하게 줄 끝까지 제거하려면 다음과 같이 사용할 수 있다.

```cpp
#include <iostream>
#include <string>
#include <limits>

int main()
{
    int age;
    std::string name;

    std::cout << "나이 : ";
    std::cin >> age;

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    );

    std::cout << "이름 : ";
    std::getline(std::cin, name);

    std::cout << "나이 : " << age << '\n';
    std::cout << "이름 : " << name << '\n';
}
```

핵심 흐름은 다음과 같다.

```text
std::cin >> age
        ↓
숫자를 읽음
        ↓
입력 버퍼에 \n이 남을 수 있음
        ↓
std::cin.ignore()
        ↓
남아 있는 \n 제거
        ↓
std::getline()
        ↓
새로운 한 줄을 정상적으로 입력받음
```

---

# 핵심 요약

```text
g++
 └─ C++ 코드 컴파일

tasks.json
 └─ VS Code에서 컴파일 작업 설정

launch.json
 └─ 실행 / 디버깅 설정

std::cout
 └─ 콘솔 출력
    └─ << 사용

std::cin
 └─ 콘솔 입력
    └─ >> 사용

std::cin.ignore()
 └─ 입력 버퍼의 불필요한 문자 제거

std::cin.get()
 └─ 문자 하나 읽기

\n
 └─ 줄바꿈

std::endl
 └─ 줄바꿈 + Flush

std::string
 └─ 문자열

std::cin >> string
 └─ 공백 전까지만 읽음

std::getline()
 └─ 공백을 포함한 한 줄 전체 읽기
```
