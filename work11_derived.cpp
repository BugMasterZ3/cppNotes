

#include <iostream>
#include <string>
using namespace std;


// 基类
class TableTennisPlayer
{
private:
    string firstname;
    string lastname;
    bool hasTable;
public:
    //TableTennisPlayer(TableTennisPlayer&);  //可以使用基类或派生类(隐式重载赋值运算符)对象初始化
    TableTennisPlayer(const string& fn = "none", const string& ln = "none", bool ht = false);
    void Name() const;
    bool HasTable() const { return hasTable; };
    void ResetTable(bool v) { hasTable = v; };
};
// 派生类
class RatedPlayer : public TableTennisPlayer
{
private:
    unsigned int rating;
public:
    RatedPlayer(unsigned int r = 0, const string& fn = "none", const string& ln = "none", bool ht = false);
    RatedPlayer(unsigned int r, const TableTennisPlayer& tp);
    unsigned int Rating() const { return rating; }  //派生类新特性
    void ResetRating(unsigned int r) { rating = r; }
};

void show(const TableTennisPlayer&) {}  //函数形参为基类引用/指针，实参可以使用基类或派生类对象地址

TableTennisPlayer::TableTennisPlayer(const string& fn, const string& ln, bool ht)
    : firstname(fn), lastname(ln), hasTable(ht) {}

void TableTennisPlayer::Name() const
{
    std::cout << lastname << ", " << firstname;
}

//派生类不能直接访问基类私有成员，只能通过基类方法访问和设置
RatedPlayer::RatedPlayer(unsigned int r, const string& fn, const string& ln, bool ht)
    : TableTennisPlayer(fn, ln, ht) //显式调用基类构造函数（否则按基类默认/隐式构造函数，释放顺序相反）
{
    rating = r;
}

RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer& tp)
    : TableTennisPlayer(tp), rating(r)
{
}

/*
1.public 继承：		基类public，protected，private->派生类public, protected, private
2.protected 继承：	基类public，protected，private->派生类protected, protected, private
3.private 继承：	基类public，protected，private->派生类private, private, private
*/
// Abstract Base Class 抽象基类(ABC,共性,纯虚函数)
/********/
const int CLIENTS = 4;
// Brass Account Class
class Brass
{
protected: //派生类可以访问基类保护成员（与私有成员的区别）
private:
    std::string fullName;
    long acctNum;
    double balance;
public:
    Brass(const std::string& s = "Nullbody", long an = -1, double bal = 0.0);// 构造/友元函数不能为虚（不同于继承机制）
    double Balance() const;
    void Deposit(double amt);
    virtual void Withdraw(double amt);  //virtual根据引用/指向的对象类型选择方法，非virtual会根据引用/指针类型选择方法
    virtual void ViewAcct() const;      //基类中声明virtual后派生类自动成为虚方法（虚函数表地址vtbl）
    virtual ~Brass() {}                 //虚析构函数（调用对象析构函数，然后自动调用基类析构函数）
};
//Brass Plus Account Class
class BrassPlus : public Brass
{
private:
    double maxLoan;
    double rate;
    double owesBank;
public:
    BrassPlus(const std::string& s = "Nullbody", long an = -1, double bal = 0.0, double ml = 500, double r = 0.11125);
    BrassPlus(const Brass& ba, double ml = 500, double r = 0.11125);//派生类构造函数将使用一个基类构造函数
    virtual void ViewAcct()const;        //多态（基类被重载，派生类应重新定义所有基类版本）
    //virtual BrassPlus* ViewAcct()const;//重新定义应确保和基类原型完全相同（返回类型是基类指针/引用可以修改为派生类）
    //virtual void ViewAcct(int a)const; //派生类重载方法不会生成两个重载版本，而是会隐藏基类版本
    virtual void Withdraw(double amt);
    void ResetMax(double m) { maxLoan = m; }
    void ResetRate(double r) { rate = r; };
    void ResetOwes() { owesBank = 0; }
};


