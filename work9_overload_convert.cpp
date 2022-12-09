

#include <iostream>
using namespace std;

class Time
{
private:
    int hours;
    int minutes;
public:
    Time();
    Time(int h, int m = 0);
    void AddMin(int m);
    void AddHr(int h);
    void Reset(int h = 0, int m = 0);
    Time operator+(const Time& t) const;    // = () [] -> ֻ��ͨ����Ա��������(�����ǵ�һ��������)
    Time operator-(const Time& t) const;
    Time operator*(double n) const;
    void Show() const;
    friend Time operator*(double m, const Time& t)   //��Ԫ����ʹ������Բ��ǵ�һ��������
    {
        return t * m;
    }
    friend std::ostream& operator<<(std::ostream& os, const Time& t);   //��Ԫ�������� << , ֱ���������show()
};

std::ostream& operator<<(std::ostream& os, const Time& t)   //���岻��Ҫfriend, os��cout�ı���
{
    os << t.hours << " hours, " << t.minutes << " minutes";
    return os;  //����iostream����֤�������
}


class Stonewt
{
private:
    enum { Lbs_per_stn = 14 };      // ��ÿӢʯ static const int ...;
    int stone;
    double pds_left;                // ʣ���   
    double pounds;
public:
    Stonewt(double lbs);           // ������캯����
    Stonewt(int stn, double lbs);
    Stonewt();
    ~Stonewt();
    void show_lbs() const;
    void show_stn() const;
    //ת������,����pounds(û�в����ͷ���ֵ���������෽��)
    operator double() const;
    explicit operator int() const; //explicit������ʾֻ������ʽǿ������ת��
    // �� int Stonewt::Stone_to_int() { return int(pounds + 0.5)}

    //ת����������Ԫ��������������
    //��Ա����������С������������ʽת����ÿ��ת�������ת�����캯��������ʱ���ڴ濪��
    //��Ԫ�������򳤣��������ٶȿ죬����ƥ���������
};

void display(const Stonewt& st, int n)
{
    for (int i = 0; i < n; i++)
    {
        st.show_stn();
    }
}


int main()
{
    using std::cout;
    using std::endl;

    //ʱ���ܼ�
    Time t1(2, 40);
    Time t2(5, 55);
    Time t3(3, 28);
    Time total;
    total = t1 + t2;
    total.Show();   // 8 hours, 35 minutes
    total = t3.operator+(total);
    total.Show();   // 12 hours, 3 minutes
    total = t1 + t2 + t3;   // t1.operator+(t2+t3) --> t1.operator+(t2.operator+(t3))
    total.Show();   // 12 hours, 3 minutes 
    total = total - t3;
    total.Show();   // 8 hours, 35 minutes
    total = total * 2;      // ����д�� 2*diff  
    total.Show();// 17 hours, 10 minutes
    total = 5.0 * t1;       //��Ԫ
    cout << "5.0 * t1: " << total << endl;  // 13 hours, 20 minutes  <<����


    //����Ӣʯת��
    Stonewt incognito = 275;
    Stonewt wolfe(285.7);    // wolfe = 285.7;
    Stonewt taft(21, 8);
    incognito.show_stn();   // 19 stone, 9 pounds
    wolfe.show_stn();       // 20 stone, 5.7 pounds
    taft.show_lbs();        // 302 pounds
    incognito = 276.8;
    taft = 325;             // taft = Stonewt(325);  intתdouble
    incognito.show_stn();   // 19 stone, 10.8 pounds
    taft.show_lbs();        // 325 pounds
    display(taft, 2);       // 23 stone, 3 pounds

    display(422, 2);             // 30 stone, 2 pounds   intתdouble-->Stonewt(double)תStonewt������ֵת����
    Stonewt poppins(9, 2.8);     // 9 stone, 2.8 pounds
    //cout << poppins << endl;   // ֻ����һ��ת������ʱ����ͨ������,����ת����������������ת��
    double p_wt = poppins;       // 128.8 ��ʽת��(����ʹ�ã����׳����⣬arr[poppins(14,4)])     
    //long p_wt = poppins;       // ������ ambiguous
    long gone1 = (double)poppins;// 128 ��ʽת����ǿת��
    long gone2 = int(poppins);   // 129

    return 0;
}


//ʱ���෽��
Time::Time()
{
    hours = minutes = 0;
}

Time::Time(int h, int m)
{
    hours = h;
    minutes = m;
}

void Time::AddMin(int m)
{
    minutes += m;
    hours += minutes / 60;
    minutes %= 60;
}

void Time::AddHr(int h)
{
    hours += h;
}

void Time::Reset(int h, int m)
{
    hours = h;
    minutes = m;
}

Time Time::operator+(const Time& t) const
{
    Time sum;
    sum.minutes = minutes + t.minutes;
    sum.hours = hours + t.hours + sum.minutes / 60;
    sum.minutes %= 60;
    return sum;
}

Time Time::operator-(const Time& t) const
{
    Time total;
    int tot1, tot2;
    tot1 = t.minutes + 60 * t.hours;
    tot2 = minutes + 60 * hours;
    total.minutes = (tot2 - tot1) % 60;
    total.hours = (tot2 - tot1) / 60;
    return total;
}

Time Time::operator*(double mult) const
{
    Time result;
    long totalminutes = hours * mult * 60 + minutes * mult;
    result.hours = totalminutes / 60;
    result.minutes = totalminutes % 60;
    return result;
}

void Time::Show() const
{
    std::cout << hours << " hours, " << minutes << " minutes" << std::endl;
}

//���෽��
Stonewt::Stonewt(double lbs)
{
    stone = int(lbs) / Lbs_per_stn;    // integer division
    pds_left = int(lbs) % Lbs_per_stn + lbs - int(lbs);
    pounds = lbs;
}

Stonewt::Stonewt(int stn, double lbs)
{
    stone = stn;
    pds_left = lbs;
    pounds = stn * Lbs_per_stn + lbs;
}

Stonewt::Stonewt()          // default constructor, wt = 0
{
    stone = pounds = pds_left = 0;
}

Stonewt::~Stonewt()         // destructor
{
}

void Stonewt::show_stn() const
{
    cout << stone << " stone, " << pds_left << " pounds\n";
}

void Stonewt::show_lbs() const
{
    cout << pounds << " pounds\n";
}

Stonewt::operator int() const
{
    return int(pounds + 0.5);
}

Stonewt::operator double()const
{
    return pounds;
}