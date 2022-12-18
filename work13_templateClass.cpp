

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

//类模板
template <class Type>   
class Stack
{
private:
    enum {SIZE = 5};    // default size
    int stacksize;
    Type * items;       
    int top;           
public:
    explicit Stack(int ss = SIZE);  //new指针数组
    Stack(const Stack & st);
    ~Stack() { delete [] items; }
    bool isempty() { return top == 0; }
    bool isfull() { return top == stacksize; }
    bool push(const Type & item);   
    bool pop(Type & item);         
    Stack & operator=(const Stack & st);
};
const int Num = 5;

//template class ArrayTP<string, 100> {...};         //显式实例化
//template <> class SortedArray<const char *> {...}; //显式具体化 
template <class T, int n>   //第二个参数为非类型non-type
class ArrayTP
{
private:
    T ar[n];
public:
    ArrayTP() {};
    explicit ArrayTP(const T & v);
    virtual T & operator[](int i);
    virtual T operator[](int i) const;
};


template <class T1, class T2>     //多个类型参数(可以提供默认值)
//template <class T1, class T2 = int>
//template <class T1> class Pair<T1, int> {...}; //部分具体化,<>里表示没有被具体化的类型参数
//template <> class Pair<int, int> {...};        //显式具体化
class Pair
{
private:
    T1 a;
    T2 b;
public:
    T1 & first();
    T2 & second();
    T1 first() const { return a; }
    T2 second() const { return b; }
    Pair(const T1 & aval, const T2 & bval) : a(aval), b(bval) { }
    Pair() {}
};

template<class T1, class T2>
T1 & Pair<T1,T2>::first()
{
    return a;
}

template<class T1, class T2>
T2 & Pair<T1,T2>::second()
{
    return b;
}
/*
    Pair<string, int> ratings[3] =
    {
        Pair<string, int>("The Purpled Duck", 5),
        Pair<string, int>("Cafe Souffle", 4),
        Pair<string, int>("Bertie's Eats", 3)
    };
    ratings[0].first() = "zhangshaunglin";  //修改
    ratings[0].second() = 6;
    int joints = sizeof(ratings) / sizeof (Pair<string, int>);  //计算size大小
    for (int i = 0; i < joints; i++)
        cout << ratings[i].second() << ":\t " << ratings[i].first() << endl;
*/

//template <class T*> 指针具体化版本
//tempalte <class T1, class T2> Person<T1, T2, T2> {...};   //Person<int, short> p1;
//template <class T1> Person<T1, *T1, *T1> {...};   //Person<char, char*, char*> p2;


template <typename T>
class beta
{
private:
    template <typename V>  // 成员模板(私有，只能在类中访问)
    class hold
    {
    private:
        V val;
    public:
        hold(V v  = 0) : val(v) {}
        void show() const { cout << val << endl; }
        V value() const { return val; }
    };
    hold<T> q;             // template object
    hold<int> n;           // template object
public:
    beta(T t, int i) : q(t), n(i) {}
    template<typename U>   // template method
    U blab(U u, T t) { return (n.value() + q.value()) * u / t; }
    void Show() const { q.show(); n.show();}
};
/* 外部定义(嵌套)
template <typename T>
    template <typename V>
        class beta<T>::hold{...};   
template <typename T>
    template <typename U>
        U beta<T>::blab(U u, T t){...}  
*/ 
/*
    beta<double> guy(3.5, 3);
    guy.Show();     // 3.5  3
    cout << guy.blab(10, 2.3) << endl;      //28
    cout << guy.blab(10.0, 2.3) << endl;    //28.2609
*/


template <template <typename T> class Thing, typename U, typename V>    //模板作为参数
class Crab
{
private:
    Thing<U> s1;
    Thing<V> s2;
public:
    Crab() {};
    bool push(U a, V x) { return s1.push(a) && s2.push(x); }
    bool pop(U & a, V & x){ return s1.pop(a) && s2.pop(x); }
};
/*
    Crab<Stack, int, double> nebula; // Stack must match template <typename T> class thing   
    int ni;
    double nb;
    cout << "Enter int double pairs, such as 4 3.5 (0 0 to end):\n";
    while (cin>> ni >> nb && ni > 0 && nb > 0)
    {
        if (!nebula.push(ni, nb))
            break;
    }
    while (nebula.pop(ni, nb))
           cout << ni << ", " << nb << endl;
*/


template <typename T> void counts();    //为约束模板友元作准备
template <typename T> void report(T &);

template <typename TT>
class HasFriendT
{
private:
    TT item;
    static int ct;
public:
    HasFriendT(const TT & i) : item(i) {ct++;}
    ~HasFriendT() { ct--; }
    //1.非模板友元函数（多个函数实现类模板）
    //2.约束模板友元函数（取决于类实例化类型，类外实现加空模板<>）
    friend void counts<TT>();
    friend void report<>(HasFriendT<TT> &);        
};
template <typename T>
int HasFriendT<T>::ct = 0;

