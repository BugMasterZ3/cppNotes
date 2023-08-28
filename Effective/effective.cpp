

/**************************************effictive*******************************/
// 一、Contents (DialyLog):
// 优秀的异常设计(客户端操作/非析构函数 + 析构函数捕获(失败将回到终止或吞咽))
// 派生类与基类转换问题(显式与隐式(dynamic_cast横/侧向转换规则)、指针与引用、智能指针)
// RAII资源管理类(智能指针+析构释放)：api访问原始资源(显式转换更安全，隐式转换更方便客户端)
// 引用传递机制(切割问题)
// 延后变量定义至明显意义初值，避免无意义默认构造
// 模板代码膨胀问题及解决方案、编译依存性
// 遮掩继承条款
// 区分接口继承与实现继承(pure/impure/non_virtual,NVI手法)
// 深入了解non_virtual函数(不要重新定义)
// 静态绑定与动态绑定
// classes(显式接口+运行期多态)、templates(隐式接口+编译期多态)
// 整合重载技术使在编译期间执行if...else测试
// 模板元编程(结构体递归求阶乘)

typedef void (*new_handler)();
new_handler set_new_handler(new handler p)	throw ();	//返回函数的函数

// 二、易错点归纳：
// 尽量使用const、enum、inline等代替#define，因为#define可能会导致一些不可预期的问题，比如符号重定义、类型不匹配等问题
// 构造函数的实参可以通过隐式类型转换来匹配对应的形参类型。但如果构造函数的形参不是const引用类型，那么这种隐式类型转换可能会导致不必要的构造函数调用和内存分配
// 在函数声明中，应该尽量避免使用与内置类型等效的默认参数，因为这样可能会导致调用者意外地使用了不期望的默认参数值
// 了解默认的函数行为，包括默认构造函数、默认拷贝构造函数、默认赋值操作符和默认析构函数等
// 避免在析构函数中抛出异常，因为这可能会导致程序崩溃或者资源泄漏等问题
// 尽量将类的数据成员声明为私有，然后提供公共的成员函数来访问和修改这些数据成员
// 在函数中尽量使用const来修饰参数和返回值，以便更好地表明函数的行为和语义
// 了解C++对象模型，包括虚函数表、多重继承、虚继承等概念
// 在重载运算符时遵循约定，以便更好地表达运算符的语义和行为
// 避免将异常传递到边界，因为这可能会导致程序崩溃或者资源泄漏等问题

// 三、难点归纳：
// 对象的构造和析构：需要深入理解对象的生命周期和管理内存的技巧
// 拷贝控制：包括拷贝构造函数、赋值操作符和析构函数，需要理解拷贝控制的概念和实现方式，以便更好地管理对象的拷贝和销毁
// 类继承和多态：面向对象编程的核心概念，需要深入理解虚函数、虚继承、多重继承等概念
// 模板编程：需要深入理解模板的概念和使用方法，以便编写出具有高度通用性和可重用性的代码
// 异常处理：需要理解异常的概念和处理方式，以便编写出具有高度健壮性和可靠性的代码
// 运算符重载：需要掌握正确使用运算符重载的方式，以便更好地表达运算符的语义和行为
// STL和泛型编程：需要熟练掌握STL中的容器、算法和迭代器等概念和使用方法，以便编写出高效、可维护和可重用的代码



/*****************************more effective**************************************/
// 当知道必须指向一个对象并且不想改变其指向时，或者在重载操作符并为防止不必要的语义误解时，不应该使用指针
// 让编译器进行隐式类型转换所造成的弊端要大于它所带来的好处，所以除非确实需要，不要定义类型转换函数

/** 异常**/
// 智能指针在捕获异常上的优越性，资源应该被封装在一个对象里，遵循这个规则通常就能避免在存在异常环境里发生资源泄漏
// C++仅仅能删除被完全构造的对象(new操作可能没有成功完成)
class BookEntry { 
public:   
	...                                      
private:   
	...   
	const auto_ptr<Image> theImage;          // auto_ptr 对象 
	const auto_ptr<AudioClip> theAudioClip;  
};

BookEntry::BookEntry(const string& name, const string& address, const string& imageFileName, const string& audioClipFileName) 
	: theName(name), theAddress(address), 
	theImage(mageFileName != "" ? new Image(imageFileName) : 0), 
	theAudioClip(audioClipFileName != "" ? new AudioClip(audioClipFileName) : 0) 
{   
}	

BookEntry::~BookEntry() {}    //// 用对应的智能指针对象替代指针成员变量，就可以防止构造函数在存在异常时发生资源泄漏，同时不用手工在析构函数中释放资源

