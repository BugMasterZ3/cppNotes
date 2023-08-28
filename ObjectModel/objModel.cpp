
// 第1章，关于对象(Object Lessons)

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




