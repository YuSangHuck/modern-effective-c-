# ch1.형식 연역(type deduction)

- [ch1.형식 연역(type deduction)](#ch1형식-연역type-deduction)
  - [요약](#요약)
  - [개요](#개요)
  - [템플릿 type deduction 규칙을 숙지하라](#템플릿-type-deduction-규칙을-숙지하라)

## 요약

- 템플릿 함수의 인자에 const나 참조한정사를 붙여라?
- type deduction이란
  - T와 ParamType을 deduction 하는 것이고,
  - 2가지에 의존해서 deduction을 하게 된다.
    - 템플릿 함수의 ParamType
    - 호출될 때 인자로 넘기는 expr

## 개요

- c++98에서는 template에 대한 type deduction만 존재했으나
- c++11에서 2가지 규칙 추가(auto, decltype)
- type들을 compiler에게 맡기므로 한 지점을 수정하면 compiler가 type deduction을 통해 전파하므로 수정해야할 부분은 줄었지만
- 코드의 의미 추론은 어려워졌다. 컴파일러의 deduction과 개발자의 추론이 상이할 수 있으므로
- 따라서 type deduction방식을 완벽히 이해해야 생산성을 높일 수 있다.
- 추가로 type deduction의 결과를 명시적으로 표시하는 방법도 알아보자


## 템플릿 type deduction 규칙을 숙지하라

- 좋은 소식은 auto는 템플릿 type deduction 규칙 기반으로 작동한다
- 나쁜 소식은 c++11에서는 c++98보단 덜 직관적임

아래는 함수 템플릿 관련 의사코드이다.
```cpp
// 함수 템플릿 선언
template<typename T>
void f(ParamType param);
// 함수 템플린 호출
f(expr);
```

컴파일러는 컴파일 도중 expr을 이용해서 두가지 type을 deduction한다.

하나는 T에 대한 type deduction이고,하나는 ParamType에 대한 type deduction이다

보통 T와 ParamType은 type이 다른데, 이는 ParamType에 const나 참조한정사(&나 &&)를 붙이므로

```cpp
template<typename T>
void f(const T& param);

int x = 0;
f(x);
// T는 `int`로
// ParamType은 `const int&`로
```

보통은 T와 expr의 type이 같을거라고 생각.
위 예제에서 x는 int이고, 실제로 T도 int로 deduction 됨.

그러나 type deduction은 expr 뿐만 아니라, ParamType의 형태에도 의존한다.
ParamType의 형태는 세가지로 분류 할 수 있다

- ParamType이 포인터 또는 참조 형식이지만, 보편참조는 아닌 경우
- ParamType이 보편 참조인 경우
- ParamType이 포인터도, 참조도 아닌 경우

- ParamType이 포인터 또는 참조 형식이지만, 보편참조는 아닌 경우
  - expr이 참조라면, 참조 부분을 무시
  - expr의 type을 ParamType에 대해 pattern-matching 방식으로 대응시켜 T를 결정
```cpp
template<typename T>
void f(T& param); // param은 참조형식

int x = 27;         // x는 int
const int cx = x;   // cx는 const int
const int& rx = x;  // rx는 const int인 x에 대한 참조

f(x);               // expr: int                      => T: int,        param: int&
f(cx);              // expr: const int                => T: const int,  param: const int&
f(rx);              // expr: const int& -> const int  => T: const int,  param: const int&
```

해설하면 아래와 같다.
위에서 f(rx)의 경우 ParamType이 T&로 참조 형식이므로
expr인 rx에서 참조 부분을 무시하면 const int&에서 const int가 되고
const int를 ParamType인 T&에 pattern-matching하면 param은 const int&가 되고
T는 const int가 된다.

다음 사실에 주목하자

- f(cx), f(rx)를 보면 인자로 넘기는 객체의 const성이 T의 deduction 결과의 일부가 된다.
  - ParamType이 T&로 참조이고, expr이 cx,rx인 경우 const이므로 param의 type에 const가 붙고, &가 붙었다.
  - 이는 호출자 입장에서 중요한데, const 객체를 인자로 넘겨도, 객체가 변하지 않을것을 기대 할 수 있기 때문이다.
- f(rx)를 보면 rx의 type이 참조이지만, T는 비참조로 deduction 됨
  - 이는 type deduction 과정 중 expr의 참조성이 무시되므로

ParamType에 const를 붙이거나, 참조가아닌 포인터인 경우 봐야 함