template <typename T>
void counts()
{
    cout << "template size: " << sizeof(HasFriendT<T>) << "; ";
    cout << "template counts(): " << HasFriendT<T>::ct << endl;
}

template <typename T>
void report(T & hf)
{
    cout << hf.item << endl;
}


template <typename T>
class ManyFriend
{
private:
    T item;
public:
    ManyFriend(const T & i) : item(i) {}
    //3.非约束模板友元函数（友元所有具体化都是类的每一个具体化的友元）            
    template <typename C, typename D> friend void show2(C &, D &);
};

template <typename C, typename D> void show2(C & c, D & d)
{
    cout << c.item << ", " << d.item << endl;
}

//模板别名
template<typename T>
    using arrtype = std::array<T, 12>;
//using=非模板与typedef等价
using pc = const char *;        //typedef const char * pc;
using pa = const int *(*)[10];  //typedef const int *(*pa)[10];


int main()
{
    
    Stack<std::string> st;   // 实例化模板
    char ch;
    std::string po;
    cout << "Please enter A to add, P to pop, or Q to quit.\n";
    while (cin >> ch && std::toupper(ch) != 'Q')
    {
        while (cin.get() != '\n')
            continue;
        if (!std::isalpha(ch))
        {
            cout << '\a';
            continue;
        }
        switch(ch)
        {
            case 'A':
            case 'a': cout << "Enter a PO number to add: ";
                      cin >> po;
                      if (st.isfull())
                          cout << "stack already full\n";
                      else
                          st.push(po);
                      break;
            case 'P':
            case 'p': if (st.isempty())
                          cout << "stack already empty\n";
                      else {
                          st.pop(po);
                          cout << "PO #" << po << " popped\n";
                          break;
                      }
        }
        cout << "Please enter A to add, P to pop, or Q to quit.\n";
    }
 /*
    std::srand(std::time(0)); 
    int stacksize;
    std::cin >> stacksize;
    Stack<const char *> st(stacksize); // 指针栈
    const char * in[Num] = {" 1: Hank Gilgamesh", " 2: Kiki Ishtar"};  // in basket
    const char * out[Num]; // 弹出字符串地址复制到out数组中
*/    
   
    // Array< Stack<int> > as;   //继承嵌套注意空白符，避免与>>混淆
    ArrayTP<int, 10> sums;       //隐式实例化
    ArrayTP<double, 10> aves;
    ArrayTP< ArrayTP<int,5>, 10> twodee;    //递归使用模板，等价于多维数组
    int i, j;
    for (i = 0; i < 10; i++)
    {
        sums[i] = 0;
        for (j = 0; j < 5; j++)
        {
            twodee[i][j] = (i + 1) * (j + 1);
            sums[i] += twodee[i][j];
        }
        aves[i] = (double) sums[i] / 10;
    }
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 5; j++)
        {
            cout.width(2);  //按2个字符宽度显示下一条目
            cout << twodee[i][j] << ' ';
        }
        cout << ": sum = ";
        cout.width(3);
        cout  << sums[i] << ", average = " << aves[i] << endl;
    } 

    return 0; 
}


//stack methods
template <class Type>
Stack<Type>::Stack(int ss) : stacksize(ss), top(0)  //类限定符加上模板列表
{
    items = new Type [stacksize];
}

template <class Type>
Stack<Type>::Stack(const Stack & st)
{
    stacksize = st.stacksize;
    top = st.top;
    items = new Type [stacksize];
    for (int i = 0; i < top; i++)
        items[i] = st.items[i];
}

template <class Type>
bool Stack<Type>::push(const Type & item)
{
    if (top < stacksize)
    {
        items[top++] = item;
        return true;
    }
    else
        return false;
}

template <class Type>
bool Stack<Type>::pop(Type & item)
{
    if (top > 0)
    {
        item = items[--top];
        return true;
    }
    else
        return false;
}

template <class Type>
Stack<Type> & Stack<Type>::operator=(const Stack<Type> & st)
{
    if (this == &st)
        return *this;
    delete [] items;
    stacksize = st.stacksize;
    top = st.top;
    items = new Type [stacksize];
    for (int i = 0; i < top; i++)
        items[i] = st.items[i];
    return *this; 
}

//array methods
template <class T, int n>
ArrayTP<T,n>::ArrayTP(const T & v)
{
    for (int i = 0; i < n; i++)
        ar[i] = v;  //数组大小作为类成员储存在定义中，尺寸可变
}

template <class T, int n>
T & ArrayTP<T,n>::operator[](int i)
{
    if (i < 0 || i >= n)
    {
        std::cerr << "Error in array limits: " << i << " is out of range\n";
        std::exit(EXIT_FAILURE);
    }
    return ar[i];
}

template <class T, int n>
T ArrayTP<T,n>::operator[](int i) const
{
    if (i < 0 || i >= n)
    {
        std::cerr << "Error in array limits: " << i << " is out of range\n";
        std::exit(EXIT_FAILURE);
    }
    return ar[i]; 
}