int main()
{
    using std::cin;
    using std::cout;
    using std::endl;

    TableTennisPlayer player1("Tara", "Boomdea", false);
    RatedPlayer rplayer1(1140, "Mallory", "Duck", true);
    cout << "Name: ";
    rplayer1.Name();          // 调用基类方法
    if (rplayer1.HasTable())
        cout << ": has a table.\n";
    else
        cout << ": hasn't a table.\n";
    cout << "Rating: " << rplayer1.Rating() << endl;    //新特性
    TableTennisPlayer* pt = &rplayer1; //ok 隐式向上强制转换，基类可以引用/指针指向派生类对象(单向不可逆，向下转换必须显式)
    pt->Name();   // Duck, Mallory


    Brass Piggy("Porcelot Pigg", 381299, 4000.00);
    BrassPlus Hoggy("Horatio Hogg", 382288, 3000.00);
    Piggy.ViewAcct();
    cout << endl;
    Hoggy.ViewAcct();
    cout << endl;
    Hoggy.Deposit(1000.00);
    cout << Hoggy.Balance() << endl; //4000
    Piggy.Withdraw(4200.00);
    cout << Piggy.Balance() << endl; //...Withdrawal canceled. 4000
    Hoggy.Withdraw(4200.00);
    Hoggy.ViewAcct();       // ...Owed to bank: $222.25    Loan Rate: 11.125%...

    Brass* p_clients[CLIENTS];  //一个（指针）数组保存多个不同类型对象
    std::string temp;
    long tempnum;
    double tempbal;
    char kind;
    for (int i = 0; i < CLIENTS; i++)
    {
        cout << "Enter client's name: ";
        getline(cin, temp);
        cout << "Enter client's account number: ";
        cin >> tempnum;
        cout << "Enter opening balance: $";
        cin >> tempbal;
        cout << "Enter 1 for Brass Account or " << "2 for BrassPlus Account: ";
        while (cin >> kind && (kind != '1' && kind != '2'))
            cout << "Enter either 1 or 2: ";
        if (kind == '1')
            p_clients[i] = new Brass(temp, tempnum, tempbal);
        else
        {
            double tmax, trate;
            cout << "Enter the overdraft limit: $";
            cin >> tmax;
            cout << "Enter the interest rate " << "as a decimal fraction: ";
            cin >> trate;
            p_clients[i] = new BrassPlus(temp, tempnum, tempbal, tmax, trate);
        }
        while (cin.get() != '\n')
            continue;
    }
    cout << endl;
    for (int i = 0; i < CLIENTS; i++)
    {
        p_clients[i]->ViewAcct();   //多态性，动态联编
        cout << endl;               //编译器对非虚方法使用静态联编，效率更高
    }
    for (int i = 0; i < CLIENTS; i++)
    {
        delete p_clients[i];  // free memory
    }


    return 0;
}


// formatting stuff
typedef std::ios_base::fmtflags format;
typedef std::streamsize precis;

format setFormat()
{
    // set up ###.## format
    return cout.setf(std::ios_base::fixed, std::ios_base::floatfield);  //定点表示法
}

void restore(format f, precis p)    //重置格式和精度
{
    cout.setf(f, std::ios_base::floatfield);
    cout.precision(p);
}

// Brass methods
Brass::Brass(const string& s, long an, double bal)
{
    fullName = s;
    acctNum = an;
    balance = bal;
}

void Brass::Deposit(double amt)
{
    if (amt < 0)
        cout << "Negative deposit not allowed; " << "deposit is cancelled.\n";
    else
        balance += amt;
}

void Brass::Withdraw(double amt)
{
    // set up ###.## format
    format initialState = setFormat();
    precis prec = cout.precision(2);

    if (amt < 0)
        cout << "Withdrawal amount must be positive; " << "withdrawal canceled.\n";
    else if (amt <= balance)
        balance -= amt;
    else
        cout << "Withdrawal amount of $" << amt << " exceeds your balance.\n" << "Withdrawal canceled.\n";
    restore(initialState, prec);
}
double Brass::Balance() const
{
    return balance;
}

void Brass::ViewAcct() const
{
    // set up ###.## format
    format initialState = setFormat();
    precis prec = cout.precision(2);
    cout << "Client: " << fullName << endl;
    cout << "Account Number: " << acctNum << endl;
    cout << "Balance: $" << balance << endl;
    restore(initialState, prec); // Restore original format
}

// BrassPlus Methods
BrassPlus::BrassPlus(const string& s, long an, double bal, double ml, double r)
    : Brass(s, an, bal)
{
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

BrassPlus::BrassPlus(const Brass& ba, double ml, double r)
    : Brass(ba)   // uses implicit copy constructor
{
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

// redefine how ViewAcct() works
void BrassPlus::ViewAcct() const
{
    // set up ###.## format
    format initialState = setFormat();
    precis prec = cout.precision(2);

    Brass::ViewAcct();   // display base portion 不加作用域解析运算符会陷入无限递归
    cout << "Maximum loan: $" << maxLoan << endl;
    cout << "Owed to bank: $" << owesBank << endl;
    cout.precision(3);  // ###.### format
    cout << "Loan Rate: " << 100 * rate << "%\n";
    restore(initialState, prec);
}

// redefine how Withdraw() works
void BrassPlus::Withdraw(double amt)
{
    // set up ###.## format
    format initialState = setFormat();
    precis prec = cout.precision(2);

    double bal = Balance();
    if (amt <= bal)
        Brass::Withdraw(amt);
    else if (amt <= bal + maxLoan - owesBank)
    {
        double advance = amt - bal;
        owesBank += advance * (1.0 + rate);
        //maxLoan -= advance;
        cout << "Bank advance: $" << advance << endl;
        cout << "Finance charge: $" << advance * rate << endl;
        Deposit(advance);
        Brass::Withdraw(amt);
    }
    else
        cout << "Credit limit exceeded. Transaction cancelled.\n";
    restore(initialState, prec);
}
