

# 相关链接	
+ [compiler_support](https://en.cppreference.com/w/cpp/compiler_support)
+ [cpp_new_features](https://github.com/0voice/cpp_new_features.git)        
+ [cpp-learning](https://github.com/chengxumiaodaren/cpp-learning.git)  
+ [csdn_cpp](https://blog.csdn.net/qq_41854911/article/details/119657617)

# C++历史总览
+ C++98是最初的C++标准，它引入了许多新的功能，包括命名空间、模板、异常处理、RTTI（运行时类型识别）等。C++98还包括了C++的基本语法和语义，如类、继承、多态、虚函数等。
+ C++03是对C++98标准的修订版，它主要是对C++98标准的一些错误和模糊之处进行了澄清和修正，没有引入新的功能。
+ C++11是C++标准的一个重大更新，它引入了许多新的功能，包括自动类型推导、Lambda表达式、右值引用、智能指针、可变参数模板等。C++11还改进了C++的性能和可移植性，包括多线程支持、原子操作、内存模型等。
+ C++14是对C++11标准的修订版，它主要是对C++11标准的一些错误和模糊之处进行了澄清和修正，没有引入新的功能。
+ C++17是C++标准的又一次重大更新，它引入了许多新的功能，包括结构化绑定、if constexpr、折叠表达式、内联变量、文件系统库等。C++17还改进了C++的性能和可移植性，包括并行算法、内存模型、constexpr函数等。
+ C++20是C++标准的又一次重大更新（四大金刚：Concepts，Modules，Ranges，Coroutines），它引入了许多新的功能，包括概念、协程、三向比较运算符、模块化编程等。C++20还改进了C++的性能和可移植性，包括多线程、内存模型、constexpr函数等。
+ C++23是C++标准注定会主要给C++20修bug，从而会是一个比较小的发行版，它将引入许多新的功能，包括范围语法、反射、模板元编程、协程等。C++23还将改进C++的性能和可移植性，包括多线程、内存模型、constexpr函数等。

## 备注
+ 经过一段C++书籍的学习，学到了很多之前未接触到的知识点，但存在一个问题，每本书籍存在交集并且各有侧重点，知识学起来比较杂乱无章，故而规划该C++标准学习路线：
+ C++历史需要考虑编译器与新标准问题（支持不同步）,从C++的历史脉络出发学习(C++11开始)，以github、知乎和C站等网站的优质文章为中心，从全局上把握知识点，对于难点辅之专业书籍深入扩展。

## C++11
[知乎链接](https://zhuanlan.zhihu.com/p/139515439)

+ auto & decltype 
+ 左值右值
+ 纯右值：运算表达式产生的临时变量、不和对象关联的原始字面量、非引用返回的临时变量、lambda表达式等都是纯右值
+ 将亡值：可以理解为即将要销毁的值
+ 左值引用：对左值进行引用的类型
+ 右值引用：对右值进行引用的类型
+ 移动语义：转移资源所有权，类似于转让或者资源窃取的意思，对于那块资源，转为自己所拥有，别人不再拥有也不会再使用
+ 完美转发：可以写一个接受任意实参的函数模板，并转发到其它函数，目标函数会收到与转发函数完全相同的实参
+ 返回值优化：当函数需要返回一个对象实例时候，就会创建一个临时对象并通过复制构造函数将目标对象复制到临时对象，这里有复制构造函数和析构函数会被多余的调用到，有代价，而通过返回值优化，C++标准允许省略调用这些复制构造函数。
+ 列表初始化
+ std::function & std::bind & lambda表达式
+ 模板的改进
+ 模板的右尖括号
+ 模板的别名
+ 函数模板的默认模板参数
+ 并发
+ 智能指针
+ 基于范围的for循环
+ 委托构造函数 (同一个类中一个构造函数调用另外一个构造函数)
+ 继承构造函数 (可以让派生类直接使用基类的构造函数)
+ nullptr
+ final & override
+ default & delete & explicit
+ const
+ constexpr (用于编译时的常量和常量函数)
+ enum class
+ 非受限联合体
+ static_assert(true/false, message);
+ 自定义字面量
+ thread_local
+ 基础数值类型
+ random
+ 正则表达式 <regex>
+chrono  (源于boost)
+ 新增数据结构
	+ std::forward_list：单向链表，只可以前进，在特定场景下使用，相比于std::list节省了内存，提高了性能
	+ std::unordered_set：基于hash表实现的set，内部不会排序，使用方法和set类似
	+ std::unordered_map：基于hash表实现的map，内部不会排序，使用方法和set类似
	+ std::array：数组，在越界访问时抛出异常，建议使用std::array替代普通的数组
	+ std::tuple：元组类型，类似pair，但比pair扩展性好
+ 新增算法
	+ all_of：检测表达式是否对范围[first, last)中所有元素都返回true，如果都满足，则返回true ***
	+ any_of：检测表达式是否对范围[first, last)中至少一个元素返回true
	+ none_of：检测表达式是否对范围[first, last)中所有元素都不返回true
	+ find_if_not：找到第一个不符合要求的元素迭代器，和find_if相反
	+ copy_if：复制满足条件的元素
	+ iota：对容器内的元素按序递增 ***
	+ minmax_element：返回容器内最大元素和最小元素位置
	+ is_sorted、is_sorted_until：返回容器内元素是否已经排好序


## C++14	
[知乎链接](https://zhuanlan.zhihu.com/p/165389083)
                        
### 类型支持（基本类型、RTTI、类型特性）
+ type_traits
	+ std::nullptr_t
	+ is_final
+ utility
	+ exchange(将实参替换为一个新值，并返回其先前值)
	+ integer_sequence(实现编译时整数数列)
+ initializer_list
	+ rbegin
	+ crbegin
	+ rend
	+ crend
+ namespace
	+ make_reverse_iterator(创建拥有从实参推出的类型的 std::reverse_iterator)
+ vector
	+ begin
	+ cbegin-----const_iterator
	+ rbegin-----reverse_iterator
	+ crbegin----const_reverse_iterator
	+ end
	+ cend
	+ rend
	+ crend
### 主要新特性
+ 函数返回值类型推导 
+ lambda参数auto
+ 变量模板
+ 别名模板
+ constexpr的限制放宽
+ [[deprecated]]标记（过时，废弃）
+ 二进制字面量与整形字面量分隔符
+ std::make_unique
+ std::shared_timed_mutex与std::shared_lock
+ std::integer_sequence
+ std::exchange
+ std::quoted


## C++17
[知乎链接](https://zhuanlan.zhihu.com/p/165640868)

+ 关键字
	+ register
+ 构造函数模板推导
+ 结构化绑定
+ if-switch语句初始化
+ 内联变量
+ 折叠表达式
+ constexpr lambda表达式
+ namespace嵌套
+ __has_include预处理表达式
+ 在lambda表达式用*this捕获对象副本
+ 新增Attribute
+ 字符串转换<charconv>
	+ to_chars(转换整数或浮点值到字符序列象)
	+ from_chars(转换字符序列到整数或浮点值)
	+ chars_format(指定 std::to_chars 和 std::from_chars 所用的格式)
+ <type_traits>
	+ byte(字节类型)
+ variant
	+ variant(类型安全的可辨识联合体)
	+ visit(以一或多个 variant 所保有的各实参调用所提供的函数对象)
	+ holds_alternative(检查某个 variant 是否当前持有某个给定类型)
	+ std::get(std::variant)(以给定索引或类型（若类型唯一）读取 variant 的值，错误时抛出异常)
	+ get_if(以给定索引或类型（若其唯一），获得指向被指向的 variant 的值的指针，错误时返回空指针)
	+ std::swap(std::variant)(特化 std::swap 算法)
	+ monostate(用作非可默认构造类型的 variant 的首个可选项的占位符类型)
	+ bad_variant_access(非法地访问 variant 的值时抛出的异常)
	+ variant_size(在编译时获得 variant 可选项列表的大小)
	+ variant_size_v(在编译时获得 variant 可选项列表的大小)
	+ variant_alternative(在编译时获得以其下标指定的可选项的类型)
	+ variant_alternative_t(在编译时获得以其下标指定的可选项的类型)
	+ std::hash<std::variant>(特化 std::hash 算法)
	+ variant_npos(非法状态的 variant 的下标)
+ optional
	+ optional(可能或可能不保有一个对象的包装器)
	+ make_optional(创建一个 optional 对象)
	+ std::swap(std::optional)(特化 std::swap 算法)
	+ std::hash<std::optional>(特化 std::hash 算法)
	+ nullopt_t(带未初始化状态的 optional 类型的指示器)
	+ bad_optional_access(指示进行了到不含值的 optional 的有检查访问的异常)
	+ nullopt(nullopt_t 类型对象)
+ any
	+ any(可保有任何可复制构造 (CopyConstructible) 类型的实例的对象)
	+ std::swap(std::any)(特化 std::swap 算法)
	+ any_cast(对被容纳对象的类型安全访问)
	+ make_any(创建 any 对象)
	+ bad_any_cast(当类型不匹配时按值返回形式的 any_cast 所抛出的异常)
+ apply
+ tuple
	+ apply(以一个实参的元组来调用函数)
	+ make_from_tuple(以一个实参元组构造对象) 
+ utility
	+ as_const(获得到其实参的 const 引用)
+ string_view
+ file_system
+ shared_mutex
+ initializer_list
	+ empty(检查容器是否为空)
	+ data(获得指向底层数组的指针)
+ map
+ unordered_map
	+ insert_or_assign(插入元素，或若键已存在则赋值给当前元素)
	+ try_emplace(若键不存在则原位插入，若键存在则不做任何事)
	+ extract(从另一容器释出结点)
	+ merge(从另一容器接合结点)


## C++20
[知乎链接](https://zhuanlan.zhihu.com/p/137646370)

+ 新增关键字 keywords
	+ concept
	+ requires
	+ constinit
	+ consteval
	+ co_await
	+ co_return
	+ co_yield
	+ char8_t
+ 新增标识符 Identifies
        + import
        + export
        + module
+ 模块 Modules
+ Ranges
+ coroutine
	+ coroutine_traits(用于发现协程承诺类型的特征类型)
	+ coroutine_handle(用于指代暂停或执行的协程)
	+ noop_coroutine(创建在等待或销毁时无操作的协程柄)
	+ noop_coroutine_promise(用于无可观察作用的协程)
	+ noop_coroutine_handle(std::coroutine_handle<std::noop_coroutine_promise> ，有意用于指代无操作协程)
	+ suspend_never(指示 await 表达式应该决不暂停)
	+ suspend_always(指示 await 表达式应该始终暂停)
+ concepts
	+ ranges::swap(交换两个对象的值)
	+ same_as(指定一个类型与另一类型相同)
	+ derived_from(指定一个类型派生自另一类型)
	+ convertible_to(指定一个类型能隐式转换成另一类型)
+ Lambda 的更新
	+ [=, this] 需要显式捕获this变量
	+ 模板形式的 Lambda 表达式
	+ Lambda 表达式打包捕获(Pack Expansion)
+ constexpr 的更新
+ 原子(Atomic)智能指针
+ 自动合流(Joining), 可中断(Cancellable) 的线程
+ 同步(Synchronization)库
	+ std::atomic_ref
+ 指定初始化(Designated Initializers)
+ 航天飞机操作符 <=>
+ 范围 for 循环语句支持初始化
+ 非类型模板形参支持字符串
+ [[likely]], [[unlikely]]
+ 日历 Calendar 和时区 Timezone 功能
+ span
	+ begin
	+ end
	+ rbegin
	+ rend
	+ front
	+ back
	+ dynamic_extent(size_t 类型常量，指明 span 拥有动态长度)
+ 特性测试宏
+ version
+ consteval 函数
+ constinit
+ 用 using 引用 enum 类型
+ 格式化库(std::format)
+ 增加数学常量
+ std::source_location
+ [[nodiscard(reason)]]
+ 位运算
+ type_traits
	+ is_bounded_array(检查类型是否为有已知边界的数组类型)
	+ is_unbounded_array(检查类型是否为有未知边界的数组类型)
	+ is_layout_compatible(检查二个类型是否布局兼容)
	+ is_pointer_interconvertible_base_of(检查一个类型是否为另一类型的指针可互转换（起始）基类)
	+ is_pointer_interconvertible_with_class(检查一个类型的对象是否与该类型的指定子对象指针可互转换)
	+ is_corresponding_member(检查二个指定成员是否在二个指定类型中的公共起始序列中彼此对应)
	+ is_nothrow_convertible(检查是否能转换一个类型为另一类型)
	+ remove_cvref(将 std::remove_cv 与 std::remove_reference 结合)
	+ type_identity(返回不更改的类型实参)
	+ is_constant_evaluated(检测调用是否在常量求值的语境内发生)
+ compare
	+ std::coroutine_traits
	+ std::coroutine_handle
	+ three_way_comparable(指定运算符 <=> 在给定类型上产生一致的结果)
	+ three_way_comparable_with(指定运算符 <=> 在给定类型上产生一致的结果)
	+ partial_ordering(三路比较的结果类型，支持所有 6 种运算符，不可替换，并允许不可比较的值)
	+ weak_ordering(三路比较的结果类型，支持所有 6 种运算符且不可替换)
	+ strong_ordering(三路比较的结果类型，支持所有 6 种运算符且可替换)
	+ is_eq
	+ is_neq
	+ is_lt
	+ is_lteq
	+ is_gt
	+ is_gteq
+ utility
	+ cmp_equal(比较二个整数值，而无转换所致的值更改)
	+ cmp_not_equal(比较二个整数值，而无转换所致的值更改)
	+ cmp_less(比较二个整数值，而无转换所致的值更改)
	+ cmp_less_equal(比较二个整数值，而无转换所致的值更改)
	+ cmp_greater_equal(比较二个整数值，而无转换所致的值更改)
	+ in_range(检查整数值是否在给定整数类型的范围内)
+ memory
	+ uninitialized_move(移动一个范围的对象到未初始化的内存区域)
	+ uninitialized_move_n(移动一定数量对象到未初始化内存区域)
	+ uninitialized_default_construct(在范围所定义的未初始化的内存区域以默认初始化构造对象)
	+ uninitialized_default_construct_n(在起始和计数所定义的未初始化内存区域用默认初始化构造对象)
	+ uninitialized_value_construct(在范围所定义的未初始化内存中用值初始化构造对象)
	+ uninitialized_value_construct_n(在起始和计数所定义的未初始化内存区域以值初始化构造对象)
	+ destroy_at(销毁在给定地址的对象)
	+ destroy(销毁一个范围中的对象)
	+ destroy_n(销毁范围中一定数量的对象)                                     
+ chrono
	+ is_clock(确定类型是否为时钟)
	+ is_clock_v(确定类型是否为时钟)
	+ utc_clock(协调世界时 (UTC) 的时钟)
	+ tai_clock(国际原子时 (TAI) 的时钟)
	+ gps_clock(GPS 时间的时钟 (Clock))
	+ file_clock(用于文件时间的时钟 (Clock))
	+ local_t(表示本地时间的伪时钟)
	+ clock_time_conversion(定义如何转换一个时钟的时间点为另一个的特性类)
	+ clock_cast(转换一个时钟的时间点为另一个)
	+ time_of_day(表示一日中的时间)
+ string、string_view
	+ starts_with(检查 string 是否始于给定前缀)
	+ ends_with(检查 string 是否终于给定后缀)
+ cuchar
	+ mbrtoc8(转换窄多字节字符为 UTF-8 编码)
	+ c8rtomb(转换 UTF-8 字符串为窄多字节编码)
+ array
	+ to_array(从内建数组创建 std::array 对象)
+ vector
	+ erase(std::vector)(擦除所有满足特定判别标准的元素)
	+ erase_if(std::vector)(擦除所有满足特定判别标准的元素)
+ map、unordered_map
	+ contains(检查容器是否含有带特定键的元素)
	+ erase_if(std::map/unordered_map)(擦除所有满足特定判别标准的元素)
+ std::ranges
	+ iter_move(将解引用迭代器的结果转型为其关联的右值引用类型)
	+ iter_swap(交换两个可解引用对象所引用的值)                                    
	+ ranges::advance(令迭代器前进给定的距离或到给定的边界)
	+ ranges::distance(返回迭代器与哨位间的距离，或范围起始与结尾间的距离)
	+ ranges::next(自增迭代器给定的距离或到边界)
	+ ranges::prev(自减迭代器给定的距离或到边界)	 
	+ ranges::begin(返回指向范围起始的迭代器)
	+ ranges::cbegin(返回指向只读范围起始的迭代器)
	+ ranges::end(返回指示范围结尾的哨位)
	+ ranges::cend(返回指示只读范围结尾的哨位)
	+ ranges::rbegin(返回指向范围的逆向迭代器)
	+ ranges::crbegin(返回指向只读范围的逆向迭代器)
	+ ranges::rend(返回指向范围的逆向尾迭代器)
	+ ranges::crend(返回指向只读范围的逆向尾迭代器)
	+ ranges::size(获得能在常数时间内计算大小的范围的大小)
	+ ranges::ssize(获得能在常数时间内计算大小的范围的大小，并将它转换成有符号整数)
	+ ranges::empty(检查范围是否为空)
	+ ranges::data(获得指向连续范围的起始的指针)
	+ ranges::cdata(获得指向只读连续范围的起始的指针)              

	
## C++23
[知乎链接上篇](https://zhuanlan.zhihu.com/p/562383157)    
[知乎链接下篇](https://zhuanlan.zhihu.com/p/562383556) 

### 类型支持（基本类型、RTTI、类型特性）
+ type_traits
	+ is_scoped_enum(检查类型是否为有作用域枚举类型)
+ utility
	+ to_underlying(转换枚举到其底层类型)
+ stacktrace
	+ stacktrace_entry(栈踪中求值的表示)
	+ basic_stacktrace(由栈踪条目组成的调用序列的近似表示)
### 动态内存管理
+ memory
	+ out_ptr_t(与外来指针设置器交互，并在析构时重设智能指针)
	+ out_ptr(以关联的智能指针和重设参数创建 out_ptr_t)
	+ inout_ptr_t(与外来指针设置器交互，从智能指针获得初始指针值，并在析构时重设它)
	+ inout_ptr(以关联的智能指针和重设参数创建 inout_ptr_t)
	+ allocation_result(记录由 allocate_at_least 分配的存储的地址与实际大小)
	+ allocate_at_least(经由分配器分配至少与请求的大小一样大的存储)
### 字符串
+ string
	+ contains(检查字符串是否含有给定的子串或字符)
+ string_view
	+ contains(检查字符串视图是否含有给定的子串或字符)







            


