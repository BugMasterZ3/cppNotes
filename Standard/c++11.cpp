
/************************************************ C++ 11 ***************************************************/
// auto & decltype 
cont int &i = 1;
int a = 2;
decltype(i) b = 2; // b是const int&, 相对于auto用于推导变量类型，decltype则用于推导表达式类型

// 左值右值
// 纯右值：运算表达式产生的临时变量、不和对象关联的原始字面量、非引用返回的临时变量、lambda表达式等都是纯右值
// 将亡值：可以理解为即将要销毁的值
// 左值引用：对左值进行引用的类型
// 右值引用：对右值进行引用的类型
// 移动语义：转移资源所有权，类似于转让或者资源窃取的意思，对于那块资源，转为自己所拥有，别人不再拥有也不会再使用
// 完美转发：可以写一个接受任意实参的函数模板，并转发到其它函数，目标函数会收到与转发函数完全相同的实参
// 返回值优化：当函数需要返回一个对象实例时候，就会创建一个临时对象并通过复制构造函数将目标对象复制到临时对象，这里有复制构造函数和析构函数会被多余的调用到，有代价，而通过返回值优化，C++标准允许省略调用这些复制构造函数。

// 列表初始化

// std::function & std::bind & lambda表达式

// 模板的改进
// 模板的右尖括号
// 模板的别名
// 函数模板的默认模板参数

// 并发
std::thread
std::mutex
std::lock
std::atomic
std::call_once
volatile
std::condition_variable
std::future
async

// 智能指针
std::shared_ptr
std::weak_ptr
std::unique_ptr

// 基于范围的for循环

// 委托构造函数 (同一个类中一个构造函数调用另外一个构造函数)
struct A {
    A(){}
    A(int a) { a_ = a; }
    A(int a, int b) : A(a) { b_ = b; }  
    A(int a, int b, int c) : A(a, b) { c_ = c; }
    int a_;
    int b_;
    int c_;
};

// 继承构造函数 (可以让派生类直接使用基类的构造函数)

struct Derived : Base { // 不使用继承构造函数：
    Derived() {}
    Derived(int a) : Base(a) {} 
    Derived(int a, int b) : Base(a, b) {} 
    Derived(int a, int b, int c) : Base(a, b, c) {} 
};

struct Derived : Base { // 使用继承构造函数：
    using Base::Base; 
};

// nullptr
// 在c++中如果表示空指针语义时建议使用nullptr而不要使用NULL，因为NULL本质上是个int型的0

void func(void *ptr) {
    cout << "func ptr" << endl;
}

void func(int i) {
    cout << "func i" << endl;
}

int main() {
    func(NULL);    // 编译失败，会产生二义性
    func(nullptr); // 输出func ptr
    return 0;
}

// final & override
// final用于修饰一个类，表示禁止该类进一步派生和虚函数的进一步重载，override用于修饰派生类中的成员函数，标明该函数重写了基类函数
struct Base final {
    virtual void func() {
        cout << "base" << endl;
    }
};
struct Derived : public Base{ // 编译失败，final修饰的类不可以被继承
    void func() override {
        cout << "derived" << endl;
    }
};

// default & delete & explicit
// default多数时候用于声明构造函数为默认构造函数，如果类中有了自定义的构造函数，编译器就不会隐式生成默认构造函数

struct A {
    // A() = default;  
    int a;
    A(int i) { a = i; }
};
int main() {
    A a; // 编译出错，因为没有匹配的构造函数，编译器没有生成默认构造函数
    return 0;
}
// c++中如果没有定义特殊成员函数，编译器会隐式自动生成一个默认的特殊成员函数，例如拷贝构造函数或者拷贝赋值操作符,可以使用delete修饰禁止对象的拷贝与赋值
// delele函数在c++11中很常用，std::unique_ptr就是通过delete修饰来禁止对象的拷贝的
struct A {
    A() = default;
    A(const A&) = delete;
    A& operator=(const A&) = delete;
    int a;
    A(int i) { a = i; }
};
int main() {
    A a1;
    A a2 = a1;  // 错误，拷贝构造函数被禁用
    A a3;
    a3 = a1;   // 错误，拷贝赋值操作符被禁用
}
// explicit专用于修饰构造函数，表示只能显式构造，不可以被隐式转换
struct A {
    explicit A(int value) {
        cout << "value" << endl;
    }
};
int main() {
    A a = 1; // error，不可以隐式转换
    A aa(2); // ok
    return 0;
}

// const
// 用于定义常量，const的修饰的变量不可更改
const int value = 5;
// 指针也可以使用const，从右向左读，即可知道const究竟修饰的是指针还是指针所指向的内容
char *const ptr; // 指针本身是常量
const char* ptr; // 指针指向的变量为常量
// 在函数参数中使用const，一般会传递类对象时会传递一个const的引用或者指针，这样可以避免对象的拷贝，也可以防止对象被修改
void func(const A& a);
// const修饰类的成员变量，表示是成员常量，不能被修改，可以在初始化列表中被赋值。
class A {
    const int value;
    A(int v) : value(v){}
};
// 修饰类成员函数，表示在该函数内不可以修改该类的成员变量
class A{
    void func() const;
};
// 修饰类对象，类对象只能调用该对象的const成员函数 ***
const A a;
a.func();

