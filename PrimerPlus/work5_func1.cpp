

/****重难点:函数指针****/

#include <iostream>
#include <string>
#include <cmath>
#include <array>
using namespace std;

// 1.声明定义
//void print(...);       //C++函数原型必不可少，不指定参数列表应使用省略号
void cheers(int);        //声明时形参名可以省略
double cube(double num); //声明与定义参数名可以不一样，修改形参不影响实参 

// 2.arr_fun
const int ArSize = 8;
int sum_arr(const int arr[], int n);   //数组表示法(指向第一个元素地址，禁止将const地址赋值给非const指针）
//int sum_arr(const int *arr, int n);  //&arr[i]==arr+i; arr[i]==*(arr+i)
int sum_range(const int * begin, const int * end);  //指定区间(双指针)
int sum_arr2(const int arr[][4], int size);      //4列的二维数组, size为行数
//int sum_arr2(const int (*arr)[4], int size);   //arr[r][c] = *(*(arr+r)+c)

// 3.str_fun
unsigned int c_in_str(const char * str, char ch);   //统计字符串某个字符个数
//unsigned int c_in_str(const char str[], char ch);   
char * buildstr(char c, int n);     // 返回字符串指针

// 4.struct_fun
const int Mins_per_hr = 60;
struct travel_time  // 时间
{
    int hours;
    int mins;
};
travel_time sum_time(travel_time t1, travel_time t2);
void show_time(travel_time t);

struct polar        // 空间
{
    double distance;      // distance 
    double angle;         // direction 
};
struct rect
{
    double x;             
    double y; 
};
void rect_to_polar(const rect * pxy, polar * pda);   //直角坐标转极坐标 
void show_polar(const polar * pda);

// 5.string_fun
const int SIZE = 5;
void show_string(const string sa[], int n);

// 6.array_fun 
const int Seasons = 4;
const std::array<std::string, Seasons> Snames = {"Spring", "Summer", "Fall", "Winter"};//可以储存类对象
void fill(std::array<double, Seasons> * pa);
void show_array(std::array<double, Seasons> da);

// 7.递归
void countdown(int n)
{
    using namespace std;
    cout << "Counting" << n << "..." << &n << endl; //n n-1 ... 2 1 0
    if (n > 0)          //递归结束条件
        countdown(n-1);    
    cout << n << ":hello!" << "..." << &n << endl; //0 1 2 ... n-1 n  相同层级 &n 地址相同
} 

const int Len = 66; //2^6+2
const int Divs = 6;
void subdivide(char ar[], int low, int high, int level)
{
    if (level == 0)
        return;
    int mid = (high + low) / 2;
    ar[mid] = '|';
    subdivide(ar, low, mid, level - 1);
    subdivide(ar, mid, high, level - 1); 
}

// 8.函数指针
double func1(int);
double func2(int);
void estimate(int lines, double (*pf)(int)) //指向函数的指针,函数名即函数地址
{
    cout << lines << " lines will take " << (*pf)(lines) << " hour(s)\n";   //调用函数(或直接 pf(lines) )
}
// *p[n]   一个包含三个指针的数组(数组名p是指向指针/函数的指针)
// (*p)[n] 一个指向包含n个元素的数组的指针
const double * f1(const double ar[], int n);    //三个函数分别返回数组三个元素的指针/地址
const double * f2(const double [], int);
const double * f3(const double *, int);


