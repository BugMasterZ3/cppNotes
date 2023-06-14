// C++历史需要考虑编译器与新标准问题（支持不同步）,C++ 编译器支持情况表链接：https://www.apiref.com/cpp-zh/cpp/compiler_support.html

/************************************************ C++ 98 ***************************************************/

/************************************************ C++ 11 ***************************************************/
新增关键字
thread_local
static_assert
nullptr
noexcept
decltype
constexpr
char16_t
char32_t
alignof
alignas
含义变化或者新增含义关键字
auto
class
default
delete
export
extern
inline
mutable
sizeof
struct
using
类型支持（基本类型、RTTI、类型特性）
Defined in header <type_traits>
is_void
is_integral
is_floating_point
is_array
is_enum
is_union
is_class
is_function
is_pointer
is_lvalue_reference
is_rvalue_reference
is_member_object_pointer
is_member_function_pointer
is_fundamental
is_arithmetic
is_scalar
is_object
is_compound
is_reference
is_member_pointer
is_const
is_volatile
is_trivial
is_trivially_copyable
is_standard_layout
is_literal_type
is_empty
is_polymorphic
is_abstract
is_signed
is_unsigned
is_constructible
is_trivially_constructible
is_nothrow_constructible
is_default_constructible
is_trivially_default_constructible
is_nothrow_default_constructible
is_copy_constructible
is_trivially_copy_constructible
is_nothrow_copy_constructible
is_move_constructible
is_trivially_move_constructible
is_nothrow_move_constructible
is_assignable
is_trivially_assignable
is_nothrow_assignable
is_copy_assignable
is_trivially_copy_assignable
is_nothrow_copy_assignable
is_move_assignable
is_trivially_move_assignable
is_nothrow_move_assignable
is_destructible
is_trivially_destructible
is_nothrow_destructible
has_virtual_destructor

STL容器
std::array
std::forward_list
std::begin
std::end
std::move
容器初始化
emplace
无序容器
std::unordered_map
std::unordered_multimap
std::unordered_set
std::unordered_multiset
元组std::tuple
std::make_tuple
std::get
std::tie
hash
std::hash<std::string>
std::hash<std::u16string>
std::hash<std::u32string>
std::hash<std::wstring>
std::hash<std::error_code>
std::hash<std::bitset>
std::hash<std::type_index>
std::hash<std::vector<bool>>
智能指针
std::shared_ptr
std::weak_ptr
std::unique_ptr
auto_ptr(弃用)
正则表达式
basic_regex
sub_match
match_results
函数
非静态成员函数
cv限定函数
引用限定
函数对象模板
std::function
std::bind
std::bad_function_call
mem_fn
类
类型别名
类成员初始化
仿函数(functor)
委托构造函数
继承构造函数
移动构造函数
移动赋值运算符
模板
尖括号“>”
别名模板
外部模板
可变参数模板
默认模板参数
原子操作
std::atomic<bool>
std::atomic<char>
std::atomic<signed char>
std::atomic<unsigned char>
std::atomic<short>
std::atomic<unsigned short>
std::atomic<int>
std::atomic<unsigned int>
std::atomic<long>
std::atomic<unsigned long>
std::atomic<long long>
std::atomic<unsigned long long>
std::atomic<char8_t>
std::atomic<char16_t>
std::atomic<char32_t>
std::atomic<wchar_t>
std::atomic<std::int8_t>
std::atomic<std::uint8_t>
std::atomic<std::int16_t>
std::atomic<std::uint16_t>
std::atomic<std::int32_t>
std::atomic<std::uint32_t>
std::atomic<std::int64_t>
std::atomic<std::uint64_t>
std::atomic<std::int_least8_t>
std::atomic<std::uint_least8_t>
std::atomic<std::int_least16_t>
std::atomic<std::uint_least16_t>
std::atomic<std::int_least32_t>
std::atomic<std::uint_least32_t>
std::atomic<std::int_least64_t>
std::atomic<std::uint_least64_t>
std::atomic<std::int_fast8_t>
std::atomic<std::uint_fast8_t>
std::atomic<std::int_fast16_t>
std::atomic<std::uint_fast16_t>
std::atomic<std::int_fast32_t>
std::atomic<std::uint_fast32_t>
std::atomic<std::int_fast64_t>
std::atomic<std::uint_fast64_t>
线程
std::thread
std::mutex
std::lock
std::call_once
std::atomic
std::cond_ition_variable
std::async
volatile
std::future
std::thread_local
异常
std::exception_ptr
std::make_exception_ptr
std::current_exception
std::rethrow_exception
std::nested_exception
std::throw_with_nested
std::rethrow_if_nested
错误
std::error_category
std::generic_category
std::error_condition
std::errc
std::error_code
std::system_error
新语法
预处理语法：__pragma(字符串字面量)
C++宏 _cplusplus宏
基于范围的for循环 for(x:range)
对齐支持(alignment support)
alignof
alignas
std::alignment_of
std::aligned_storage
std::max_align_t
std::align
显式转换操作符(explicit)
静态断言语法：static_assert(常量表达式，"提示字符串")
数字限制(numeric limits)
原始字符串(raw string)
追踪返回类型语法(trailing return type syntax)
扩展的friend语法(extended friend syntax)
扩展的整型(extended integer types)
非受限联合体(unrestricted union)
内联名字空间(lnline namespace)
用户定义的字面量(user-defined literals)
强类型枚举(scoped and strongly typed enums)
随机装置(random device)
std::ref和std::cref
常量表达式(constexpr)
lamda表达式
指针空值(nullptr)
防止类型收窄(Preventing narrowing)
初始化列表(initializer lists)
initializer_list(作入参)
统一的初始化语法和语义(Uniform initialization syntax and semantics)
POD(plain old data)
long long整型
移动语义(move semantics)
右值引用(rvalue reference)
c99特性(c99)
一般化的SFINAE规则(generalized SFINAE rules)
  


  
  
