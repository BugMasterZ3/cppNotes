

#include <iostream>
#include <cmath>
#include <new>
#include <string>
using namespace std;

// cv限定符：const volatile(告诉编译器其值可能意想不到变化，不要进行这种优化)
// mutuable 成员：const 的结构体、类的成员也可以被修改

// 外部链接性变量/函数/指针 （extern）
int Global = 2 * sizeof(long);		// 8
const char const* str = "hahaha";
int* parr = new int[5]{ 1 ,2 ,3 , 4, 5 };  //delete [] parr; 只能用于堆空间
// extern "C" void fun(int);    //默认C++

// 内部链接性
static double Pi = 4.0 * atan(1.0);	//静态函数原型和定义都需要 static 关键字

void strcount(const char* str)
{
    static int total = 0;        //零初始化的（静态初始化），被留在内存中
    int count = 0;
    while (*str++)
        count++;
    total += count;
}

//名称空间
// namespace MEF = myth::elements::fire; //嵌套空间取别名
// 未命名即为内部链接性的静态变量的替代品  namespace {int count;}  == statict int count;
// 首选作用域解析运算符::的using声明方法而非using编译指令；首选局部设置而非全局设置
int count = 0;
namespace first_space1 {	// 第一个命名空间
    int count = 1;
    void func() {
        cout << "Inside first_space1" << endl;
    }
    namespace first_space2 {	// 嵌套 
        void func() {
            cout << "Inside first_space2" << endl;
        }
    }
}

namespace second_space {	// 第二个命名空间
    int count = 2;
    void func() {
        cout << "Inside second_space" << endl;
    }
}


int main()
{
    register int count_fast;	//before C++11 建议编译器使用CPU寄存器储存自动变量(无链接性，提高访问变量的速度)
    //static int count;			

    // 1.using声明
    using first_space1::count;    
    using second_space::count;
    //cout << count << endl;  // 名称空间成员同名选择问题
    
    // 2.using编译指令
    using namespace first_space1;   
    int count = 3;  // 局部变量与名称同名覆盖问题
    std::cout << ::count << first_space1::count << count << std::endl; // 0 1 3   ::区别重名的全局变量与局部变量
    func();         // Inside first_space1

    namespace F12 = first_space1::first_space2; //别名
    using namespace F12;
    F12::func();    // Inside first_space2
    
    // 3.运算符直接访问
    second_space::func();          

    return 0;
}