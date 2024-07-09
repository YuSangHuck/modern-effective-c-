/*
// 오른값 참조?
#include <iostream>
#include <string>

void
foo(const std::string &s) {
    std::cout << "const lvalue reference: " << s << std::endl;
}

void
bar(const std::string &&s) {
    std::cout << "const rvalue reference: " << s << std::endl;
}

int
main() {
    std::string a = "Hello";
    const std::string b = "World";

    foo(a);            // const lvalue reference 호출
    bar(std::move(a)); // const rvalue reference 호출

    // bar(b);  // 컴파일 에러: const lvalue reference는 const rvalue
    // reference로 변환되지 않음

    return 0;
}
 */

/*
#include <iostream>
#include <utility> // std::move

class MyClass
{
  public:
    MyClass() : data_(new int[10]), size_(10) {
        std::cout << "Default constructor" << std::endl;
    }

    // 이동 생성자
    MyClass(MyClass &&other) noexcept : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr; // 원본 객체의 자원을 무효화
        other.size_ = 0;
        std::cout << "Move constructor" << std::endl;
    }

    // 이동 대입 연산자
    MyClass &
    operator=(MyClass &&other) noexcept {
        if (this != &other) {
            delete[] data_; // 기존 자원 해제

            data_ = other.data_;
            size_ = other.size_;

            other.data_ = nullptr; // 원본 객체의 자원을 무효화
            other.size_ = 0;
            std::cout << "Move assignment operator" << std::endl;
        }
        return *this;
    }

    ~MyClass() {
        delete[] data_;
    }

    void
    print() const {
        std::cout << "MyClass with size " << size_ << std::endl;
    }

  private:
    int *data_;
    size_t size_;
};

int
main() {
    MyClass a; // 기본 생성자 호출
    a.print();

    MyClass b = std::move(a); // 이동 생성자 호출
    b.print();
    a.print(); // a는 이동 후 비어있는 상태

    MyClass c;
    c = std::move(b); // 이동 대입 연산자 호출
    c.print();
    b.print(); // b는 이동 후 비어있는 상태

    return 0;
}
 */

/*
#include <iostream>

class MyClass
{
  public:
    MyClass() : data_(0) {
        std::cout << "Default constructor" << std::endl;
    }

    MyClass(int data) : data_(data) {
        std::cout << "Parameterized constructor" << std::endl;
    }

    MyClass(const MyClass &other) : data_(other.data_) {
        std::cout << "Copy constructor" << std::endl;
    }

    MyClass(MyClass &&other) noexcept : data_(other.data_) {
        std::cout << "Move constructor" << std::endl;
        other.data_ = 0;
    }

    ~MyClass() {
        std::cout << "Destructor" << std::endl;
    }

    void
    print() const {
        std::cout << "Data: " << data_ << std::endl;
    }

  private:
    int data_;
};
// RVO를 유도하는 함수
MyClass
createObjectWithRVO() {
    MyClass obj(42); // 생성된 객체
    return obj;      // RVO가 적용될 수 있음
}

// 복사를 강제하는 함수
MyClass
createObjectWithoutRVO() {
    MyClass obj(42);    // 생성된 객체
    MyClass copy = obj; // 명시적으로 복사 생성자 호출
    return copy;        // 복사가 발생할 수 있음
}

int
main() {
    std::cout << "RVO Test:" << std::endl;
    MyClass a = createObjectWithRVO(); // RVO가 적용될 수 있음
    a.print();

    std::cout << "\nNo RVO Test:" << std::endl;
    MyClass b = createObjectWithoutRVO(); // 복사가 발생할 수 있음
    b.print();

    // std::forward()
    // std::move()

    std::cout << std::endl;

    return 0;
}
 */


// 보편참조 오버로딩 예제.
// cloneOfP(p)에서 완벽전달생성자를 연역하면 Person&가되고
// 복사생성자(const Person&)가 아닌 완벽전달생성자(Person&)가 호출되고,
// std:string에는 Person을 받는 생성자가 없으므로에러
#include <iostream>
#include <string>

class Person {
public:
  template<typename T>
  explicit Person(T&& n): name(std::forward<T>(n)) {}
  explicit Person(int idx);

private:
  std::string name;
};

int main() {
  // Person p1("fail");
  // auto cloneOfP(p1);
  const Person p2("success");
  auto cloneOfP(p2);
  return 0;
}