// 禁止异常传递到析构函数外有两个原因：
// 	第一能够在异常转递的堆栈辗转开解（stack-unwinding）的过程中，防止 terminate 被调用
// 	第二它能帮助确保析构函数总能完成我们希望它做的所有事情
// 异常对象被拷贝时，拷贝构造函数是对象的静态类型所对应类的拷贝构造函数而非对象的动态类型对应类的拷贝构造函数
// 异常生成的拷贝是一个临时对象（临时对象能让编译器优化它的生存期）
catch (const void*) ...              //捕获任何指针类型异常  

try { ... } 				// 调用一个虚拟函数
catch (invalid_argument& ex) { ... }    // 处理 invalid_argument   
catch (logic_error& ex) { ... }         // 处理所有其它的logic_errors 异常 

// 一个对象传递给函数或一个对象调用虚拟函数与把一个对象做为异常抛出，这之间有三个主要区别:
// 	1. 异常对象在传递时总被进行拷贝；当通过传值方式捕获时，异常对象被拷贝了两次。对象做为参数传递给函数时不一定需要被拷贝
// 	2. 对象做为异常被抛出与做为参数传递给函数相比，前者类型转换比后者要少（前者只有两种转换形式）
// 	3. catch 子句进行异常类型匹配的顺序是它们在源代码中出现的顺序，第一个类型匹配成功的 catch 将被用来执行。
// 当一个对象调用一个虚拟函数时，被选择的函数位于与对象类型匹配最佳的类里，即使该类不是在源代码的最前头

// 通过引用（reference）捕获异常
// 四个标准的异常：
// bad_alloc	当 operator new(参见条款 M8)不能分配足够的内存时，被抛出
// bad_cast	当 dynamic_cast 针对一个引用（reference）操作失败时，被抛出
// bad_typeid	当 dynamic_cast 对空指针进行操作时，被抛出
// bad_exception用于 unexpected 异常

//编译器允许调用一个函数，其抛出的异常与发出调用的函数的异常规格不一致
void f2() throw(int) 
{   
	...   
	f1();  // 即使 f1 可能抛出不是 int 类型的异常，这也是合法的
	... 
} 

// 避免调用 unexpected 函数:
// 	1.模板和异常规格不要混合使用
// 	2.在一个函数内调用其它没有异常规格的函数时应该去除这个函数的异常规格
// 	3.处理系统本身抛出的异常
// 为了使你的异常开销最小化，尽量采用不支持异常的方法编译程序，并且只有在确为异常的情况下才抛出异常


/**效率**/
// 惰性求值的本质——计算被推迟到实际需要值的时候
// 如果一个计算需要频繁进行，可设计一个数据结构高效地处理这些计算需求，这样可以降低每次计算需求时的开销
// 在任何时候只要见到常量引用参数，就存在建立临时对象而绑定在参数上的可能性
// 在任何时候只要见到函数返回对象，就会有一个临时对象被建立（以后被释放）
// 通过把函数声明为 inline 来消除 operator*的调用开销
// 通过重载避免隐式类型转换：没有必要实现大量的重载函数，除非你有理由确信程序使用重载函数以后其整体效率会有显著的提高
// 面对在命名对象和临时对象间进行选择时，用临时对象更好一些
// operator的赋值形式（operator+=）比单独形式(operator+)效率更高
// 理解虚拟函数、多继承、虚基类和 RTTI 所需的代价
// 限制某个类所能产生的对象数量(构造函数私有化)
// 避免重载new等堆问题

// 灵巧指针应该谨慎使用,灵巧指针的实现、理解、调试和维护需要大量的技巧; 同时灵巧指针的使用在一些领域受到极大的限制，例如测试空值、转换到dumb 指针、继承类向基类转换和对指向 const 的指针的支持
// 了解指针引用与写时(深)拷贝(嵌套类继承引用计数类),总结引用计数在下列情况下对提高效率很有用：
// 	1.少量的值被大量的对象共享。对象/值的比例越高，越是适宜使用引用计数
// 	2.对象的值的创建和销毁代价很高昂，或它们占用大量的内存。
// 只有一个方法来确认这些条件是否满足，这个方法是使用 profiler 或其它工具来分析发现是否创建和销毁值的行为是性能瓶颈，并能得出对象/值的比例。只有当你手里有了这些数据，你才能得出是否从引用计数上得到的好处超过其缺点

