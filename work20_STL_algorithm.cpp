
#include <iostream>
#include <vector>
#include <algorithm>	//比较、交换、查找、遍历操作、复制、修改等等
#include <functional>	//模板类，用以声明内建函数对象
#include <numeric>		//简单数据运算的模板函数:accumulate,fill
using namespace std;


//STL函数对象
//函数对象(仿函数)是类不是函数
class MyAdd
{
public:
	int operator()(int v1, int v2)
	{
		return v1 + v2;
	}
};
//MyAdd myadd;
//cout << myadd(10, 10) << endl;
class MyPrint
{
public:
	MyPrint()
	{
		this->count = 0;
	}
	void operator()(string test)
	{
		cout << test << endl; 
		this->count++;	
	}
	int count;//内部自己状态
};
void doPrint(MyPrint& mp, string test)
{
	mp(test);
}
//MyPrint myprint;
//myprint("hello world");
//cout << "MyPrint调用次数为:" << myprint.count << endl;
//doPrint(myprint, "hello c++");

//谓词(返回bool类型的仿函数)
class Greater5	
{
public:
	bool operator()(int val) //一元谓词(一个参数)
	{
		return val > 5;
	}
};
class AgeGreater20
{
public:
	bool operator()(Person &p)
	{
		return p.m_Age > 20;
	}
};
class MyCompare
{
public:
	bool operator()(int val1,int val2)	//二元谓词
	{
		return val1 > val2;
	}
};
//sort(v.begin(), v.end(),MyCompare());	//改变为降序

//内建函数对象(#include<functional>)
//1.算数仿函数:
//plus, minus, mutiplies, divides, modulus取模, negate取反 
plus<int>p;	//默认认定传的是同种数据类型
cout << p(10, 20) << endl;

//2.关系仿函数
//equal_to, not_equal_to, greater, greater_equal, less, less_equal
sort(v.begin(),v.end(), MyCompare());
sort(v.begin(),v.end(), greater<int>());

//3.逻辑仿函数
//logical_and, logical_or, logical_not
vector<bool>v1;
vector<bool>v2;
v2.resize(v1.size());	//利用逻辑非将容器v1搬运到容器v2中，并执行取反操作
transform(v1.begin(), v1.end(), v2.begin(),logical_not<bool>());//()代表对象的创建


//普通函数
void Print(int val) { cout << val << " "; }

//仿函数
class MyPrint
{
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};

class TransForm
{
public:
	int operator()(int val)
	{
		return val + 100;
	}
};

const int LIM = 6;
void Show(double v)
{
	std::cout.width(6);
	std::cout << v << ' ';
}


