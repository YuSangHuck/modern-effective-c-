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

/*
// 보편참조 오버로딩 예제.
// cloneOfP(p)에서 완벽전달생성자를 연역하면 Person&가되고
// 복사생성자(const Person&)가 아닌 완벽전달생성자(Person&)가 호출되고,
// std:string에는 Person을 받는 생성자가 없으므로에러
#include <iostream>
#include <string>

class Person {
public:
  template<typename T>
  explicit Person(T&& n): name(std::forward<T>(n)) {
		// T 객체로부터 std::string을 생성할 수 있는지 점검한다.
		static_assert(
			std::is_constructible<std::string, T>::value,
			"Parameter n can't be used to construct a std::string"
		);
  }
  explicit Person(int idx);

private:
  std::string name;
};

class Person2
{
  public:
    template <typename T,
              typename = typename std::enable_if<
               !std::is_base_of<Person2,
                               typename std::decay<T>::type
                               >::value
               >::type>
    explicit Person2(T &&n): name(std::forward<T>(n)) {};

  private:
    std::string name;
};

int main() {
  // Person p1("fail");
  // auto cloneOfP(p1);
  // const Person p2("success");
  // auto cloneOfP(p2);

  Person2 p1("success");
  auto cloneOfP(p1);
  return 0;
}
 */

/*
// std::enable_if 예제
#include <iostream>
#include <type_traits>

// 조건이 참일 때만 이 함수가 활성화됩니다.
template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
foo(T t) {
    std::cout << "Integral type\n";
    return t;
}
// 조건이 거짓일 때만 이 함수가 활성화됩니다.
template <typename T>
typename std::enable_if<!std::is_integral<T>::value, T>::type
foo(T t) {
    std::cout << "Non-integral type\n";
    return t;
}


template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
print(T t) {
    std::cout << "Arithmetic type: " << t << std::endl;
}
template <typename T>
typename std::enable_if<std::is_class<T>::value>::type
print(T t) {
    std::cout << "Class type\n";
}
struct MyClass
{
};

int
main() {
  bool is_class = std::is_class<MyClass>::value;
    bool is_int = std::is_class<int>::value;
    foo(10); // Integral type
    foo(10.5); // Non-integral type

    print(42);   // Arithmetic type: 42
    print(3.14); // Arithmetic type: 3.14
    MyClass myObj;
    print(myObj); // Class type
    return 0;
}
 */

int
main() {
    int x;
    auto& &rx = x;
    return 0;
}

