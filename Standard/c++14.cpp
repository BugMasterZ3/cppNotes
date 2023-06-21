
/************************************************ C++ 14 ***************************************************/

////////// 函数返回值类型推导 
auto func(int i) {      // C++11是不能通过编译的
    return i;
}
//用在模板中
template<typename T> auto func(T t) { return t; }       
cout << func(4) << endl;
cout << func(3.4) << endl;
//函数内如果有多个return语句，必须返回相同的类型，否则编译失败
auto func(bool flag) {  
    if (flag) return 1;
    else return 2.3;    // error
}
//返回初始化列表会失败
auto func() {
    return {1, 2, 3}; // error returning initializer list
}
//虚函数不能使用返回值类型推导
struct A {
    virtual auto func() { return 1; }  // error
}
//可以用在前向声明中，但是在使用它们之前翻译单元中必须能够得到函数定义
auto f();               // declared, not yet defined
auto f() { return 42; } // defined, return type is int
//可以用在递归函数中，但是递归调用必须以至少一个返回语句作为先导，以便编译器推导出返回类型。
auto sum(int i) {
    if (i == 1)
        return i;              // return int
    else
        return sum(i - 1) + i; // ok
}


/////////// lambda参数auto
// 在C++11中，lambda表达式参数需要使用具体的类型声明
auto f = [] (int a) { return a; } 
// C++14中对此进行优化，lambda表达式参数可以直接是auto
auto f = [] (auto a) { return a; };
cout << f(1) << endl;
cout << f(2.3f) << endl;


//////////// 变量模板
template<class T>
constexpr T pi = T(3.1415926535897932385L);
cout << pi<int> << endl;    // 3
cout << pi<double> << endl; // 3.14159
  

///////////// 别名模板
template<typename T, typename U>
struct A {
    T t;
    U u;
};

template<typename T>
using B = A<T, int>;


//////////// constexpr的限制放宽
// C++11中constexpr函数可以使用递归，在C++14中可以使用局部变量和循环
constexpr int factorial(int n) { // C++14 和 C++11均可
    return n <= 1 ? 1 : (n * factorial(n - 1));
}

constexpr int factorial(int n) { // C++11中不可，C++14中可以
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        ret += i;
    }
    return ret;
}
//C++11中constexpr函数必须必须把所有东西都放在一个单独的return语句中，而constexpr则无此限制
constexpr int func(bool flag) { // C++14 和 C++11均可
    return 0;
}

constexpr int func(bool flag) { // C++11中不可，C++14中可以
    if (flag) return 1;
    else return 0;
}


////////////// [[deprecated]]标记（过时，废弃）
//修饰类、变、函数等，当程序中使用到了被其修饰的代码时，编译时被产生警告，用户提示开发者该标记修饰的内容将来可能会被丢弃，尽量不要使用

struct [[deprecated]] A { };

int main() {
    A a;        // warning: ‘A’ is deprecated [-Wdeprecated-declarations]
    return 0;
}


////////////// 二进制字面量与整形字面量分隔符
int a = 0b0001'0011'1010;
double b = 3.14'1234'1234'1234;


////////////// std::make_unique
std::unique_ptr<A> ptr = std::make_unique<A>();


//////////// std::shared_timed_mutex与std::shared_lock
//实现读写锁，保证多个线程可以同时读，但是写线程必须独立运行，写操作不可以同时和读操作一起进行。
struct ThreadSafe {
    mutable std::shared_timed_mutex mutex_;  // timed锁可以带超时时间
    int value_;

    ThreadSafe() {
        value_ = 0;
    }

    int get() const {
        std::shared_lock<std::shared_timed_mutex> lock(mutex_);
        return value_;
    }

    void increase() {
        std::unique_lock<std::shared_timed_mutex> lock(mutex_);
        value_ += 1;
    }
};


///////////// std::integer_sequence
template<typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq)
{
    std::cout << "The sequence of size " << int_seq.size() << ": ";
    ((std::cout << ints << ' '), ...);
    std::cout << '\n';
}
    print_sequence(std::integer_sequence<int, 9, 2, 5, 1, 9, 1, 6>{});  // 输出：7 9 2 5 1 9 1 6
//std::integer_sequence和std::tuple的配合使用
template <std::size_t... Is, typename F, typename T>
auto map_filter_tuple(F f, T& t) {
    return std::make_tuple(f(std::get<Is>(t))...);
}

template <std::size_t... Is, typename F, typename T>
auto map_filter_tuple(std::index_sequence<Is...>, F f, T& t) {
    return std::make_tuple(f(std::get<Is>(t))...);
}

template <typename S, typename F, typename T>
auto map_filter_tuple(F&& f, T& t) {
    return map_filter_tuple(S{}, std::forward<F>(f), t);
}


//////////////// std::exchange
std::vector<int> v;
std::exchange(v, {1,2,3,4});    //貌似和std::swap作用相同
cout << v.size() << endl;
for (int a : v) {
        cout << a << " ";
}
// exchange的实现：new_value的值给了obj，而没有对new_value赋值（与swap的区别）
template<class T, class U = T>
constexpr T exchange(T& obj, U&& new_value) {
    T old_value = std::move(obj);
    obj = std::forward<U>(new_value);
    return old_value;
}


////////////// std::quoted
//用于给字符串添加双引号
    string str = "hello world";
    cout << str << endl;                // hello world
    cout << std::quoted(str) << endl;   // "hello world"



















