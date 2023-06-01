

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> 
using namespace std;

inline double square(double x) { return x * x; }

void swap(int & a, int & b)    // use references 
{
    int temp;
    temp = a;       
    a = b;
    b = temp;
}

//通常数组用指针，类对象用引用，结构用指针或引用

double refcube1(double &ra)   //变量属于可修改的左值，不匹配时(表达式)会报错
{
    ra *= ra * ra;
    return ra; 
}
double refcube2(const double &ra)   //const变量属于不可修改的左值，不匹配时(常量/表达式)会生成临时变量
{
    return ra *ra * ra;
}

//结构引用
struct free_throws
{
    std::string name;
    int made;
    int attempts;
    float percent;
};
void display(const free_throws & ft);   //结构引用,注意const修饰表示不可修改的左值
void set_pc(free_throws & ft);
const free_throws & accumulate(free_throws &target, const free_throws &source);//返回的是不可修改的const左值，常规函数返回右值

 //类对象引用
string version1(const string & s1, const string & s2)
{
    string temp;
    temp = s2 + s1 + s2;    //复制到temp临时储存单元
    return temp;            //main中temp内容被复制到result中
}
const string & version2(string & s1, const string & s2)  
{
    s1 = s2 + s1 + s2;
    return s1;              //会修改原s1数据
}
const string & version3(string & s1, const string & s2)   
{
    string temp;
    temp = s2 + s1 + s2;
    return temp;            //警告，temp临时储存单元只在函数中有效，故不可返回指向temp的引用
}

//file_fun
void file_it(ostream& os, double fo, const double fe[], int n); //ostream&可以接收ostream或子类对象(cout/fout...)

//默认参数
const int ArSize = 80;
char* left(const char* str, int n = 1); //函数原型指定默认值后定义可以不用指定（调用时省略则按默认，传值则覆盖）
//char* left(const char* str, int n = 1, int m);  //invalid 必须从右往左添加默认值

//函数重载（特征标）
unsigned long left(unsigned long num, unsigned ct);

//函数模板
template <typename T>  // or class T
void Swap(T& a, T& b);

//重载模板
const int Lim = 8;
template <typename T>
void Swap(T* a, T* b, int n);

//显式具体化
struct job
{
    char name[40];
    double salary;
    int floor;
};
template <> void Swap<job>(job& j1, job& j2);   //<job>指示类型可选
//template <> void Swap(job& j1, job& j2);

//显式实例化
//template void Swap<int>(int&, int&);    //无 <>

//总结:非模块函数优于模板函数 (func<>()自己选择模板函数，多个参数必须考虑所有参数匹配情况)
//     显式具体化优于隐式具体化 (const只适用于指针和引用，否则会出现二义性ambiguous)
template <typename T>            // template A
void ShowArray(T arr[], int n);
template <typename T>            // template B(更具体，假设数组内容是指针，解引用*arr[i])
void ShowArray(T * arr[], int n);

template <class T1, class T2>
void add(T1 x, T2 y)
{
    decltype(x + y) sum1 = x + y;    //自动推断sum模板类型,()表达式可以是函数，表示其返回值类型
    typedef decltype(x + y) xytype;
    xytype sum2 = x + y;
}

template <class T1, class T2>
auto add(T1 x, T2 y) -> decltype(x + y) //后置返回类型
{
   return x + y;    //不能直接decltype(), xy不在作用域
}


