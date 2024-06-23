- [오른값 참조, 이동 의미론, 완벽 전달](#오른값-참조-이동-의미론-완벽-전달)
  - [item 23. std::move와 std::forward를 숙지하라](#item-23-stdmove와-stdforward를-숙지하라)
    - [책 읽기전 q\&a](#책-읽기전-qa)
      - [정리](#정리)
      - [질답](#질답)

# 오른값 참조, 이동 의미론, 완벽 전달

## item 23. std::move와 std::forward를 숙지하라

### 책 읽기전 q&a

#### 정리

- std::move
  - 객체를 무조건 rvalue로 변환한다(casting에 가깝다)
  - move semantics
- std::forward
  - perfect forwarding

#### 질답

- 항목 23: std::move와 std::forward를 숙지하라의 내용이 이해가 잘 안가는데 자세히 설명해줘
  - c++11에서 도입된 두 가지 중요한 표준 라이브러리 함수에 대한 내용
  - 위 함수들은 이동 시멘틱(?)과 완벽한 전달(perfect forwarding)과 관련있음
  - std::move는 객체를 무조건 rvalue로 casting하며, 이를 통해 객체의 자원을 이동할 수 있고, 이동 시멘틱은 복사보다 효율적이다
  - std::forward는 템플릿 인수 전달시 사용된다. 전달받은 신수를 원래타입 그대로 전달하여, 최적의 성능을 유지하고 완벽한 전달 구현하는데 필수

- 이동 시멘틱과 **perfect forwarding**이 뭐길래 std::move와 std::forward와 관련이 있는가?
  - std::move를 이용하여 lvalue를 rvalue로 casting해 **move semantics**를 활성화 한다
  - std::forward를 이용해 템플릿 함수에서 매개변수를 원래 타입 그대로 전달하여 성능을 최적화 하는것
- MyClass(const std::string& str) : data(str) {}에서 data(str) {}가 뭔지
  - **initializer list**로 객체 생성과 동시에 값을 지정한다. 더 효율적
- 아래 코드 하나하나 설명해줘. c++을 처음 배우는 사람이야. 다음 4가지는 꼭 포함해서 설명해줘 
  - 3) MyClass(MyClass&& other) noexcept : data(std::move(other.data)) { other.data.clear(); }가 뭔지
  - 4) std::move를 안쓰면 어떻게 되는지
```c++
#include <iostream>
#include <string>
#include <utility>

class MyClass {
public:
    std::string data;

    MyClass(const std::string& str) : data(str) {}
    MyClass(MyClass&& other) noexcept : data(std::move(other.data)) {
        other.data.clear();
    }
};

int main() {
    MyClass obj1("Hello");
    MyClass obj2(std::move(obj1));  // obj1의 자원을 obj2로 이동
    std::cout << "obj1: " << obj1.data << std::endl;  // 빈 문자열 출력
    std::cout << "obj2: " << obj2.data << std::endl;  // "Hello" 출력
}
```
- 위 코드에서 obj1이 메모리에 할당되는 구조와, obj2가 메모리에 할당되는 구조가 어떻길래 obj1.data에 빈문자열이 있니? 1) obj1의 rvalue를 생성자 MyClass(MyClass&& other)의 인자로 넘겼고, other의 오른값을 obj2.data에 넣었으니 obj1.data, obj2.data 모두 같은 주소 아니니?
- 아래 코드 하나하나 설명해줘. c++을 처음 배우는 사람이야. 다음 4가지는 꼭 포함해서 설명해줘 1)템플릿 함수가 뭔지 2)wrapper(a)는 왜 Lvalue reference를 호출하는지 3) wrapper(42)는 왜 rvalue reference를 호출하는지는 꼭 설명해줘 4) std::forward를 안쓰면 어떻게 되는지
```c++
#include <iostream>
#include <utility>

void process(int& x) {
    std::cout << "Lvalue reference" << std::endl;
}

void process(int&& x) {
    std::cout << "Rvalue reference" << std::endl;
}

template <typename T>
void wrapper(T&& arg) {
    process(std::forward<T>(arg));
}

int main() {
    int a = 42;
    wrapper(a);          // Lvalue reference 호출
    wrapper(42);         // Rvalue reference 호출
}
```
- int &&rvalueRef = std::move(a); 에서 rvalueRef는 오른값 참조니? 오른값 참조가 뭐니? 보편참조는 뭐니?