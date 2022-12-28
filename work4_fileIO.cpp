

#include <iostream> //1.程序与终端IO
#include <cstring>
#include <cmath>
#include <iomanip>  //控制符头文件:setprecision(), setfill(), setw()
#include <exception>
#include <fstream>   //2.程序与文件IO ifstream + ofstream    
#include <cstdlib>   // exit()
#include <sstream>   //3.程序与string对象IO  ostringstream, wostringstream<--ostream, wostream
#include <string>
/*
//ofstream, ifstream ,fstream 分别从ostream, istream 和iostream 引申而来
void open(const char * filename, ios_base::openmode);
void open(const wchar_t *_Filename, ios_base::openmode, int prot);
// 模式:
      ios::out   写入   //ios_base
      ios::in    读取 
      ios::app   追加到末尾 
      ios::ate   定位到末尾 
      ios::trunc 打开时截断清空 
      ios::binary 二进制文件

// prot属性:
      0	普通文件，打开操作
      1	只读文件
      2	隐含文件
      4	系统文件

// 文件位置指针：istream:seekg(),tellg(),  ostream:seekp(), tellp()
      fileObject.seekg( n ); 		   // 定位到第 n 个字节（假设是 ios::beg）
      fileObject.seekg( n, ios::cur ); // 读指针从当前位置向后移 n 个字节
      fileObject.seekg( n, ios::beg ); // 读指针从开头位置往回移 n 个字节
      fileObject.seekg( 0, ios::end ); // 定位到末尾...

// 函数:open(), is_open(), eof(), fail(), close()...
*/

const char * filename = "file.txt";

const int LIM = 20;

struct planet
{
    char name[LIM];      // name of planet
    double population;  // its population
    double g;           // its acceleration of gravity
};

const char * file = "planets.dat";  // ASSUMED TO EXIST (binary.cpp example)

inline void eatline() { while (std::cin.get() != '\n') continue; }


