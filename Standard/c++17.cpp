
/************************************************ C++ 17 ***************************************************/
关键字   register
类型支持（基本类型、RTTI、类型特性）
<type_traits>
	byte(字节类型)
	is_aggregate(检查类型是否聚合类型)
	is_swappable_with(检查一个类型的对象是否能与同类型或不同类型的对象交换)
	is_swappable(检查一个类型的对象是否能与同类型或不同类型的对象交换)
	is_nothrow_swappable_with(检查一个类型的对象是否能与同类型或不同类型的对象交换)
	is_nothrow_swappable(检查一个类型的对象是否能与同类型或不同类型的对象交换)
	is_invocable(检查类型能否以给定的实参类型调用（如同以 std::invoke）)
	is_invocable_r(检查类型能否以给定的实参类型调用（如同以 std::invoke）)
	is_nothrow_invocable(检查类型能否以给定的实参类型调用（如同以 std::invoke）)
	is_nothrow_invocable_r(检查类型能否以给定的实参类型调用（如同以 std::invoke）)
	invoke_result(推导以一组实参调用一个可调用对象的结果类型)
	void_t(变参别名模板)
	conjunction(变参的逻辑与元函数)
	disjunction(变参的逻辑或元函数)
	ndisjunctionegation(逻辑非元函数)
	integral_constant(具有指定值的指定类型的编译期常量)

<utility>
	as_const(获得到其实参的 const 引用)
<tuple>
	apply(以一个实参的元组来调用函数)
	make_from_tuple(以一个实参元组构造对象)
<optional>
	optional(可能或可能不保有一个对象的包装器)
	make_optional(创建一个 optional 对象)
	std::swap(std::optional)(特化 std::swap 算法)
	std::hash<std::optional>(特化 std::hash 算法)
	nullopt_t(带未初始化状态的 optional 类型的指示器)
	bad_optional_access(指示进行了到不含值的 optional 的有检查访问的异常)
	nullopt(nullopt_t 类型对象)
<variant>
	variant(类型安全的可辨识联合体)
	visit(以一或多个 variant 所保有的各实参调用所提供的函数对象)
	holds_alternative(检查某个 variant 是否当前持有某个给定类型)
	std::get(std::variant)(以给定索引或类型（若类型唯一）读取 variant 的值，错误时抛出异常)
	get_if(以给定索引或类型（若其唯一），获得指向被指向的 variant 的值的指针，错误时返回空指针)
	std::swap(std::variant)(特化 std::swap 算法)
	monostate(用作非可默认构造类型的 variant 的首个可选项的占位符类型)
	bad_variant_access(非法地访问 variant 的值时抛出的异常)
	variant_size(在编译时获得 variant 可选项列表的大小)
	variant_size_v(在编译时获得 variant 可选项列表的大小)
	variant_alternative(在编译时获得以其下标指定的可选项的类型)
	variant_alternative_t(在编译时获得以其下标指定的可选项的类型)
	std::hash<std::variant>(特化 std::hash 算法)
	variant_npos(非法状态的 variant 的下标)
<any>
	any(可保有任何可复制构造 (CopyConstructible) 类型的实例的对象)
	std::swap(std::any)(特化 std::swap 算法)
	any_cast(对被容纳对象的类型安全访问)
	make_any(创建 any 对象)
	bad_any_cast(当类型不匹配时按值返回形式的 any_cast 所抛出的异常)
<charconv>
	to_chars(转换整数或浮点值到字符序列象)
	from_chars(转换字符序列到整数或浮点值)
	chars_format(指定 std::to_chars 和 std::from_chars 所用的格式)
<initializer_list>
	empty(检查容器是否为空)
	data(获得指向底层数组的指针)
容器库
<map>
	insert_or_assign(插入元素，或若键已存在则赋值给当前元素)
	try_emplace(若键不存在则原位插入，若键存在则不做任何事)
	extract(从另一容器释出结点)
	merge(从另一容器接合结点)
<unordered_map>
	insert_or_assign(插入元素，或若键已存在则赋值给当前元素)
	try_emplace(若键不存在则原位插入，若键存在则不做任何事)
	extract(从另一容器释出结点)
	merge(从另一容器接合结点)
<array>
<deque>
<forward_list>
<iterator>
<list>
<map>
<regex>
<set>
<span>
<string>
<string_view>
<unordered_map>
<unordered_set>
<vector>
namespace
	size(返回容器或数组的大小)
	empty(检查容器是否为空)
	data(获得指向底层数组的指针)


	
template <typename ... Ts>	//引入了折叠表达式
auto sum(Ts ... ts) {
    return (ts + ...);
}

constexpr auto lamb = [] (int n) { return n * n; };

namespace A::B::C {
    void func();)
}

//C++11和C++14
[[carries_dependency]] //让编译期跳过不必要的内存栅栏指令
[[noreturn]] //函数不会返回
[[deprecated]] //函数将弃用的警告	
//C++17
[[fallthrough]] //用在switch中提示可以直接落下去，不需要break，让编译期忽略警告
[[nodiscard]] //表示修饰的内容不能被忽略，可用于修饰函数，标明返回值一定要被处理
[[maybe_unused]] //提示编译器修饰的内容可能暂时没有使用，避免产生警告

std::optional<int> StoI(const std::string &s) {
    try {
        return std::stoi(s);
    } catch(...) {
        return std::nullopt;	//异常情况下可以返回nullptr(代替指针，不用涉及内存管理)
    }
}

void func() {
    std::string s{"123"};
    std::optional<int> o = StoI(s);
    if (o) {
        cout << *o << endl;
    } else {
        cout << "error" << endl;
    }
}

std::any a = 1;		//存储任何类型的单个值
cout << a.type().name() << " " << std::any_cast<int>(a) << endl;
a = 2.2f;
cout << a.type().name() << " " << std::any_cast<float>(a) << endl;
if (a.has_value()) {
	cout << a.type().name();
}
a.reset();


