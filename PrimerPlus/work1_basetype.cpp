
/*
OOP（面向对象编程）强调数据，试图让语言来满足问题的要求。OOP程序设计方式首先设计类，有助于代码的可重用

C++支持泛型编程编程（模板）模式。与OOP的目标相同，都是为了重用代码和简化抽象概念，但是泛型编程强调的是独立于特定数据类型 

可移植性两大障碍：硬件 + 语言差异 ——> 新标准 C++98,C++11,C99

程序创建: 源代码 -> 编译成机器语言 + 目标带代码连接程序（启动代码，库代码）-> 可执行代码
源代码文件扩展名取决于C++的实现（如UNIX不区分大小写）

C语言新增了诸如控制结构和函数等特性。C++增加了对面向对象编程和泛型编程的支持
ISOC++标准（C++98/03和C++11）为确保众多实现的兼容提供了基础
*/


#include <iostream>	//#include <iostream.h>
#include <cmath>	//<math.h>
#include <climits>  //定义符号常量（数据类型最值）:#define INT_MAX 32767 ...
#include <typeinfo>
#include <vector>
#include <cstring> //<string.h>
#include <string>	//class
using namespace std;	//命名空间编译指令

struct student 	//tag 无标签之后无法创建其他变量 
{
	int age;
	std::string name;	// char name[20];
	double score;
}s1 = 
{ 
	22, 
	"zhangsan", 
	85.0
};

union num	//共用体只能存储其中一种数据类型（int或long） ,长度为最大成员 
{
	int x;
	long y;
}; 

struct widget
{
	int type;	//id类型标识符(程序员编写) 
	union		//匿名共用体(anonymous union)成员储存地址相同 
	{
		int id1;
		char id2[20];	
	};	
};
/*
	widget w1;
	if (w1.type == 1)
		cin >> w1.id1;
	else
		cin >> w1.id2; 
*/ 

int 

