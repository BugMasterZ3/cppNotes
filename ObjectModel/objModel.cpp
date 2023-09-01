
// 第1章，关于对象(Object Lessons)
// C++在布局以及存取时间上主要的额外负担是由virtual引起
// 如果struct关键词的使用实现了C的数据萃取观念，而class关键词实现的是C++的ADT观念（封装继承哲学,组合composition struct）
// 只有通过pointer或reference的间接处理，才支持OO程序设计所需的多态性质
// 多态的主要用途是经由一个共同的接口来影响类型的封装，这个接口通常被定义在一个抽象的base class中

// 第2章，构造函数语意学(The Semantics of Constructors)

// 第3章，Data语意学(The Semantics of Data)

// 第4章，Function语意学(The Semantics of Function)

// 第5章，构造、解构、拷贝语意学(Semantics of Construction,Destruction,and Copy)

// 第6章，执行期语意学(Runtime Semantics),检视执行期的某些对象模型行为，包括临时对象的生命及其死亡，以及对new运算符和delete运算符的支持

// 第7章，在对象模型的尖端(On the Cusp of the Object Model),专注于exception handling、template support、runtime type identification
// RTTI
Base* base_ptr = new Derived1;
Derived1* derived1_ptr = dynamic_cast<Derived1*>(base_ptr);  // cast successfully
Derived2* derived2_ptr = dynamic_cast<Derived2*>(base_ptr);  // cast failed




