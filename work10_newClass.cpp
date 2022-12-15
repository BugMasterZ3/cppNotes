

#include <iostream>
#include <cstring>
#include <cstdlib>      // rand(), srand()
#include <ctime>        // time()
#include <string>
#include <new>          //定位new运算符
using namespace std;


class StringBad
{
private:
    char * str;               
    int len;                  
    static int num_strings;   //共享副本,声明时不能初始化（若是整型或枚举型const可以初始化）
public:
    StringBad(const char * s); 
    StringBad();               
    ~StringBad();              
    friend std::ostream & operator<<(std::ostream & os, const StringBad & st);
};

void callme1(StringBad &);  
void callme2(StringBad);    // 会导致析构函数被调用


/*特殊成员函数
*默认构造函数（显式/隐式，只能有一个（二义性问题））
*复制构造函数（对象引用作为构造函数参数，默认浅复制，显式/深度复制方法）
*赋值运算符（重载赋值问题，深度复制数据而不仅仅复制地址）
*静态成员函数（对象不能调用，独立定义不包含static，只能使用静态成员）
*/
const int ArSize = 10;
const int MaxLen =81;

class String
{
private:
    char * str;             // pointer to string
    int len;                // C++11允许类内初始化，但会被初始化列表的构造函数覆盖   
    static int num_strings; // number of objects
    static const int CINLIM = 80;  // cin input limit
    //const int Len;
    //StringBad & sb;
public:
// constructors and other methods
    //String(int n, StringBad & s) : Len(n*2+1), str(NULL), sb(s) {}   //构造函数初始化const常量成员/引用类成员(成员初始化列表不仅限于常量)  
    String(const char * s); // new []  C++11空指针:nullptr
    String();               
    String(const String &); // copy constructor
    ~String();              // delete []
    int length () const { return len; }
// overloaded operator methods    
    String & operator=(const String &);  // ()返回引用不会调用复制构造函数，效率更高
    String & operator=(const char *);    // 深度复制
    char & operator[](int i);
    const char & operator[](int i) const;
// overloaded operator friends
    friend bool operator<(const String &st, const String &st2);
    friend bool operator>(const String &st1, const String &st2);
    friend bool operator==(const String &st, const String &st2);
    friend ostream & operator<<(ostream & os, const String & st);
    friend istream & operator>>(istream & is, String & st);
// static function
    static int HowMany();
};


const int BUF = 512;

class JustTesting
{
private:
    string words;
    int number;
public:
    JustTesting(const string& s = "Just Testing", int n = 0)
    {
        words = s; number = n; cout << words << " constructed\n";
    }
    ~JustTesting() { cout << words << " destroyed\n"; }
    void Show() const { cout << words << ", " << number << endl; }
};


int main()
{

    StringBad headline1("Celery Stalks at Midnight");
    StringBad headline2("Lettuce Prey");
    StringBad sports("Spinach Leaves Bowl for Dollars");
    callme1(headline1);
    cout << "headline1: " << headline1 << endl;
    callme2(headline2);
    cout << "headline2: " << headline2 << endl;
    StringBad sailor = sports;  // sailor = StringBad(sports); 隐式复制构造函数（返回对象地址）
    cout << "sailor: " << sailor << endl;
    StringBad knot;
    knot = headline1;
    cout << "knot: " << knot << endl; 


    String name;
    cout <<"Hi, what's your name?\n>> ";
    cin >> name;
    cout << name << ", please enter up to " << ArSize << " short sayings <empty line to quit>:\n";
    String sayings[ArSize];     // array of objects
    char temp[MaxLen];          // temporary string storage
    int i;
    for (i = 0; i < ArSize; i++)
    {
        cout << i+1 << ": ";
        cin.get(temp, MaxLen);
        while (cin && cin.get() != '\n')
            continue;
        if (!cin || temp[0] == '\0')    // empty line
            break;              
        else
            sayings[i] = temp; 
    }
    int total = i;              
    if (total > 0)
    {
        cout << "Here are your sayings:\n";
        for (i = 0; i < total; i++)
            cout << sayings[i] << "\n";

        String* shortest = &sayings[0]; //指向对象的指针
        String* first = &sayings[0];
        for (i = 1; i < total; i++)
        {
            if (sayings[i].length() < shortest->length())   /指针访问类方法
                shortest = &sayings[i];
            if (sayings[i] < *first)     
                first = &sayings[i];     // assign address
        }
        cout << "Shortest saying:\n" << *shortest << endl;
        cout << "First alphabetically:\n" << *first << endl;

        srand(time(0));
        int choice = rand() % total;
        String* favorite = new String(sayings[choice]); //初始化指向对象的指针
        cout << "My favorite saying:\n" << *favorite << endl;   //解引用
        delete favorite;    //显式删除指针，才会调用所指对象析构函数
    }
    else
        cout << "Not much to say, bye\n";


    char* buffer = new char[BUF];       // get a block of memory
    JustTesting* pc1, * pc2;
    pc1 = new (buffer) JustTesting;     //定位new运算符（缓冲区中创建对象）
    pc2 = new JustTesting("Heap1", 20); //常规new运算符
    cout << (void*)buffer << endl;  //004CF690   
    cout << pc1 << ": ";
    pc1->Show();                    //004CF690: Just Testing, 0
    JustTesting* pc3, * pc4;
    // fix placement new location
    pc3 = new (buffer + sizeof(JustTesting)) JustTesting("Better Idea", 6); //确保缓冲区两个不同地址且内存单元不重叠
    pc4 = new JustTesting("Heap2", 10);
    delete pc2;           // 销毁堆中对象
    delete pc4;
    pc3->~JustTesting();  // 显式调用析构函数相反顺序销毁对象，释放缓冲区（delete不能与定位new运算符配合使用）
    pc1->~JustTesting(); 
    delete[] buffer;      // free buffer
    
    return 0;
}


