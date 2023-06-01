

#include <iostream>
#include <cstring>
#include <string>   
#include <valarray> //数值类方法:[] size() sum() max() min()
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;
using std::string;
using std::strchr;  //判断字符是否在字符串中

/*
1.public 继承：		基类public，protected，private->派生类public, protected, private
2.protected 继承：	基类public，protected，private->派生类protected, protected, private
3.private 继承：	基类public，protected，private->派生类private, private, private
*/

/*
class Student
{   
private:
    typedef std::valarray<double> ArrayDb;  
    std::string name;       
    ArrayDb scores;         // has-a 关系,包含易于理解
    std::ostream & arr_out(std::ostream & os) const;  // private method for scores output
public:
    Student() : name("Null Student"), scores() {}     //初始化顺序与声明一致，与列表顺序无关              
    explicit Student(const std::string & s) : name(s), scores() {}  //防单参数隐式转换
    explicit Student(int n) : name("Nully"), scores(n) {}           
    Student(const std::string & s, int n) : name(s), scores(n) {}                       //n个数
    Student(const std::string & s, const ArrayDb & a) : name(s), scores(a) {}
    Student(const char * str, const double * pd, int n) : name(str), scores(pd, n) {}   //n个数pd
    ...
};
*/
//私有继承,不能隐式向上转换,不指定默认私有继承
class Student : private std::string, private std::valarray<double>  //多重继承, has-a 关系，类名::方法访问
{   
private:
    typedef std::valarray<double> ArrayDb;
    std::ostream & arr_out(std::ostream & os) const;
public:
    Student() : std::string("Null Student"), ArrayDb() {}   //通过类名初始化
    explicit Student(const std::string & s) : std::string(s), ArrayDb() {}
    explicit Student(int n) : std::string("Nully"), ArrayDb(n) {}
    Student(const std::string & s, int n) : std::string(s), ArrayDb(n) {}
    Student(const std::string & s, const ArrayDb & a) : std::string(s), ArrayDb(a) {}
    Student(const char * str, const double * pd, int n) : std::string(str), ArrayDb(pd, n) {}
    ~Student() {}
    //using std::valarray<double>::max; 使student对象能调用基类方法max()
    double Average() const;
    double & operator[](int i);
    double operator[](int i) const;
    const std::string & Name() const;
    // input
    friend std::istream & operator>>(std::istream & is, Student & stu);  // 1 word
    friend std::istream & getline(std::istream & is, Student & stu);     // 1 line
    // output
    friend std::ostream & operator<<(std::ostream & os, const Student & stu);
};

const int pupils = 2;   //学生个数
const int quizzes = 4;  //成绩个数

void set(Student & sa, int n)
{
    cout << "Please enter the student's name: ";
    getline(cin, sa);
    cout << "Please enter " << n << " quiz scores:\n";
    for (int i = 0; i < n; i++)
        cin >> sa[i];
    while (cin.get() != '\n')
        continue; 
}


class Worker   // an abstract base class
{
private:
    std::string fullname;
    long id;
protected:      
    virtual void Data() const; //设置为保护使继承层次结构中的类能使用，避免调用方法出现二义性
    virtual void Get();
public:
    Worker() : fullname("no one"), id(0L) {}
    Worker(const std::string & s, long n) : fullname(s), id(n) {}
    virtual ~Worker() = 0; // pure virtual function
    virtual void Set() = 0;
    virtual void Show() const = 0;
};

class Waiter : virtual public Worker //虚基类(共享一个Worker对象)，避免派生类向上转换产生二义性
{
private:
    int panache;
protected:
    void Data() const;
    void Get();
public:
    Waiter() : Worker(), panache(0) {}
    Waiter(const std::string & s, long n, int p = 0) : Worker(s, n), panache(p) {}
    Waiter(const Worker & wk, int p = 0) : Worker(wk), panache(p) {}
    void Set();
    void Show() const;
};

class Singer : virtual public Worker //虚基类(共享一个Worker对象)，避免派生类向上转换产生二义性
{
protected:
    enum {other, alto, contralto, soprano, bass, baritone, tenor};
    enum {Vtypes = 7};
    void Data() const;
    void Get();
private:
    static char *pv[Vtypes];    // 静态指针数组指向声音类型
    int voice;
public:
    Singer() : Worker(), voice(other) {}
    Singer(const std::string & s, long n, int v = other) : Worker(s, n), voice(v) {}
    Singer(const Worker & wk, int v = other) : Worker(wk), voice(v) {}
    void Set();
    void Show() const;
};

// multiple inheritance
// 虚基类与非虚基类混合继承将包含 （1 + 非虚派生类数量）个(Worker)基类子对象
class SingingWaiter : public Singer, public Waiter
{
protected:
    void Data() const;  //优先级相同，限定符区分，避免二义性
    void Get();
public:
    SingingWaiter()  {}
    //显式调用虚基类Worker构造函数（后面多条途径传递给Worker会产生冲突，使Worker构造失效按默认构造）
    SingingWaiter(const std::string & s, long n, int p = 0, int v = other) 
            : Worker(s,n), Waiter(s, n, p), Singer(s, n, v) {}
    SingingWaiter(const Worker & wk, int p = 0, int v = other)
            : Worker(wk), Waiter(wk,p), Singer(wk,v) {}
    SingingWaiter(const Waiter & wt, int v = other)
            : Worker(wt),Waiter(wt), Singer(wt,v) {}
    SingingWaiter(const Singer & wt, int p = 0)
            : Worker(wt),Waiter(wt,p), Singer(wt) {}
    void Set();     //同名称派生类优先于直接/间接祖先类
    void Show() const; 
};

