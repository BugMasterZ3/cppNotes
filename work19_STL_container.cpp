

//STL容器(序列式和关联式)，迭代器
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <algorithm>//标准算法的头文件
#include <functional>
#include <numeric>
using namespace std;

void myPrint(int val)
{
	cout << val << endl;
}

void output(const std::string& s) { std::cout << s << " "; }

class Person
{
public:
	Person(string name, int age)
	{
		this->m_Age = age;
		this->m_Name = name;
	}
	string m_Name;
	int m_Age;
};


int main(void)
{
	
	/****迭代器算法****/
	vector<int>v;			//存放基本数据类型
	v.push_back(10);
	vector<Person>v;		//存放自定义数据类型
	Person p1("a1", 10);
	v.push_back(p1);
	vector<vector<int>>v;	//嵌套容器(类似二维数组)
	vector<int>v1;				//创建小容器
	vector<int>v2;
	for (int i = 0; i < 2; i++)	//向小容器中添加数据
	{
		v1.push_back(i + 1);
		v2.push_back(i + 2);
	}
	v.push_back(v1);			//将小容器插入到大容器中
	v.push_back(v2);
	
	//通过迭代器来访问容器中的数据
	vector<int>::iterator itBegin = v.begin();	//起始迭代器，指向容器中第一个元素（可用auto自动类型推断）
	vector<int>::iterator itEnd = v.end();		//结束迭代器，指向容器中最后一个元素的下一个位置
	//第一种遍历方式 
	while (itBegin != itEnd)
	{
		cout << *itBegin << endl;
		itBegin++;
	}
	//第二种遍历方式
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		//cout << "姓名:" << (*it).m_Name << "年龄:" << (*it).m_Age << endl;
		cout << "姓名:" << it->m_Name << "年龄:" << it->m_Age << endl;
	}
	for (vector<vector<int>>::iterator it = v.begin(); it != v.end(); it++)	//嵌套
	{
		for (vector<int>::iterator vit = (*it).begin(); vit != (*it).end(); vit++)
		{
			cout << *vit << " ";
		}
		cout << endl;
	}
	//第三种遍历方式，利用STL提供遍历算法:for_each(), random_shuffle(), sort()
	for_each(v.begin(), v.end(), myPrint);
	for (auto& x : v) myPrint(x);	//C++11,可指定引用通过函数修改容器内容
	//sort()默认升序，可加函数选择排序方式