main(void)	//合法格式（回车与空格可互换）
{
	
	cout << "hello" 
		<< "world\n";	//发送到cout的信息流 << (运算符重载)
	int a, b, c;
	a = b = c = 2;	//合法，从右向左赋值，c=2, b=c, a=b
	a = (b = 3) + 3;
	cin >> a;		//cin是一个istream类对象
					//cin.get()需要两条语句，第一条读取，第二条暂停直到按下enter
	std::cout << a << b << c; //cout将变量替换成当前值25，然后把值转换成合适的输出字符
	cout << endl;	//控制流
	//return 0;		//返回给操作系统ANSI/ISO C++标准会隐式加入这条语句，仅限于main()

	int t = true; int f = false;	// **<-->bool
	bool start = -100; bool stop = 0;
	const int Months = 12;			//限定符
	
	char ch = 'a';
	int i = ch;
	cout.put(ch);	//a
	cout.put(i);	//a	输出字符
	cout.put(97);	//a
	cout.put('a');	//a
	cout << i;		//97
	cout << 'a';	//a
	cout << '\n';
	//cout << "\"hello\" \u00E2"; //转义字符与通用字符名
	//wchar_t op = L'p'; //宽字符类型（整数类型）	
	//char16_t ch1 = u'q';//新增类型（无符号）	版本编译问题
	//char32_t ch2 = U'\u0000222B';
	//wout << L"tall" << endl;

	//精度问题
	cout.setf(ios_base::fixed, ios_base::floatfield);
	float f = 10.0 / 3.0;
	double d = 10.0 / 3.0;
	float million = 1.0e6;
	cout << f << d << endl;				//3.333333
	cout << f * million << endl;		//3333333.250000	第七个值后产生误差
	cout << 10 * f * million << endl;	//33333332.000000
	cout << d * million << endl;		//3333333.333333
	float f1 = 2.34e+22f;
	float f2 = f1 + 1.0;
	cout << f2 - f1;			//0	精度丢失
	float f = 120 / 4 * 5;		//150	优先级相同从左往右
	float ff = 1 * 2 + 2 * 3;	//8
	
	//数据类型转换问题：long（short)没问题；short（long）产生问题（可用强制转换static_cast<>）
	cout << sqrt(4) << endl << pow(2, 3) << endl << rand() << endl;
	int int_max = INT_MAX;
	int a(25);	//C没有的初始化语法
	int b{ 25 };// b = {25} 等号使用与否都可
	int c{}; // c = {} 初始化为0
	const int x1 = 65;
	int x2 = 95;
	char c1 = { x1 };	//A 常数合法
	//char c2 = { x2 };	//变量不合法(x2可能很大)
	cout << sizeof(int) << ":" << INT_MIN << "~" << INT_MAX << endl;
	int oc = 042; //34
	int hx = 0xA5; //10*16+5=165
	
	//自动推断类型
	auto a = 1.3e12L; 
	cout << typeid(a).name(); //long double
	std::vector<double>scores;
	auto pv = scores.begin(); //std::vector::iterator pv = scores.begin();
	auto b = 0;    // 自动推断类型初始化为0会产生问题
	
	//数组
	int arr[] = { 1, 2, 3 }; //自动识别数组大小
	//int arr[] = { 1, 2, 3.0 }; //error
	char ch[3]{ '1', 'a', '\0' }; //new C++
	float f[3];
	//f[3] = {0};    //error 定义时才能初始化
	f[0] = 1.0;
	cout << sizeof arr << sizeof arr[0] << arr[1] * arr[2] << endl; //12 4 6
	cout << f[0] << " " << f[1] << " " << f[2] << endl;	//1 -1.07374e+08 -1.07374e+08
	//char ch = "S"; //illegal "S"('S'+'\0')表示字符串内存地址
	cout << "I am a stu"
		"dent";  //任何两个空白字符串常量会自动拼接成一个
	char str_arr[12] = "hello"; //字符串数组
	cout << str_arr << strlen(str_arr) << endl; //hello 5 strlen()不计算空字符
	str_arr[2] = '\0';
	cout << str_arr << strlen(str_arr) << endl; //he 2 空字符'\0'后会被忽略
	
	//面向行的类成员函数
	const int Asize = 12;
	char name[Asize];
	char food[Asize];
	cin >> name; //zhang san cin会将换行符留在输入队列,下次输入会读取
	//cin.ignore(1024, '\n'); //1024可用 numeric_limits<streamsize>::max() 代替
	cin >> food; // name=zhang food=san 输入空字符使name被分开读取（同时还有越界问题）
	
	cin.getline(name, Asize); //字符不超过(Asize-1)直到换行符， 并丢弃'\n'('\0'替换)
	cin.getline(food, Asize);
	//or cin.getline(name, Asize).getline(food, Asize);	//合并输入两行表示两个变量
	
	cin.get(name, Asize);  //保存换行符在输入队列中，第二次get()会读取无法跨过
	cin.get(food, Asize);  //problem 无内容 	
	cin.get(name, Asize);  //使用不带参处理换行符解决问题
	cin.get();     //or cin.get(name, Asize).get(); //成员函数拼接合并
	cin.get(food, Asize);
	
	cin.clear();  //空行问题会设置失效位failbit，clear()恢复输入
	cin.sync();   //清除缓冲区数据流
	short int n1,n2;
    cin >> n1;  //31600000
    cin >> n2;
    cout<< n1 << n2 << endl; //32767 -248
    if (cin.fail() == true)
    {
		cout << "cin.fail() == true\n";
		cin.clear();
		cout << "cin can work now\n";
    }
    cin >> n2;  //31600000
    cout << n1<< n2 << endl;  //32767 32767

	int age = 0; //混合输入字符串和数组
	cin >> age;	
	cin.get();	 //or (cin >> age).get();
	cin.getline(name, Asize);
	cout << "age = " << age << " name = " << name << endl;

	//string类
	char s[20];
	cout << strlen(s) << endl;	//486 长度大于20，未初始化数组第一个空字符位置是随机的
	cin.getline(s, 20);			//一行输入读取到数组中（cin是istream对象，getline()是istream类方法）
	char s1[] = { "hhh" };//初始化
	char s2[]{ "fff" };
	//s1 = s2;	//invalid
	
	string str;	
	cout << str.size();	// 0 未初始string对象长度自动设置为0（自动调节str长度）
	string str1 = "hhh";	
	string str2 = { "xxx" };
	string str3{ "yyy" };
	//cin >> str1;
	getline(cin, str1);	//hahaha  string类友元函数，istream类中没有处理string对象的类方法
	cout << str1.size() << str1.length() << str1[1] << endl;	// 6 6 a
	str1 = str2;	//valid string对象赋值 == strcpy(str1, str2)
	str1 = str2 + str3;	//合并拼接运算符	
	str1 += str2;	//strcat(str1, str2)

	wchar_t t1[] = L"ifconfig";	//new C++
	char16_t t2[] = u"ifconfig";
	char32_t t3[] = U"ifconfig";
	cout << R"(zh"\n"ang)";		//zh"\n"ang  R标记为原始（raw）字符串（省转义序列\）
	cout << R"+*("(zh)"ang)+*";	//"(zh)"ang  编译器遇到)"就会结束，()头尾+*解决
	
	//结构体
	//student s1 = { 22, "zhangsan", 85.0 };
	student s2{};	// 初始化=可省略
	cout << s2.age << s2.score << endl;	//0 0 空{}初始化默认为0
	student s[2] = 
	{
		{ 22, "zhangsan", 85.0 }, 
		{ 24, "lisi", 88.0 }
	};	//初始化结构体数组 
	
	struct teacher
	{
		unsigned int birthyaer : 4;	//new 位字段指定占用位数 (低级编程)
		bool man : 1;
	};
	
	//枚举
	enum led{red=-5, green=0, orange, blue=1, yellow = 9};	// 新类型枚举 {枚举量(自定义+默认后比前大1)} ，代替const
	//enum {red, green, blue};	//不创建变量只使用常量可省略类型名
	cout << red << green << orange << blue << yellow << endl;	// -5 0 1 1 9 枚举量值可以相同
	led led1;	//枚举变量
	led1 = red;	//valid
	int color = 3 + blue;	// 4 枚举量-->int
	//led1 = 5;	//invalid 只能使用定义时的枚举量
	//led1++;	//invalid 枚举只有赋值运算符没有算术运算
	//led1 = red + blue;	//左为枚举，右为int/long/long long，类型不一致
	//枚举取值范围：[0(min>=0)或小于min的-2的幂值+1(min<0), 大于max的2的幂值-1],如上led枚举范围为[-2^3+1, 2^4-1] = [-7,15]
	led1 = led(6);			//有效值强制转化
	led1 = led(66);			//undefined 不适当值结果不确定？(运行结果没问题)

	return 0;
}