class Person
{
public:
	Person(string name,int age)
	{
		this->m_Age = age;
		this->m_Name = name;
	}
	//重载==
	bool operator ==(const Person& p)
	{
		if (this->m_Age == p.m_Age && this->m_Name == p.m_Name)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	string m_Name;
	string m_Age;
};

template<class T>  // functor class defines operator()()
class TooBig
{
private:
	T cutoff;
public:
	TooBig(const T& t) : cutoff(t) {}
	bool operator()(const T& v) { return v > cutoff; }
};

void outint(int n) { std::cout << n << " "; }


int main(void)
{
	
	//遍历搬运 
	vector<int>v;
	for_each(v.begin(), v.end(),MyPrint());	// or Print
	vector<int>vTarget;			//目标容器
	vTarget.resize(v.size());	//目标容器需要提前开辟空间
	transform(v.begin(), v.end(), vTarget.begin(), TransForm());	
	for_each(vTarget.begin(), vTarget.end(), MyPrint());
	
	double arr1[LIM] = { 28, 29, 30, 35, 38, 59 };
	double arr2[LIM] = { 63, 65, 69, 75, 80, 99 };
	vector<double> gr8(arr1, arr1 + LIM);
	vector<double> m8(arr2, arr2 + LIM);
	cout.setf(ios_base::fixed);
	cout.precision(1);
	vector<double> sum(LIM);
	transform(gr8.begin(), gr8.end(), m8.begin(), sum.begin(), plus<double>()); //两个函数参数
	for_each(sum.begin(), sum.end(), Show); // 91.0 94.0 99.0 110.0 118.0 158.0
	vector<double> prod(LIM);
	transform(gr8.begin(), gr8.end(), prod.begin(), bind1st(multiplies<double>(), 2.5));// bind2st
	for_each(prod.begin(), prod.end(), Show);// 70.0 72.5 75.0 87.5 95.0 147.5


	//查找统计 
	vector<int>::iterator it = find(v.begin(), v.end(), 5);	//内置(返回值迭代器)
	vector<int>::iterator it = find_if(v.begin(), v.end(), Greater5());
	vector<Person>::iterator it = find(V.begin(), V.end(), p1);	////自定义数据类型
	vector<Person>::iterator it = find_if(V.begin(), V.end(), AgeGreater20());
	vector<int>::iterator it = adjacent_find(v.begin(), v.end());//查找相邻重复元素 
	if (it == v.end())
		cout << "没找到" << endl;
	else
		cout << "找到" << *it << endl;
		//cout << "找到了" << it->m_Name<<" "<<it->m_Age << endl;
	bool ret = 	binary_search(v.begin(), v.end(),9);//二分查找法必须是有序的容器，返回bool 
	if (ret)
		cout << "找到了" << endl;
	else
		cout << "没找到" << endl;
	int num = count(v.begin(), v.end(), 10);//内置统计
	int num = count_if(v.begin(), v.end(), Greater5());
	int num = count(v.begin(), v.end(), p5);//自定义数据类型（配合重载operator==） 
	int num = count_if(v.begin(), v.end(),AgeGreater20());
	
	//排序合并反转 
	sort(v.begin(), v.end()); //升
	sort(v.begin(), v.end(), greater<int>());//降
	random_shuffle(v.begin(), v.end());	//指定范围随机调整次序（洗牌）
	reverse(v.begin(), v.end());		//反转 
	vector<int>v1;//两个容器合并存储到另一个容器
	vector<int>v2;//合并的两个容器必须得是有序序列
	vector<int>vTarget;
	vTarget.resize(v1.size() + v2.size());
	merge(v1.begin(),v1.end(),v2.begin(),v2.end(),vTarget.begin());//合并
	
	//拷贝替换互换
	vector<int>v1;
	vector<int>v2;
	v2.resize(v1.size());	//提前开辟空间
	copy(v1.begin(), v1.end(), v2.begin());
	replace(v.begin(), v.end(), 20, 200);	//20->200 
	replace_if(v.begin(), v.end(),Greater5(),200);// >5 -> 200
	swap(v1, v2);
	
	//删除元素
	TooBig<int> f100(100); // limit = 100
	int vals[10] = { 50, 100, 90, 180, 60, 210, 415, 88, 188, 201 };
	list<int> yadayada(vals, vals + 10); 
	list<int> etcetera(vals, vals + 10);
	//  list<int> yadayada = {50, 100, 90, 180, 60, 210, 415, 88, 188, 201};
	//  list<int> etcetera {50, 100, 90, 180, 60, 210, 415, 88, 188, 201};
	yadayada.remove_if(f100);               
	etcetera.remove_if(TooBig<int>(200));  
	for_each(yadayada.begin(), yadayada.end(), outint);
	for_each(etcetera.begin(), etcetera.end(), outint);


	//算数生成算法
	int total = accumulate(v.begin(), v.end(), 0起始值);//计算区间内容器元素累计总和
	fill(v.begin(),v.end(),100);	//将容器区间内元素填充为指定的值
	
	//集合算法（两个容器必须得是有序序列） 
	vector<int>v1;
	vector<int>v2;
	vector<int>vTarget;
	
	vTarget.resize(min(v1.size(),v2.size()));//交集最特殊情况大容器包含小容器
	vector<int>::iterator itEnd = set_intersection(v1.begin(), v1.end(), 
                                v2.begin(), v2.end(), vTarget.begin());//返回交集末尾位置，帮助for_each
	
	vTarget.resize(v1.size() + v2.size());	//并集最特殊情况大容器+小容器
	vector<int>::iterator itEnd = set_union(v1.begin(), v1.end(), 
                                v2.begin(), v2.end(), vTarget.begin());
	
	vTarget.resize(max(v1.size(), v2.size()));//差集最特殊情况两个容器没有交集，取大容器size
	vector<int>::iterator itEnd = set_difference(v1.begin(), v1.end(), 
                                v2.begin(), v2.end(), vTarget.begin());
	
	for_each(vTarget.begin(),itEnd, Print);
	
	
	return 0;
}
