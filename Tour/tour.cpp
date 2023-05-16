

constexpr double square(double x) { return x * x; }
consteval double square2(double x) { return x * x; }
    //int i2 {7.8};    // error: floating-point to integer conversion
    constexpr int dmv = 17; //to be evaluated at compile time
    constexpr double max1 = 1.4 * square(17);   // OK: 1.4*square(17) is a constant expression
    constexpr double max2 = 1.4 * square(var);  // error: var is not a constant, so square(var) is not a constant
    const double max3 = 1.4 * square(var);      // OK: may be evaluated at run time
                                                // constexpr并非强制限定为常量表达式
    constexpr double max4 = 1.4 * square2(17);  // OK: 1.4*square(17) is a constant expression
    const double max5 = 1.4 * square2(var);     // error: var is not a constant(强制性)


//export module Vector;...C++20
//import Vector;    // == #include 
    enum Color{black,white,red};	//black、white、red作用域和color作用域相同
    enum class Color{black,white,red}; //作用域仅在大括号内生效（解决命名冲突）


//union 优化内存-->#include <variant>
struct Entry {
    string name;
    variant<Node*,int> v;  //or  //union Value { Node* p; int i; };
};
void f(Entry* pe)
{
    if (holds_alternative<int>(pe->v))   // does *pe hold an int? (see §15.4.1)
        cout << get<int>(pe->v);         // get the int
    // ...
}
    //using Node = variant<Expression,Statement,Declaration,Type>; 简化
    std::variant<int, std::string> var{"hi"}; // initialized with string alternative 
    std::cout << var.index(); // prints 1
    var = 42; // now holds int alternative
    std::cout << var.index(); // prints 0
    ...
    try {
    std::string s = std::get<std::string>(var); // access by type
    int i = std::get<0>(var); // access by index
    }
    catch (const std::bad_variant_access& e) { // in case a wrong type/index is used
    ...
    }
    //默认构造函数初始化第一个类型，std::monostate支持第一个类型没有默认构造函数的variant对象
struct NoDefConstr
{
    NoDefConstr(int i) { std::cout << "NoDefConstr::NoDefConstr(int) called\n"; }
};
    std::variant<NoDefConstr, int> v1; // ERROR: can’t default construct first type
    std::variant<std::monostate, NoDefConstr> v2; // OK
    std::cout << "index: " << v2.index() << '\n'; // prints 0
    //检查monostate
    if (!v2.index()) { std::cout << "has monostate\n"; }
    if (std::holds_alternative<std::monostate>(v2)) { std::cout << "has monostate\n"; }
    if (std::get_if<0>(&v2)) { std::cout << "has monostate\n"; }
    if (std::get_if<std::monostate>(&v2)) { std::cout << "has monostate\n"; }
    //传递多个值进行初始化
    std::variant<std::complex<double>> v10{std::in_place_type<std::complex<double>>, 3.0, 4.0};
    std::variant<std::complex<double>> v11{std::in_place_index<0>, 3.0, 4.0};
    //std::variant<int, int> v12{std::in_place_index<1>, 77}; // init 2nd int 解决初始化过程中的歧义或匹配问题
    //访问
    std::variant<int, int, std::string> var; // sets first int to 0, index()==0
    auto a = std::get<double>(var); // compile-time ERROR: no double
    auto b = std::get<4>(var); // compile-time ERROR: no 4th alternative
    auto c = std::get<int>(var); // compile-time ERROR: int twice
    try{
        auto s = std::get<std::string>(var); // throws exception (first int currently set)
        auto i = std::get<0>(var); // OK, i==0
        auto j = std::get<1>(var); // throws exception (other int currently set)
    }
    catch (const std::bad_variant_access& e) { // in case of an invalid access
        std::cout << "Exception: " << e.what() << '\n';
    }

    if (auto ip = std::get_if<1>(&var); ip) //返回指向当前值的指针或nullptr
        std::cout << *ip << '\n';
    else    
        std::cout << "alternative with index 1 not set\n";
    //赋值修改
    std::variant<int, int, std::string> var; // sets first int to 0, index()==0
    var = "hello"; // sets string, index()==2
    var.emplace<1>(42); // sets second int, index()==1

    std::get<0>(var) = 77; // OK, because first int already set
    std::get<1>(var) = 99; // throws exception (other int currently set)
    if (auto p = std::get_if<1>(&var); p) { // if second int set
        *p = 42; // modify it
    }
    //异常
