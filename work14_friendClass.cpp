

#include <iostream>
#include <string>

class Tv;         

class Remote
{
public:
    enum State{Off, On};
    enum {MinVal,MaxVal = 20};
    enum {Antenna, Cable};
    enum {TV, DVD};
private:
    int mode;    // controls TV or DVD
public:
    Remote(int m = TV) : mode(m) {}
    //friend void func(Remote & r, Tv & t);   //共同友元
    bool volup(Tv & t);         //通过Tv公有接口实现内联方法
    bool voldown(Tv & t);
    void onoff(Tv & t);
    void chanup(Tv & t);
    void chandown(Tv & t);
    void set_mode(Tv & t);
    void set_input(Tv & t);
    void set_chan(Tv & t, int c);  //设置频道(唯一路径)
};

class Tv
{
public:
    //friend class Remote;    // 友元类(所有方法都可能改变Tv私有成员，不需要提前声明)
    friend void Remote::set_chan(Tv & t, int c); // 友元方法改变Tv私有成员channel(提前声明)
    //friend void func(Remote & r, Tv & t);      //共同友元
    enum State{Off, On};
    enum {MinVal,MaxVal = 20};
    enum {Antenna, Cable};
    enum {TV, DVD};

    Tv(int s = Off, int mc = 125) : state(s), volume(5),
        maxchannel(mc), channel(2), mode(Cable), input(TV) {}
    void onoff() {state = (state == On)? Off : On;} //state ^= 1;
    bool ison() const {return state == On;}
    bool volup();
    bool voldown();
    void chanup();
    void chandown();
    void set_mode() {mode = (mode == Antenna)? Cable : Antenna;}
    void set_input() {input = (input == TV)? DVD : TV;}
    void settings() const;  // display all settings
private:
    int state;             // on or off
    int volume;           
    int maxchannel;        // maximum number of channels
    int channel;           // current channel setting
    int mode;              // broadcast or cable
    int input;             // TV or DVD
};


template <class Item>
class QueueTP
{
private:
    enum { Q_SIZE = 10 };
    class Node  //嵌套类 nested class,公有时外部通过QueueTP::Node访问
    {
    public:
        Item item;
        Node* next;
        Node(const Item& i) :item(i), next(0) { }       // nullptr
    };
    Node* front;        // pointer to front 
    Node* rear;         // pointer to rear 
    int items;          // current number 
    const int qsize;    // maximum number 
    QueueTP(const QueueTP& q) : qsize(0) {}
    QueueTP& operator=(const QueueTP& q) { return *this; }
public:
    QueueTP(int qs = Q_SIZE);
    ~QueueTP();
    bool isempty() const
    {
        return items == 0;
    }
    bool isfull() const
    {
        return items == qsize;
    }
    int queuecount() const
    {
        return items;
    }
    bool enqueue(const Item& item); // add item to end
    bool dequeue(Item& item);       // remove item from front
};



int main()
{
    using std::string;
    using std::cin;
    using std::cout;

    Tv s42;
    s42.settings(); //off 
    s42.onoff();    //初始化
    s42.chanup();
    s42.settings(); //on
    Remote grey;    //一个遥控可用于多台电视机
    grey.set_chan(s42, 10); //调频道
    grey.volup(s42);        //调音量
    grey.volup(s42); 
    cout << "\n42\" settings after using remote:\n";
    s42.settings();
    Tv s58(Tv::On);
    s58.set_mode();
    grey.set_chan(s58,28);
    cout << "\n58\" settings after using remote:\n";
    s58.settings();
    
    QueueTP<string> cs(5);
    string temp;
    while (!cs.isfull())
    {
        cout << "Please enter your name. You will be served in the order of arrival.\n"
                "name: ";
        getline(cin, temp);
        cs.enqueue(temp);
    }
    cout << "The queue is full. Processing begins!\n";
    while (!cs.isempty())
    {
        cs.dequeue(temp);
        cout << "Now processing " << temp << "...\n";
    }
    
    return 0; 
}


//Tv methods
bool Tv::volup()
{
    if (volume < MaxVal)
    {
        volume++;
        return true;
    }
    else
        return false;
}
bool Tv::voldown()
{
    if (volume > MinVal)
    {
        volume--;
        return true;
    }
    else
        return false;
}

void Tv::chanup()
{
    if (channel < maxchannel)
        channel++;
    else
        channel = 1;
}

void Tv::chandown()
{
    if (channel > 1)
        channel--;
    else
        channel = maxchannel;
}

void Tv::settings() const
{
    using std::cout;
    using std::endl;
    cout << "TV is " << (state == Off? "Off" : "On") << endl;
    if (state == On)
    {
        cout << "Volume = " << volume << endl;
        cout << "Channel = " << channel << endl;
        cout << "Mode = " << (mode == Antenna? "antenna" : "cable") << endl;
        cout << "Input = " << (input == TV? "TV" : "DVD") << endl;
    }
}

// Remote methods
inline bool Remote::volup(Tv & t) { return t.volup();}
inline bool Remote::voldown(Tv & t) { return t.voldown();}
inline void Remote::onoff(Tv & t) { t.onoff(); }
inline void Remote::chanup(Tv & t) {t.chanup();}
inline void Remote::chandown(Tv & t) {t.chandown();}
inline void Remote::set_mode(Tv & t) {t.set_mode();}
inline void Remote::set_input(Tv & t) {t.set_input();}
inline void Remote::set_chan(Tv & t, int c) {t.channel = c;} 

// QueueTP methods
template <class Item>
QueueTP<Item>::QueueTP(int qs) : qsize(qs)
{
    front = rear = 0;
    items = 0;
}

template <class Item>
QueueTP<Item>::~QueueTP()
{
    Node* temp;
    while (front != 0)      // while queue is not yet empty
    {
        temp = front;       // save address of front item
        front = front->next;// reset pointer to next item
        delete temp;        // delete former front
    }
}

template <class Item>
bool QueueTP<Item>::enqueue(const Item& item)
{
    if (isfull())
        return false;
    Node* add = new Node(item);    // create node
    items++;
    if (front == 0)         // if queue is empty
        front = add;       
    else
        rear->next = add;   // else place at rear
    rear = add;             // have rear point to new node
    return true;
}

template <class Item>
bool QueueTP<Item>::dequeue(Item& item)
{
    if (front == 0)
        return false;
    item = front->item;    // set item to first item in queue
    items--;
    Node* temp = front;    // save location of first item
    front = front->next;   // reset front to next item
    delete temp;           // delete former first item
    if (items == 0)
        rear = 0;
    return true;
}
