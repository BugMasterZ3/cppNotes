
/************************************************ C++ 23 ***************************************************/
//C++23语言部分盘点：

语言 - T1
Deducing This：显式this参数

语言 - T2
多元operator[]：多维数组支持
size_t字面量：补全缺憾
扩展浮点字面量：支持更多的架构
假定表达式：让编译器拿到更多信息
静态operator()：效率至上
if consteval：C++20的bugfix
auto(x) / decay-copy
语言 - T3(bugfix)
新的预处理指令：30年的落后
Down with ()!：简化lambda
constexpr扩展：永远前进的征途
Unicode转义字符增强：\N与\u{}
Implicit Move的世界：return x背后的努力
确定性的定义顺序：灵活性太高也是一件坏事
CTAD增强：继承构造函数的缺憾
重要的CWG Issue



// C++23标准库部分盘点

标准库 - T0.5
import std：新时代的#include <bits/stdc++.h>

标准库 - T1
std::print：新时代的输出手段
Ranges格式化输出：cout的缺憾
std::expected：新时代的异常处理方式
std::generator：Coroutines ?? Ranges
ranges::to & 容器Ranges支持：补全C++20 Ranges的最大缺憾
mdspan：多维数组视图
堆栈信息库：Finally
平坦容器flat_{map,set}：10年后的新容器

标准库 - T2 - Ranges适配器
zip家族
as_const：Range版std::as_const
as_rvalue：Range版std::move
cartesian_product：笛卡尔积
join_with：带分隔符的join/flatten
chunk_by：分块
chunk与slide：滑动窗格
stride：定宽滑动窗格
repeat：重复单一元素的生成器

标准库 - T2 - Ranges算法
fold家族
contains：25年的补偿
{starts,ends}_with：通用化的String操作
iota/shift_{left,right}：最后的算法补全
find_last：无人预料的缺失

标准库 - T2 - 其他
std::function的伙伴：函数参数增强
spanstream：strstream的替代品
Monadic std::optional & std::expected：看齐其他语言
[in]out_ptr：指针作为输出参数的支持
std::unreachable：此路不通
string::contains()：Finally Here
to_underlying：enum类的增强支持
string_view的Ranges构造函数：一个混乱的故事
invoke_r：带返回值类型的invoke
std::byteswap：Have Fun
string::resize_and_overwrite()：String Resize的效率改进
allocate_at_least：独木难支
forward_like：Deducing This的附加功能

标准库 - T3
自定义Range适配器支持
constexpr扩展：<cmath>与更多
tuple-like：类tuple类型的完全支持
异质容器成员：最后的拼图
Ranges迭代器与pre-C++20算法支持
Reference Binding to Temporary：生命周期错误检测
禁止nullptr构造string：半截解决方案
fstream Exclusive Mode：太迟了！
string::substr() &&：右值优化
Move-only类型的Ranges支持:纯数学概念如何在C++中生存？