/*
struct Review {
	std::string title;
	int rating;
};
//全排序
bool operator<(const Review & r1, const Review & r2)
{
	if (r1.title < r2.title)
		return true;
	else if (r1.title == r2.title && r1.rating < r2.rating)
		return true;
	else
		return false;
}
//完整弱排序
bool worseThan(const Review & r1, const Review & r2)
{
	if (r1.rating < r2.rating)
		return true;
	else
		return false;
}
*/
	//迭代器类型与层次：输入，输出，正向，双向，随机
	int casts[10] = { 6, 7, 2, 9 ,4 , 11, 8, 7, 10, 5 };
	vector<int> dice(10);
	copy(casts, casts + 10, dice.begin());			// copy from array to vector
	ostream_iterator<int, char> out_iter(cout, " ");// create an ostream iterator
	copy(dice.begin(), dice.end(), out_iter);		// copy from vector to output
	copy(dice.rbegin(), dice.rend(), out_iter);				//Implicit（反向迭代器）
	// vector<int>::reverse_iterator ri;					// use if auto doesn't work
	for (auto ri = dice.rbegin(); ri != dice.rend(); ++ri)	//Explicit
		cout << *ri << ' ';

	string s1[4] = { "fine", "fish", "fashion", "fate" };
	string s2[2] = { "busy", "bats" };
	string s3[2] = { "silly", "singers" };
	vector<string> words(4);
	copy(s1, s1 + 4, words.begin());
	for_each(words.begin(), words.end(), output);
	// construct anonymous back_insert_iterator object
	copy(s2, s2 + 2, back_insert_iterator<vector<string> >(words));	//尾插  front_insert_iterator
	for_each(words.begin(), words.end(), output);
	// construct anonymous insert_iterator object
	copy(s3, s3 + 2, insert_iterator<vector<string> >(words, words.begin()));//需插入位置参数
	for_each(words.begin(), words.end(), output);
	


	/****容器****/
	// vector(矢量，动态扩展的单端数组)
	//构造函数
	vector<int>v1;						//默认构造 无参构造
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	vector<int>v2(v1.begin(), v1.end());//通过区间的方式进行构造
	vector<int>v3(10, 100);				//n个elem方式构造（10个100）
	vector<int>v4(v3);					//拷贝构造
	//赋值操作
	v2 = v1;						//operator= 			
	v3.assign(v1.begin(), v1.end());//assign
	v4.assign(10, 100);				
	//容量和大小
	if (v1.empty())
		cout << "空" << endl;
	else
		cout << "不空" << endl;
	cout << "v1的容量=" << v1.capacity() << endl;
	cout << "v1的大小=" << v1.size() << endl;
	v1.resize(15, 100);	//重新指定的比原来长默认用0填充，第二个参数指定默认填充值
	v1.resize(5);		//如果重新指定的比原来短，超出的部分会删除掉
	//插入和删除
	v1.push_back(10);	//尾插 
	v1.pop_back();		//尾删
	v1.insert(v1.begin(), 100);		//迭代器指定位置插入100
	v1.insert(v1.begin(), 2, 100);	//迭代器指定位置插入2个100
	v1.insert(v1.begin(), v2.begin() + 1, v2.end()); //指定位置插入新容器迭代器参数指定区间
	v1.erase(v1.begin());			//删除参数也是迭代器,返回下一个元素迭代器 
	v1.erase(v1.begin(), v1.end());	//清空（指定区间，左闭右开）
	v1.clear();
	//数据存取访问
	cout << v1[i];
	cout << v1.at(i);			//vector deque
	cout << v1.front() << endl;//获取第一个元素
	cout << v1.back() << endl; //获取最后一个元素
	//互换容器
	v1.swap(v2);
	v.resize(3);
	vector<int>(v).swap(v);	//巧用swap可以收缩内存空间
	cout << "容量" << v.capacity() << endl;
	cout << "大小" << v.size() << endl;
	//预留空间(减少vector在动态内存扩容时的扩展次数)
	v1.reserve(int len);	//预留len个长度，不初始化，元素不可访问 


	//deque(双端数组，可对头尾进行插入删除操作)	
	deque<int>d;
	d.push_back(10);	//尾插
	d.push_front(100);	//头插
	d.pop_back();		//尾删
	d.pop_front();		//头删
	sort(d.begin(), d.end());//区间内排序


	//stack(先进后出)
	stack<int>stk;
	stk.push(1);	//顶加 
	stk.pop();		//顶出 
	stk.top();		//顶值
	cout << stk.size() << endl;
	while (!stk.empty())
	{
		cout << stk.top() << endl;
		stk.pop();
	}


	//queue (先进先出，两个出口)
	//尾插头出，只有头尾能被外界访问，因此不允许有遍历行为
	queue<Person>q;
	Person p1("s1", 1);
	q.push(p1);	//尾加 
	q.pop();		//头出 
	q.back();		//尾值 
	q.front(); 	//头值 
	cout << q.size() << endl;
	while (!q.empty())
	{
		cout << q.front().m_Name << " " << q.front().m_Age << endl;
		q.pop();
	}


	//list双向循环链表（非连续存储结构，双向迭代器）
	//插入操作和删除操作不会造成原list迭代器的失效，vector不成立
	list<int>l1;
	l1.push_back(1);
	l1.push_front(10);
	l1.pop_back();
	l1.pop_front();
	cout << l1.front() << endl;//第一个元素
	cout << l1.back() << endl;//最后一个元素
	list<int>::iterator it = l1.begin();
	it++;	//list中不可以用[]/at()访问容器中的元素,支持++ --双向,it = it+1不行(不支持随机访问)
	l1.insert(it, 1000);
	l1.insert(10, 1000);
	l1.merge(list<T, Alloc>x);					//合并（线性时间）
	l1.splice(iterator pos, list<T, Alloc>x);	//将x插入到pos前（固定时间）
	l1.remove(1000);	//删除所有匹配的元素 
	l1.reverse();		//反转
	l1.unique();		//连续相同元素压缩为单个元素
