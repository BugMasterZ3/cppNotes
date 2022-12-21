

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <memory>   //智能指针头文件
#include <vector>

using std::string;
const int NUM = 8;
const string wordlist[NUM] = {"danger", "health", "loaner", "manage", "remote", "train", "useful", "valid" };


int main()
{
    using std::cout;
    using std::cin;
    using std::tolower;
    using std::endl;

    /**使用字符串**/
      //赋值操作
    string str1 = "hello world";//通过[] or at()访问/修改
    string str2 = str1;
    string str3 = "c";
    string str4, str5, str6, str7;
    str4.assign("hello c++");   
    str5.assign("hello c++", 5);//把字符串当前n个字符赋给当前的字符串
    str6.assign(str5);          
    str7.assign(10, 'c');       //用n个字符c赋给当前字符串
    //增删改查
    string str1 = "he";
    string str2 = " zbc";
    str1 += "llo";      //重载+=操作符
    str1 += str2;
    string str3 = "You";
    str3.append(" SB");             //追加到到当前字符串结尾
    str3.append("hahaha hahaha", 4);//把字符串s的前n个字符连接到当前字符串的结尾
    str3.append(str2);              //同operator+=(const string& str)
    str3.append(str2, 0, 1);        //把字符串中从pos开始的n个字符连接到字符串结尾
    str3.insert(1, "111");
    str3.insert(0, 5, 'x');         //指定位置0处插入5个字符
    str3.erase(1,3);			    //删除从1开始的3个字符
    string& replace(int pos, int n, const string & str);//替换从pos开始n个字符为str
    string& replace(int pos, int n, const char* s);     //替换从pos开始的n个字符为s
    //find查找从左往右，rfind从右往左
    int find(const string& str, int pos = 0) const;//找到返回首现首字符位置，失败返回string::npos
    int find(const char* s, int pos = 0) const;
    int find(const char* s, int pos, int n) const; //从pos位置查找s的前n个字符子串
    int find(const char c, int pos = 0) const;	   
    int rfind(const string& str, int pos = npos) const;	//查找str最后一次位置
    int rfind(const char* s, int pos = npos) const;
    int rfind(const char* s, int pos, int n) const;		//从pos查找s的前n个字符最后一次位置
    int rfind(const char c, int pos = 0) const;
    find_first_of();	//查找参数任意字符首现位置
    find_last_of();		//参数任意字符最后出现位置
    find_first_not_of();//查找第一个不包含在参数中的字符位置
    find_last_not_of();
    //获取子串
    string email = "zhangsan@qq.com"; //从邮箱地址中获取用户名信息
    int pos = email.find("@");
    string usrName = email.substr(0, pos);
    //容量大小
    string empty;
    string small = "bit";
    cout << empty.size() << endl;       //0 or length()
    cout << small.size() << endl;       //3
    cout << empty.capacity() << endl;   //15 当前分配内存块大小
    cout << small.capacity() << endl;   //15
    empty.reserve(20);  //请求内存块最小长度
    cout << empty.capacity() << endl;   //31
    //c_str()
    string filename;
    ofstream fout.open(filename.c_str());   //转c风格打开文件
	
    /**案例：猜字母游戏**/
    std::srand(std::time(0));
    char play;
    cout << "Will you play a word game? <y/n> ";
    cin >> play;
    play = tolower(play);
    while (play == 'y')
    {
        string target = wordlist[std::rand() % NUM];
        int length = target.length();   // or size()
        string attempt(length, '-');
        string badchars;
        int guesses = 6;
        cout << "Guess my secret word. It has " << length << " letters, and you get " << guesses << " wrong guesses.\n";
        cout << "Your word: " << attempt << endl;
        while (guesses > 0 && attempt != target)    // str1.compare(str2)
        {
            char letter;
            cout << "Guess a letter: ";
            cin >> letter;
            if (badchars.find(letter) != string::npos || attempt.find(letter) != string::npos)
            {
                cout << "You already guessed that. Try again.\n";
                continue;
            }
            int loc = target.find(letter);
            if (loc == string::npos)
            {
                cout << "Oh, bad guess!\n";
                --guesses;
                badchars += letter; // add
            }
            else
            {
                cout << "Good guess!\n";
                attempt[loc] = letter;
                loc = target.find(letter, loc + 1); 
                while (loc != string::npos) //循环查找字母是否再次出现,依次插入相应位置
                {
                    attempt[loc] = letter;
                    loc = target.find(letter, loc + 1);
                }
            }
            cout << "Your word: " << attempt << endl;
            if (attempt != target)
            {
                if (badchars.length() > 0)
                    cout << "Bad choices: " << badchars << endl;
                cout << guesses << " bad guesses left\n";
            }
        }
        if (guesses > 0)
            cout << "That's right!\n";
        else
            cout << "Sorry, the word is " << target << ".\n";
        cout << "Will you play another? <y/n> ";
        cin >> play;
        play = tolower(play);
    }


    //智能指针:自动释放new出来的内存，避免内存泄漏（delete/智能指针）
    //智能指针相互赋值解决方法：深复制，建立所有权，引用计数
    /*
    //三个常用函数：
    //1. get() 获取智能指针托管的指针地址        Test *tmp = test.get();
    //2. release() 取消智能指针对动态内存的托管  Test *tmp2 = test.release();
    //3. reset() 重置智能指针托管的内存地址，如果地址不一致，原来的会被析构掉
    test.reset();			// 释放掉智能指针托管的指针内存，并将其置NULL
    test.reset(new Test());	// 释放掉智能指针托管的指针内存，并将参数指针取代之

    //使用陷阱:不要把一个原生指针给多个智能指针管理
    int *x = new int(10);
    unique_ptr<int> up1(x);
    unique_ptr<int> up2(x); //up1 up2指向同一个内存,非常危险
    up1.reset(x);	        //同上
    up2.reset(x);

    //使用u.release()的返回值(release不会释放u所指内存，返回值是这块内存的唯一索引）

    //禁止delete智能指针get()返回的指针;
    //主动释放get函数指针，智能指针内部指针就变成野指针，析构时造成重复释放

    //禁止用任何类型get函数返回的指针去初始化另外一个智能指针
    shared_ptr<int> sp4(sp1.get());//典型的错误用法
    */
    class Report
    {
    private:
        std::string str;
    public:
        Report(const std::string s) : str(s) { std::cout << "Object created!\n"; }
        ~Report() { std::cout << "Object deleted!\n"; }
        void comment() const { std::cout << str << "\n"; }
    };
    //new返回指针作为智能指针（都有显式explicit）构造函数参数
    std::auto_ptr<Report> pa(new Report("using auto_ptr")); //C++98
    pa->comment();
    std::shared_ptr<Report> ps(new Report("using shared_ptr"));
    ps->comment();
    std::unique_ptr<Report> pu(new Report("using unique_ptr")); //可用于数组，BOOST库scoped_ptr类似
    pu->comment();
    std::shared_ptr<double> p1;
    double* pd = new double;
    //p1 = pd;                          // error (implicit)
    p1 = std::shared_ptr<double>(pd);   // ok (explicit)
    //std::shared_ptr<double> p1 = pd;  // error
    std::shared_ptr<double> p2(pd);     // ok


    using namespace std;
    class Test {
    public:
        Test() { cout << "Test的构造函数..." << endl; }
        ~Test() { cout << "Test的析构函数..." << endl; }
        int getDebug() { return this->debug; }
    private:
        int debug = 20;
    };


    /**** auto_ptr *****/  
    //Test *test = new Test;		//并没有调用析构函数
    auto_ptr<Test> test(new Test);	//调用析构函数
    cout << "test->debug：" << test->getDebug() << endl;
    cout << "(*test).debug：" << (*test).getDebug() << endl;
    auto_ptr<Test>* tp = new auto_ptr<Test>(new Test);//尽可能不要将auto_ptr变量定义为全局变量/指针	
    auto_ptr<Test> t1(new Test);
    auto_ptr<Test> t2(new Test);
    t1 = t2;	//不要把auto_ptr智能指针赋值给同类型的另外一个智能指针，除非自己知道后果 

    //被C++11抛弃的主要原因
    //基于排他所有权模式：两个指针不能指向同一个资源
    auto_ptr<string> p1(new string("I'm Li Ming!"));
    auto_ptr<string> p2(new string("I'm age 22."));
    p1 = p2;    //复制或者赋值都会改变资源的所有权，p1托管了p2托管的指针，p2放弃托管制NULL	
    //STL容器中使用auto_ptr存在着重大风险，因为容器内元素必须支持复制/赋值
    vector<auto_ptr<string>> vec;
    vec.push_back(std::move(p1));//std::move修饰成右值才可以插入
    vec.push_back(std::move(p2));
    cout << *vec.at(0) << endl;
    cout << *vec[1] << endl;
    vec[0] = vec[1];	// 进行赋值问题又回到上面	
    //不支持对象数组的内存管理	                
    auto_ptr<int[]> array(new int[5]);	//not allow


    /**** unique_ptr ****/
    //基于排他所有权模式：两个指针不能指向同一个资源
    //无法进行左值复制赋值操作，但允许临时右值赋值构造和赋值
    //保存指向某个对象的指针，当它本身离开作用域时会自动释放它指向的对象
    //在容器中保存指针是安全的
    unique_ptr<string> p1(new string("I'm Li Ming!"));
    unique_ptr<string> p2(new string("I'm age 22."));
    cout << "p1：" << p1.get() << endl;
    cout << "p2：" << p2.get() << endl;
    unique_ptr<string> p3(p2);	// 禁止左值赋值构造
    p1 = p2;					// 禁止左值赋值
    unique_ptr<string> p3(std::move(p1));
    p1 = std::move(p2);	        // move左值转成右值可以赋值，效果和auto_ptr一样
    cout << "p1：" << p1.get() << endl;
    cout << "p2：" << p2.get() << endl;

    vector<unique_ptr<string>> vec;
    vec.push_back(std::move(p1));
    vec.push_back(std::move(p2));
    vec[0] = vec[1];				//容器中不允许直接赋值
    vec[0] = std::move(vec[1]);		//需要使用move修饰，使得程序员知道后果,vec[1]已经是NULL，再继续访问就越界
    unique_ptr<int[]> array(new int[5]); //支持对象数组的内存管理

    // 构造
    class DestructTest {    // 自定义一个内存释放器 
    public:
	    void operator()(Test* pt) {
		    delete pt;
	    }
    };
    unique_ptr<int[]> t3;
    unique_ptr<int[]> t4(new int[5]);
    unique_ptr<Test> t1;	            //空up，可以指向类型对象
    unique_ptr<Test> t2(new Test);	    //定义up,同时指向类型对象
    unique_ptr<Test, DestructTest> t5;  //空up，接受一个D类型删除器
    unique_ptr<Test, DestructTest> t6(new Test);//定义up,指向类型为T的对象，接受一个D类型的删除器D
    //赋值
    t1 = std::move(t2);
    //主动释放对象
    t1 = NULL;
    t1 = nullptr;
    t1.reset();
    //放弃对象的控制权
    Test* t2 = t1.release();
    //重置
    t1.reset(new Test);

    //auto_ptr 与 unique_ptr内存管理陷阱
    auto_ptr<string> p1;
    string* str = new string("智能指针的内存管理陷阱");
    p1.reset(str);		// p1托管str指针
    {
	    auto_ptr<string> p2;
	    p2.reset(str);	// p2接管str指针时，会先取消p1的托管再对str托管
    }
    cout << "str：" << *p1 << endl;//内存报错！p1已经没有托管内容指针(NULL)


    /**** shared_ptr ****/
    //指针变量共享(复制或拷贝引用计数加1,计数为零代表没有指针指向这块内存)
    class Person {
    public:
	    Person(int v) {
		    this->no = v;
		    cout << "构造函数 \t no = " << this->no << endl;
	    }
	    ~Person() {
		    cout << "析构函数 \t no = " << this->no << endl;
	    }
    private:
	    int no;
    };
    class DestructPerson {	// 仿函数，内存删除
    public:
	    void operator() (Person* pt) {
		    cout << "DestructPerson..." << endl;
		    delete pt;
	    }
    };
    //use_count()：引用计数/共享指针的数量 
    shared_ptr<Person> sp1;
    shared_ptr<Person> sp2(new Person(2));
    cout << "sp1 use_count() = " << sp1.use_count() << endl;//0	
    cout << "sp2 use_count() = " << sp2.use_count() << endl << endl;//1
    sp1 = sp2;	// 共享
    cout << "sp1 use_count() = " << sp1.use_count() << endl;//2
    cout << "sp2 use_count() = " << sp2.use_count() << endl << endl;//2
    shared_ptr<Person> sp3(sp1);
    cout << "sp1 use_count() = " << sp1.use_count() << endl;//3
    cout << "sp2 use_count() = " << sp2.use_count() << endl;//3
    cout << "sp2 use_count() = " << sp3.use_count() << endl << endl;//3
    //构造
    shared_ptr<Person> sp1;	//空sp，可以指向类型对象
    Person* person1 = new Person(1);
    sp1.reset(person1);	    // 托管person1
    shared_ptr<Person> sp2(new Person(2));  //定义sp,同时指向类型为T的对象
    shared_ptr<Person> sp3(sp1);
    shared_ptr<Person[]> sp4;               //空sp，可以指向类型[]数组对象 C++17后支持
    shared_ptr<Person[]> sp5(new Person[5]{ 3, 4, 5, 6, 7 });//指向类型数组对象
    shared_ptr<Person> sp6(NULL, DestructPerson());          //空sp，接受一个D类型的删除器
    shared_ptr<Person> sp7(new Person(8), DestructPerson());
    //初始化
    shared_ptr<int> sp1(new int(10));  // int(10) 的引用计数为1
    shared_ptr<int> sp2(up1);          // 使用智能指针up1构造up2, 此时int(10) 引用计数为2
    shared_ptr<int> sp3 = make_shared<int>(2);              //多个参数以逗号','隔开，最多接受十个
    shared_ptr<string> sp4 = make_shared<string>("字符串");  //分配内存效率更高(推荐使用)
    shared_ptr<Person> sp5 = make_shared<Person>(9);
    //赋值
    sp1 = sp2;	    // sp1引用计数-1,等于0内存释放，sp2共享给sp1引用计数+1=2
    //主动释放对象
    sp1 = nullptr;	// 引用计数-1,归零内存释放 
    sp1 = NULL; 	
    //重置
    sp1.reset();        //重置为空指针，管理对象引用计数-1
    sp1.reset(p1);      //重置为p1（的值）,sp1管控对象计数-1，sp1接管对p1指针的管控
    sp1.reset(p1, d);   //将sp1重置为p1（的值），sp1管控对象计数-1并使用d作为删除器
    //交换
    std::swap(sp1, sp2);// 交换管理对象，原对象引用计数不变
    sp1.swap(sp2);        

    //shared_ptr使用陷阱:循环引用造成无法释放资源
    class Girl;

    class Boy {
    public:
	    Boy() { cout << "Boy 构造函数" << endl; }
	    ~Boy() { cout << "~Boy 析构函数" << endl; }
	    void setGirlFriend(shared_ptr<Girl> _girlFriend) { this->girlFriend = _girlFriend; }
    private:
	    shared_ptr<Girl> girlFriend;
    };
    class Girl {
    public:
	    Girl() { cout << "Girl 构造函数" << endl; }
	    ~Girl() { cout << "~Girl 析构函数" << endl; }
	    void setBoyFriend(shared_ptr<Boy> _boyFriend) { this->boyFriend = _boyFriend; }
    private:
	    shared_ptr<Boy> boyFriend;
    };

    void useTrap() {
	    shared_ptr<Boy> spBoy(new Boy());
	    shared_ptr<Girl> spGirl(new Girl());

	    //spBoy->setGirlFriend(spGirl);// 陷阱用法
	    //spGirl->setBoyFriend(spBoy); // 此时boy和girl的引用计数都是2,并没有释放内存

	    spGirl->setBoyFriend(spBoy);  // 单方获得管理可以正常释(或使用weak_ptr弱指针)	
    }


    /****weak_ptr****/
    //构造和析构不会引起引用记数的增加或减少
    //弱指针的使用（配合shared_pt）
    weak_ptr wpGirl_1;          // 定义空的弱指针
    weak_ptr wpGirl_2(spGirl);  // 使用共享指针构造
    wpGirl_1 = spGirl;          // 允许共享指针赋值给弱指针
    wpGirl_1.use_count();       //弱指针也可以获得引用计数；
    //wpGirl_1->setBoyFriend(spBoy); //没有重载*和->
    //(*wpGirl_1).setBoyFriend(spBoy); 
    spgirl = wpGirl_1.lock();   //转换成共享指针 
    spgirl = NULL;	            //使用完后将共享指针置NULL即可

    class Girl;
    class Boy {
    public:
	    Boy() { cout << "Boy 构造函数" << endl; }
	    ~Boy() { cout << "~Boy 析构函数" << endl; }
	    void setGirlFriend(shared_ptr<Girl> _girlFriend) {
		    this->girlFriend = _girlFriend;
		    // 在必要的使用可以转换成共享指针
		    shared_ptr<Girl> sp_girl;
		    sp_girl = this->girlFriend.lock();
		    cout << sp_girl.use_count() << endl;
		    // 使用完之后，再将共享指针置NULL即可
		    sp_girl = NULL;
	    }
    private:
	    weak_ptr<Girl> girlFriend;
    };

    void useTrap() {
	    shared_ptr<Boy> spBoy(new Boy());
	    shared_ptr<Girl> spGirl(new Girl());

	    spBoy->setGirlFriend(spGirl);
	    spGirl->setBoyFriend(spBoy);
    }

    //expired函数
    //判断当前weak_ptr是否还有托管对象，有返回false，无返回true(等价于use_count()==0)
    std::weak_ptr<int> wp;
    auto sp = std::make_shared<int>(42);
    wp = sp;
    if (!wp.expired())
	    std::cout << "wp is valid\n";	// 有效的，还有托管的指针
    else 
	    std::cout << "wp is expired\n";	// 过期的，没有托管的指针

	return 0;
}