int main()
{

    // 1.inline内联函数(不能递归):函数代码代替函数调用，无需跳转，占用更多内存
    double a, b;
    double c = 4.0;
    a = square(5.0);
    b = square(2.0 + 3.0);   // 能通过表达式：与宏（直接替换而非传参）的区别
    cout << a << b << square(++c) << endl;  // 25 25 25

    // 2.引用变量reference 
    int a = 10, b = 5;
    swap(a, b);     //a=5 b=10与指针等效，传递变量本身而非变量副本
    int & r = a;    //引用必须在声明时初始化(此处 & 非取地址符号)
    cout << a << r << endl; // 5 5
    r++;
    cout << a << r << endl; // 6 6
    r = b;          //不能改变引用地址(只是改变了值)
    cout << a << b << r << endl;    //10 10 10
    cout << &a << &r << &b << endl; //0x61fef8 0x61fef8 0x61fef4
    
    double x = 5.0, y = 5.0;
    //cout << refcube1(x + 5.0);        //error 引用参数必须是变量，不能是表达式
    cout << refcube1(x);
    cout << " = cube of " << x << endl; // 125 = cube of 125 
    cout << refcube2(5.0);      // 125  temporary variable
    cout << refcube2(y + 5.0);  // 1000 temporary variable
    cout << refcube2(y);
    cout << " = cube of " << y << endl; // 125 = cube of 5 
    
    //结构引用
    free_throws one = {"zhang", 10, 10};    //percent默认0
    free_throws two = {"yang", 10, 10};
    free_throws three = {"wang", 10, 10};
    free_throws team = {"team", 0, 0};
    set_pc(one);
    display(one);
    accumulate(team, one);
    display(team);  
    display(accumulate(team, two)); // ok 内部函数返回const引用
    display(team);  
    // accumulate(accumulate(team, three), four); //invalid 内部函数返回const引用，不能作为外部函数第一个参数
    // accumulate(dup,one) = two;                 //invalid 返回的是不可修改的左值
    const free_throws  dup = accumulate(team,three);    //dup是team的别名
    display(dup);   
    
    //类对象引用
    string input;
    string copy;
    string result;
    cout << "Enter a string: ";
    getline(cin, input);    // www
    copy = input;
    result = version1(input, "***");    //第二个实参C风格字符串 char*-->string&
    cout << result << endl; // ***www***
    cout << input << endl;  // ww
    result = version2(input, "###");
    cout << result << endl; // ###www###
    cout << input << endl;  // ###www###
    input = copy;           //reset
    cout << input << endl;  // www
    result = version3(input, "@@@");
    cout << result << endl; // 程序崩溃，试图引用已释放的内存
    
    
    char sample[ArSize];
    cin.get(sample, ArSize);//hello char*
    char* temp;
    temp = left(sample, 4); // hell
    delete[] temp;       // free old
    temp = left(sample);        // h 默认
    delete[] temp;       // free new
    unsigned long n = 12345678; 
    cout << left(n, 5) << endl; // 12345 重载
 
    //具体化与实例化
    int i = 10;
    int j = 20;
    double x = 10.0;
    double y = 20.0;
    Swap(i, j);         
    Swap(x, y);                             //模板 （1.隐式实例化）
    int d1[Lim] = { 0,7,0,4,1,7,7,6 };
    int d2[Lim] = { 0,7,2,0,1,9,6,9 };
    Swap(d1, d2, Lim);  //重载模板
    job sue = { "Sue", 73000.60, 7 };
    job sid = { "Sid", 78060.72, 9 };
    Swap(sue, sid);                         // 2.显式具体化
    //template void Swap<int>(int&, int&);  // 3.显式实例化
    float a = 10.5, b = 15.5;
    Swap<float>(a, b);  //强转(显式)实例化 (生成float版本)
    Swap(a, b);         //使用上面显式实例化float模板进行具体化

    return 0;  
}

void display(const free_throws & ft)
{
    using std::cout;
    cout << "Name: " << ft.name << '\t';
    cout << "Made: " << ft.made << '\t';
    cout << "Attempts: " << ft.attempts << '\t';
    cout << "Percent: " << ft.percent << '\n';
}
void set_pc(free_throws & ft)
{
    if (ft.attempts != 0)
        ft.percent = 100.0f *float(ft.made)/float(ft.attempts);
    else
        ft.percent = 0;
}

const free_throws & accumulate(free_throws & target, const free_throws & source)
{
    target.attempts += source.attempts;
    target.made += source.made;
    set_pc(target);
    return target;  //返回引用内存块
}

void file_it(ostream& os, double fo, const double fe[], int n)
{
    // save initial formatting state
    ios_base::fmtflags initial;
    initial = os.setf(ios_base::fixed, ios_base::floatfield);   //定点表示法
    std::streamsize sz = os.precision(0);
    os << "Focal length of objective: " << fo << " mm\n";
    os.precision(1);
    os.width(12);
    os << "f.l. eyepiece";
    os.width(15);
    os << "magnification" << endl;
    for (int i = 0; i < n; i++)
    {
        os.width(12);
        os << fe[i];
        os.width(15);
        os << int(fo / fe[i] + 0.5) << endl;
    }
    // restore initial formatting state
    os.setf(initial, ios_base::floatfield);
    os.precision(sz);
}

char* left(const char* str, int n)
{
    //int len = strlen(str);
    //n = (n < len) ? n : len;
    if (n < 0)
        n = 0;
    char* p = new char[n + 1];
    int i;
    for (i = 0; i < n && str[i]; i++) //空字符结束循环
        p[i] = str[i];  
    while (i <= n)
        p[i++] = '\0';  
    return p;
}

unsigned long left(unsigned long num, unsigned ct)
{
    unsigned digits = 1;
    unsigned long n = num;

    if (ct == 0 || num == 0)
        return 0;       // return 0 if no digits
    while (n /= 10)
        digits++;
    if (digits > ct)
    {
        ct = digits - ct;
        while (ct--)
            num /= 10;
        return num;        
    }
    else                
        return num;     
}

template <typename T>  
void Swap(T& a, T& b)
{
    T temp;   
    temp = a;
    a = b;
    b = temp;
}

template <typename T>
void Swap(T a[], T b[], int n)
{
    T temp;
    for (int i = 0; i < n; i++)
    {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

template <> void Swap<job>(job& j1, job& j2)  // specialization 不交换姓名
{
    double t1;
    int t2;
    t1 = j1.salary;
    j1.salary = j2.salary;
    j2.salary = t1;
    t2 = j1.floor;
    j1.floor = j2.floor;
    j2.floor = t2;
}
