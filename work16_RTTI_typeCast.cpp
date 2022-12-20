

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>     //bad_cast，bad_typeid异常
#include <cstring>
using namespace std;


//运行阶段类型识别(RTTI)，用于包含虚函数的类结构层次中
class Grand
{
private:
    int hold;
public:
    Grand(int h = 0) : hold(h) {}
    virtual void Speak() const { cout << "grand class\n"; }
    virtual int Value() const { return hold; }
};

class Superb : public Grand
{
public:
    Superb(int h = 0) : Grand(h) {}
    void Speak() const { cout << "superb class\n"; }
    virtual void Say() const { cout << "value = " << Value() << "\n"; }
};

class Magnificent : public Superb
{
private:
    char ch;
public:
    Magnificent(int h = 0, char c = 'A') : Superb(h), ch(c) {}
    void Speak() const { cout << "magnificent class\n"; }
    void Say() const { cout << "character = " << ch << "  integer = " << Value() << "\n"; }
};

Grand* GetOne()
{
    Grand* p = nullptr;
    switch (std::rand() % 3)    //向上随机转换
    {
    case 0: p = new Grand(std::rand() % 100);
        break;
    case 1: p = new Superb(std::rand() % 100);
        break;
    case 2: p = new Magnificent(std::rand() % 100, 'A' + std::rand() % 26);
        break;
    }
    return p;
}

void change(const int* pt, int n)
{
    int* pc;
    pc = const_cast<int*>(pt);  //const_cast
    *pc += n;                   //传入const参数后，编译器可能禁止修改，主函数值不变
}


