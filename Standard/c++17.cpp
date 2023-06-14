

/************************************************ C++ 17 ***************************************************/
template <typename ... Ts>	//引入了折叠表达式
auto sum(Ts ... ts) {
    return (ts + ...);
}

constexpr auto lamb = [] (int n) { return n * n; };

namespace A::B::C {
    void func();)
}

[[carries_dependency]] //让编译期跳过不必要的内存栅栏指令
[[noreturn]] //函数不会返回
[[deprecated]] //函数将弃用的警告	//C++11和C++14
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


