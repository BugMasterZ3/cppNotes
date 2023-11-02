
/************************************************ C++ 23 ***************************************************/

/////////////////////////////// C++23语言部分盘点 //////////////////////////////

// 语言 - T1
// Deducing This：显式this参数
auto fact = [](this auto self, int n) {
    if (n <= 1) return 1;
    return n * self(n - 1);
};
std::println("{}", fib(5)); // output 120


// 语言 - T2
// 多元operator[]：多维数组支持
struct Matrix{
    value_type& operator[](int row, int col) {/* ... */}
};
Matrix m;
m[2, 3] = 4;

// size_t字面量
for (auto i = 0uz, i < vec.size(); ++i)  // 0uz、0zu

// 扩展浮点字面量：支持更多的架构
<stdfloat>
#ifdef __STDCPP_{FLOAT}_T__ where FLOAT is in {FLOAT16, FLOAT32, FLOAT64, FLOAT128, BFLOAT16}
auto a = 1.0f16; // std::float16_t
auto b = 1.0bf16; // std::bfloat16_t
  
// 假定表达式：让编译器拿到更多信息
void limiter(float* data, size_t size)  // 让编译器直接把循环优化成一次处理32个非负元素的并行指令
{
    [[assume(size > 0)]];
    [[assume(size % 32 == 0)]];
    for (size_t i = 0; i < size; ++i)
    {
        [[assume(std::isfinite(data[i]))]];
        data[i] = std::clamp(data[i], -1.0f, 1.0f);  // 限制data[i]的值在-1.0f和1.0f之间。值小于-1.0f将被设置为-1.0f；值大于1.0f将被设置为1.0f
    }
}

// 静态operator()
template <typename T>
struct less {
    static constexpr bool operator()(const T& x, const T& y)  // 运算符重载必须是非成员函数或者非静态的成员函数这一原则被改变
    {
        return x < y;
    };
};
less<int>{}(2, 3);

auto f = [](int i) static {return i * 2;}  // static的lambda不能有capture

// if consteval
consteval int compiler_computation(std::span<const int> sp) {
    int res = 0;
    for (auto a : sp) {res += a * a;}
    return res;
}
constexpr int some_computation(std::span<const int> sp) {
    if consteval {
        return compiler_computation(sp);
    }
    else {
        __asm__("Some SIMD Things");
    }
}

// auto(x) / decay-copy


// 语言 - T3
// 新的预处理指令
#warning
#elifdef & #elifndef

// Down with ()!：简化lambda
[] mutable {return 0;}  // 如果lambda没有参数的话可以省略()
  
// constexpr扩展
// Unicode转义字符增强：\N与\u{}
  
// Implicit Move的世界：return x背后的努力
struct Source {/* ... */};
struct Sink { Sink(Source&&); };
Sink process() { Source s; return s; }     // okay
Source&& process() { Source s; return s; } // error!
Sink process(Source&& s) { return s; }     // okay
Source&& process(Source&& s) { return s; } // error!

// 确定性的定义顺序：灵活性太高也是一件坏事
// CTAD增强：继承构造函数的缺憾
// 重要的CWG Issue



/////////////////////////// C++23标准库部分盘点 ////////////////////////////////

// 标准库 - T0.5
// import std：新时代的#include <bits/stdc++.h>

// 标准库 - T1
// std::print：新时代的输出手段
// Ranges格式化输出：cout的缺憾
// std::expected：新时代的异常处理方式
// std::generator：Coroutines ?? Ranges
// ranges::to & 容器Ranges支持：补全C++20 Ranges的最大缺憾
// mdspan：多维数组视图
// 堆栈信息库：Finally
// 平坦容器flat_{map,set}：10年后的新容器

// 标准库 - T2 - Ranges适配器
// zip家族
// as_const：Range版std::as_const
// as_rvalue：Range版std::move
// cartesian_product：笛卡尔积
// join_with：带分隔符的join/flatten
// chunk_by：分块
// chunk与slide：滑动窗格
// stride：定宽滑动窗格
// repeat：重复单一元素的生成器

// 标准库 - T2 - Ranges算法
// fold家族
// contains：25年的补偿
// {starts,ends}_with：通用化的String操作
// iota/shift_{left,right}：最后的算法补全
// find_last：无人预料的缺失

// 标准库 - T2 - 其他
// std::function的伙伴：函数参数增强
// spanstream：strstream的替代品
// Monadic std::optional & std::expected：看齐其他语言
// [in]out_ptr：指针作为输出参数的支持
// std::unreachable：此路不通
// string::contains()：Finally Here
// to_underlying：enum类的增强支持
// string_view的Ranges构造函数：一个混乱的故事
// invoke_r：带返回值类型的invoke
// std::byteswap：Have Fun
// string::resize_and_overwrite()：String Resize的效率改进
// allocate_at_least：独木难支
// forward_like：Deducing This的附加功能

// 标准库 - T3
// 自定义Range适配器支持
// constexpr扩展：<cmath>与更多
// tuple-like：类tuple类型的完全支持
// 异质容器成员：最后的拼图
// Ranges迭代器与pre-C++20算法支持
// Reference Binding to Temporary：生命周期错误检测
// 禁止nullptr构造string：半截解决方案
// fstream Exclusive Mode：太迟了！
// string::substr() &&：右值优化
// Move-only类型的Ranges支持:纯数学概念如何在C++中生存？















