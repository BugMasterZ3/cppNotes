

#include <iostream>
#include <fstream>   // ifstream + ofstream    
#include <cstdlib>   // exit()
using namespace std;

/*
//ofstream, ifstream ,fstream 分别从ostream, istream 和iostream 引申而来

// 模式:
      ios::out  写入 
      ios:in    读取 
      ios:app   追加到末尾 
      ios:ate   定位到末尾 
      ios:trunc 打开时截断清空 

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
int main()
{
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


    //位置指针操作
    long l,m;                  //获得二进制文件大小
    ifstream in(filename, ios::in|ios::binary);
    l = in.tellg();
    in.seekg(0, ios::end);
    m = in.tellg();
    in.close();
    cout << "size of " << filename << " is " << (m-l) << " bytes.\n";

    char * buf;             //二进制文件从缓存（buffer）中读出或写入的字符数 reading binary file
    long size;              //write/read ( char * buffer, streamsize size )
    ifstream in (filename, ios::in|ios::binary|ios::ate);
    size = in.tellg();
    in.seekg(0, ios::beg);
    buf = new char [size];
    in.read(buf, size);
    in.close();
    cout << "the complete file is in a buffer";
    delete[] buf;

    return 0;
} 
