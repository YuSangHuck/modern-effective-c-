- [ch5. 오른값 참조, 이동 의미론, 완벽 전달](#ch5-오른값-참조-이동-의미론-완벽-전달)
  - [그냥 사전지식?](#그냥-사전지식)
  - [item 23. std::move와 std::forward를 숙지하라](#item-23-stdmove와-stdforward를-숙지하라)
    - [1. move는 오른값으로 무조건 캐스팅한다. 이동하는게 아니다.](#1-move는-오른값으로-무조건-캐스팅한다-이동하는게-아니다)
    - [2. forward는 주어진 인수가 오른값에 묶인 경우에만, 오른값으로 캐스팅 한다.](#2-forward는-주어진-인수가-오른값에-묶인-경우에만-오른값으로-캐스팅-한다)
    - [3. move,forward 둘 다 싱핼시점에서는 아무일도 하지 않는다.](#3-moveforward-둘-다-싱핼시점에서는-아무일도-하지-않는다)
  - [item 24. 보편 참조와 오른값 참조를 구별하라](#item-24-보편-참조와-오른값-참조를-구별하라)
    - [1. 함수 템플릿 매개변수의 형식이 T\&\&이고, T가 연역된다면 또는 객체를 auto\&\&로 선언한다면 이는 보편참조이다.](#1-함수-템플릿-매개변수의-형식이-t이고-t가-연역된다면-또는-객체를-auto로-선언한다면-이는-보편참조이다)
    - [2. 형식선언의 형태가 정확히 형식\&\&가 아니면, 혹은 형식 연역이 일어나지 않는다면 이는 오른값참조다.](#2-형식선언의-형태가-정확히-형식가-아니면-혹은-형식-연역이-일어나지-않는다면-이는-오른값참조다)
    - [3. 오른값으로 초기화되는 보편참조는 오른값참조에 해당한다. 왼값으로 초기화되는 보편참조는 왼값참조에 해당한다.](#3-오른값으로-초기화되는-보편참조는-오른값참조에-해당한다-왼값으로-초기화되는-보편참조는-왼값참조에-해당한다)
  - [item 25. 오른값 참조에는 std::move를, 보편참조에는 std::forward를 사용하라](#item-25-오른값-참조에는-stdmove를-보편참조에는-stdforward를-사용하라)
    - [1. 오른값참조나 보편참조가 마지막으로 쓰이는 지점에서, 오른값참조에는 move를, 보편참조에는 forward를 사용하라](#1-오른값참조나-보편참조가-마지막으로-쓰이는-지점에서-오른값참조에는-move를-보편참조에는-forward를-사용하라)
    - [2. 결과를 값 전달하는 함수이고, 오른값참조,보편참조인 경우 move,forward를 사용하라](#2-결과를-값-전달하는-함수이고-오른값참조보편참조인-경우-moveforward를-사용하라)
    - [3. RVO가 적용될 수 있는 지역객체에는 move,forward를 적용하지 말라](#3-rvo가-적용될-수-있는-지역객체에는-moveforward를-적용하지-말라)
  - [item 26. 보편참조에 대한 중복적재를 피하라](#item-26-보편참조에-대한-중복적재를-피하라)
    - [1. 보편참조에 오버로딩의 빈번한 호출:보편참조를 사용한 오버로딩은 예상보다 자주 호출되는 상황으로 이어진다.](#1-보편참조에-오버로딩의-빈번한-호출보편참조를-사용한-오버로딩은-예상보다-자주-호출되는-상황으로-이어진다)
    - [2. 완벽전달생성자는 non-const 왼값에 대해 복사생성자보다 더 좋은 매칭이 된다. 이는 기본클래스의 복사,이동 생성자를 호출하려는 파생클래스의 생성자 호출을 가로챌 수 있는 문제가 있어 의도치 않은 동작을 유발 할 수 있다](#2-완벽전달생성자는-non-const-왼값에-대해-복사생성자보다-더-좋은-매칭이-된다-이는-기본클래스의-복사이동-생성자를-호출하려는-파생클래스의-생성자-호출을-가로챌-수-있는-문제가-있어-의도치-않은-동작을-유발-할-수-있다)
  - [item 27. 보편참조에 대한 오버로딩 대신 사용할 수 있는 기법들을 알아두라](#item-27-보편참조에-대한-오버로딩-대신-사용할-수-있는-기법들을-알아두라)
    - [1. 보편참조와 오버로딩의 조합에 대한 대안으로는 구별되는 함수이름 사용, 매개변수를 const에 대한 왼값 참조로 전달, 매개변수를 값으로 전달, 꼬리표 배분 사용 등이 있다.](#1-보편참조와-오버로딩의-조합에-대한-대안으로는-구별되는-함수이름-사용-매개변수를-const에-대한-왼값-참조로-전달-매개변수를-값으로-전달-꼬리표-배분-사용-등이-있다)
    - [2. std::enable\_if 를 통해 템플릿의 인스턴스화를 제한함으로써 보편참조와 오버로딩을 함께 사용할 수 있다(std::enable\_if 는 컴파일러가 보편참조를 오버로딩하는 조건을 개발자가 직접 제어)](#2-stdenable_if-를-통해-템플릿의-인스턴스화를-제한함으로써-보편참조와-오버로딩을-함께-사용할-수-있다stdenable_if-는-컴파일러가-보편참조를-오버로딩하는-조건을-개발자가-직접-제어)
    - [3. 보편참조 매개변수는 효율성 면에서 장점인 경우가 많지만, 대체로 사용성 면에서는 단점이 된다](#3-보편참조-매개변수는-효율성-면에서-장점인-경우가-많지만-대체로-사용성-면에서는-단점이-된다)
  - [item 28. 참조축약(collapse)을 숙지하라](#item-28-참조축약collapse을-숙지하라)
    - [1. 참조축약은 템플릿 인스턴스화, auto 타입 추론, typedef와 별칭선언의 지정 및 사용, decltype의 지정 및 사용이라는 네가지 문맥에서 일어난다.](#1-참조축약은-템플릿-인스턴스화-auto-타입-추론-typedef와-별칭선언의-지정-및-사용-decltype의-지정-및-사용이라는-네가지-문맥에서-일어난다)
    - [2. 컴파일러가 참조축약 문맥에서 참조에 대한 참조를 만들어 내면, 그 결과는 하나의 참조가 된다. 원래의 두 참조 중 하나라도 왼값 참조이면 결과는 왼값 참조이고, 그렇지 않으면 오른값 참조이다.](#2-컴파일러가-참조축약-문맥에서-참조에-대한-참조를-만들어-내면-그-결과는-하나의-참조가-된다-원래의-두-참조-중-하나라도-왼값-참조이면-결과는-왼값-참조이고-그렇지-않으면-오른값-참조이다)
    - [3. 타입추론이 왼값과 오른값을 구분하는 문맥과 참조축약이 일어나는 문맥에서 보편참조는 오른값 참조이다.](#3-타입추론이-왼값과-오른값을-구분하는-문맥과-참조축약이-일어나는-문맥에서-보편참조는-오른값-참조이다)
  - [item 29. 이동연산이 존재하지않고, 저렴하지 않고, 적용되지 않는다고 가정하라.](#item-29-이동연산이-존재하지않고-저렴하지-않고-적용되지-않는다고-가정하라)
    - [1. 이동연산들이 존재하지 않고, 저렴하지 않고, 적용되지 않을것이라고 가정하라.](#1-이동연산들이-존재하지-않고-저렴하지-않고-적용되지-않을것이라고-가정하라)
    - [2. 타임들과 이동의미론 지원여부를 미리 알 수 있는경우에는 그런 가정을 둘 필요가 없다](#2-타임들과-이동의미론-지원여부를-미리-알-수-있는경우에는-그런-가정을-둘-필요가-없다)
  - [item 30. 완벽전달이 실패하는 경우들을 잘 알아두라](#item-30-완벽전달이-실패하는-경우들을-잘-알아두라)
    - [1. 완벽 전달은 템플릿 타입 추론이 실패하거나, 틀린 타입을 추론했을 때 실패한다](#1-완벽-전달은-템플릿-타입-추론이-실패하거나-틀린-타입을-추론했을-때-실패한다)
    - [2. 인수가 중괄호 초기치이거나 0 또는 NULL로 표현된 널포인터, 선언만 된 정수 static sconst 및 constexpr 데이터 멤버, 템플릿 오버로딩된 함수 이름, 비트필드이면 완벽전달이 실패한다](#2-인수가-중괄호-초기치이거나-0-또는-null로-표현된-널포인터-선언만-된-정수-static-sconst-및-constexpr-데이터-멤버-템플릿-오버로딩된-함수-이름-비트필드이면-완벽전달이-실패한다)

# ch5. 오른값 참조, 이동 의미론, 완벽 전달

## 그냥 사전지식?

- 참조란?
  - alias, 포인터에 비해 메모리(주소저장)와 연산(주소연산)면에서 효율적
  - 수정가능성(alias이므로 원본 데이터)
  - null safe
- 오른값 참조란?
  - 말 그대로 오른값에 대한 참조로, 이동의미론과 완벽전달에 사용
  - 이동의미론은 복사대신 이동을 통한 효율성
  - 완벽전달은 인자를 완벽히 전달해 성능 및 유연성 유지
- 보편참조는?
  - 생긴건 오른값 참조처럼 &&지만, template, auto, ... 에 사용
  - lvalue, rvalue 모두 참조를 받을 수 있으므로 유연(완벽전달)
  - const vs non-const, volatile vs non-volatile 그냥 유연 그 자체
- lvalue, xvalue, rvalue
  - [참조](https://modoocode.com/294)
  - type과 value category가 있는데
  - 정체의 유무, 이동가능성으로 나눔
- 참조의 변환
  - const T&& -> const T& 가능(상수성 유지)

| x      | 이동 가능 | 이동불가능 |
| ------ | --------- | ---------- |
| 정체 o | xvalue    | lvalue     |
| 정체 x | pravlue   | 쓸모 없음  |

- decltype{표현식}은 함수처럼 쓰이고, 컴파일시 표현식에 대한 type을 반환한다
  - decltype(xavlue) -> T&&
  - decltype(lavlue) -> T&
  - decltype(ravlue) -> T

## item 23. std::move와 std::forward를 숙지하라

### 1. move는 오른값으로 무조건 캐스팅한다. 이동하는게 아니다.

- move(이동 의미론)
  - 1. 이동을 할 객체가 const면 복사하므로 이동을 보장하지않고, const로 선언하면 안된다.
    - `string(string&& rhs)`일 때, `Annotation(const std::string text): value(std::move(text)) { ... }` // string의 이동생성자가 존재할 때, text는 이동이 아닌 복사된다(const 정확성 유지를 위해)
      - text가 const 왼값이므로 std::move(text)는 const text의 오른값 참조를 반환
      - const 오른값 참조인데, 이동생성자는 오른값 참조이므로 이동생성자 호출 안됨
      - const 오른값 참조는 암시적으로 const 왼값 참조로 변환될 수 있으므로 복사생성자 호출
  - 2. 확실한건 반환값은 오른값 참조이긴 함(이동된 오른값 참조거나, 복사된 오른값 참조거나)

### 2. forward는 주어진 인수가 오른값에 묶인 경우에만, 오른값으로 캐스팅 한다.

- forward(move와 비슷하나 조건부 casting, 완벽 전달)
  - forward의 인수가 오른값으로 초기화 된 경우에만, 오른값으로 casting한다
  - 오른값으로 초기화 여부는 어떻게 아는가? 템플릿 매개변수에 부호화 되어있다.(T에대해 연역을 할때 부호화 되어있음. [item 28](#3-타입추론이-왼값과-오른값을-구분하는-문맥과-참조축약이-일어나는-문맥에서-보편참조는-오른값-참조이다))

- 그러면 forward만 써도 되는가?
  - 가능은 하지만, 굳이? 명확성도 떨어지고 버그가능성도 높아지고?

### 3. move,forward 둘 다 싱핼시점에서는 아무일도 하지 않는다.

## item 24. 보편 참조와 오른값 참조를 구별하라

> 걍 두개 구분해라가 전부고
> 오른값참조는 이동을 위해(이동의 원본 객체 지정)
> 보편참조는 전달을 위해(전달의 원본 객체 지정?)

### 1. 함수 템플릿 매개변수의 형식이 T&&이고, T가 연역된다면 또는 객체를 auto&&로 선언한다면 이는 보편참조이다.

### 2. 형식선언의 형태가 정확히 형식&&가 아니면, 혹은 형식 연역이 일어나지 않는다면 이는 오른값참조다.

### 3. 오른값으로 초기화되는 보편참조는 오른값참조에 해당한다. 왼값으로 초기화되는 보편참조는 왼값참조에 해당한다.

- 오른값 참조
  - `void f(Widget&& param)`
  - `Widget&& var1 = Widget()`
  - `template<typename T> void f(std::vector<T>&& param)`
- 보편참조
  - `auto&& var2 = var1`
  - `template<typename T> void f(T&& param)`

- 오른값 참조
  - 이동의 원본이 될 수 있는 개체 지정
- 보편참조
  - 거의 항상 전달을 적용해야하므로 전달참조라고 부르기도 함
  - 초기값에 따라 왼값참조 혹은 오른값참조
  - 형식 연역이 일어나는 문맥이고, 단, T&& 형태여야만 한다
  - 형식연역은 호출타임에 일어난다(vector의 push_back은 이미 인스턴스화 된 시점에서 type이 고정임)

## item 25. 오른값 참조에는 std::move를, 보편참조에는 std::forward를 사용하라

### 1. 오른값참조나 보편참조가 마지막으로 쓰이는 지점에서, 오른값참조에는 move를, 보편참조에는 forward를 사용하라

- 오른값참조를 다른 함수에 전달할 때는 move
  <details>
    <summary>예제</summary>

    ```cpp
    //-----------------------------------------------------------------------------
    // 우측값 객체를 다른 함수에 넘겨주되 그 함수가
    // 객체의 우측값 성질을 활용할 수 있도록
    // 넘겨주어야 하는 경우도 흔히 생긴다.

    // 이를 위해서는 그런 객체에 묶이는 매개변수를
    // 우측값으로 캐스팅해야 한다.

    // 항목 23에서 설명하듯이, std::move가
    // 하는 일이 바로 그것이다.

    class Widget {
    public:
      Widget(Widget&& rhs)					// rhs는 우측값 참조
      : name(std::move(rhs.name)),
        p(std::move(rhs.p))
        { ... }
      ...

    private:
      std::string name;
      std::shared_ptr<SomeDataStructure> p;
    };
    ```
  </details>
- 보편참조를 다른 함수에 전달할 때는 forward
  <details>
    <summary>예제</summary>

    ```cpp
    //-----------------------------------------------------------------------------
    // 반면 보편 참조(universal reference)는 이동에 적합한 객체에
    // 묶일 수도 있고 아닐 수도 있다(항목 24 참고).

    // 보편 참조(universal reference)는 우측값으로 초기화되는 경우에만
    // 우측값으로 캐스팅되어야 한다.

    // 항목 23에서 설명하듯이, std::forward가
    // 하는 일이 바로 그것이다.

    class Widget {
    public:
      template <typename T>
      void setName(T&& newName)				// newName은
      { name = std::forward<T>(newName); }	// 보편 참조(universal reference)

      ...
    };
    ```
  </details>
- forward 대신 move를 사용 할 수도 있지만, 관용적인 표현도 아니고 그렇게 해서 이득이 없다. 그냥 하지마라
  <details>
    <summary>예제</summary>

    ```cpp
    //-----------------------------------------------------------------------------
    // 항목 23에서 설명하듯이 우측값 참조에
    // std::forward를 사용해도 되지만, 소스
    // 코드가 장황하고 실수의 여지가 있으며
    // 관용구에서 벗어난 모습이 된다.

    // 따라서 우측값 참조에 std::forward를
    // 사용하는 것은 피해야 한다.

    // 보편 참조(universal reference)에 std::move를 사용하는
    // 것은 더 나쁘다.

    // 그러면 좌측값이 의도치 않게 수정되는
    // 결과가 빚어질 수 있기 때문이다.

    class Widget {
    public:
      template <typename T>
      void setName(T&& newName)				    // 보편 참조(universal reference)
      { name = std::move(newName); }			// 컴파일되긴 하지만
      ...										// 아주 아주 나쁘다!

    private:
      std::string name;
      std::shared_ptr<SomeDataStructure> p;
    };

    std::string getWidgetName(void);			// 팩터리 함수

    Widget w;

    auto n = getWidgetName();					// n은 지역 변수

    w.setName(n);								// n을 w로 이동한다.

    ...											// 이제 n의 값은 알 수 없다.
    ```
  </details>

- 보편참조를 쓰면 3가지 장점
  - 유지보수 편함
    <details>
      <summary>예제</summary>

      ```cpp
      class Widget {
      public:
        void setName(const std::string& newName)	// const 좌측값으로
        { name = newName; }							// name을 설정

        void setName(std::string&& newName)			// 우측값으로
        { name = std::move(newName); }				// name을 설정

        ...
      };
      ```
    </details>
  - 효율성(임시객체 생성 및 소멸)
    <details>
      <summary>예제</summary>

      ```cpp
      w.setName("Adela Novak");
      ```
    </details>
  - 오른값일수도 왼값일수도 있는 매개변수가 무제한인 경우 overloading은 불가능. 오로지 보편참조
    <details>
      <summary>예제</summary>

      ```cpp
      template <class T, class... Args>				// C++11 표준에서
      shared_ptr<T> make_shared(Args&&... args);		// 발췌

      template <class T, class... Args>				// C++14 표준에서
      unique_ptr<T> make_unique(Args&&... args);		// 발췌

      // 이런 함수들에 대해서는 좌측값과 우측값에 대한
      // 오버로딩이 현실적으로 불가능하다.
      ```
    </details>
- move,forward를 적용하는 시점은 해당 참조를 다 쓰고 마지막 참조여야 한다.
  <details>
    <summary>예제</summary>

    ```cpp
    template <typename T>
    void setSignText(T&& text)					// text는 보편 참조(universal reference)
    {
      sign.setText(text);						// text를 사용하되
                                    // 수정하지는 않는다.

      auto now =								// 현재 시간을 얻는다.
        std::chrono::system_clock::now();

      signHistory.add(now,
              std::forward<T>(text));	// text를 우측값으로
    }											// 조건부 캐스팅
    ```
  </details>

### 2. 결과를 값 전달하는 함수이고, 오른값참조,보편참조인 경우 move,forward를 사용하라

- 함수의 결과가 값을 반환한다면, move나 forward를 사용하는게 바람직하다(복사보단 이동이 낫다)
  <details>
    <summary>예제</summary>

    ```cpp
    //-----------------------------------------------------------------------------
    // 함수가 결과를 값으로 돌려준다면(return by value),
    // 그리고 그것이 우측값 참조나 보편 참조(universal reference)에
    // 묶인 객체라면, 해당 참조를 돌려주는 return
    // 문에서 std::move나 std::forward를 사용하는
    // 것이 바람직하다.

    Matrix											// 결과를 값으로
    operator+(Matrix&& lhs, const Matrix& rhs)		// 반환
    {
      lhs += rhs;
      return std::move(lhs);						// lhs를 반환값으로
    }												// 이동한다.

    // return 문에서 lhs를 우측값으로 캐스팅한
    // 덕분에, 컴파일러는 lhs를 함수의 반환값
    // 장소로 이동한다.

    // 다음처럼 std::move 호출이 없다면,

    Matrix
    operator+(Matrix&& lhs, const Matrix& rhs)
    {
      lhs += rhs;
      return lhs;									// lhs를 반환값으로
    }												// 복사한다.

    // lhs가 좌측값이므로, 컴파일러는 그것을
    // 반환값 장소로 복사해야 한다.

    // Matrix 타입이 복사 생성보다 효율적인
    // 이동 생성을 지원한다고 할 때, return
    // 문에서 std::move를 사용하면 좀 더
    // 효율적인 코드가 만들어진다.

    // Matrix가 이동을 지원하지 않는다고
    // 해도, 우측값으로의 캐스팅이 해가 되지는
    // 않는다.

    // 이 경우 그냥 복사가 일어난다(항목 23 참고).

    // 오히려 나중에 Matrix에 이동 지원이 추가되면,
    // 다음번에 operator+를 재컴파일 했을 때
    // 효율성이 저절로 향상된다(얻을 것이 많다).


    //-----------------------------------------------------------------------------
    // 보편 참조(universal reference)와 std::forward에 대한
    // 상황도 이와 비슷하다.

    // 기약분수가 아닐 수도 있는 분수를 나타내는
    // Fraction 객체를 받아서 그것을
    // 약분한 결과의 복사본을 돌려주는 함수
    // 템플릿 reduceAndCopy가 있다고 하자.

    // 만일 원래의 객체가 우측값이라면, 그 객체의
    // 값을 반환값으로 이동하는 것이 바람직하다.

    // 그러나 원래의 객체가 좌측값이라면 실제로
    // 복사본을 생성해야 한다.

    template <typename T>
    Function							// 값 전달 방식의 반환값
    reduceAndCopy(T&& frac)				// 보편 참조(universal reference) 매개변수를 받는다.
    {
      frac.reduce();
      return std::forward<T>(frac);	// 우측값은 반환값으로
    }
    ```
  </details>

### 3. RVO가 적용될 수 있는 지역객체에는 move,forward를 적용하지 말라

- RVO가 적용되면 지역객체를 반환하는 함수에서 반환값이 복사되는걸 막을 수 있다. 조건은 1)지역객체의 타입이 반환타입과 같아야하고, 2)지역객체가 반환값이어야 한다
- 표준에 따르면 RVO가 허용되는 경우, 복사제거가 일어나거나, 아니면 반환되는 객체에 암묵적으로 std::move가 적용된다.
- 따라서 함수가 지역객체를 반환하는 경우 std::move를 쓰면 RVO를 무효화하거나, 어차피 암묵적으로 적용될것이므로 쓰지 않는게 좋다.
  <details>
    <summary>예제</summary>

    ```cpp
    Widget makeWidget(void)
    {
      Widget w;
      ...
      return w;
    }

    // 이 경우 컴파일러는 반드시 w의 복사 제거를
    // 수행하거나, 아니면 함수를 애초에 다음과 같이
    // 작성된 것처럼 취급해야 한다.

    Widget makeWidget(void)
    {
      Widget w;
      ...
      return std::move(w);		// 복사 제거를 수행하지 않을 때에는
    }								// w를 우측값으로 취급한다.

    // 이는 값 전달 방식의 함수
    // 매개변수의 경우와 비슷하다.

    // 그런 매개변수는 함수의 반환값
    // 최적화를 위한 복사 제거의
    // 대상이 아니지만, 함수가 그런
    // 매개변수를 반환하는 경우
    // 컴파일러는 그것을 반드시
    // 우측값으로 취급해야 한다.

    // 즉, 다음과 같은 함수가 있을 때

    Widget makeWidget(Widget w)		// 함수의 반환값과 타입이 같은,
    {								// 값 전달 방식의 매개변수
      ...
      return w;
    }

    // 컴파일러는 이를 마치 다음과 같이
    // 작성된 것처럼 취급해야 한다.

    Widget makeWidget(Widget w)
    {
      ...
      return std::move(w);		// w를 우측값으로 취급한다.
    }
    ```
  </details>

## item 26. 보편참조에 대한 중복적재를 피하라

### 1. 보편참조에 오버로딩의 빈번한 호출:보편참조를 사용한 오버로딩은 예상보다 자주 호출되는 상황으로 이어진다.

- 보편참조를 받는 템플릿 함수는 c++에서 가장 욕심이 많은 함수다. -> 개발자의 예상보다 훨신 많은 인수형식을 담당하게 된다.
  <details>
    <summary>예제</summary>

    ```cpp
    std::multiset<std::string> names;			// 전역 자료구조

    template <typename T>
    void logAndAdd(T&& name)
    {
      auto now = std::chrono::system_clock::now();
      log(now, "logAndAdd");
      names.emplace(std::forward<T>(name));
    }

    std::string petName("Darla");				// 이전과 동일

    logAndAdd(petName);							// 이전처럼 좌측값이
                          // multiset으로 복사됨

    logAndAdd(std::string("Persephone"));		// 우측값을 이동한다
                          // (복사가 아니라).


    logAndAdd("Patty Dog");						// 임시 std::string 객체를
                          // 복사하는 대신, multiset
                          // 안에 std::string을
                          // 생성한다.

    // 이름은 모르고 idx만 알고있는 클라이언트들을 위해
    // logAndAdd를 오버로딩한다고
    // 하자.

    void logAndAdd(int idx)
    {
      auto now = std::chrono::system_clock::now();
      log(now, "logAndAdd");
      names.emplace(nameFromIdx(idx));
    }

    // 두 오버로딩된 함수에 대한 호출들은
    // 예상대로 적절히 해소된다.

    std::string petName("Darla");				// 이전과 동일

    logAndAdd(petName);							// 이전과 동일, 이들은
    logAndAdd(std::string("Persephone"));		// 모두 T&&를 받는
    logAndAdd("Patty Dog");						// 오버로딩된 함수를 호출한다.

    logAndAdd(22);								// int 버전을 호출한다.

    // 그런데 다음의 경우에는 예상대로
    // 작동하지 않는다.

    short nameIdx;
    ...											// nameIdx에 값을 대입

    logAndAdd(nameIdx);							// 오류!

    // 보편 참조(universal reference)를 받는 버전은 T를 short&로
    // 추론할 수 있으며, 그러면 주어진
    // 인수와 정확히 부합하는 형태가 된다.

    // int를 받는 버전은 short 인수를 int로
    // 승격(promotion)해야 호출과 부합한다.

    // 보통의 오버로딩 해소 규칙에 따라,
    // 정확한 부합이 승격을 통한 부합보다.
    // 우선시된다.

    // 결국 보편 참조(universal reference)를 받는 오버로딩된 함수가
    // 호출된다.

    // 따라서 emplace에 short값이 전달되지만,
    // std::string의 생성자 중에 short를
    // 받는 버전이 없으므로, 오류가
    // 발생한다.

    ```
  </details>

### 2. 완벽전달생성자는 non-const 왼값에 대해 복사생성자보다 더 좋은 매칭이 된다. 이는 기본클래스의 복사,이동 생성자를 호출하려는 파생클래스의 생성자 호출을 가로챌 수 있는 문제가 있어 의도치 않은 동작을 유발 할 수 있다

- 완벽전달생성자
  <details>
    <summary>예제</summary>

    ```cpp
    class Person {
    public:
      template <typename T>			// 완벽 전달 생성자
      explicit Person(T&& n)
      : name(std::forward<T>(n)) {}

      explicit Person(int idx);		// int를 받는 생성자

      Person(const Person& rhs);		// 복사 생성자
                      // (컴파일러가 작성함)

      Person(Person&& rhs);			// 이동 생성자
                      // (컴파일러가 작성함)
      ...
    private:
      std::string name;
    };

    Person p("Nancy");

    auto cloneOfP(p);					// p로부터 새 Person을 생성
                      // 컴파일에 실패한다!

    // 이 코드를 보면, 복사 생성자를 호출할 것
    // 같지만 사실 복사 생성자를 호출하지 않는다.

    // 실제로는 완벽 전달 생성자가 호출되며,
    // std::string에는 Person을 받는 생성자가
    // 없으므로 오류가 발생한다.
    ```
  </details>
- 상속이 관여되면 더 심각함
  <details>
    <summary>예제</summary>

    ```cpp
    //-----------------------------------------------------------------------------
    // 상속이 관여하는 클래스에는 완벽 전달 생성자와
    // 컴파일러가 작성한 복사 및 이동 연산들 사이의
    // 상호작용이 미치는 여파가 더욱 크다.

    // 특히, 파생 클래스에서 통상적인 방식으로
    // 구현한 복사 및 이동 연산들이 상당히 놀라운
    // 행동을 보인다.

    class SpecialPerson: public Person {
    public:
      SpecialPerson(const SpecialPerson& rhs)	// 복사 생성자;
      : Person(rhs);							// 기반 클래스의 완벽
      { ... }									// 전달 생성자를 호출

      SpecialPerson(SpecialPerson&& rhs)		// 이동 생성자;
      : Person(std::move(rhs))				// 기반 클래스의 완벽
      { ... }									// 전달 생성자를 호출
    };

    // 파생 클래스의 복사, 이동 생성자들은 해당 기반
    // 클래스의 복사, 이동 생성자를 호출하지 않고
    // 기반 클래스의 완벽 전달 생성자를 호출한다.

    // 왜 그런지는 파생 클래스 함수들이 SpecialPerson
    // 타입의 인수를 기반 클래스에 넘겨준다는 점에
    // 주목해서 Person 클래스 안에서의 템플릿
    // 인스턴스화 오버로딩 해소 과정을 짚어 보면
    // 이해할 수 있다.

    // 결과적으로, SpecialPerson을 받는 std::string
    // 생성자가 없어서 컴파일되지 않는다.
    ```
  </details>

위의 문제점들에 대한 해결책은 27에서 보자

## item 27. 보편참조에 대한 오버로딩 대신 사용할 수 있는 기법들을 알아두라

### 1. 보편참조와 오버로딩의 조합에 대한 대안으로는 구별되는 함수이름 사용, 매개변수를 const에 대한 왼값 참조로 전달, 매개변수를 값으로 전달, 꼬리표 배분 사용 등이 있다.

- 오버로딩을 포기
  - 단순히 오버로딩을 포기하고, 보편참조를 받는 함수와, 아닌 함수를 이름으로 구별. 생성자는 이름이 정해져있으므로 이 방법을 적용할 수 없다.
- 매개변수를 const에 대한 왼값 참조로 전달
  - 보편참조 대신 const T&를 매개변수로 받고, 오버로딩을 한다. 효율성을 포기하고 예기치 않은 문제를 피하라.
- 매개변수를 값으로 전달
  - 확실히 복사가 될 객체는 보편참조 대신 값으로 전달하라
- 꼬리표 배분 사용
  <details>
    <summary>예제</summary>

    ```cpp
    template <typename T>
    void logAndAdd(T&& name)
    {
      logAndAddImpl(
        std::forward<T>(name),
        std::is_integral<typename std::remove_reference<T>::type>()
      );
    }

    // 우선 보편 참조(universal reference)를 받는 버전을 보자.
    template <typename T>								// 비정수 인수를
    void logAndAddImpl(T&& name, std::false_type)		// 받는 버전:
    {													// 그 인수를 전역
      auto now = std::chrono::system_clock::now();	// 자료구조에 추가
      log(now, "logAndAdd");							// 한다.
      names.emplace(std::forward<T>(name));
    }

    // T가 정수 타입일 때 호출되는 logAndAddImpl의
    // 오버로딩 버전은 다음과 같다.
    std::string nameFromIdx(int idx);					// 항목 26에 나옴

    void logAndAddImpl(int idx, std::true_type)			// 정수 인수를
    {													// 받는 버전:
      logAndAdd(nameFromIdx(idx));					// 조회한 이름으로
    }													// logAndAdd를
                              // 호출한다.


    logAndAdd(1) // logAndAddImpl(int, std::true_type) 호출
    logAndAdd("1") // logAndAddImpl(T&&, std::false_type) 호출
    ```
  </details>
  - 하지만, 일반함수가 아닌 생성자인 경우, 컴파일러가 자동생성한 복사생성자가 문제가 될 수 있다. 이 경우 템플릿을 제한하는 방법을 써야 함

### 2. std::enable_if 를 통해 템플릿의 인스턴스화를 제한함으로써 보편참조와 오버로딩을 함께 사용할 수 있다(std::enable_if 는 컴파일러가 보편참조를 오버로딩하는 조건을 개발자가 직접 제어)

- 보편참조를 받는 템플릿을 제한한다
  - std::enable_if 를 이용하면 컴파일러가 마치 특정 템플릿이 존재하지 않는 것처럼 행동하게 할 수 있고, 그런 템플릿을 disabled 템플릿이라 부른다.
  - 기본적으로 모든 템플릿은 enabled 상태이며, std::enable_if 를 사용하면 지정된 조건을 만족할 때만 enable 된다.
    <details>
      <summary>예제</summary>

      ```cpp
      // std::enable_if<bool>
      // std::is_same<T, U> // type 비교
      // std::decay<T> // cv 한정사 제거(const, volatile) 및 배열과 함수타입의 경우 포인터
      // std::is_base_of<Base, Derived> // Derived 가 Base 에서 파생되면 true
      class Person {
      public:
        template <
          typename T,
          typename = std::enable_if_t<
            !std::is_base_of<Person, std::decay_t<T> >::value
            &&
            !std::is_integral<std::remove_reference_t<T> >::value
          >
        >
        explicit Person(T&& n)			// std::string이나
        : name(std::forward<T>(n))		// std::string으로 변환되는
        { ... }							// 인수를 위한 생성자

        explicit Person(int idx)		// 정수 인수를 위한 생성자
        : name(nameFromIdx(idx))
        { ... }

        ...								// 기타 복사, 이동 연산자들

      private:
        std::string name;
      };
      ```
    </details>

### 3. 보편참조 매개변수는 효율성 면에서 장점인 경우가 많지만, 대체로 사용성 면에서는 단점이 된다

- 절충점들
  - 완벽전달에도 단점은 있다. 그 중 하나는 완벽전달이 불가능한 인수들이 있다는 점. 구체적인 타입을 받는 함수에는 전달할 수 있어도 완벽 전달은 불가능할 수 있다. 이처럼 완벽전달이 불가능한 경우는 [item 30](#item-30-완벽전달이-실패하는-경우들을-잘-알아두라)에서 알아보자
  - 또 다른 단점은 클라이언트가 유효하지 않은 인수를전달했을 때 나오는 오류메시지가 난해하다.
  - 이러한 이유로 보편참조를 성능이 최우선 관심사인 인터페이스에만 사용하는것이 좋다고 생각하는 개발자들이 많다.
  - Person의 경우 전달함수의 보편참조 매개변수가 std::string에 대한 초기치로 쓰일것을 알고있으므로, 그런 초기치로 사용하는것이 가능한지를 미리 static_assert를 이용해 점검하는 방법도 있다. std::in_constructible이라는 타입 특성은 한타입의 객체를 다른 한타입(또는 타입들의 집합)의 객체(또는 객체들의 집합)로부터 생성할 수 있는지를 컴파일 시점에서 판정한다. 이를 이용하면 assertion을 쉽게 작성할 수 있다.
    <details>
      <summary>예제</summary>

      ```cpp
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

      private:
        std::string name;
      };

      int main() {
        Person p1("fail");
        auto cloneOfP(p1);

        return 0;
      }
      ```
    </details>

## item 28. 참조축약(collapse)을 숙지하라

### 1. 참조축약은 템플릿 인스턴스화, auto 타입 추론, typedef와 별칭선언의 지정 및 사용, decltype의 지정 및 사용이라는 네가지 문맥에서 일어난다.

- 참조에 대한 참조는 c++에서 위법이지만, 보편참조에 대한 참조는 된다
  <details>
    <summary>예제</summary>

    - 참조에 대한 참조는 오류
      ```cpp
      int main() {
        // 오류! 참조에 대한 참조는
        // 선언할 수 없음
        int x;
        auto& &rx = x; // int& &rx = x

        return 0;
      }
      ```
    - 템플릿 인스턴스화에서 참조축양
      ```cpp
      template <typename T>
      void func(T&& param);

      int main() {
        // func를 왼값으로 호출한다.
        // 보편참조의 초기치가 왼값이니 보편참조는 왼값참조로 추론된다. T는 Widget&
        // void func<Widget&>(Widget& && param); 로 추론되고
        // T는 Widget&로 축약된다.
        Widget w;
        func(w);

        return 0;
      }
      ```
    - auto 타입 추론서 참조축약
      ```cpp
      int main() {
        // 보편참조의 초기치가 왼값이니 보편참조는 왼값참조로 추론된다. type은 Widget&
        // Widget& && w1 = w;
        // type은 Widget&로 축약
        Widget w;
        auto&& w1 = w;

        return 0;
      }
      ```
    - typedef와 별칭선언의 지정 및 사용서 참조축약
      ```cpp
      template <typename T>
      class Widget {
      public:
        typedef T&& RvalueRefToT;
        ...
      };
      int main() {

        // 그리고 Widget을 왼값 참조 타입으로
        // 인스턴스화한다고 하자.
        Widget<int&> w;

        // Widget의 T를 int&로 대체하면
        // typedef는 다음과 같은 모습이 된다.
        typedef int& && RvalueRefToT;

        // 참조 축약(collapse)에 의해 이는 다음으로
        // 줄어든다.
        typedef int& RvalueRefToT;

        return 0;
      }
      ```
    - decltype의 지정 및 사용(item 3을 참조하라)
  </details>

### 2. 컴파일러가 참조축약 문맥에서 참조에 대한 참조를 만들어 내면, 그 결과는 하나의 참조가 된다. 원래의 두 참조 중 하나라도 왼값 참조이면 결과는 왼값 참조이고, 그렇지 않으면 오른값 참조이다.

- 참조는 왼값, 오른값 참조가 있으므로, 조합은 4가지이고, 둘다 오른값인경우만 오른값참조, 그 외에는 왼값 참조다.

### 3. 타입추론이 왼값과 오른값을 구분하는 문맥과 참조축약이 일어나는 문맥에서 보편참조는 오른값 참조이다.

- 보편참조에 대해서 왼값 인수가 전달되면 T는 왼쪽값참조로, 오른값 인수가 전달되면 T는 비참조로 추론되며, 이는 T가 추론된 타입에 따라 param이 왼값인지,오른값인지 알 수 있는 정보가 부호화 되어있음을 의미
  <details>
    <summary>예제</summary>

    ```cpp
    template <typename T>
    void func(T&& param);

    int main() {
      // 우측값을 돌려주는 함수
      Widget widgetFactory();

      // 변수(좌측값)
      Widget w;

      // func를 좌측값으로 호출한다;
      // T는 Widget&로 추론된다.
      func(w);

      // func를 우측값으로 호출한다;
      // T는 Widget으로 추론된다.
      func(widgetFactory());

      return 0;
    }
    ```
  </details>
- std::forward가 작동하는 것은 참조축약 덕분이다
  <details>
    <summary>예제</summary>

    ```cpp
    //-----------------------------------------------------------------------------
    // std::forward 함수의 일반적인 용례는
    // 다음과 같은 모습이다.

    template <typename T>
    void f(T&& fParam)
    {
      someFunc(std::forward<T>(fParam));	// fParam을
    }										                  // someFunc로 전달

    // std::forward는 대략 다음과 같이 생겼을
    // 것이다. 이것은 완벽히 정확한 구현은 아니지만,
    // std::forward의 작동 방식을 이해하는
    // 목적으로는 충분하다.

    template <typename T>									                  // 이름공간
    T&& forward(typename remove_reference<T>::type& param)	// std 안에서
    {
      return static_cast<T&&>(param);
    }


    //-----------------------------------------------------------------------------
    // f에 전달된 인수가 Widget
    // 타입의 좌측값이라고 하자.

    // 그러면 T는 Widget&로 추론되며,
    // std::forward 호출은 std::forward<Widget&>
    // 형태로 인스턴스화된다.

    // Widget&를 std::forward의 구현에 대입하면
    // 다음과 같은 코드가 나온다.

    Widget& && forward(typename remove_reference<Widget&>::type& param)
    {
      return static_cast<Widget& &&>(param);
    }

    // 타입 특성 std::remove_reference<Widget&>::type은
    // Widget을 산출하므로, std::forward는 다음이 된다.

    Widget& && forward(Widget& param)
    {
      return static_cast<Widget& &&>(param);
    }

    // 참조 축약(collapse)은 반환 타입과 캐스팅에도 적용된다.
    // 참조 축약(collapse)까지 적용한 최종 버전은 다음과 같이 된다.

    Widget& forward(Widget& param)				// 여전히 이름공간
    {											                // std 안에서
      return static_cast<Widget&>(param);
    }

    // 이 예에서 보듯이, 좌측값 인수가 전달되면
    // std::forward는 좌측값 참조를 돌려준다.


    //-----------------------------------------------------------------------------
    // f에 전달된 인수가 Widget 타입의 우측값일
    // 때에는 어떻게 될까?

    // 이 경우 f의 타입 매개변수 T에 대해 추론되는
    // 타입은 그냥 Widget이다.

    // 따라서 f 내부의 std::forward 호출은
    // std::forward<Widget>으로 인스턴스화된다.

    // std::forward의 구현에서 T를 Widget으로
    // 대체하면 다음과 같은 모습이 된다.

    Widget&& forward(typename remove_reference<Widget>::type& param)
    {
      return static_cast<Widget&&>(param);
    }

    // std::remove_reference를 비참조 타입 Widget에
    // 적용하면 애초의 타입(Widget)이 산출되므로, std::forward는
    // 다음이 된다.

    Widget&& forward(Widget& param)
    {
      return static_cast<Widget&&>(param);
    }

    // 여기에는 참조에 대한 참조가 없으므로 참조 축약(collapse)도 없다.
    // 이것이 이 호출에 대한 std::forward 인스턴스의 최종
    // 버전이다.

    // 정리하자면, f에 전달된 우측값 인수는 하나의
    // 우측값으로써 someFunc에 전달되며, 이 역시 마땅히
    // 그래야 하는 결과이다.


    //-----------------------------------------------------------------------------
    // C++14에서는 std::remove_reference_t 덕분에
    // std::forward를 좀 더 간결하게 구현할 수 있다.

    template <typename T>						          // C++14; 역시
    T&& forward(remove_reference_t<T>& param)	// 이름공간 std
    {											                    // 안에서
      return static_cast<T&&>(param);
    }
    ```
  </details>

## item 29. 이동연산이 존재하지않고, 저렴하지 않고, 적용되지 않는다고 가정하라.

### 1. 이동연산들이 존재하지 않고, 저렴하지 않고, 적용되지 않을것이라고 가정하라.

- c++11은 c++98 표준 라이브러리를 전체적으로 개정했는데, 특히 이동을 복사보다 빠르게 구현할 수 있는 타입들에는 이동연산을 추가했다. 또한 라이브러리 구성요소들의 구현을 그런 연산들의 장점을 취하도록 개정했다.
- 그러나 c++11에 맞게 우리가 다루는 코드가 수정되지 않았다면, 컴파일러가 이동을 지원한다고 해도 성능이 저절로 좋아지지는 않을 것이다.
- 이동연산을 명시적으로 지원하지 않는 타입에 대해 c++11이 자동으로 이동연산을 작성해주긴하지만, 타입에 복사연산자,이동연산,소멸연산 중 하나라도 있으면 자동작성은 일어나지 않는다.
- 타입의 데이터 멤버나 기반 클래스에 이동이 비활성화되어있으면, 역시 컴파이러의 이동연산 작성은 일어나지 않는다. 이동을 명시적으로 지원하지 않으며 컴파일러의 이동연산 작성의 대상이 아닌 타입에 대해서는 C++98에 비해 c++11이 어떤 형태로든 성능을 향상해주리라고 기대할 이유가 없다.
- 이동을 명시적으로 지원하는 타입에서도, 성능상의 이득이 생각만큼 크지 않을 수 있다.
- 예를 들어 c++11 표준 라이브러리의 모든 컨테이너는 이동을 지원하지만, 모든 컨테이너의 이동이 저렴하다고 가정하는 것은 실수다. 그 이유는 이동을 저렴하게 만들 방법이 없는 컨테이너들도 있고, 컨테이너가 제공하는 진정으로 저렴한 이동 연산이 요구하는 까다로운 조건을 컨테이너 요소들이 만족할 수 없는 경우도 있기 때문이다.
  <details>
    <summary>예제</summary>

    ```cpp
    //-----------------------------------------------------------------------------
    // C++11에 새로 도입된 컨테이너인
    // std::array를 생각해 보자.

    // std::array는 내장 배열에 STL 인터페이스를
    // 씌운 것이다.

    // 이 컨테이너는 자신의 내용을 힙에 저장하는
    // 다른 표준 컨테이너들과는 근본적으로 다르다.

    // 개념적으로, 그런 컨테이너 타입의 객체는
    // 컨테이너의 내용이 저장된 힙 메모리를
    // 가리키는 포인터만 담는다.

    // 컨테이너 전체 내용을 상수 시간으로 이동할 수
    // 있는 것은 바로 이 포인터 덕분이다.

    // 그런데 std::array 객체에는 그런 포인터가 없다.

    // std::array의 내용은 std::array 객체
    // 자체에 직접 저장되기 때문이다.

    // std::array에 담긴 원소의 타입이 복사보다 빠른
    // 이동 연산을 지원한다면, 그 std::array는
    // 복사하는 것보다 이동하는 것이 더 빠르다.

    std::array<Widget, 10000> aw1;

    // aw1에 데이터를 채운다.

    ...

    // aw1을 aw2로 이동한다. 이 이동은
    // 선형 시간으로 실행된다. aw1의
    // 모든 원소가 aw2로 이동된다.
    auto aw2 = std::move(aw1);

    // 만일 Widget의 이동 연산이 복사 연산보다
    // 빠르다면 aw1을 aw2로 복사하는 것 보다
    // 이동하는 것이 더 빠르다.

    // 하지만, 더 빠르다고 해도 여전히 선형
    // 시간이 걸린다는 사실은 변함이 없다.

    // aw1의 모든 요소를 일일히 이동해야
    // 하기 때문이다.


    //-----------------------------------------------------------------------------
    // std::string은 어떨까?

    // 항상 이동이 복사보다 빠를것 같지만,
    // 그렇지 않을 수도 있다.

    // 문자열 구현 중에는 작은 문자열 최적화
    // (small string optimization, SSO)를
    // 사용하는 것들이 많다.

    // 그런 구현은 '작은' 문자열(이를테면 용량이 15자 이하인)
    // 을 std::string 객체 안의 버퍼에 저장하고,
    // 힙에 할당한 저장소는 사용하지 않는다.

    // 이런 구현을 사용하는 std::string 객체는,
    // 작은 문자열의 경우 이동이 복사보다 빠르지 않다.
    ```
  </details>
- 빠른 이동을 지원하는 타입에서도, 겉으로 보기에 이동이 일어날만한 상황에서 복사가 일어나는 경우가 생기기도 한다
- 표준 라이브러리의 일부 컨테이녀 연산들은 강한 예외 안정성을 보장한다. 이를 위해 이동 연산들이 예외를 던지지 않음이 확실한 경우에만 복사연산을 이동연산으로 대체한다
- 이 때문에, 더 효율적인 이동연산을 제공하는 타입이더라도, 그리고 코드의 특성 지점에서 일반적으로 이동연산이 더 적합하다고 하더라도, 해당 이동연산이 noexcept로 선언되어있지 않으면 컴파일러는 여전히 복사연산을 호출할 수 있다.
- 정리하면 c++11의 이동의미론이 도움되지않는 시나리오는 아래의 4가지다
  - 이동연산이 없다: 이동할 객체가 이동연산들을 제공하지 않는다. 이 경우 이동요청은 복사요청이 된다
  - 이동이 더 빠르지않다: 이동할 객체의 이동연산이 복사연산보다 빠르지 않다.
  - 이동을 사용할 수 없다: 이동이 일어나려면 이동 연산이 예외를 방출하지 않아야 하는 문맥에서, 해당 연산이 noexcept로 선언되어 있지 않다.
  - 원본 객체가 왼값이다: 아주 드문 경우지만, 오직 우측값만 이동 연산의 원본이 될 수 있는 경우도 있다.

### 2. 타임들과 이동의미론 지원여부를 미리 알 수 있는경우에는 그런 가정을 둘 필요가 없다

- 일반적 코드에서는 대체로 이동연산들이 존재하지 않고, 저렴하지 않고, 적용되지 않는다는 가정이 사실이다. 이런 경우 코드에 쓰이는 모든 타입을 알 수 없기 때문인다. 이 점은 "안정적이지 않은 코드" 즉, 코드가 사용하는 타입의 특징들이 비교적 자주 바뀌는 코드에도 적용된다.
- 그런데 코드가 사용하는 구체적인 타입들을 미리 알 수 있는, 그리고 그 타입들의 특징이 바귀지 않으리라고 확실할 수 있는 경우에는 이번 항목의 가정들을 둘 필요가 없다.

## item 30. 완벽전달이 실패하는 경우들을 잘 알아두라

### 1. 완벽 전달은 템플릿 타입 추론이 실패하거나, 틀린 타입을 추론했을 때 실패한다

- 전달함수 예제
  ```cpp
  // f라는 함수에 인수들을 전달하는 함수 템플릿을
  // 작성한다고 하자. 다음은 그런 함수의 가장
  // 기초적인 형태이다.

  template <typename T>
  void fwd(T&& param)						// 임의의 인수를 받는다.
  {
    f(std::forward<T>(param));			// 그 인수를 f에 전달한다.
  }

  // 위의 fwd 템플릿은 임의의 타입의 인수를 받아서
  // 그대로 전달한다. 이러한 일반성을 논리적으로
  // 연장하면, 전달 함수는 그냥 템플릿 함수가 아니라
  // 가변 인수 템플릿(variadic template), 즉 임의의
  // 타입과 개수의 인수들을 받는 템플릿이어야 한다는
  // 결론에 도달한다.

  // 다음은 fwd의 가변 인수 버전이다.

  template <typename... Ts>
  void fwd(Ts&&... params)				// 임의의 인수들을 받는다.
  {
    f(std::forward<Ts>(params)...);		// 그것들을 f에 전달한다.
  }

  // 이것이 전달 함수의 공통적인 형태이다.

  // 표준 컨테이너의 emplace류 함수들(항목 42 참고)
  // 과 스마트 포인터 팩터리 함수 std::make_shared,
  // std::make_unique(항목 21 참고)에서 이런
  // 형태를 볼 수 있다.

  // 위의 함수 템플릿을 사용하면 대부분의 경우
  // 다음의 두 식은 같지만,

  f( 표현식 );
  fwd( 표현식 );

  // 특정한 경우 둘의 결과가 달라지는 경우가 있다.
  // 이번 항목에서는 이 둘의 결과가 달라지는,
  // 즉 완벽 전달에 실패하는 경우와 우회 방법에
  // 대해 알아본다.
  ```
- 다음 두 조건중 하나라도 만족되면 완벽전달은 실패한다
  - fwd의 매개변수들 중 하나이상에 대해 컴파일러가 타입추론을 못한다. 이 경우 코드는 컴파일되지 않는다.
  - fwd의 매개변수들 중 하나 이상에대해 컴파일러가 타입을 잘못 추론한다. -> 컴파일에 실패하거나, fwd를 호출한경우와 직접 f를 호출하는 경우가 다르게 동작한다

### 2. 인수가 중괄호 초기치이거나 0 또는 NULL로 표현된 널포인터, 선언만 된 정수 static sconst 및 constexpr 데이터 멤버, 템플릿 오버로딩된 함수 이름, 비트필드이면 완벽전달이 실패한다

- 중괄호 초기치
  - 템플릿 타입 추론에서는 중괄호 초기치를 추론하지 못하므로 완벽전달에도 실패한다.
  - auto에서는 추론에서는 중괄호 초기치를 추론할 수 있으므로 완벽전달에도 성공한다.
    <details>
      <summary>예제</summary>

      ```cpp
      auto il = { 1, 2, 3 };
      // il의 타입 추론 결과는
      // std::initializer_lis<int>이다.

      fwd(il);
      // OK; il이 f로 완벽하게
      // 전달된다.
      ```
    </details>
- 널포인터를 뜻하는 0 또는 NULL
  - 널포인터를 0이나 NULL을 넘기게되면 컴파일러는 int타입으로 추론하고, 이는 포인터가 아니므로 완벽전달에 실패한다.
  - nullptr을 써라
- 선언만 된 정수 static const 및 constexpr 데이터 멤버
  - 일반적인 규칙으로 정수 static const 데이터 멤버와 정수 static constexpr 데이터 멤버는 클래스 안에서 정의할 필요가 없다. 선언만 하면 된다. 이는 그런 멤버의 값에 대해 컴파일러가 const 전파를 적용해서, 그런 멤버의 값을 위한 메모리를 따로 마련할 필요가 없어지기 때문이다.
  - 하지만, 만일 그런 멤버들의 주소를 취하는 코드를 만든다면, 그런 멤버를 위한 저장소가 필요해지며, 그러면 이 코드는 컴파일되긴 하지만 링크에 실패한다.
  - 컴파일러가 산출한 코드에서 참조는 포인터처럼 취급되는게 보통이다. 따라서 그런 멤버들을 보편참조에 묶으려 하면 링크에 실패하는 코드가 만들어질 가능성이 크고, 링크가 되더라도 표준이 아니므로 이식성이 떨어진다.
  - 따라서 그러한 멤버들을 완벽전달하려면 그런 멤버들의 정의를 만들어주면 된다.
    <details>
      <summary>예제</summary>

      ```cpp
      class Widget {
      public:
        static constexpr std::size_t MinVals = 28;	// MinVals의 선언
        ...
      };
      ...												// MinVals의 정의는 없음

      std::vector<int> widgetData;
      widgetData.reserve(Widget::MinVals);			// MinVals의 사용

      // 위 코드는 아무런 문제가 없다.

      // 하지만 어떤 코드가 MinVals의 주소를 취한다면
      // (이를테면 MinVals를 가리키는 포인터를 만든다면)
      // 컴파일은 되지만 링크에 실패한다.

      // 컴파일러가 산출한 코드에서 참조는 포인터처럼
      // 취급되는(즉, 주소를 취하는) 것이 보통이므로,
      // MinVals가 보편 참조(universal reference)에 묶이면 링크에 실패한다.

      // 즉 다음의 코드는 문제가 없지만,

      void f(std::size_t val);

      f(Widget::MinVals);					// OK; 그냥 f(28)로 처리됨

      // 다음의 코드는 링크에 실패한다.

      template <typename T>
      void fwd(T&& param)
      {
        f(std::forward<T>(param));
      }

      fwd(Widget::MinVals);				// 오류! 링크에 실패한다.

      // 이것을 이식성 있게 해결하려면, 구현 파일에
      // MinVals의 정의를 만들어 줘야 한다.

      constexpr std::size_t Widget::MinVals;			// Widget의 .cpp 파일에서
      ```
    </details>
- 템플릿 오버로딩된 함수 이름
  - 오버로딩된 함수 이름이나 함수 템플릿의 이름은 그 자체로 타입을 갖지 않는다. 따라서 완벽하게 전달하려고 하면, 타입추론에 실패해서 컴파일되지 않는다.
  - 우회방법은 함수포인터를 하나 만들고, 명시적으로 오버로딩된 함수나 함수 템플릿 인스턴스를 가리키게 한 뒤 전달하면 된다.
    <details>
      <summary>예제</summary>

      ```cpp
      void f(int (*pf)(int));			// pf는 processing function
                                  // (처리 함수)를 뜻한다.

      // f를 더 간단히 비 포인터 구문으로
      // 선언할 수도 있다.

      void f(int pf(int));			// 위와 동일한 f를 선언한다.

      // 이제 오버로딩된 processVal 함수가
      // 있다고 하자.

      int processVal(int value);
      int processVal(int value, int priority);

      // 다음처럼 processVal을 f에 넘겨주는
      // 것이 가능하다.

      f(processVal);					// OK

      // f가 요구하는 함수의 타입을 미리 알 수
      // 있기 때문이다.

      // 하지만 다음은 컴파일되지 않는다.

      template <typename T>
      void fwd(T&& param)
      {
        f(std::forward<T>(param));
      }

      fwd(processVal);				// 오류! 어떤 processVal 인지?

      // 왜냐하면 fwd는 어떤 타입도 받을 수
      // 있기 때문에 오버로딩된 두 함수 중에
      // 어느 것을 전달해야 할 지 모호하기
      // 때문이다.

      // 마찬가지의 이유로, 다음 코드도
      // 컴파일되지 않는다.

      template <typename T>
      T workOnVal(T param)			// 값들을 처리하는 템플릿 함수
      { ... }

      fwd(workOnVal);					// 오류! workOnVal의
                              // 어떤 인스턴스인지?

      // 이를 해결하려면, 전달하고자 하는 오버로딩된 함수나
      // 템플릿 인스턴스를 명시적으로 지정해야 한다.

      using ProcessFuncType =							// typedef들을 만든다;
        int (*)(int);								      // 항목 9 참고

      ProcessFuncType processValPtr = processVal;		// processVal에
                                                    // 필요한 시그니처를
                                                    // 명시한다.

      fwd(processValPtr);								// OK

      fwd(static_cast<ProcessFuncType>(workOnVal));	// 역시 OK

      // 물론 이를 위해서는 fwd가 전달하는
      // 함수 포인터의 타입을 알고 있어야 한다.

      // 다행히, 완벽 전달 함수의 문서화에
      // 그 타입에 대한 정보가 나와 있으리라고
      // 가정하는 것이 비합리적인 생각은 아니다.
      ```
    </details>
- 비트필드
  - 보편참조는 보통 포인터로 처리되는데, 임의의 비트를 가르키는 포인터를 만들수 없고, 이는 보편참조와 완벽전달로 처리될 수 없음을 의미
  - 우회방법은 값으로 전달하거나, const에 대한 참조로 전달
  - 값으로 전달하게 되면, 비트필드값의 복사본을 받는다. 그리고 const에 대한 참조로 전달하는 경우 표준에 따르면 그 참조는 어떤 표준 정수타입의 객체에 저장된 비트필드 값의 복사본에 묶여야한다. 즉, 그 const 참조는 비트필드 자체가 아닌, 비트필드 값이 복사된 보통객체에 묶인다
  - 따라서 비트필드를 완벽전달함수에 넘겨주려면, 비트필드 값의 복사본을 직접 생성하고 그 복사본을 전달하면 된다.
    <details>
      <summary>예제</summary>

      ```cpp
      // 다음은 IPv4 헤더를 나타내는 구조체이다.

      struct IPv4Header {
        std::uint32_t version:4,
                IHL:4,
                DSCP:6,
                ECN:2,
                totalLength:16;
        ...
      };

      void f(std::size_t sz);		// 호출할 함수

      IPv4Header h;
      ...
      f(h.totalLength);			// OK

      // 그러나 다음은 컴파일되지 않는다.

      template <typename T>
      void fwd(T&& param)
      {
        f(std::forward<T>(param));
      }

      fwd(h.totalLength);			// 오류!

      // 이를 해결하려면, 비트필드 값의 복사본을
      // 직접 생성해서 그 복사본을 전달해야 한다.

      // 비트필드 값을 복사한다; 이런 초기화 구문에 관해서는 항목 6을 보라
      auto length = static_cast<std::uint16_t>(h.totalLength);

      fwd(length);				// 복사본을 전달한다.
      ```
    </details>
