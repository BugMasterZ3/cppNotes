
/************************************************ C++ 17 ***************************************************/

//////////// 构造函数模板推导
pair<int, double> p(1, 2.2); // before c++17
pair p(1, 2.2); 	// c++17 自动推导
vector v = {1, 2, 3};   // c++17


/////////////// 结构化绑定
//结构化绑定不止可以绑定pair和tuple，还可以绑定数组和结构体等
std::tuple<int, double> func() {
    return std::tuple(1, 2.2);
}
    auto[i, d] = func(); 

std::pair a(1, 2.3f);
auto[i, f] = a;
int array[3] = {1, 2, 3};
auto [a, b, c] = array;

map<int, string> m = {
	{0, "a"},
	{1, "b"},  
};
for (const auto &[i, s] : m) {
	cout << i << " " << s << endl;
}

struct Point {
    int x;
    int y;
};
Point func() {
    return {1, 2};
}
const auto [x, y] = func();	
//使用引用改变对象的值
std::pair a(1, 2.3f);
auto& [i, f] = a;
i = 2;
cout << a.first << endl; // 2 
//注意结构化绑定不能应用于constexpr
constexpr auto[x, y] = std::pair(1, 2.3f); // compile error, C++20可以


/////////////////// if-switch语句初始化
//C++17前if语句需要这样写代码：
int a = GetValue();
if (a < 101) {
    cout << a;
}
//C++17之后可以这样：if (init; condition)
//尽可能约束作用域，让代码更简洁，可读性可能略有下降
if (int a = GetValue()); a < 101) {
    cout << a;
}

string str = "Hi World";
if (auto [pos, size] = pair(str.find("Hi"), str.size()); pos != string::npos) {
    std::cout << pos << " Hello, size is " << size;
}

	
/////////////// 内联变量
//C++17前只有内联函数，现在有了内联变量，我们印象中C++类的静态成员变量在头文件中是不能初始化的，但是有了内联变量，就可以达到此目的：
struct A {
    static const int value;  
};
inline int const A::value = 10;
// ==========或者========
struct A {
    inline static const int value = 10;
}


/////////// 折叠表达式
template <typename ... Ts>
auto sum(Ts ... ts) {
    return (ts + ...);
}


////////////// constexpr lambda表达式
//编译期进行计算
constexpr auto lamb = [] (int n) { return n * n; };
static_assert(lamb(3) == 9, "a");
//注意：constexpr函数有限制：函数体不能包含汇编语句、goto语句、label、try块、静态变量、线程局部存储、没有初始化的普通变量，不能动态分配内存，不能有new delete等，不能虚函数。


////////////// namespace嵌套
namespace A {
    namespace B {
        namespace C {
            void func();
        }
    }
}
// c++17
namespace A::B::C {
    void func();)
}


///////////////// __has_include预处理表达式
//可以判断是否有某个头文件，代码可能会在不同编译器下工作，不同编译器的可用头文件有可能不同，所以可以使用此来判断：
#if defined __has_include
#if __has_include(<charconv>)
#define has_charconv 1
#include <charconv>
#endif
#endif

std::optional<int> ConvertToInt(const std::string& str) {
    int value{};
#ifdef has_charconv
    const auto last = str.data() + str.size();
    const auto res = std::from_chars(str.data(), last, value);
    if (res.ec == std::errc{} && res.ptr == last) return value;
#else
    // alternative implementation...
    其它方式实现
#endif
    return std::nullopt;
}


//////////// 在lambda表达式用*this捕获对象副本
//正常情况下，lambda表达式中访问类的对象成员变量需要捕获this，但是这里捕获的是this指针，指向的是对象的引用
//如果多线程情况下，函数的作用域超过了对象的作用域，对象已经被析构了，还访问了成员变量，就会有问题
struct A {
    int a;
    void func() {
        //auto f = [this] 
	auto f = [*this] { cout << a << endl; }; //捕获*this，不持有this指针，而是持有对象的拷贝，这样生命周期就与对象的生命周期不相关了
        f();
    }  
};

    A a;
    a.func();


//////////////// 新增Attribute
struct A { short f[3]; } __attribute__((aligned(8)));
void fatal() __attribute__((noreturn));
//在C++11和C++14中有更方便的方法：
[[carries_dependency]] 	//让编译期跳过不必要的内存栅栏指令
[[noreturn]] 		//函数不会返回
[[deprecated]] 		//函数将弃用的警告	
[[noreturn]] void terminate() noexcept;
[[deprecated("use new func instead")]] void func() {}