int main(int argc, char * argv[])
{
    
    using namespace std;

    /**输出格式**/
    const char * state1 = "Florida";
    const char * state2 = "Kansas";
    const char * state3 = "Euphoria";
    cout.put('a').put('b') << flush;      // or flush(cout) 刷新输出缓冲区
    cout << (void*)state1 << ":" << state1 << endl; //0x405065:Florida  void*打印地址
    int len = std::strlen(state2);
    cout.write(state2, len) << endl;     //Kansas
    cout.write(state2, len + 5) << endl; //Kansas Euph 长度超出导致打印问题

    //科学计数法格式
    double f1 = 1.200;
    cout << f1 << ":\n";
    cout << (f1 + 1.0 / 9.0) << ":\n";  //1.31111
    double f2 = 1.67E2;
    cout << f2 << ":\n";                //167
    f2 += 1.0 / 9.0;
    cout << f2 << ":\n";                //167.111
    cout << (f2 * 1.0e4) << ":\n";      //1.67111e+006
    double f3 = 2.3e-4;
    cout << f3 << ":\n";                //0.00023
    cout << f3 / 10 << ":\n";           //2.3e-005
   
    //精度宽度设置
    cout.fill('*'); //指定填充字符(一直有效直到被重新设置)
    cout.setf(ios_base::showpoint); //显示小数点(ios_base静态常量)
    cout.precision(3);   //设置精度(一直有效直到被重新设置)
    const char * staff[2] = { "Waldo Whipsnade", "Wilmarie Wooper"};
    float bonus[2] = {90.25, 130.50};
    for (int i = 0; i < 2; i++)
    {
        cout << staff[i] << ": $";
        cout.width(6);  //设置字符宽度(只影响下一个显示，默认右对齐)
        cout << bonus[i] << "\n";
    }
    cout.setf(ios_base::showpos);    // show + （十进制）
    cout << std::hex << endl;        // or hex(cout)修改计数系统hex,oct,dec
    cout.setf(ios_base::uppercase);  
    cout.setf(ios_base::showbase);   //0X基数前缀
    cout << true << endl;            //0X1
    cout.setf(ios_base::boolalpha);  //输入输出bool值时可以为true,false
    cout << true << "\n";            //true
    dec(cout);//还原为十进制 
    // ios_base::basefield : ios_base::dec/oct/hex
    // ios_base::floatfield : ios_base::fixed/scientific
    // ios_base::adjustfield : ios_base::left/right/internal(符号/基数左对齐，数值右对齐)
    ios_base::fmtflags old = cout.setf(ios_base::scientific, ios_base::floatfield);
    cout.setf(ios_base::internal, ios_base::adjustfield);
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.setf(old, ios_base::floatfield);   // 恢复old浮点数设置
    cout.unsetf(ios_base::floatfield);      //消除/切换到默认模式
    //noboolalpha, noshowbase, noshowpos, nouppercase <==> unsetf()

    cout << fixed << right; // use new standard manipulators
    cout << setw(6) << "N" << setw(14) << "square root" << setw(15) << "fourth root\n"; // use iomanip manipulators
    double root;
    for (int n = 10; n <=100; n += 10)
    {
        root = sqrt(double(n));
        cout << setw(6) << setfill('.') << n << setfill(' ')
            << setw(12) << setprecision(3) << root          
            << setw(14) << setprecision(4) << sqrt(root) << endl;//精度即小数位数
    }


    /**输入**/
    cin.exceptions(ios_base::failbit);
    cout << "Enter numbers: ";
    int sum = 0;
    int input;
    try {
        while (cin >> input)    //跳过空白...wcin, wcout, wcerr, wclog
        {
            sum += input;
        }
    } catch(ios_base::failure & bf)
    {
        cout << bf.what() << endl;
    }
   
    const int Limit = 255;
    char input[Limit];
    cin.getline(input, Limit, '#'); //666#777  遇到#结束
    cout << input << endl;  //666
    char ch;
    cin.get(ch);
    cout << ch << endl;    //7 getline()会丢弃分界字符，get()不会
    if (ch != '\n')
        cin.ignore(Limit, '\n');    // 读取并丢弃一行
    cin.get(input, Limit, '#'); //666#777
    cout << input << endl;  //666
    cin.get(ch);
    cout << ch << endl;     //#

    char ch;
    while(cin.get(ch))          // terminates on EOF
    {
        if (ch != '#')
            cout << ch;
        else
        {
            cin.putback(ch);    // reinsert character
            break;
        }
    }
    if (!cin.eof())
    {
        cin.get(ch);
        cout << endl << ch << " is next input character.\n";    //#
    }
    else
    {
        cout << "End of file reached.\n";
        std::exit(0);
    }
    while(cin.peek() != '#')    // peek()返回下一个字符
    {
        cin.get(ch);
        cout << ch;
    }


    /**文件IO**/
    //读写操作
    char data[100];
    ofstream outfile;	// 以写模式打开文件
    outfile.open(filename);
    cout << "Writing to the file" << endl;
    cout << "Enter your name: "; 
    cin.getline(data, 100);
    outfile << data << endl;	// 向文件写入用户输入的数据
    cout << "Enter your age: "; 
    cin >> data;
    cin.ignore();
    outfile << data << endl; // 再次向文件写入用户输入的数据
    outfile.close();			// 关闭打开的文件

    ifstream infile; 		// 以读模式打开文件
    infile.open(filename); 
    cout << "Reading from the file" << endl; 
    infile >> data; 
    cout << data << endl;	// 在屏幕上写入数据
    infile >> data; 			// 再次从文件读取数据，并显示它
    cout << data << endl; 
    infile.close();			// 关闭打开的文件

    //内核格式化(管理字符串数据)
    ostringstream outstr;   // manages a string stream
    string hdisk;
    getline(cin, hdisk);
    int cap;
    cin >> cap;
    outstr << "The hard disk " << hdisk << " has a capacity of " << cap << " gigabytes.\n";
    string result = outstr.str();   // save result，str()返回被初始化为缓冲区内容的字符串对象
    cout << result;                 // show contents

    string lit = "It was a dark and stormy day, and "
                 " the full moon glowed brilliantly. ";
    istringstream instr(lit);   // use buf for input
    string word;
    while (instr >> word)       // read a word a time
        cout << word << endl;

    //命令行处理技术
    if (argc == 1)          // quit if no arguments
    {
        cerr << "Usage: " << argv[0] << " filename[s]\n";
        exit(EXIT_FAILURE);
    }
    ifstream fin;              // open stream
    long count;
    long total = 0;
    char ch;
    for (int file = 1; file < argc; file++)
    {
        fin.open(argv[file]);  // connect stream to argv[file]
        if (!fin.is_open())
        {
            cerr << "Could not open " << argv[file] << endl;
            fin.clear();
            continue;
        }
        count = 0;
        while (fin.get(ch))
            count++;
        cout << count << " characters in " << argv[file] << endl;
        total += count;
        fin.clear();           // needed for some implementations
        fin.close();           // disconnect file
    }
    cout << total << " characters in all files\n";

    //常用函数
    ofstream out(filename);   //写入数据
    if (out.is_open()) 
    {
        out << "This is a line.\n";
        out << "This is another line.\n";
        out.close();
    }

    char buffer[256];          //读取数据
    ifstream in(filename);
    if (! in.is_open())
    { 
        cout << "Error opening file"; 
        exit (1); 
    }
    while (!in.eof() )
    {
        in.getline(buffer,100);
        cout << buffer << endl;
    }

    //位置指针(随机存取)
    long l,m;                  //获得二进制文件大小
    ifstream in(filename, ios_base::in | ios_base::binary);
    l = in.tellg();
    in.seekg(0, ios::end);
    m = in.tellg();
    in.close();
    cout << "size of " << filename << " is " << (m-l) << " bytes.\n";

    char * buf;             //二进制文件从缓存（buffer）中读出或写入的字符数 reading binary file
    long size;              //write/read ( char * buffer, streamsize size )
    ifstream in (filename, ios::in | ios::binary | ios::ate);
    size = in.tellg();
    in.seekg(0, ios::beg);
    buf = new char [size];
    in.read(buf, size);
    in.close();
    cout << "the complete file is in a buffer";
    delete[] buf;


    /***二进制文件案列***/
    planet pl;
    cout << fixed;
    fstream finout;     // read and write streams
    finout.open(file, ios_base::in | ios_base::out | ios_base::binary);
    int ct = 0;
    if (finout.is_open())
    {
        finout.seekg(0);    // go to beginning
        cout << "Here are the current contents of the " << file << " file:\n";
        while (finout.read((char *) &pl, sizeof(pl)))
        {
            cout << ct++ << ": " << setw(LIM) << pl.name << ": "
                 << setprecision(0) << setw(12) << pl.population
                 << setprecision(2) << setw(6) << pl.g << endl;
        }
        if (finout.eof())
            finout.clear(); // clear eof flag
        else
        {
            cerr << "Error in reading " << file << ".\n";
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        cerr << file << " could not be opened -- bye.\n";
        exit(EXIT_FAILURE);
    }
    // change a record
    cout << "Enter the record number you wish to change: ";
    long rec;
    cin >> rec;
    eatline();              // get rid of newline
    if (rec < 0 || rec >= ct)
    {
        cerr << "Invalid record number -- bye\n";
        exit(EXIT_FAILURE);
    }
    streampos place = rec * sizeof(pl);  // convert to streampos type
    finout.seekg(place);    // random access
    if (finout.fail())
    {
        cerr << "Error on attempted seek\n";
        exit(EXIT_FAILURE);
    }

    finout.read((char *) &pl, sizeof(pl));
    cout << "Your selection:\n";
    cout << rec << ": " << setw(LIM) << pl.name << ": "
         << setprecision(0) << setw(12) << pl.population
         << setprecision(2) << setw(6) << pl.g << endl;
    if (finout.eof())
        finout.clear();     // clear eof flag

    cout << "Enter planet name: ";
    cin.get(pl.name, LIM);
    eatline();
    cout << "Enter planetary population: ";
    cin >> pl.population;
    cout << "Enter planet's acceleration of gravity: ";
    cin >> pl.g;
    finout.seekp(place);    // go back
    finout.write((char *) &pl, sizeof(pl)) << flush;
    if (finout.fail())
    {
        cerr << "Error on attempted write\n";
        exit(EXIT_FAILURE);
    }
    finout.close();
  
    return 0;
} 