const int SIZE = 5;


int main()
{
    
    Student ada[pupils] = {Student(quizzes), Student(quizzes)};
    int i;
    for (i = 0; i < pupils; ++i)
        set(ada[i], quizzes);
    for (i = 0; i < pupils; ++i)
        cout << ada[i].Name() << endl;
    for (i = 0; i < pupils; ++i)
    {
        cout << endl << ada[i]; // scores for...
        cout << "average: " << ada[i].Average() << endl;
    }


    Worker * lolas[SIZE];
    int ct;
    for (ct = 0; ct < SIZE; ct++)
    {
        char choice;
        cout << "Enter the employee category:\n"
            << "w: waiter  s: singer  t: singing waiter  q: quit\n";
        cin >> choice;
        while (strchr("wstq", choice) == NULL)
        {
            cout << "Please enter a w, s, t, or q: ";
            cin >> choice;
        }
        if (choice == 'q')
            break;
        switch(choice)
        {
            case 'w':   lolas[ct] = new Waiter;
                        break;
            case 's':   lolas[ct] = new Singer;
                        break;
            case 't':   lolas[ct] = new SingingWaiter;
                        break;
        }
        cin.get();
        lolas[ct]->Set();
    }
    cout << "\nHere is your staff:\n";
    int i;
    for (i = 0; i < ct; i++)
    {
        cout << endl;
        lolas[i]->Show();
    }
    for (i = 0; i < ct; i++)
        delete lolas[i];


    return 0;
}


// public methods
double Student::Average() const
{
    /*
    if (scores.size() > 0)
        return scores.sum()/scores.size();  
    */
    if (ArrayDb::size() > 0)    //访问基类方法
        return ArrayDb::sum()/ArrayDb::size();  
    else
        return 0;
}

const string & Student::Name() const
{
    return (const string &) *this;  //强制类型转创造引用换访问基类string对象,避免调用构造对象 
}

double & Student::operator[](int i)
{
    return ArrayDb::operator[](i);         // use ArrayDb::operator[]()
}

double Student::operator[](int i) const
{
    return ArrayDb::operator[](i);
}

// private method
ostream & Student::arr_out(ostream & os) const
{
    int i;
    int lim = ArrayDb::size();
    if (lim > 0)
    {
        for (i = 0; i < lim; i++)
        {
            os << ArrayDb::operator[](i) << " ";
            if (i % 5 == 4)
                os << endl;
        }
        if (i % 5 != 0)
            os << endl;
    }
    else
        os << " empty array ";
    return os; 
}

// friends
istream & operator>>(istream & is, Student & stu)
{
    is >> (string &)stu;     
    return is; 
}

istream & getline(istream & is, Student & stu)
{
    getline(is, (string &)stu);
    return is;
}

ostream & operator<<(ostream & os, const Student & stu)
{
    os << "Scores for " << (const string &) stu  << ":\n"; //访问基类友元函数 
    stu.arr_out(os);  // use private method for scores
    return os;
}


// Worker methods
Worker::~Worker() { }
// protected methods
void Worker::Data() const
{
    cout << "Name: " << fullname << endl;
    cout << "Employee ID: " << id << endl;
}
void Worker::Get()
{
    getline(cin, fullname);
    cout << "Enter worker's ID: ";
    cin >> id;
    while (cin.get() != '\n')
        continue;
}

// Waiter methods
void Waiter::Set()
{
    cout << "Enter waiter's name: ";
    Worker::Get();
    Get();
}
void Waiter::Show() const
{
    cout << "Category: waiter\n";
    Worker::Data();
    Data();
}
// protected methods
void Waiter::Data() const
{
    cout << "Panache rating: " << panache << endl;
}
void Waiter::Get()
{
    cout << "Enter waiter's panache rating: ";
    cin >> panache;
    while (cin.get() != '\n')
        continue;
}

// Singer methods
char * Singer::pv[Singer::Vtypes] = {"other", "alto", "contralto", "soprano", "bass", "baritone", "tenor"};
void Singer::Set()
{
    cout << "Enter singer's name: ";
    Worker::Get();
    Get();
}
void Singer::Show() const
{
    cout << "Category: singer\n";
    Worker::Data();
    Data();
}
// protected methods
void Singer::Data() const
{
    cout << "Vocal range: " << pv[voice] << endl;
}
void Singer::Get()
{
    cout << "Enter number for singer's vocal range:\n";
    int i;
    for (i = 0; i < Vtypes; i++)
    {
        cout << i << ": " << pv[i] << "   ";
        if ( i % 4 == 3)
            cout << endl;
    }
    if (i % 4 != 0)
        cout << '\n';
    while (cin >>  voice && (voice < 0 || voice >= Vtypes) )
        cout << "Please enter a value >= 0 and < " << Vtypes << endl;
    while (cin.get() != '\n')
        continue;
}

// SingingWaiter methods
void SingingWaiter::Data() const
{
    Singer::Data(); //优先级相同，限定符区分，避免二义性
    Waiter::Data();
}
void SingingWaiter::Get()
{
    Waiter::Get();
    Singer::Get();
}
void SingingWaiter::Set()
{
    cout << "Enter singing waiter's name: ";
    Worker::Get();
    Get();
}
void SingingWaiter::Show() const
{
    cout << "Category: singing waiter\n";
    Worker::Data();
    Data();
}