// constexpr (用于编译时的常量和常量函数)
// const只表示read only的语义，只保证了运行时不可以被修改，但它修饰的仍然有可能是个动态变量
// constexpr修饰的才是真正的常量，它会在编译期间就会被计算出来，整个运行过程中都不可以被改变
// constexpr可以用于修饰函数，这个函数的返回值会尽可能在编译期间被计算出来当作一个常量，但是如果编译期间此函数不能被计算出来，那它就会当作一个普通函数被处理 ***
constexpr int func(int i) {
    return i + 1;
}
int main() {
    int i = 2;
    func(i);// 普通函数
    func(2);// 编译期间就会被计算出来
}

// enum class
// 不带作用域的枚举类型enum可以自动转换成整形，且不同的枚举可以相互比较
enum class AColor {
    kRed,
    kGreen,
    kBlue
};
enum class BColor {
    kWhite,
    kBlack,
    kYellow
};
int main() {
    if (AColor::kRed == BColor::kWhite) { // 编译失败
        cout << "red == white" << endl;
    }
    return 0;
}
// 使用带有作用域的枚举类型后，对不同的枚举进行比较会导致编译失败，消除潜在bug，同时带作用域的枚举类型可以选择底层类型(默认是int)
enum class AColor : char {
    kRed,
    kGreen,
    kBlue
};

// 非受限联合体
// c++11之前union中数据成员的类型不允许有非POD类型（大体上可以理解为对象可以直接memcpy的类型），而这个限制在c++11被取消，允许数据成员类型有非POD类型 ***
struct A {
    int a;
    int *b;
};
union U {
    A a; // 非POD类型 c++11之前不可以这样定义联合体
    int b;
};

// sizeof
// c++11中sizeof可以用的类的数据成员上 ***
struct A {
    int data[10];
    int a;
};
int main() {
    A a;
    cout << "size " << sizeof(a.data) << endl;  // c++11前
    cout << "size " << sizeof(A::data) << endl; // c++11后
    return 0;
}

// assertion
// static_assert(true/false, message); 用于在编译期间检查，如果第一个参数值为false，则打印message，编译失败

// 自定义字面量
std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 100ms
std::this_thread::sleep_for(std::chrono::seconds(100)); // 100s
std::this_thread::sleep_for(100ms); // c++14里可以这么使用，这里举个自定义字面量使用的例子
std::this_thread::sleep_for(100s);

// 内存对齐: 理论上计算机对于任何变量的访问都可以从任意位置开始，然而实际上系统会对这些变量的存放地址有限制，通常将变量首地址设为某个数N的倍数，这就是内存对齐
// 为什么要内存对齐
// 硬件平台限制，内存以字节为单位，不同硬件平台不一定支持任何内存地址的存取，一般可能以双字节、4字节等为单位存取内存，为了保证处理器正确存取数据，需要进行内存对齐
// 提高CPU内存访问速度，一般处理器的内存存取粒度都是N的整数倍，假如访问N大小的数据，没有进行内存对齐，有可能就需要两次访问才可以读取出数据，而进行内存对齐可以一次性把数据全部读取出来，提高效率
void align_cpp11_before()
{
    static char data[sizeof(void *) + sizeof(A)];
    const uintptr_t kAlign = sizeof(void *) - 1;
    char *align_ptr = reinterpret_cast<char *>(reinterpret_cast<uintptr_t>(data + kAlign) & ~kAlign);
    A *attr = new (align_ptr) A;
}
// c++11关于内存对齐新增了一些函数：alignof()、std::alignment_of()、alignas()...
void align_cpp11_after()
{
    static std::aligned_storage<sizeof(A), alignof(A)>::type data;
    A *attr = new (&data) A;
}

// thread_local
// 修饰的变量具有thread周期，每一个线程都拥有并只拥有一个该变量的独立实例，一般用于需要保证线程安全的函数中,类似于static
#include <iostream>
#include <thread>
class A {
   public:
    A() {}
    ~A() {}
    void test(const std::string &name) {
        thread_local int count = 0;
        ++count;
        std::cout << name << ": " << count << std::endl;
    }
};
void func(const std::string &name) {
    A a1;
    a1.test(name);
    a1.test(name);
    A a2;
    a2.test(name);
    a2.test(name);
}
int main() {
    std::thread(func, "thread1").join();
    std::thread(func, "thread2").join();
    return 0;
}
输出：
thread1: 1
thread1: 2
thread1: 3
thread1: 4
thread2: 1
thread2: 2
thread2: 3
thread2: 4

// 基础数值类型
// c++11新增了几种数据类型：long long、char16_t、char32_t等

// random
// c++11关于随机数功能则较之前丰富了很多，典型的可以选择概率分布类型,伯努利分布、正态分布...
std::default_random_engine random(time(nullptr));
std::uniform_int_distribution<int> int_dis(0, 100);       // 整数均匀分布
std::uniform_real_distribution<float> real_dis(0.0, 1.0); // 浮点数均匀分布
for (int i = 0; i < 10; ++i) {
    cout << int_dis(random) << ' ';
    cout << real_dis(random) << ' ';
}

