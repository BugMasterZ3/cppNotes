
// 第1章，关于对象(Object Lessons)
// C++在布局以及存取时间上主要的额外负担是由virtual引起
// 如果struct关键词的使用实现了C的数据萃取观念，而class关键词实现的是C++的ADT观念（封装继承哲学,组合composition struct）
// 只有通过pointer或reference的间接处理，才支持OO程序设计所需的多态性质
// 多态的主要用途是经由一个共同的接口来影响类型的封装，这个接口通常被定义在一个抽象的base class中
// 补充扩展：Curiously Recurring Template Pattern (CRTP)：用于实现编译时多态性，此模式允许创建静态多态性，与依赖虚拟函数和继承的常规运行时多态性不同,不增加虚拟函数调用的开销,无需运行时性能成本
  template <typename Derived>
  class Base 
  {
  public:
      void interface() { static_cast<Derived*>(this)->implementation(); }
      void implementation() { std::cout << "Default implementation in Base" << std::endl; }
  };
  
  class Derived1 : public Base<Derived1>
  {
  public:
      void implementation() { std::cout << "Custom implementation in Derived1" << std::endl; }
  };
  
  class Derived2 : public Base<Derived2> 
  {
      // No custom implementation, so Base::implementation will be used.
  };


// 第2章，构造函数语意学(The Semantics of Constructors)
// nontrivial （implicit） default constructor
  // 带有Default Constructor的Member Class Object（编译器会安插码，自动扩张操作已存在的成员类的constructors，但所有其它的nonstatic data member不会被初始化）
  // 带有Default Constructor的Base Class
  // 带有一个Virtual Function的Class
  // 带有一个Virtual Base Class的Class
// Copy constructor(Default Memberwise Initialization)
// 不展现/失效的Bitwise Copy Semantics（位逐次拷贝，直接简单复制创建副本）
  // 当内含一个带有copy constructor的Member Object时，编译器会合成一个default copy constructors，并且所有其它的nonclass members也都会被复制
  // 当class继承自一个带有copy constructor的base class时(不论是被明确声明或是被合成而得)
  // 当class声明了一个或多个virtual functions时（切割问题）
  // 当class派生自一个继承串链，其中有一个或多个virtual base classes时（多态问题）


// 第3章，Data语意学(The Semantics of Data)

// 第4章，Function语意学(The Semantics of Function)

// 第5章，构造、解构、拷贝语意学(Semantics of Construction,Destruction,and Copy)

// 第6章，执行期语意学(Runtime Semantics),检视执行期的某些对象模型行为，包括临时对象的生命及其死亡，以及对new运算符和delete运算符的支持

// 第7章，在对象模型的尖端(On the Cusp of the Object Model),专注于exception handling、template support、runtime type identification
// RTTI
Base* base_ptr = new Derived1;
Derived1* derived1_ptr = dynamic_cast<Derived1*>(base_ptr);  // cast successfully
Derived2* derived2_ptr = dynamic_cast<Derived2*>(base_ptr);  // cast failed




