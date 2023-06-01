
#include <iostream>
#include <cstring>
#include <vector>   // STL C++98
#include <array>    // C++11
using namespace std;

char * getname(void)//save memory func
{
    //static int id;  //静态储存(或函数外)
    char temp[80];  //temporary storage 自动储存，函数结束自动释放(LIFO)
    cin >> temp;
    char * pn = new char[strlen(temp) + 1]; //动态储存
    strcpy(pn, temp);   
    return pn;          //返回字符串副本地址
}
/* main:
    char * name;       
    name = getname();   
    cout << name << " at " << (int *) name << "\n";
    delete [] name;   //new delete 分开放置  
    ...
*/

int main()
{
  
	//指针
	int* p1, a;    //a是int
    a = 2;
    //*p1 = 10086; //未初始化指针解引用编译器默会解释为地址
    double *p2;
    cout << sizeof(p1) << sizeof(p2) <<endl;    //4 4 指针长度通常相等
	//p1 = 0xB8000000;      //error 指针不完全等于整型地址
    p1 = (int*)0xB8000000;  //valid

    //new
    int * ptr1 = new int;    //返回地址，内存耗尽返回0，此时为空指针(null pointer)
    ptr1 = &a;
    //int* ptr2 = ptr1;      //not ok
    delete ptr1;             
    //delete ptr1;           //not ok (已释放)
    int *p1 = &a;
    //delete p1;             //not allowed , new/delete成对（memory leak），不能释放声明变量的内存
    
    //指针和const
    int a = 22;             //变量自身可以修改
    const int b = 24;       //变量不能修改
    int * p1 = &a;
    //int * p2 = &b;       //invalid const地址不能赋值给常规(非const)指针
    //const **pp = &p1;    //not allowed
    const int * p3 = &a;   //指向常量的指针(*p为常量,只有一层间接关系)，不能通过指针修改值,但可以改变指针指向
    const int * p4 = &b;   //valid 
    int * const p5 = &a;   //可以通过指针修改值,但不可以改变指针指向
    const int * const p6 = &a;//即不能改变指向，也不能修改值

    //指针与数组
    int *parr = new int[3];
    parr[0] = 2;
    parr[1] = 4;
    parr[2] = 6;
    parr = parr + 1;        //根本区别
    cout << *parr << *(parr+1) << endl;             // 4 6 
    parr = parr - 1;       //pointer back
    delete [] parr;

    int arr[3] = {1, 3, 5};    //数组名指向第一个元素地址
    cout << arr << endl;       //0x61ff00   4(指向的内存块大小即首地址)    arr=&arr[0]
    cout << &arr << endl;      //0x61ff00   12(指向整个数组内存块)   int (*p)[3] = &arr    *p==arr: (*p)[0] = arr[0]
    //&arr+1表示数组后面一个12字节内存块地址;
    //获取值需要解除两次引用：**&arr = *arr = arr[0]  *(*&arr+i) = *(arr+i) = arr[i]  
    //arr = arr + 1;           //error
    cout << sizeof(parr) << sizeof(arr) << endl;    // 4 12 new指针不能获得数组字节大小
    int *parr1 = arr;
    int *parr2 = &arr[2];
    cout << (parr2 - parr1) << endl;  // 2 指针差为元素间隔

    //指针与字符串
    char name[20] = "zhang";    
    const char * pstr1 = "bird";     // "bird"实际表示字符串常量地址,禁止改变指向内容
    cout << name << pstr1 << endl;   //wang bird 
    
    char * pstr2;
    cin >> name;
    pstr2 = name;          // =复制地址
    cout << (int*)name << (int*)pstr2 << endl; //0x61fef4  0x61fef4 强转为字符串地址
    pstr2 = new char[strlen(name) + 1];
    strcpy(pstr2, name);   // strcpy()/strncpy()获得独立副本  
    cout << (int*)name << (int*)pstr2 << endl; //0x61fef4  0x10b18c8
    delete [] pstr2;

    //new动态结构（内存运行时分配而非编译时分配）
    typedef struct student
    {
        int age;
        char name[20];
    }stu;
    stu s[3] = {{18, "zhang"}, {20, "yang"}, {22, "wang"}};
    const stu *p[3] = {&s[0], &s[1],&s[2]};
    const stu **pp = p; //pp指向p第一个元素p[0]，即*pp = &s[0]
    //auto pp = p;       //C++11
    //cout << *pp->age;  //error,试图将*应用于pp->age,age不是指针
    cout << (*pp)->age << (*pp)->name << endl;  //18 zhang
    cout << (**pp).age << (**pp).name << endl;  //18 zhang
    cout << (*(pp+1))->age << (*(pp+2))->name << endl;  //20 wang

    stu * ps = new stu;
    cin.get(ps->name, 20);
    cin >> (*ps).age;
    cout << ps->age << (*ps).name << endl;
    delete ps;

    //数组替代品模板类vector,array（包含在std中）
    // C
    double a1[4] = {1.2, 2.4, 3.6, 4.8};
    a1[-2] = 20.2;    // allowed *(a1-2) = 20.2 C/C++都不检查超界错误
    cout << a1[-2] << &a1[-2] << endl;  // 20.2 0x61fed8
    // C++98 
    vector<double> a2(4);//自由储存区/堆区
    a1[-2] = .5;  
    a2[0] = 1.0/3.0;     //不能用列表初始化
    a2.at(1) = 1.0/5.0;  //at()赋值在运行期间会捕捉非法索引，运行时间更长，防止越界问题
    // C++11
    array<double, 4> a3 = {3.14, 2.72, 1.62, 1.41};  //可用列表初始化，储存在栈区
    array<double, 4> a4;
    a4 = a3;            // valid (元素个数相同)
    a3[100] = 1.4;
    
    return 0;
}