/*
bool myCompare(int v1, int v2)
{
	return v1 > v2;//降序 第一个数 >第二个数
}
//自定义数据类型指定排序规则
bool comparePerson(Person &p1,Person &p2)
{
	//按照年龄升序
	if (p1.m_Age == p2.m_Age)
	{
		//年龄相同 按照身高降序
		return p1.m_Height > p2.m_Height;
	}
	else
	{
		return p1.m_Age < p2.m_Age;
	}
}
l1.sort(myCompare);		//降序
l1.sort(comparePerson);*/
	

	class MyCompare1	//内置类型,仿函数
	{
	public:
		bool operator()(int v1, int v2)const	//vs2019结尾加const
		{
			return v1 > v2; //降序
		}
	};
	class Mycompare2	//自定义类型
	{
	public:
		bool operator()(const Person& p1, const Person& p2)const
		{
			return p1.m_Age > p2.m_Age;
		}
	};

	//set/multiset(关联式容器,自动排序)
	//set不允许重复元素,multiset允许容重复元素
	set<int>s1;
	s1.insert(2);//只有insert,自动排序，不能插入重复数据 
	s1.insert(1);
	s1.insert(3);
	s1.erase(3);	//删元素3 
	//查找和统计
	set<int>::iterator pos = s1.find(3);//存在返回迭代器，不存在返回set.end() 
	if (pos != s1.end())
		cout << "找到" << *pos << endl;
	else
		cout << "没找到" << endl;
	int num = s1.count(3);	//对于set而言 统计结果 0 或 1，因为无重复
	//集合
	const int N = 6;
	string s1[N] = { "buffoon", "thinkers", "for", "heavy", "can", "for" };
	string s2[N] = { "metal", "any", "food", "elegant", "deliver","for" };
	set<string> A(s1, s1 + N);
	set<string> B(s2, s2 + N);
	ostream_iterator<string, char> out(cout, " ");
	copy(A.begin(), A.end(), out);
	copy(B.begin(), B.end(), out);
	set_union(A.begin(), A.end(), B.begin(), B.end(), out);			//并集
	set_intersection(A.begin(), A.end(), B.begin(), B.end(), out);	//交集
	set_difference(A.begin(), A.end(), B.begin(), B.end(), out);	//差集
	set<string> C;
	set_union(A.begin(), A.end(), B.begin(), B.end(), insert_iterator<set<string> >(C, C.begin()));
	copy(C.begin(), C.end(), out);
	string s3("grungy");
	C.insert(s3);
	copy(C.begin(), C.end(), out);
	copy(C.lower_bound("ghost"), C.upper_bound("spook"), out);	//Showing a range
	//set和multiset区别
	set<int>s1;
	pair<set<int>::iterator, bool>ret = s1.insert(10);
	if (ret.second)
		cout << "插入成功" << endl;
	else
		cout << "插入失败" << endl;
	//第二次
	ret = s1.insert(10);
	if (ret.second)
		cout << "插入成功" << endl;
	else
		cout << "插入失败" << endl;
	multiset<int>ms;
	ms.insert(10);
	ms.insert(10);
	//排序(默认升序)
	set<int, MyCompare1>s1;//set容器要在还没插数据之前对排序进行改变
	for (set<int, MyCompare1>::iterator it = s1.begin(); it != s1.end(); it++)
	{
		cout << *it << " ";
	}
	set<Person, Mycompare2>s1;
	for (set<Person, Mycompare2>::iterator it = s1.begin(); it != s1.end(); it++)
	{
		cout << it->m_Name << " " << it->m_Age << endl;
	}


	//map/multimap(关联式容器,自动排序)
	//map不允许重复key，multimap允许重复key
	//pair对组创建
	pair<string, int>p("Tom", 11);				//第一种
	cout << p.first << " " << p.second << endl;
	pair<string, int>p = make_pair("Jerry", 12);//第二种
	cout << p.first << " " << p.second << endl;
	
	map<int, int>m1;
	for (map<int, int>::iterator it = m1.begin(); it != m1.end(); it++)
	{
		//cout << "key=" << (*it).first << "value=" << (*it).second << "   " ;
		cout << "key=" << it->first << " " << "value=" << it->second << endl;
	}
	//插入和删除
	m1.insert(pair<int, int>(1, 10));			//第一种
	m1.insert(make_pair(2, 20));				//第二种
	m1.insert(map<int, int>::value_type(3, 30));//第三种
	m1[4] = 40;		//第四种，不建议，用途是利用key访问到value,不存在会自动创建，应该确定存在再访问
	m1.erase(3);	//按照key删除
	typedef int KeyType;
	typedef std::pair<const KeyType, std::string> Pair;
	typedef std::multimap<KeyType, std::string> MapCode;
	MapCode codes;
	codes.insert(Pair(415, "San Francisco"));
	codes.insert(Pair(510, "Oakland"));
	codes.insert(Pair(718, "Brooklyn"));
	codes.insert(Pair(718, "Staten Island"));
	pair<MapCode::iterator, MapCode::iterator> range = codes.equal_range(718);//键作参数
	//auto range = codes.equal_range(718);
	cout << "Cities with area code 718:\n";
	for (it = range.first; it != range.second; ++it)
		cout << (*it).second << endl;
	//查找和统计
	map<int, int>::iterator pos = m1.find(3);//返回迭代器
	if (pos != m1.end())
		cout << "找到了" << pos->first << " " << pos->second << endl;
	else
		cout << "没找到" << endl;
	int num = m1.count(3);//0/1，multimap可以大于1（可以重复） 
	//排序
	map<int, int, MyCompare1>m1;
	

	//unordered_set, unordered_multiset, unordered_map, unordered_multimap (无序关联容器)


	return 0;
}