int main()
{
    // 1
    cheers(cube(2));    // 自动转换类型(算术类型)：2->2.0, 8.0->8

    // 2.arr
    const int cookies[ArSize] = {1,2,4,8,16,32,64,128};
    std::cout << cookies << endl;           // 0x61feec
    std::cout << sizeof(cookies) <<  endl;  // 32
    int sum = sum_arr(cookies, ArSize);     // 0x61feec 4 255
    sum = sum_arr(cookies, 4);              // 0x61feec 4 15
    sum = sum_arr(cookies + 4, 4);          // 0x61fefc 4 240 第五个元素地址
    sum = sum_range(cookies, cookies + ArSize);   // 255
    sum = sum_range(cookies, cookies + 4);        // 15
    sum = sum_range(cookies + 4, cookies + 8);    // 240

    // 3.str
    char *ps = buildstr('w', 3);
    cout << ps << endl;
    delete [] ps;                   // free memory
    
    // 4.struct
    //时间
    travel_time day1 = {5, 45};    
    travel_time day2 = {4, 55};    
    show_time(sum_time(day1, day2));    // 10 hours, 40 minutes
    //空间
    rect rplace;
    polar pplace;
    while (cin >> rplace.x >> rplace.y)  // 返回istream对象cin
    {
        rect_to_polar(&rplace, &pplace);
        show_polar(&pplace);
    }
    
    // 5.string
    string list[SIZE];    
    for (int i = 0; i < SIZE; i++)  //输入
    {
        cout << i + 1 << ": ";
        getline(cin,list[i]);
    }
    show_string(list, SIZE);    //显示
   
    // 6.array
    std::array<double, 4> expenses;
    fill(&expenses);
    show_array(expenses);
    
    // 7.recursive function
    countdown(4);           

    char ruler[Len];
    ruler[Len - 1] = '\0';
    int max = Len - 2;
    int min = 0;
    ruler[min] = ruler[max] = '|';
    int i;
    for (i = 1; i < Len - 2; i++)
        ruler[i] = ' ';
    std::cout << ruler << std::endl;
    for (i = 1; i <= Divs; i++)
    {
        subdivide(ruler,min,max, i);
        std::cout << ruler << std::endl;
        for (int j = 1; j < Len - 2; j++)
            ruler[j] = ' ';  // reset to blank ruler
    }
    
    // 8.函数指针
    estimate(100, func1);   //100 lines will take 5 hour(s)
    estimate(100, func2);   //100 lines will take 7 hour(s)
  
    double av[3] = {1.3, 1.6, 2.9};
    const double *(*p1)(const double *, int) = f1;  //指向函数的指针 
    auto p2 = f2;  // 自动类型推断功能代替 
    typedef const double *(*p_fun)(const double *, int);    //取别名简化
    p_fun p3 = f3;  
    cout << "Address  Value\n"; //分别获取地址和值
    cout <<  (*p1)(av,3) << ": " << *(*p1)(av,3) << endl; // 调用函数(*pf)() = pf()
    cout << p2(av,3) << ": " << *p2(av,3) << endl;
    cout << p3(av,3) << ": " << *p3(av,3) << endl;
   
    const double *(*pa[3])(const double *, int) = {f1,f2,f3};   // 指针(函数)数组,不能使用auto
    cout << "Address  Value\n";
    for (int i = 0; i < 3; i++)     //使用指针数组
        cout << pa[i](av,3) << ": " << *pa[i](av,3) << endl;
    // auto不适用于列表初始化，但它适用于初始化为单个值
    // const double *(**pb)(const double *, int) = pa;
    auto pb = pa;   //指向pa的第一个元素(指向指针的指针)  
    cout << "Address  Value\n";
    for (int i = 0; i < 3; i++)     //使用指向指针的指针
        cout << pb[i](av,3) << ": " << *pb[i](av,3) << endl;
    // const double *(*(*pc)[3])(const double *, int) = &pa;
    auto pc = &pa;  //指向整个pa指针数组 
    const double *(*(*pd)[3])(const double *, int) = &pa;   
    const double * pdb = (*pd)[2](av,3);  // 调用pd保存第三个函数
    cout << "Address  Value\n";
    cout << (*pc)[0](av,3) << ": " << *(*pc)[0](av,3) << endl;
    cout << (*(*pd)[1])(av,3) << ": " << *(*(*pd)[1])(av,3) << endl;
    cout << pdb << ": " << *pdb << endl;
     
    return 0;
}


void cheers(int n)
{
    for (int i = 0; i < n; i++)
        cout << "Cheers!" << endl;
}

double cube(double x)
{
    return x * x * x; 
}

int sum_arr(const int arr[], int n)
{
    int total = 0;
    
    std::cout << arr << endl;            // 传入的地址
    std::cout << sizeof(arr) << endl;    // 4 不能获取原始数组长度 

    for (int i = 0; i < n; i++)
        total = total + arr[i];
    return total; 
}

int sum_range(const int * begin, const int * end)
{
    const int * pt;
    int total = 0;

    for (pt = begin; pt != end; pt++)
        total = total + *pt;
    return total; 
}

unsigned int c_in_str(const char * str, char ch)
{
    unsigned int count = 0;

    while (*str)        // quit when *str is '\0'
    {
        if (*str == ch)
            count++;
        str++;       
    }
    return count; 
}

char * buildstr(char c, int n)     
{
    char * pstr = new char[n + 1];
    pstr[n] = '\0';         // terminate string
    while (n-- > 0)
        pstr[n] = c;        
    return pstr; 
}

travel_time sum_time(travel_time t1, travel_time t2)
{
    travel_time total;
    total.mins = (t1.mins + t2.mins) % Mins_per_hr;     //分钟的处理
    total.hours = t1.hours + t2.hours + (t1.mins + t2.mins) / Mins_per_hr;
    return total;
}

void show_time(travel_time t)
{
    cout << t.hours << " hours, " << t.mins << " minutes\n";
}

void rect_to_polar(const rect * pxy, polar * pda)
{
    pda->distance = sqrt(pxy->x * pxy->x + pxy->y * pxy->y);
    pda->angle = atan2(pxy->y, pxy->x);   //弧度值
}


void show_polar (const polar * pda)
{
    const double pi = acos(-1.0);
    const double Rad_to_deg = 180 / pi;  //弧度值转角度值
    cout << "distance = " << pda->distance << ", angle = " << pda->angle * Rad_to_deg << endl;
}

void show_string(const string sa[], int n)
{
    for (int i = 0; i < n; i++)
        cout << i + 1 << ": " << sa[i] << endl;
}

void fill(std::array<double, Seasons> * pa)
{
    for (int i = 0; i < Seasons; i++)
    {
        std::cout << "Enter " << Snames[i] << " expenses: ";
        std::cin >> (*pa)[i];
    }
}

void show_array(std::array<double, Seasons> da)
{
    double total = 0.0;
    std::cout << "\nEXPENSES\n";
    for (int i = 0; i < Seasons; i++)
    {
        std::cout << Snames[i] << ": $" << da[i] << '\n';
        total += da[i];
    }
    std::cout << "Total: $" << total << '\n';
}

double func1(int lns)
{
    return 0.05 * lns;
}

double func2(int lns)
{
    return 0.03 * lns + 0.0004 * lns * lns;
}

const double * f1(const double * ar, int n)
{
    return ar;
}
const double * f2(const double ar[], int n)
{
    return ar+1;
}
const double * f3(const double ar[], int n)
{
    return ar+2;
}
