

#include <iostream>
#include <cstring>
#include <string>
#include <ctime>
#include <climits>
#include <cctype>   //字符函数库 <ctype.h>: 
                    //isalpha(), isspace(), isdigit(), islower/upper, tolower/upper, ispunct()标点符号...
using namespace std;

int main()
{
    
    // 1.for循环
    int i;
    i + 6;  //valid but useless 表达式+分号=语句，反之不对
    for (i = 0 ; i < 5; ++i)    
        cout << i;              //多条语句没有花括号只有第一条语句会进入循环
        cout << i * i;
    for (i = 0 ; i < 5; i++){}  //后缀比前缀效率低（返回副本）
    cout << (i == 5) << endl;   //1    << 优先级高于表达式
    cout.setf(ios_base::boolalpha);   // 设置标志显示true/false,而非1/0
    cout << (i < 5) << endl;    //false
    
    int x = 2;
    {
        int y = 2;
        cout << x << y; // 2 2
        int x = 4;//new x
        cout << x;      // 4
    }
    cout << x;    // 2
    //cout << y;  //invalid 语句块中变量被释放
    
    //逗号运算符
    string word1;
    cin >> word1;
    char temp;
    int i = 5, j = 2 * i;   // j = 10   C++确保先运算前表达式
    i = 2, 4;               //逗号优先级最低(4无意义)
    j = (10, 20);           //括号优先级最高（=最右侧值）
    cout << i << j << endl; //2 20
    for (j = 0, i = word1.size() - 1; j < i; --i, ++j)   //反转字符串
    {                       
        temp = word1[i];
        word1[i] = word1[j];
        word1[j] = temp;
    }                       

    char word2[5] = "date";
    for (char ch = 'a'; strcmp(word2, "gate"); ch++)
    {
        cout << word2 << endl;
        word2[0] = ch;
    }
    int arr[3] = { 1, 2, 3 };
    for (int x : arr)       //基于范围的for循环  int x : {1 ,2 ,3}
        cout << x;  // 123
    for (int &x : arr)      //引用变量修改内容
        x = x * x;
    cout << arr[0] << arr[1] << arr[2]; //149

    //二维数组嵌套循环
    const int Cities = 2;
    const int Years = 2;
    const char * cities[Cities] =   // 指针数组(更节约内存) <==> char cities[Cities][25]...
    //const string cities[Cities] =   //可修改省略const
    {                               
        "Shenzhen",
        "Shanghai"
    };
    int maxtemps[Years][Cities] =   
    {
        {96, 100},  
        {96, 98}
    };
    for (int city = 0; city < Cities; ++city)
    {
        cout << cities[city] << ":\t";
        for (int year = 0; year < Years; ++year)
            cout << maxtemps[year][city] << "\t";
        cout << endl;
    }


    // 2.while循环
    int a = 1,b = 0;
    while (a++ < 2)
        cout << a << endl;  //2
    b = (2 + a++) + (2 + a++);  //避免非完整表达式中自增/减（无法保证）
    cout << a << b << endl; //5？ 11

    float secs;
    cin >> secs;
    clock_t delay = secs * CLOCKS_PER_SEC;  // CLOCKS_PER_SEC:每秒包含的系统时间单位数
    clock_t start = clock();
    while (clock() - start < delay);        
    
    char ch1;
    int count = 0;
    cin.get(ch1);        
    while (cin.fail() == false) //返回bool值达到EOF 
    {
        cout << ch1;
        ++count;
        cin.get(ch1);   
    }
    //可用以下代替//
    int ch2;
    ch2 = cin.get();    //转整型
    while(ch2 != EOF)   //返回EOF值达到EOF while ((ch2 = cin.get()) != EOF) 
    //while (cin.fail() == false)  
    //while (!cin.fail())  
    {
        cout.put(ch2);
        ++count;
        ch2 = cin.get();
    }


    // 3.if与逻辑运算符
    
    //and, or, not（优先级: ! >  &&  > ||）
    int i = 9, j = 10;
    cout << ((i < 10)? !i ? j : i : -1) << endl;    //9 嵌套三目运算符，可读性差

    if (1 < i < 2)            //前部分结果为真或假（0/1）,总小于2
        cout << "true forever\n";
    
    if (i++ > 5 || j++ < 15)  //第一个表达式为true后不会去判断后面的表达式
        cout << "i = " << i << "\t" << "j = " << j << endl;    // i = 10    j = 10
    
    if (!(i <= INT_MAX && i >= INT_MIN))  // C++确保从左往右计算逻辑表达式
        cout << "Out of range of integer\n";
    else
        cout << "it's an integer\n";
    
    //while循环测试或switch比较int和枚举量标签时，会将枚举量提升为int
    enum {red, yellow, blue};
    int code;
    cin >> code;
    while (code >= red && code <= blue)
    {
        switch (code)
        {
            case red     : cout << "red\n"; break;  //标签值必须是常量整数
            case yellow  : cout << "yellow\n"; break;
            case blue    : cout << "blue\n"; break;
        }
        cin >> code;
    }
    
    return 0;
}





