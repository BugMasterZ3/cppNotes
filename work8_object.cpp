

#include <iostream>
#include <cctype>
using namespace std;

const int STKS = 5;
class Stock
{
private:    //默认私有
    std::string company;
    long shares;    //m_shares shares_
    double share_val;
    double total_val;
    void set_tot() { total_val = shares * share_val; }
    static const int Months = 12;   // 对象共享  
    double costs[Months];
public:
    Stock();        // 默认构造函数或设置默认值参数
    Stock(const std::string& co, long n = 0, double pr = 0.0);  //带参构造，shares,share_val默认0
    ~Stock();       // delete new对象  
    void buy(long num, double price);   //成员函数可以访问私有成员和方法
    void sell(long num, double price);
    void update(double price);
    void show() const;  //const确保对象不被修改 void show(const Stock* this);
    const Stock& topval(const Stock& s) const;  // *this
};


typedef unsigned long Item;
class Stack
{
private:
    enum { MAX = 10 };  // 对象未创建不拥有此枚举  C++新枚举enum class防止同作用域名称冲突
    Item items[MAX];    // holds stack items
    int top;            // index for top stack item
public:
    Stack();
    bool isempty() const;
    bool isfull() const;
    bool push(const Item& item);
    bool pop(Item& item);
};


int main()
{
    //默认构造函数（无参或将参数全部设置默认值）
    //Stock s1;	
    //Stock s1{};

    //带参构造函数初始化
    Stock stock1("NanoSmart", 12, 20.0);
    Stock stock2 = Stock("Boffo Objects", 2, 2.0);
    //Stock *pstock = new Stock("NanoSmart", 12, 20.0);    //对象指针
    stock1.show();
    stock2.show();
    stock2 = stock1;    //复制
    stock1.show();
    stock2.show();
    stock1 = Stock("Nifty Foods", 10, 50.0);  //新的临时对象（非初始化）
    stock1.show();
    //列表初始化C++11（与构造函数保持一致）
    //Stock stock1{ "NanoSmart"};            
    //Stock stock1 = { "NanoSmart", 12, 20.0 }; //一个参数直接S s1 = *;  
    const Stock stock3{ "Tencent" };
    stock3.show();

    //对象数组
    Stock stocks[STKS] = {
            Stock(),                    //不同构造函数初始化，未初始化默认构造函数初始化
            Stock("NanoSmart", 12, 20.0),
            Stock("Fleep Enterprises", 60, 6.5)
    };
    int st;
    for (st = 0; st < STKS; st++)
        stocks[st].show();
    // set pointer to first element
    const Stock* top = &stocks[0];
    for (st = 1; st < STKS; st++)
        top = &top->topval(stocks[st]);
    top->show();    // Company: Fleep Enterprises  Shares: 60  Share Price: $6.500  Total Worth: $390.00


    //模拟栈
    Stack st; // create an empty stack
    char ch;
    unsigned long po;
    cout << "Please enter A to add a purchase order,\n"
        << "P to process a PO, or Q to quit.\n";
    while (cin >> ch && toupper(ch) != 'Q')
    {
        while (cin.get() != '\n')
            continue;
        if (!isalpha(ch))
        {
            cout << '\a';
            continue;
        }
        switch (ch)
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
        case 'p':
            if (st.isempty())
                cout << "stack already empty\n";
            else
            {
                st.pop(po);
                cout << "PO #" << po << " popped\n";
            }
            break;
        }
        cout << "Please enter A to add a purchase order,\n"
            << "P to process a PO, or Q to quit.\n";
    }

    return 0;
}


Stock::Stock()
{
    std::cout << "Default constructor called\n";
    company = "no name";
    shares = 0;
    share_val = 0.0;
    total_val = 0.0;
}

Stock::Stock(const std::string& co, long n, double pr)
{
    std::cout << "Constructor using " << co << " called\n";
    company = co;

    if (n < 0)
    {
        std::cout << "Number of shares can't be negative; " << company << " shares set to 0.\n";
        shares = 0;
    }
    else
        shares = n;
    share_val = pr;
    set_tot();
}

Stock::~Stock()
{
    std::cout << "Bye, " << company << "!\n";
}


void Stock::buy(long num, double price)
{
    if (num < 0)
    {
        std::cout << "Number of shares purchased can't be negative. " << "Transaction is aborted.\n";
    }
    else
    {
        shares += num;
        share_val = price;
        set_tot();
    }
}

void Stock::sell(long num, double price)
{
    using std::cout;
    if (num < 0)
    {
        cout << "Number of shares sold can't be negative. " << "Transaction is aborted.\n";
    }
    else if (num > shares)
    {
        cout << "You can't sell more than you have! " << "Transaction is aborted.\n";
    }
    else
    {
        shares -= num;
        share_val = price;
        set_tot();
    }
}

void Stock::update(double price)
{
    share_val = price;
    set_tot();
}

void Stock::show() const
{
    using std::cout;
    using std::ios_base;
    // set format to #.###
    ios_base::fmtflags orig = cout.setf(ios_base::fixed, ios_base::floatfield);
    std::streamsize prec = cout.precision(3);

    cout << "Company: " << company << "  Shares: " << shares;
    cout << "  Share Price: $" << share_val;
    // set format to #.##
    cout.precision(2);
    cout << "  Total Worth: $" << total_val << '\n';
    // restore original format
    cout.setf(orig, ios_base::floatfield);
    cout.precision(prec);
}

const Stock& Stock::topval(const Stock& s) const
{
    if (s.total_val > total_val)
        return s;
    else
        return *this;
}

//栈
Stack::Stack()    // create an empty stack
{
    top = 0;
}

bool Stack::isempty() const
{
    return top == 0;
}

bool Stack::isfull() const
{
    return top == MAX;
}

bool Stack::push(const Item& item)
{
    if (top < MAX)
    {
        items[top++] = item;
        return true;
    }
    else
        return false;
}

bool Stack::pop(Item& item)
{
    if (top > 0)
    {
        item = items[--top];
        return true;
    }
    else
        return false;
}
