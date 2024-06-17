# ch0.소개소개

- [ch0.소개소개](#ch0소개소개)
  - [새로운 기능들](#새로운-기능들)
  - [기능의 적용](#기능의-적용)
  - [c++ 버전별 기능](#c-버전별-기능)
  - [책 서술 규칙](#책-서술-규칙)
  - [복사본(복사생성자, 이동생성자, parameter, argument)과 완벽전달](#복사본복사생성자-이동생성자-parameter-argument과-완벽전달)
  - [기본보장(basic guarantee)과 강한보장(strong guarantee)](#기본보장basic-guarantee과-강한보장strong-guarantee)
  - [함수객체(functino object)와 closure](#함수객체functino-object와-closure)
  - [선언과 정의](#선언과-정의)
  - [signature](#signature)
  - [비권장기능](#비권장기능)
  - [미정의 행동](#미정의-행동)
  - [raw 포인터와 smart 포인터와](#raw-포인터와-smart-포인터와)

## 새로운 기능들

- auto 선언
- 범위기반 for loop
- 람다 표현식
- 오른값 참조
- 새로운 동시성기능
- 0,typedef 대신 nullptr과 alias
- enum에 범위 적용
- raw 포인터 보단 smart 포인터(unique_ptr, shared_ptr, weak_ptr과 new보단 make_unique, make_shared)

## 기능의 적용

- auto의 적재적소
- const 멤버함수가 thread-safe한 이유
- std::unique_ptr을 이용해서 Pimpl 관용구를 구현하는 방법
- 람다 표현식에서 기본 갈무리모드 지양하는 이유
- std::atomic과 volatile의 차이

## c++ 버전별 기능

- c++98(c++03 포함)
- c++11(c++14 포함)
  - 동시성, 람다표현식 추가
  - 이동 의미론이 널리 쓰임
    - 이동은 move고, 이동 의미론은 왼값과 오른값에 해당되는 expression이 구분된다는 점의 근거.
    - 즉, 오른값은 이동연산이 가능한 객체, 왼값은 일반적으로 불가능한 객체
    - 그냥 type을 보는게 아니라 주소를 취할수있으면 왼값, 취할수없으면 오른값으로 보는게 편함.
    - cf) c++에서 expression은 독립적인 두가지 속성으로 구분된
          1. type
          2. value category(왼값 오른값이 여기에 해당)
             정확히 얘기하면 값범주는 3가지. 자세한건 [참조](http://www.stroustrup.com/terminology.pdf)
- c++14
  - 일반화된 함수 반환 형식 유추 지원

## 책 서술 규칙

- rhs(right-hand side), lhs(left-hand side)
  - 이동연산(이동 생성자, 이동 배정 연산자)의 매개변수에 주로 사용
  - 복사연산(복사 생성자, 복사 배정 연산자)의 매개변수에 주로 사용
  - 이항 연산자의 매개변수에 주로 사용
- 코드의 볼드체는 좋고 나쁨이 아니라 그냥 조금 더 눈여겨 봐라
- ...는 가변인자가 아니라 그냥 코드 생략

## 복사본(복사생성자, 이동생성자, parameter, argument)과 완벽전달

```c
// parameter는 w이다.
void someFunc(Widget w);

Widget wid;

// 1) 복사생성자
// argument는 wid로 parameter w를 초기화
someFunc(wid);
// 2) 이동생성자
// argument는 std::move(wid)로 parameter w를 초기화
someFunc(std::move(wid));
```
- 복사본이란?
  - 이미 존재하는 객체(a)를 통해 새로운 객체(b)를 초기화 한다면 -> b는 a의 복사본
  - 단, 복사생성자, 이동생성자로 초기화된 객체를 구분하지 않고 모두 복사본이라 함
  - 대체로 오른값 복사본은 이동생성, 왼값 복사본은 복사생성
  - 따라서 한 객체가 복사본인것만 알고있다면, 그 복사본의 생성 cost가 비싼지 싼지는 알 수 없음
  - cost를 알려면 위 예제에서 a)argument가 왼값인지, 오른값인지 b)Widget의 이동과 복사 비용 을 알아야 한다
- parameter와 argument
  - parameter는 함수 정의시 호출과 함께 넘어오는 변수들
  - argument는 함수 호출시 parameter를 초기화 하는데 쓰인다
  - parameter가 왼값이더라도, argument는 왼값일수도 오른값일수도 있고, 이는 완벽전달에서 중요하다
  - 완벽전달은 왼값,오른값여부를 보존해 또 다른 함수로 전달하는 것

## 기본보장(basic guarantee)과 강한보장(strong guarantee)

- 기본보장
  - 잘 설계된 함수는 예외에 안전하다(즉, basic exception safe를 보장한다)
  - 예외 발생하더라도 invariant들이 위반되지 않음(자료구조가 깨지지 않고, 자원 누수가 없음)
- 강한보장
  - 예외 발생하더라도 함수 호출 전,후로 프로그램의 상태가 변하지 않는다

## 함수객체(functino object)와 closure

- 함수객체
  - 일반적으로 operator() 멤버함수를 지원하는 객체를 뜻하고, 이는 함수처럼 행동하는 객체를 의미한다.(c++11)
  - 그러나 때에 따라서 비멤버 함수의 호출구문의 현태를 이용해서 실행할 수 있는 모든것을 뜻한다.(c++98)
  - 즉, c에서 함수포인터도 함수객체에 포함된다.
  - 멤버함수포인터를 추가해서 이를 더욱 일반화하면 호출가능객체(callable object)가 된다
- closure
  - 람다표현식을 통해 생성된 객체
  - 람다표현식과 closure를 굳이 구분해야 하는 경우는 드물어서 보통 둘 다 람다라고 칭하는 경우가 많다.
  - 마찬가지로 함수템플리과 템플릿함수, 클래스템플릿과 템플릿클래스

## 선언과 정의

- 선언은 저장장소와 세부사항 지정 x
- 정의는 저장상소와 세부사항까지 지정
- 이 책에서는 정의가 중요하지 않은경우 보통 선언까지만

## signature

- 함수 선언 중 parameter의 type들과 return type을 지칭

## 비권장기능

- 언제든지 deprecated될 수 있는 기능(알아서 찾아서 지양하자)
- 예를들어 std::auto_ptr가 있고 이는 std::unique_ptr이 더 잘한다

## 미정의 행동

- runtime의 행동을 예측할수없음(불확실성) -> 지양해야 함
  - std::vector의 한원소를 []로 참조시 벡터의 범위를 벗어나는 것
  - 초기화되지않은 iterator를 dereferencing하는것
  - 자료경쟁(멀티스레드에서 공유자원에 동시에 쓰기접근)

## raw 포인터와 smart 포인터와

- 내장포인터 -> raw 포인터
- smart 포인터는 포인터의 역참조 연산자들(operator->, operator*)를 overloading 하지만, std::weak_ptr은 예외다
- dtor는 파괴자(destructor)의 줄임말이다.