/******/
int StringBad::num_strings = 0; //初始化静态成员

StringBad::StringBad(const char * s)
{
    len = std::strlen(s);             
    str = new char[len + 1];        
    std::strcpy(str, s);             
    num_strings++;                    
    cout << num_strings << ": \"" << str << "\" object created\n";    
}

StringBad::StringBad()               
{
    len = 4;
    str = new char[4];
    std::strcpy(str, "C++");          
    num_strings++;
    cout << num_strings << ": \"" << str << "\" default object created\n";  
}

StringBad::~StringBad()               
{
    cout << "\"" << str << "\" object deleted, ";    
    --num_strings;                    
    cout << num_strings << " left\n"; 
    delete [] str;                    
}

std::ostream & operator<<(std::ostream & os, const StringBad & st)
{
    os << st.str;
    return os; 
}

void callme1(StringBad & rsb)
{
    cout << "String passed by reference:\n";
    cout << "    \"" << rsb << "\"\n";
}

void callme2(StringBad sb)
{
    cout << "String passed by value:\n";
    cout << "    \"" << sb << "\"\n";
}

/******/
int String::num_strings = 0;
// static method
int String::HowMany()
{
    return num_strings;
}

String::String(const char * s)    
{
    len = std::strlen(s);         
    str = new char[len + 1];       // allot storage
    std::strcpy(str, s);           // initialize pointer
    num_strings++;                 // set object count
}

String::String()                 
{
    len = 4;
    str = new char[1];             //确保与析构函数兼容
    str[0] = '\0';                 
    num_strings++;
}

String::String(const String & st)
{
    num_strings++;             // handle static member update
    len = st.len;              
    str = new char [len + 1];  
    std::strcpy(str, st.str);  
}

String::~String()                     
{
    --num_strings;                    
    delete [] str;                   
}

// assign a String to a String
String & String::operator=(const String & st)
{
    if (this == &st)
        return *this;
    delete [] str;
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str, st.str);
    return *this;
}

// assign a C string to a String
String & String::operator=(const char * s)
{
    delete [] str;
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    return *this;
}

// read-write char access for non-const String
char & String::operator[](int i)
{
    return str[i];
}

// read-only char access for const String
const char & String::operator[](int i) const
{
    return str[i];
}

// overloaded operator friends
bool operator<(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str, st2.str) < 0);
}

bool operator>(const String &st1, const String &st2)
{
    return st2 < st1;
}

bool operator==(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str, st2.str) == 0);
}

// simple String output
ostream & operator<<(ostream & os, const String & st)
{
    os << st.str;
    return os; 
}

// quick and dirty String input
istream & operator>>(istream & is, String & st)
{
    char temp[String::CINLIM];
    is.get(temp, String::CINLIM);
    if (is)
        st = temp;
    while (is && is.get() != '\n')
        continue;
    return is; 
}