struct S
{
    operator int() { throw "EXCEPTION"; } // any conversion to int throws
};
    std::variant<double, int> var{ 12.2 }; // initialized as double
    std::cout << std::boolalpha << var.valueless_by_exception() << std::endl;   //false
    try
    { 
        var.emplace<1>(S{}); // OOPS: throws while set as int
    }
    catch (...)
    {
        std::cout << var.valueless_by_exception() << std::endl; //true
        if (var.index() == std::variant_npos)
        {
            std::cout << "variant_npos" << std::endl;
        }
    }


namespace My_code {
class complex {
// ...
};
complex sqrt(complex);
// ...

int main();   //final不能再被继承重写, override检查覆写类型
}

int My_code::main() 
{
    complex z {1,2};
    auto z2 = sqrt(z);
    std::cout << '{' << z2.real() << ',' << z2.imag() << "}\n";
    // ...
}
    complex<double> z = {1,2};
    auto [re,im] = z+2;    // re=3; im=2
    // return My_code::main();


int& bad()
{
    int x;
    // ...
    return x;    // bad: return a reference to the local variable x
}


auto mul(int i, double d) { return i*d; }    // deduce type (careful)
auto mul(int i, double d) -> double { return i*d; }    // Suffix(后缀) Return Type
void incr(map<string,int>& m)    // increment the value of each element of m
{
    for (auto& [key,value] : m)
        ++value;
}


Entry read_entry(istream& is)    // naive read function (for a better version, see §11.5)
{
    string s;
    int i;
    is >> s >> i;
    return {s,i};
}
//auto [n,v] = read_entry(is);


//lambda通式: auto func = [capture] (params) opt -> ret { func_body; }; //opt->ret可省略
class Test 
{
public:
    void output(int x, int y)
    {
        auto x1 = [] {return m_number; };                // error
        //auto x1 = [](){ return {1, 2}; }    //error,不能通过列表初始化自动推导出返回值类型
        auto x2 = [=] -> int {return m_number + x + y; };// ok 可读（拷贝副本,默认添加this [=, this]
        //auto x2 = [=]()mutable {m_number++; };         // ok mutable取消operator只读（const）属性
        auto x3 = [&] {return m_number + x + y; };       // ok 可读写,默认添加this [&, this]
        auto x4 = [this] {return m_number++; };          // ok thisCopy=*this(拷贝)
        auto x5 = [this] {return m_number + x + y; };    // error
        auto x6 = [this, x, y] {return m_number + x + y; };    // ok
    }
    int m_number = 100; //若加mutable关键字，则类成员可以在const函数中被改变
};


class R {
    // ...
    auto operator<=>(const R& a) const = default;
};
void user(R r1, R r2)
{
    bool b1 = (r1<=>r2) == 0;   // r1==r2 与strcmp()类似
    bool b2 = (r1<=>r2) < 0;    // r1<r2
    bool b3 = (r1<=>r2) > 0;    // r1>r2
    bool b4 = (r1==r2);         // ok <=>定义为默认值时==隐式定义
    bool b5 = (r1<r2);
}

/*
Standard-Library Suffixes for Literals
<chrono>         std::literals::chrono_literals       h, min, s, ms, us, ns
<string>         std::literals::string_literals       s
<string_view>    std::literals::string_literals       sv
<complex>        std::literals::complex_literals      i, il, if
*/
constexpr complex<double> operator""i(long double arg) // imaginary literal
{
    return {0,arg};
}


//模板特化和SFINAE机制
template<typename T>
std::string toStr(T t) {
    if constexpr (std::is_same_v<T, std::string>)   //解决了返回类型自动推导问题，加快了编译效率
        return t;
    else
        return std::to_string(t);
}


template<typename Sequence, typename Number>
    // requires Arithmetic<range_value_t<Sequence>,Number>
Number sum(Sequence s, Number n)
{
    for (const auto& x : s)
        v+=x;
    return v;
}
   
//auto g() { return 99; }          // g() returns an int
//int f(auto x) { /* ... */ }       // take an argument of any type
auto twice(Arithmetic auto x) { return x+x; } // just for numbers
auto thrice(auto x) { return x+x+x; }         // for anything with a +
   
