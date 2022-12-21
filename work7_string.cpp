

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <cctype>
using namespace std;

const int NUM = 8;
const string wordlist[NUM] = {"danger", "health", "loaner", "manage", "remote", "train", "useful", "valid" };


int main()
{
   
    /**使用字符串**/
    //初始化
    string one("Lottery Winner!");     // #1 字符串s初始化 
    cout << one << endl;               // overloaded <<
    string two(20, '$');               // #2 n个字符c初始化
    string three(one);                 // #3 使用另一个一个string对象初始化
    one += " Oops!";                   // overloaded +=
    two = "Sorry! That was ";
    three[0] = 'P';                    // overloaded []
    string four;                       // #4
    four = two + three;                // Sorry! That was Pottery Winner!   overloaded +, = 
    char alls[] = "All's well that ends well";
    string five(alls,20);              // #5 
    cout << five << "\n";              // All's well that ends
    string six(alls+6, alls+10);       // #6 模板参数(地址) well
    string seven(&five[6], &five[10]); 
    string eight(four, 7, 16);         // #7 从位置7开始16个字符  That was Pottery
    string nine = {'a', '0', '1'};     // #8 字符列表初始化 initializer_list<char>
    //string nine{'a', '0', '1'}; 
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


    /**输入**/
    string ten;
    getline(cin, ten); 
    ifstream fin;
    fin.open("tobuy.txt"); //open(filename.c_str());   //string文件名转c风格打开文件
    if (fin.is_open() == false)
    {
      cerr << "Can't open file. Bye.\n";
      exit(EXIT_FAILURE);
    }
    string item;
    int count = 0;
    //自动调节string对象大小（最大允许长度由string::npos指定，通常为unsigned int），可选参数指定输入边界(默认\n)
    getline(fin, item, ':'); 
    //eofbit达到文件尾, failbit达到npos, badbit(硬盘故障...), goodbit一切顺利
    while (fin)  // while input is good
    {
      ++count;
      cout << count <<": " << item << endl;
      getline(fin, item,':');     
    }
    cout << "Done\n";
    fin.close();


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

    return 0; 
}
