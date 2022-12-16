


#include <iostream>
#include <cstring>

//  Base Class Using DMA
class baseDMA
{
private:
    char* label;
    int rating;

public:
    baseDMA(const char* l = "null", int r = 0);
    baseDMA(const baseDMA& rs);
    virtual ~baseDMA();
    baseDMA& operator=(const baseDMA& rs);
    friend std::ostream& operator<<(std::ostream& os, const baseDMA& rs);
};

// derived class without DMA
// no destructor needed
// uses implicit copy constructor
// uses implicit assignment operator
class lacksDMA :public baseDMA
{
private:
    enum { COL_LEN = 40 };
    char color[COL_LEN];
public:
    lacksDMA(const char* c = "blank", const char* l = "null", int r = 0);
    lacksDMA(const char* c, const baseDMA& rs);
    friend std::ostream& operator<<(std::ostream& os, const lacksDMA& rs);
};

// derived class with DMA
class hasDMA :public baseDMA
{
private:
    char* style;
public:
    hasDMA(const char* s = "none", const char* l = "null", int r = 0);//派生new构造，需要析构函数
    hasDMA(const char* s, const baseDMA& rs);
    hasDMA(const hasDMA& hs);
    ~hasDMA();
    hasDMA& operator=(const hasDMA& rs);
    friend std::ostream& operator<<(std::ostream& os, const hasDMA& rs);
};


int main()
{
    using std::cout;
    using std::endl;

    baseDMA shirt("Portabelly", 8);
    lacksDMA balloon("red", "Blimpo", 4);
    hasDMA map("Mercator", "Buffalo Keys", 5);
    cout << shirt << endl;
    cout << balloon << endl;
    cout << map << endl;
    lacksDMA balloon2(balloon);
    cout << balloon2 << endl;
    hasDMA map2;
    map2 = map;
    cout << map2 << endl;

    return 0;
}


// baseDMA methods
baseDMA::baseDMA(const char* l, int r)
{
    label = new char[std::strlen(l) + 1];
    std::strcpy(label, l);
    rating = r;
}

baseDMA::baseDMA(const baseDMA& rs)
{
    label = new char[std::strlen(rs.label) + 1];
    std::strcpy(label, rs.label);
    rating = rs.rating;
}

baseDMA::~baseDMA()
{
    delete[] label;
}

baseDMA& baseDMA::operator=(const baseDMA& rs)
{
    if (this == &rs)
        return *this;
    delete[] label;
    label = new char[std::strlen(rs.label) + 1];
    std::strcpy(label, rs.label);
    rating = rs.rating;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const baseDMA& rs)
{
    os << "Label: " << rs.label << std::endl;
    os << "Rating: " << rs.rating << std::endl;
    return os;
}

// lacksDMA methods
lacksDMA::lacksDMA(const char* c, const char* l, int r) : baseDMA(l, r)
{
    std::strncpy(color, c, 39);
    color[39] = '\0';
}

lacksDMA::lacksDMA(const char* c, const baseDMA& rs) : baseDMA(rs)
{
    std::strncpy(color, c, COL_LEN - 1);
    color[COL_LEN - 1] = '\0';
}

std::ostream& operator<<(std::ostream& os, const lacksDMA& ls)
{
    os << (const baseDMA&)ls;
    os << "Color: " << ls.color << std::endl;
    return os;
}

// hasDMA methods
hasDMA::hasDMA(const char* s, const char* l, int r) : baseDMA(l, r)
{
    style = new char[std::strlen(s) + 1];
    std::strcpy(style, s);
}

hasDMA::hasDMA(const char* s, const baseDMA& rs) : baseDMA(rs)
{
    style = new char[std::strlen(s) + 1];
    std::strcpy(style, s);
}

hasDMA::hasDMA(const hasDMA& hs) : baseDMA(hs)  // invoke base class copy constructor
{
    style = new char[std::strlen(hs.style) + 1];
    std::strcpy(style, hs.style);
}

hasDMA::~hasDMA()
{
    delete[] style;
}

hasDMA& hasDMA::operator=(const hasDMA& hs)
{
    if (this == &hs)
        return *this;
    baseDMA::operator=(hs); //函数表示法，防止运算符表示法 *this = hs 陷入递归
    delete[] style;         // prepare for new style
    style = new char[std::strlen(hs.style) + 1];
    std::strcpy(style, hs.style);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const hasDMA& hs)
{
    os << (const baseDMA&)hs;   //友元函数不能使用::表示，强转访问基类成员,等价于dynamic_cast<const baseDMA&>(hs)
    os << "Style: " << hs.style << std::endl;
    return os;
}