//C++17新增了三个：
[[fallthrough]] 	//用在switch中提示可以直接落下去，不需要break，让编译期忽略警告
[[nodiscard]] 		//表示修饰的内容不能被忽略，可用于修饰函数，标明返回值一定要被处理
[[maybe_unused]] 	//提示编译器修饰的内容可能暂时没有使用，避免产生警告
switch (i) {}
    case 1:
        xxx; // warning, 没有break
    case 2:
        xxx; 
        [[fallthrough]];      // 警告消除
}

[[nodiscard]] int func();
func(); // warning 没有处理函数返回值

[[maybe_unused]] void func2() {} // 警告消除
[[maybe_unused]] int y = 2; // 警告消除


////////////// <charconv> 字符串转换
// 新增from_chars函数和to_chars函数
    const std::string str{"123456098"};
    int value = 0;
    const auto res = std::from_chars(str.data(), str.data() + 4, value);
    if (res.ec == std::errc()) {
        cout << value << ", distance " << res.ptr - str.data() << endl;
    } else if (res.ec == std::errc::invalid_argument) {
        cout << "invalid" << endl;
    }
    str = std::string("12.34");
    double val = 0;
    const auto format = std::chars_format::general;
    res = std::from_chars(str.data(), str.data() + str.size(), value, format);

    str = std::string("xxxxxxxx");
    const int v = 1234;
    res = std::to_chars(str.data(), str.data() + str.size(), v);
    cout << str << ", filled " << res.ptr - str.data() << " characters \n";
    // 1234xxxx, filled 4 characters


//////////////// std::variant
//实现类似union的功能,但比union更高级，举个例子union里面不能有string这种类型，但std::variant却可以，还可以支持更多复杂类型，如map等
    std::variant<int, std::string> var("hello");
    cout << var.index() << endl;
    var = 123;
    cout << var.index() << endl;

    try {
        var = "world";
        std::string str = std::get<std::string>(var); // 通过类型获取值
        var = 3;
        int i = std::get<0>(var); // 通过index获取对应值
    } catch(...) {
        // xxx;
    }
//注意：一般情况下variant的第一个类型一般要有对应的构造函数，否则编译失败：
struct A {
    A(int i){}  
};
    //std::variant<A, int> var; // 编译失败
    std::variant<std::monostate, A> var; // 编译成功，可以使用std::monostate来打个桩，模拟一个空状态


///////////////// std::optional
//异常情况下可以返回nullptr(代替指针，不用涉及内存管理)
std::optional<int> StoI(const std::string &s) {
    try {
        return std::stoi(s);
    } catch(...) {
        return std::nullopt;
    }
}
    std::string s{"123"};
    std::optional<int> o = StoI(s);
    if (o) {
        cout << *o << endl;
    } else {
        cout << "error" << endl;
    }


////////////////// std::any
//可以存储任何类型的单个值
    std::any a = 1;
    cout << a.type().name() << " " << std::any_cast<int>(a) << endl;
    a = std::string("a");
    cout << a.type().name() << " " << std::any_cast<std::string>(a) << endl;
    if (a.has_value()) {
        cout << a.type().name();
    }
    a.reset();
  

/////////////////// std::apply
//使用std::apply可以将tuple展开作为函数的参数传入
int add(int first, int second) { return first + second; }
auto add_lambda = [](auto first, auto second) { return first + second; };
int main() {
    std::cout << std::apply(add, std::pair(1, 2)) << '\n';
    std::cout << add(std::pair(1, 2)) << "\n"; // error
    std::cout << std::apply(add_lambda, std::tuple(2.0f, 3.0f)) << '\n';
}


///////////// std::make_from_tuple
//使用make_from_tuple可以将tuple展开作为构造函数参数
struct Foo {
    Foo(int first, float second, int third) {
        std::cout << first << ", " << second << ", " << third << "\n";
    }
};
int main() {
   auto tuple = std::make_tuple(42, 3.14f, 0);
   std::make_from_tuple<Foo>(std::move(tuple));
}


/////////////// std::string_view
//通常我们传递一个string时会触发对象的拷贝操作，大字符串的拷贝赋值操作会触发堆内存分配，很影响运行效率，string_view就可以避免拷贝操作，平时传递过程中传递string_view即可
void func(std::string_view stv) { cout << stv << endl; }
int main(void) {
    std::string str = "Hello World";
    std::cout << str << std::endl;

    std::string_view stv(str.c_str(), str.size());
    cout << stv << endl;
    func(stv);
    return 0;
}


/////////// as_const
//可以将左值转成const类型
std::string str = "str";
const std::string& constStr = std::as_const(str);


////////// file_system
//提供了关于文件的大多数功能
namespace fs = std::filesystem;
fs::create_directory(dir_path);
fs::copy_file(src, dst, fs::copy_options::skip_existing);
fs::exists(filename);
fs::current_path(err_code);


/////////// std::shared_mutex
C++17引入了shared_mutex，可以实现读写锁