// 正则表达式 <regex>
std::string s = "I know, I'll use2 regular expressions.";
// 忽略大小写
std::regex self_regex("REGULAR EXPRESSIONS", std::regex_constants::icase); 
if (std::regex_search(s, self_regex)) {
    std::cout << "Text contains the phrase 'regular expressions'\n";
}
// 匹配字母数字等字符
std::regex word_regex("(\\w+)");  
auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
auto words_end = std::sregex_iterator();
std::cout << "Found " << std::distance(words_begin, words_end) << " words\n";
const int N = 6;
std::cout << "Words longer than " << N << " characters:\n";
for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
    std::smatch match = *i;
    std::string match_str = match.str();
    if (match_str.size() > N) {
        std::cout << "  " << match_str << '\n';
    }
}
// 超过7个字符的单词用[]包围
std::regex long_word_regex("(\\w{7,})");
std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
std::cout << new_s << '\n';

//chrono  (源于boost)
duration
time_point
clocks
// 1. std::chrono::duration 表示一段时间，常见的单位有s、ms等,
std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 休眠100ms
// sleep_for里面其实就是std::chrono::duration，表示一段时间，实际是这样：typedef duration<int64_t, milli> milliseconds; typedef duration<int64_t> seconds;
//duration具体模板：
template <class Rep, class Period = ratio<1> > class duration;// Rep表示一种数值类型，用来表示Period的数量，比如int、float、double
                        // Period是ratio类型，用来表示【用秒表示的时间单位】比如second，常用的duration<Rep, Period>已经定义好了，在std::chrono::duration下：
        ratio<3600, 1>：hours
        ratio<60, 1>：minutes
        ratio<1, 1>：seconds
        ratio<1, 1000>：microseconds
        ratio<1, 1000000>：microseconds
        ratio<1, 1000000000>：nanoseconds
        // ratio的具体模板：
        template <intmax_t N, intmax_t D = 1> class ratio;  // N代表分子，D代表分母，所以ratio表示一个分数，我们可以自定义Period，比如ratio<2, 1>表示单位时间是2秒

// 2. time_point 表示一个具体时间点，如2020年5月10日10点10分10秒，拿获取当前时间举例：
std::chrono::time_point<std::chrono::high_resolution_clock> Now() { 
    return std::chrono::high_resolution_clock::now(); // std::chrono::high_resolution_clock为高精度时钟
}

// 3. clocks 时钟，chrono里面提供了三种时钟：
steady_clock
system_clock
high_resolution_clock
// steady_clock 稳定的时间间隔，表示相对时间，相对于系统开机启动的时间，无论系统时间如何被更改，后一次调用now()肯定比前一次调用now()的数值大，可用于计时
// system_clock 表示当前的系统时钟，可以用于获取当前时间：
        using std::chrono::system_clock;
        system_clock::time_point today = system_clock::now();
        std::time_t tt = system_clock::to_time_t(today);
        std::cout << "today is: " << ctime(&tt);
// high_resolution_clock 表示系统可用的最高精度的时钟，实际上就是system_clock或者steady_clock其中一种的定义(不同系统可能不一样)

// 新增数据结构
std::forward_list：单向链表，只可以前进，在特定场景下使用，相比于std::list节省了内存，提高了性能
std::unordered_set：基于hash表实现的set，内部不会排序，使用方法和set类似
std::unordered_map：基于hash表实现的map，内部不会排序，使用方法和set类似
std::array：数组，在越界访问时抛出异常，建议使用std::array替代普通的数组
std::tuple：元组类型，类似pair，但比pair扩展性好
        typedef std::tuple<int, double> Mytuple;
        Mytuple t(0, 1);
        std::cout << "0 " << std::get<0>(t);
        std::cout << "1 " << std::get<1>(t);

// 新增算法
all_of：检测表达式是否对范围[first, last)中所有元素都返回true，如果都满足，则返回true ***
        std::vector<int> v(10, 2);
        if (std::all_of(v.cbegin(), v.cend(), [](int i) { return i % 2 == 0; })) {
          std::cout << "All numbers are even\n";
        }
any_of：检测表达式是否对范围[first, last)中至少一个元素返回true
none_of：检测表达式是否对范围[first, last)中所有元素都不返回true
find_if_not：找到第一个不符合要求的元素迭代器，和find_if相反
copy_if：复制满足条件的元素
iota：对容器内的元素按序递增 ***
        std::vector<int> l(10);
        std::iota(l.begin(), l.end(), 19);      // 19为初始值
        for (auto n : l) std::cout << n << ' '; // 19 20 21 22 23 24 25 26 27 28
minmax_element：返回容器内最大元素和最小元素位置
        std::vector<int> v = {3, 9, 1, 4, 2, 5, 9};
        auto result = std::minmax_element(v.begin(), v.end());
        std::cout << "min element at: " << *(result.first) << '\n';
        std::cout << "max element at: " << *(result.second) << '\n';
is_sorted、is_sorted_until：返回容器内元素是否已经排好序


  


  
  
