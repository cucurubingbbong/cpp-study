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
```
