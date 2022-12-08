

#include <iostream>
#include <cmath>
#include <new>
#include <string>
using namespace std;

// cv�޶�����const volatile(���߱�������ֵ�������벻���仯����Ҫ���������Ż�)
// mutuable ��Ա��const �Ľṹ�塢��ĳ�ԱҲ���Ա��޸�

// �ⲿ�����Ա���/����/ָ�� ��extern��
int Global = 2 * sizeof(long);		// 8
const char const* str = "hahaha";
int* parr = new int[5]{ 1 ,2 ,3 , 4, 5 };  //delete [] parr; ֻ�����ڶѿռ�
// extern "C" void fun(int);    //Ĭ��C++

// �ڲ�������
static double Pi = 4.0 * atan(1.0);	//��̬����ԭ�ͺͶ��嶼��Ҫ static �ؼ���

void strcount(const char* str)
{
    static int total = 0;        //���ʼ���ģ���̬��ʼ�������������ڴ���
    int count = 0;
    while (*str++)
        count++;
    total += count;
}

//���ƿռ�
// namespace MEF = myth::elements::fire; //Ƕ�׿ռ�ȡ����
// δ������Ϊ�ڲ������Եľ�̬���������Ʒ  namespace {int count;}  == statict int count;
// ��ѡ��������������::��using������������using����ָ���ѡ�ֲ����ö���ȫ������
int count = 0;
namespace first_space1 {	// ��һ�������ռ�
    int count = 1;
    void func() {
        cout << "Inside first_space1" << endl;
    }
    namespace first_space2 {	// Ƕ�� 
        void func() {
            cout << "Inside first_space2" << endl;
        }
    }
}

namespace second_space {	// �ڶ��������ռ�
    int count = 2;
    void func() {
        cout << "Inside second_space" << endl;
    }
}


int main()
{
    register int count_fast;	//before C++11 ���������ʹ��CPU�Ĵ��������Զ�����(�������ԣ���߷��ʱ������ٶ�)
    //static int count;			

    // 1.using����
    using first_space1::count;    
    using second_space::count;
    //cout << count << endl;  // ���ƿռ��Աͬ��ѡ������
    
    // 2.using����ָ��
    using namespace first_space1;   
    int count = 3;  // �ֲ�����������ͬ����������
    std::cout << ::count << first_space1::count << count << std::endl; // 0 1 3   ::����������ȫ�ֱ�����ֲ�����
    func();         // Inside first_space1

    namespace F12 = first_space1::first_space2; //����
    using namespace F12;
    F12::func();    // Inside first_space2
    
    // 3.�����ֱ�ӷ���
    second_space::func();          

    return 0;
}