int main()
{
    
    std::srand(std::time(0));
    Grand* pg;
    Superb* ps;
    for (int i = 0; i < 5; i++)
    {
        pg = GetOne();
        pg->Speak();
        if (ps = dynamic_cast<Superb*>(pg))     //dynamic_cast检查转换是否安全(is_a),失败返回0(空指针)
            ps->Say();
        //typeid返回对象类型,type_info特定类型信息
        if (typeid(Magnificent) == typeid(*pg)) //pg为空指针引发bad_typeid异常（类似sizeof,接受类名/对象作为参数）
            cout << "Yes, you're really magnificent.\n";
    }
    /*
    try{
        super & rs = dynamic_cast<super &>(rg); //引用失败产生bad_cast异常
    }
    catch(bad_cast &) { ... };
    */

    //四种类型转换运算符
    //1. static_cast
    //编译时转换,运行时不会检查类型转换的安全性（向上转换合法）
    //不能转换掉表达式的const、volitale或 __unaligned属性
    const int i = 20;
    int ii = static_cast<int>(i);//error
    class B {};
    class C : public B {};
    //B* pB1 = static_cast<B*>(pc); //向上转换安全
    //C* pC1 = static_cast<C*>(pb); //static_cast向下转换合法

    enum Week { Monday = 1, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
    Week noday = static_cast<Week>(7);  //ok 整形转枚举值
    //Week noday = static_cast<Week>(8) //error
    int a = 124;
    char c = static_cast<char>(a);	        //int->char...
    const int b = static_cast<const int>(a);//non-const->const
    int* pI = NULL;
    void* cI = static_cast<void*>(pI);//将int类型空指针转换为char空指针（可将任何类型的表达式都转换为void类型）
   
   //2. dynamic_cast
   //运行时进行类型检查
   //只用于类继承结构中基类和派生类之间指针或引用的转换(基类中必须有虚函数)
   //dynamic_cast<new_type*>(expression)  new_type必须为有效指针
   //dynamic_cast<new_type&>(expression)  new_type必须为左值
   //dynamic_cast<new_type&&>(expression) new_type必须为右值
    struct B { virtual void test() {} };
    struct D1 : virtual B { };
    struct D2 : virtual B { };
    struct MD : D1, D2 { };
    D1* pd1 = new MD();
    std::cout << pd1 << std::endl;//0x1061920
    B* pb = dynamic_cast<B*>(pd1);		// 向上转型
    std::cout << pb << std::endl;//0x1061920
    MD* pmd = dynamic_cast<MD*>(pd1);	// 向下转型
    std::cout << pmd << std::endl;//0x1061920
    D2* pd2 = dynamic_cast<D2*>(pd1);	// 横向转型
    std::cout << pd2 << std::endl;//0x1061928
/*
class B
{
public:
    int m_i;
    virtual void f();//基类必须有一个虚函数
};
class C :public B
{
public:
    char* m_Str[100];
}
void f(const C & c) {	//不存在所谓空引用，失败抛出std::bad_cast异常(typeinfo头) 
    try {
        const B& b = dynamic_cast<const C&>(c);
        //使用b引用的C对象
    }
    catch (std::bad_cast) {
        //处理类型转换失败的情况
    }
}*/

    //3. const_cast
    //用于修改类型的const/volatile属性,去掉属性/标签，常量指针/引用->非常量指针/引用 
    //不能去除变量的常量性，只能用来去除指向常数对象的指针或引用的常量性
    const int val = 6;
    int* cp = &val;	//error 
    const int i = 10;
    int* p = const_cast<int*>(&i);//去掉const常量的const属性
    const int i = 20;
    int& h = const_cast<int&>(i);//去掉const引用const属性
    const char* str = "hello";
    char* h = const_cast<char*>(str);//去掉const指针const属性

    //int init = 6;
    //const int val = init; //变量赋值
    const int val = 6;
    std::cout << &val << val << std::endl;	//6
    const int* cp = &val;
    int* p = const_cast<int*>(cp);
    *p = 2;
    std::cout << &val << val << std::endl;	//6	 变量赋值直接更改为2 
    std::cout << p << *p << std::endl;//地址一样 //2 编译时对常量值进行替换

    //4. reinterpret_cast
    //最不安全,主要适用于依赖底层实现的编程技术，具有不可移植性 
    int* p = new int;						//1.不同类型指针或引用之间的转换
    char* p1 = static_cast<char*>(p);		// error
    char* p2 = reinterpret_cast<char*>(p1); // ok
    //B* x = new B();
    //A* new_a = reinterpret_cast<A*>(x);   //class B to class A

    struct B { int val; };
    B b{ 101 };								//2.指针和整数之间的转换
    std::cout << "&b=" << &b << std::endl; 		//&b=0x7ffffdc4f270
    long addr = reinterpret_cast<long>(&b); 	//将地址转换成整数
    std::cout << "addr=" << addr << std::endl;	//addr=140737450930800

    class Data
    {
    public:
        short a;
        short b;
    };
    void delete_ptr(void* p)
    {
        if (p != nullptr)
        {
            delete p;
            p = nullptr;
        }
    }
    long value = 0xAAAABBBB;
    Data* pData = reinterpret_cast<Data*>(&value);
    cout << hex << pData->a << endl;	//BBBB 
    cout << hex << pData->b << endl;	//AAAA
    // 不需要释放指针pData的空间，它的地址和变量value相同，会自动释放掉
    // delete_ptr(pData);

    

    //自动类型转换
    /*
    1.当不同类型的变量同时运算(条件判断中，非布尔型自动转换为布尔类型)
    char + int:  char->int
    int + double : int->double
    2.一个参数作为另一个不同类型参数的赋值
    参数char，输入int:int通过ASCII转换为字符
    参数int，输入浮点型，自动转换为浮点型 */
    
    //string <--> const char*
    string a = "hello";
    const char* b = a.c_str();
    string c = b;
    string(b)
    //string <--> char*
    char* b = const_cast<char*>(a.c_str());
    char* c = (char*)a.c_str();
    string d = c;
    string(c);
    //string <--> char[]
    char b[] = "nihao";
    for (int i = 0; i < strlen(b); i++) b[i] = a[i];
    strcpy_s(b, a.c_str());  //strcpy_s(微软库函数)
    string c = b;
    string(b)
    //string <--> int,long,double
    string c = "3.14"
    cout << atoi(c.c_str()) << endl;//方法一
    cout << atol(c.c_str()) << endl;
    cout << atof(c.c_str()) << endl;
/*  
template<class T>				   //方法二
T StrToNum(const string & str) {
    istringstream iss(str);
    T num;
    iss >> num;
    return num;
}*/
    float a = 3.14;
    to_string(a);       //方法一
/*    
template<class T>		//方法二
string NumToStr(T & num) {
    ostringstream oss;
    oss << num;
    string str(oss.str());
    return str;
}*/  

    //const char* <--> char* 
    const char* a = "hello";
    char* c = const_cast<char*>(a);
    char* d = (char*)a;
    const char* f = d;
    cout << (const char*)d << endl;
    //const char* <--> char[]
    char a[100];
    const char* s = "hello";
    strcpy_s(a, s);
    const char* s = a;
    //cosnt char* <--> int,long,double
    const char* a = "3.14"
        cout << atoi(a) << endl;//方法一
    cout << atol(a) << endl;
    cout << atof(a) << endl;
/*  
template<class T>		        //方法二
T StrToNum(const char*& str) {
    istringstream iss(str);
    T num;
    iss >> num;
    return num;
}*/
    float a = 3.14;
    to_string(a).c_str();  //方法一
/*  
template<class T>	      //方法二
const char* NumToStr(T & num) {
    ostringstream oss;
    oss << num;
    const char* str = oss.str();
    return str;
}*/  

    //char* <--> char[]
    char a[100];
    char* s = "nihao";
    strcpy_s(a, s);
    const char* s = a;
    //char* <--> int,long,double
    char* a = "3.14"
    cout << atoi(a) << endl;//方法一
    cout << atol(a) << endl;
    cout << atof(a) << endl;
/*  
template<class T>		//方法二
T StrToNum(char*& str) {
    istringstream iss(str);
    T num;
    iss >> num;
    return num;
}*/
    float a = 3.14;
    char* c = const_cast<char*>(to_string(a).c_str());//方法一
/*    
template<class T>	//方法二
char* NumToStr(T & num) {
    ostringstream oss;
    oss << num;
    char* str = oss.str();
    return str;
}*/  

    //char[] <--> int，float，double
    char a[] = "3.14"
    cout << atoi(a) << endl;
    cout << atol(a) << endl;
    cout << atof(a) << endl;
    int b = 3;
    char arr[100] = { 0 };
    strcpy_s(s, to_string(b).c_str());

    //int，float，double互转
    float a = 3.14;
    int b = a;
    cout << int(b) << endl;

    //char <--> int
    char a = '1';
    int b = a - '0';
    int c = 1;
    char d = c + '0';

    return 0;
}