class RCObject 	 // base class for reference-counted objects     
{                   
public:    
	void addReference() { ++refCount; }
	void removeReference() { if (--refCount == 0) delete this; }
	void markUnshareable() { shareable = false; } 
	bool isShareable() const { return shareable; }
	bool isShared() const { return refCount > 1; }
protected:   
	RCObject() : refCount(0), shareable(true) {}
	RCObject(const RCObject& rhs) : refCount(0), shareable(true) {}    
	RCObject& operator=(const RCObject& rhs) { return *this; }
	virtual ~RCObject() {} 	// = 0; 
private:   
	int refCount;   
	bool shareable;
}; 
// 假设能够访问有关类的源码
template<class T>     // template class for smart pointers-to-T objects; T must inherit from RCObject  
class RCPtr
{                          	 	
public:     
	RCPtr(T* realPtr = 0) : pointee(realPtr) { init(); }
	RCPtr(const RCPtr& rhs) : pointee(rhs.pointee) { init(); } 
	~RCPtr() { if (pointee) pointee->removeReference(); }  

	RCPtr& operator=(const RCPtr& rhs)
	{   
		if (pointee != rhs.pointee) 
		{     
			if (pointee) pointee->removeReference();     
			pointee = rhs.pointee;     
			init();   
		} 
		return *this; 
	} 
	T* operator->() const { return pointee; }   
	T& operator*() constt { return *pointee; }
private:  
	T *pointee;  
	void init()
	{   
		if (pointee == 0) return;   
		if (pointee->isShareable() == false) 
		{     
			pointee = new T(*pointee);   
		} 
  		pointee->addReference(); 
	}
};

class String 	 // class to be used by application developers 
{                           
public: 
	String(const char *initValue = "") : value(new StringValue(initValue)) {}
	const char& operator[](int index) const { return value->data[index]; } 
	char& operator[](int index)
	{   
		if (value->isShared()) 
		{     
			value = new StringValue(value->data);   
		}   
		value->markUnshareable();   
		return value->data[index]; 
	} 
private:  
	// class representing string values   
	struct StringValue: public RCObject 
	{     
		char *data;  
		void init(const char *initValue)
		{   
			data = new char[strlen(initValue) + 1];   
			strcpy(data, initValue); 
		}
		StringValue(const char *initValue) { init(initValue); }      
		StringValue(const StringValue& rhs) { init(rhs.data); } 
		~StringValue() { delete [] data; } 
	};   
	RCPtr<StringValue> value; 
};
// 在现存类上增加引用计数(将引用计数加到任意类型上)
template<class T>     // template class for smart pointers-to-T objects; T must inherit from RCObject  
class RCIPtr
{                          	 	
public:     
	RCIPtr(T* realPtr = 0) :counter(new CountHolder) {   counter->pointee = realPtr; init(); }
	RCIPtr(const RCPtr& rhs) : counter(rhs.counter)  { init(); } 
	~RCIPtr() { counter->removeReference(); }  

	RCIPtr& operator=(const RCIPtr& rhs)
	{   
		if (counter != rhs.counter) 
		{     
			counter->removeReference();     
			counter = rhs.counter;     
			init();  
		}
		return *this; 
	} 
	const T* operator->() const { return counter->pointee; }   
	T* operator->() { makeCopy(); return counter->pointee; }
	const T& operator*() const { return *(counter->pointee); }
	T& operator*() { makeCopy(); return *(counter->pointee); }
private:  
	struct CountHolder: public RCObject
	{     
		~CountHolder() { delete pointee; }     
		T *pointee;  
	};

	CountHolder *counter;

	void init()
	{   
		if (counter->isShareable() == false) 
		{    
			T *oldValue = counter->pointee;     
			counter = new CountHolder;     
			counter->pointee = new T(*oldValue);   
		}   
		counter->addReference();
	}
	void makeCopy()
	{                                
		if (counter->isShared()) 
		{     
			T *oldValue = counter->pointee;     
			counter->removeReference();     
			counter = new CountHolder;     
			counter->pointee = new T(*oldValue);     
			counter->addReference();  
		} 
	}
};

class Widget 
{ 
public:  
	Widget(int size);   
	Widget(const Widget& rhs);   
	~Widget(); 

	Widget& operator=(const Widget& rhs);   
	void doThis();   
	int showThat() const; 
};
class RCWidget 
{ 
public:   
	RCWidget(int size): value(new Widget(size)) {}   
	void doThis() { value->doThis(); }   
	int showThat() const { return value->showThat(); } 
private:   
	RCIPtr<Widget> value; 
}; 


/*****************************modern effective************************************/
// auto无法推导出整个模板T，但可以推导出std::initializer_list<T>,
// C++14：decltype(auto) 	
// C++11：auto...->decltype(...)





/*****************************effective STL************************************/






