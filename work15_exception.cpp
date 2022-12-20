

#include <iostream>
#include <string>
#include <cstdlib>  //cerr标准错误流,abort()
#include <cfloat>   //DBL_MAX
#include <cmath>
#include <exception>    //基类异常exception-->bad_exception，what()虚方法，terminate(), set_terminate(), set_unexpected() 
#include <stdexcept>   
// 1. logic_error-->domain_error, invalid_argument, length_error, out_of_bounds索引越界
// 2. runtime_error-->range_error, overflow_error, underflow_error浮点数计算
#include <new>          //bad_alloc 内存异常
using namespace std;


//error1 -- abort()
double hmean1(double a, double b)
{
    if (a == -b)
    {
        std::cout << "untenable arguments to hmean()\n";
        std::abort();   //是否刷新文件缓冲区取决于实现（异常终止，不返回main），默认异常调用函数
    }
    return 2.0 * a * b / (a + b);   //两个数的调和平均数
}

//error2 -- 返回错误码
bool hmean2(double a, double b, double* ans) // 指针/引用
{
    if (a == -b)
    {
        *ans = DBL_MAX;
        return false;
    }
    else
    {
        *ans = 2.0 * a * b / (a + b);
        return true;
    }
}

// error3 -- using an exception
double hmean3(double a, double b)
{
    if (a == -b)
        throw "bad hmean() arguments: a = -b not allowed";  //抛出异常（字符串）
    return 2.0 * a * b / (a + b);
}


//error4 对象用作异常类型
class bad_hmean     
{
private:
    double v1;
    double v2;
public:
    bad_hmean(double a = 0, double b = 0) : v1(a), v2(b) {}
    void mesg() { std::cout << "hmean(" << v1 << ", " << v2 << "): " << "invalid arguments: a = -b\n"; }
};

class bad_gmean     // : public std::exception 继承异常类
{
public:
    double v1;
    double v2;
    bad_gmean(double a = 0, double b = 0) : v1(a), v2(b) {}
    const char* mesg() { return "gmean() arguments should be >= 0\n"; } //const char* what()
};

double hmean(double a, double b)    // + noexcept 指出函数不会引发异常
{
    if (a == -b)
        throw bad_hmean(a, b);      //编译器总会创建临时拷贝,即使catch指定引用
    return 2.0 * a * b / (a + b);
}

double gmean(double a, double b)   
{
    if (a < 0 || b < 0)
        throw bad_gmean(a, b);
    return std::sqrt(a * b);    //几何平均值
}

//异常与继承
class Sales
{
public:
    enum {MONTHS = 12};   // could be a static const
    class bad_index : public std::logic_error   //嵌套异常
    {
    private:
        int bi;  // bad index value
    public:
        explicit bad_index(int ix, const std::string & s = "Index error in Sales object\n");
        int bi_val() const {return bi;}
        virtual ~bad_index() throw() {}     //异常规范throw(), C++98
    };
    explicit Sales(int yy = 0);
    Sales(int yy, const double * gr, int n);
    virtual ~Sales() { }
    int Year() const { return year; }
    virtual double operator[](int i) const;
    virtual double & operator[](int i);
private:
    double gross[MONTHS];
    int year;
};

class LabeledSales : public Sales
{
  public:
    class nbad_index : public Sales::bad_index
    {
    private:
        std::string lbl;
    public:
        nbad_index(const std::string & lb, int ix, const std::string & s = "Index error in LabeledSales object\n");
        const std::string & label_val() const {return lbl;}
        virtual ~nbad_index() throw() {}
     };
    explicit LabeledSales(const std::string & lb = "none", int yy = 0);
    LabeledSales(const std::string & lb, int yy, const double * gr, int n);
    virtual ~LabeledSales() { }
    const std::string & Label() const {return label;}
    virtual double operator[](int i) const;
    virtual double & operator[](int i);
private:
    std::string label;
};