template<forward_iterator Iter, Arithmetic<iter_value_t<Iter>> Val>
Val accumulate(Iter first, Iter last, Val res)
{
    for (auto p = first; p!=last; ++p)
        res += *p;
    return res;
}
template<Printable T, Printable... Tail>
void print(T head, Tail... tail)
{
    cout << head << ' ';
    if constexpr(sizeof...(tail) > 0)
        print(tail...);
}  
template<Number... T>
int sum(T... v)
{
    return (v + ... + 0);    // (v[0]+(v[1]+(v[2]+(v[3]+(v[4]+0))))) 
    return (0 + ... + v);    // (((((0+v[0])+v[1])+v[2])+v[3])+v[4])
}
template<Printable ...T>
void print(T&&... args)
{
    (std::cout << ... << args) << '\n';    // print all arguments
}

template<concepts::InputTransport Transport>
class InputChannel {
public:
    // ...
    InputChannel(Transport::Args&&... transportArgs)
        : _transport(std::forward<TransportArgs>(transportArgs)...)
    {}
    // ...
    Transport _transport;
};


string_view bad()   //only read 
{
    string s = "Once upon a time";
    return {&s[5],4};    // bad: returning a pointer to a local
}


for (auto& w : words)
    std: : cout << *w <<" ";
//for (auto iter = std::begin(words);iter != std::end(words); ++iter)
//    std::cout << **iter <<" ";
for (auto& w : words)
    delete w; // Delete the string pointed to
words.clear(); // Delete all the elements from the vector
/*
for (auto iter = std::begin(words); iter != std::end(words);)
{
    if (**iter == "one")
    {
        delete *iter;//Release the memory...
        words.erase (iter);    //... then delete the pointer
    }
    else
        ++iter;
}
*/
for (auto iter = std::begin(words);iter != std::end(words); ++iter)
    delete *iter;


auto t1 = std::make_tuple(string{"Herring"},10,1.23);
string fish = get<0>(t1);
auto [fish, count, price] = t1;
cout << fish << ' ' << count << ' ' << price << '\n';    // read


void binary(int i)
{
    bitset<8*sizeof(int)> b = i;    // assume 8-bit byte (see also §17.7)
    cout << b.to_string() << '\n';  // write out the bits of i
}


int sum(optional<int> a, optional<int> b)
{
    int res = 0;
    if (a) res += *a; // note the dereference (*)
    if (b) res += *b;
    return res;
}


any compose_message(istream& s)
{
    string mess;

    // ... read from s and compose message ...

    if (no_problems)
        return mess;         // return a string
    else
        return error_number; // return an int
}
auto m = compose_message(cin);
string& s = any_cast<string>(m);


//Concurrency并发
jthread t1 {f};    // 后续无需join()

mutex m;   // controlling mutex
shared_mutex mx;    // a mutex that can be shared

void f()
{
    //scoped_lock lck {mutex1,mutex2,mutex3};    // acquire all three locks
    scoped_lock lck {m}; // acquire mutex
    sh += 7;             // manipulate shared data
} // release mutex implicitly
void reader()
{
    shared_lock lck {mx};    // willing to share access with other readers
    // ... read ...
}
void writer()
{
    unique_lock lck {mx};    // needs exclusive (unique) access
    // ... write ...
}




std::vector<int> vec;
const std::vector<int>::iterator iter = vec.begin();// iter acts like a T* const
*iter = 10; // OK, changes what iter points to
++iter; // error! iter is const
std::vector<int>::const_iterator cIter = vec.begin();// cIter acts like a const T* vec.begin();
*cIter = 10; // error! *cIter is const
++cIter; // fine, changes cIter


//更好的异常设计：
//解构器永远不应该发出异常。如果在析构函数中调用的函数可能会抛出，析构函数应该捕获任何异常，然后吞下它们或终止程序
//如果类客户端需要能够对操作过程中抛出的异常做出反应，则类应该提供一个执行该操作的常规（即非析构函数）函数
class DBConn {
public:
...
    void close() // new function for
    {   // client use
        db.close();
        closed = true;
    }
    ~DBConn()
    {
        if (!closed) {
            try {           // close the connection
                db.close(); // if the client didn’t
            }
            catch (...) {   // if closing fails,
                make log entry that call to close failed;   // note that and 
                ...                                         // terminate or swallow
            }
        }
    }
private:
    DBConnection db;
    bool closed;
};