int main()
{
    
    using std::cout;
    using std::cin;
    using std::endl;

    double x, y, z;
    cout << "Enter two numbers: ";
    while (cin >> x >> y)
    {
        //error1
        z = hmean1(x, y);
        cout << "Harmonic mean of " << x << " and " << y << " is " << z << endl;
        
        //error2
        if (hmean2(x, y, &z))
            cout << "Harmonic mean of " << x << " and " << y << " is " << z << endl;
        else
            cout << "One value should not be the negative of the other - try again.\n";
        
        //error3
        try {                   //标识异常代码块
            z = hmean3(x, y);
        }                       
        catch (const char* s)  // 捕获异常类型（匹配到异常字符串）
        {
            cout << s << endl;
            cout << "Enter a new pair of numbers: ";
            continue;
        }                       
        cout << "Harmonic mean of " << x << " and " << y << " is " << z << endl;
        

        //cout << "Enter next set of numbers <q to quit>: ";
        
        //error4
        try {                 
            z = hmean(x,y);
            cout << "Harmonic mean of " << x << " and " << y << " is " << z << endl;
            cout << "Geometric mean of " << x << " and " << y << " is " << gmean(x,y) << endl;
            cout << "Enter next set of numbers <q to quit>: ";
        }
        catch (bad_hmean & bg)    //处理不同异常，引用指向副本（基类引用能捕获所有派生类）
        {
            bg.mesg();
            cout << "Try again.\n";
            continue;
        }                  
        catch (bad_gmean & hg) 
        {
            cout << hg.mesg();
            cout << "Values used: " << hg.v1 << ", " << hg.v2 << endl;
            cout << "Sorry, you don't get to play any more.\n";
            break;
        } 
        // catch(std::exception & e) { cout << e.what() << endl; } 捕获所有exception派生类异常
        catch (...)         //调用其他函数但未知其类型
        {
        }
    }

    // bad_alloc
    struct Big
    {
        double stuff[20000];
    };
    Big * pb;
    //pb = new (std::nothrow) Big[12000];   //异常返回空指针
    //if(pb == 0) exit(EXIT_FAILURE);   
    try {
        cout << "Trying to get a big block of memory:\n";
        pb = new Big[12000]; 
        cout << "Got past the new request:\n";
    }
    catch (bad_alloc & ba)
    {
        cout << "Caught the exception!\n";
        cout << ba.what() << endl;  // std::bad_alloc
        //delete [] pb;               //清理工作
        exit(EXIT_FAILURE);
    }
    cout << "Memory successfully allocated\n";
    pb[0].stuff[0] = 4;
    cout << pb[0].stuff[0] << endl;
    delete [] pb;
    

    double vals1[12] =
    {
        1220, 1100, 1122, 2212, 1232, 2334,
        2884, 2393, 3302, 2922, 3002, 3544
    };
    double vals2[12] =
    {
        12, 11, 22, 21, 32, 34,
        28, 29, 33, 29, 32, 35
    };
    Sales sales1(2011, vals1, 12);
    LabeledSales sales2("Blogstar",2012, vals2, 12);

    try
    {
        int i;
        cout << "Year = " << sales1.Year() << endl;
        for (i = 0; i < 12; ++i)
        {
            cout << sales1[i] << ' ';
            if (i % 6 == 5)
                cout << endl;
        }
        cout << "Year = " << sales2.Year() << endl;
        cout << "Label = " << sales2.Label() << endl;
        //for (i = 0; i <= 12; ++i)  //索引越界
        for (i = 0; i < 12; ++i)
        {

            cout << sales2[i] << ' ';
            if (i % 6 == 5)
                cout << endl;
        }

        sales2[2] = 37.5;
        sales1[20] = 23345;   //索引越界
    }
    catch(LabeledSales::nbad_index & bad)
    {
        cout << bad.what();                             //Index error in LabeledSales object
        cout << "Company: " << bad.label_val() << endl; //Blogstar
        cout << "bad index: " << bad.bi_val() << endl;  //12
    }
    catch(Sales::bad_index & bad)
    {
        cout << bad.what();                             //Index error in Sales object
        cout << "bad index: " << bad.bi_val() << endl;  //20
    }
       
    return 0;
}


Sales::bad_index::bad_index(int ix, const string & s ) : std::logic_error(s), bi(ix)
{
}

Sales::Sales(int yy)
{
    year = yy;
    for (int i = 0; i < MONTHS; ++i)
        gross[i] = 0;
}

Sales::Sales(int yy, const double * gr, int n)
{
    year = yy;
    int lim = (n < MONTHS)? n : MONTHS;
    int i;
    for (i = 0; i < lim; ++i)
        gross[i] = gr[i];
    for ( ; i < MONTHS; ++i)    // for i > n and i < MONTHS
        gross[i] = 0;
}

double Sales::operator[](int i) const
{
    if(i < 0 || i >= MONTHS)
        throw bad_index(i);
    return gross[i];
}

double & Sales::operator[](int i)
{
    if(i < 0 || i >= MONTHS)
        throw bad_index(i);
    return gross[i];
}

LabeledSales::nbad_index::nbad_index(const string & lb, int ix, const string & s ) : Sales::bad_index(ix, s)
{
    lbl = lb;
}

LabeledSales::LabeledSales(const string & lb, int yy) : Sales(yy)
{
    label = lb;
}

LabeledSales::LabeledSales(const string & lb, int yy, const double * gr, int n) : Sales(yy, gr, n)
{
    label = lb;
}

double LabeledSales::operator[](int i) const
{    if(i < 0 || i >= MONTHS)
        throw nbad_index(Label(), i);
    return Sales::operator[](i);
}

double & LabeledSales::operator[](int i)
{
    if(i < 0 || i >= MONTHS)
        throw nbad_index(Label(), i);
    return Sales::operator[](i);
}
