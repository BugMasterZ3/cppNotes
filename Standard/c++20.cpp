
/************************************************ C++ 20 ***************************************************/
新增关键字
        char8_t
        concept
        consteval
        co_await
        co_return
        co_yield
        requires
含义变化或者新增含义关键字
         export
类型支持（基本类型、RTTI、类型特性）
<type_traits>
        is_bounded_array(检查类型是否为有已知边界的数组类型)
        is_unbounded_array(检查类型是否为有未知边界的数组类型)
        is_layout_compatible(检查二个类型是否布局兼容)
        is_pointer_interconvertible_base_of(检查一个类型是否为另一类型的指针可互转换（起始）基类)
        is_pointer_interconvertible_with_class(检查一个类型的对象是否与该类型的指定子对象指针可互转换)
        is_corresponding_member(检查二个指定成员是否在二个指定类型中的公共起始序列中彼此对应)
        is_nothrow_convertible(检查是否能转换一个类型为另一类型)
        remove_cvref(将 std::remove_cv 与 std::remove_reference 结合)
        type_identity(返回不更改的类型实参)
        is_constant_evaluated(检测调用是否在常量求值的语境内发生)
<coroutine>
        coroutine_traits(用于发现协程承诺类型的特征类型)
        coroutine_handle(用于指代暂停或执行的协程)
        noop_coroutine(创建在等待或销毁时无操作的协程柄)
        noop_coroutine_promise(用于无可观察作用的协程)
        noop_coroutine_handle(std::coroutine_handle<std::noop_coroutine_promise> ，有意用于指代无操作协程)
        suspend_never(指示 await 表达式应该决不暂停)
        suspend_always(指示 await 表达式应该始终暂停)
<compare>
        std::coroutine_traits
        std::coroutine_handle
        three_way_comparable(指定运算符 <=> 在给定类型上产生一致的结果)
        three_way_comparable_with(指定运算符 <=> 在给定类型上产生一致的结果)
        partial_ordering(三路比较的结果类型，支持所有 6 种运算符，不可替换，并允许不可比较的值)
        weak_ordering(三路比较的结果类型，支持所有 6 种运算符且不可替换)
        strong_ordering(三路比较的结果类型，支持所有 6 种运算符且可替换)
        is_eq
        is_neq
        is_lt
        is_lteq
        is_gt
        is_gteq
        compare_three_way(实现 x <=> y 的函数对象)
        compare_three_way_result(获得三路比较运算符 <=> 在给定类型上的结果)
        common_comparison_category(给定的全部类型都能转换到的最强比较类别)
        strong_order(进行三路比较并产生 std::strong_ordering 类型结果)
        weak_order(进行三路比较并产生 std::weak_ordering 类型结果)
        partial_order(进行三路比较并产生 std::partial_ordering 类型结果)
        compare_strong_order_fallback(进行三路比较并产生 std::strong_ordering 类型的结果，即使 operator<=> 不可用)
        compare_weak_order_fallback(进行三路比较并产生 std::weak_ordering 类型的结果，即使 operator<=> 不可用)
        compare_partial_order_fallback(进行三路比较并产生 std::partial_ordering 类型的结果，即使 operator<=> 不可用
<concepts>
        ranges::swap(交换两个对象的值)
<utility>
        cmp_equal(比较二个整数值，而无转换所致的值更改)
        cmp_not_equal(比较二个整数值，而无转换所致的值更改)
        cmp_less(比较二个整数值，而无转换所致的值更改)
        cmp_less_equal(比较二个整数值，而无转换所致的值更改)
        cmp_greater_equal(比较二个整数值，而无转换所致的值更改)
        in_range(检查整数值是否在给定整数类型的范围内)
<memory>
        uninitialized_move(移动一个范围的对象到未初始化的内存区域)
        uninitialized_move_n(移动一定数量对象到未初始化内存区域)
        uninitialized_default_construct(在范围所定义的未初始化的内存区域以默认初始化构造对象)
        uninitialized_default_construct_n(在起始和计数所定义的未初始化内存区域用默认初始化构造对象)
        uninitialized_value_construct(在范围所定义的未初始化内存中用值初始化构造对象)
        uninitialized_value_construct_n(在起始和计数所定义的未初始化内存区域以值初始化构造对象)
        destroy_at(销毁在给定地址的对象)
        destroy(销毁一个范围中的对象)
        destroy_n(销毁范围中一定数量的对象)                                     
Concepts library(概念库)
<concepts>
        same_as(指定一个类型与另一类型相同)
        derived_from(指定一个类型派生自另一类型)
        convertible_to(指定一个类型能隐式转换成另一类型)
        common_reference_with(指定两个类型共有一个公共引用类型)
        common_with(指定两个类型共有一个公共类型)
        integral(指定类型为整型类型)
        signed_integral(指定类型为有符号的整型类型)
        unsigned_integral(指定类型为无符号的整型类型)
        floating_point(指定类型为浮点类型)
        assignable_from(指定一个类型能从另一类型赋值)
        swappable(指定一个类型能进行交换，或两个类型能彼此交换)
        swappable_with(指定一个类型能进行交换，或两个类型能彼此交换)
        destructible(指定能销毁该类型的对象)
        constructible_from(指定该类型的变量能从一组实参类型进行构造，或绑定到一组实参类型)
        default_initializable(指定能默认构造一个类型的对象)
        move_constructible(指定能移动构造一个类型的对象)
        copy_constructible(指定能复制构造和移动构造一个类型的对象)
        boolean-testable(指定能用于布尔语境的类型)
        equality_comparable(指定运算符 == 为等价关系)
        equality_comparable_with(指定运算符 == 为等价关系)
        totally_ordered(指定比较运算符在该类型上产生全序)
        totally_ordered_with(指定比较运算符在该类型上产生全序)
        movable(指定能移动及交换一个类型的对象)
        copyable(指定能复制、移动及交换一个类型的对象)
        semiregular(指定能赋值、移动、交换及默认构造一个类型的对象)
        regular(指定类型为正则，即它既为 semiregular 亦为 equality_comparable)
        invocable(指定能以给定的一组实参类型调用的可调用类型)
        regular_invocable(指定能以给定的一组实参类型调用的可调用类型)
        predicate(指定可调用类型为布尔谓词)
        relation(指定可调用类型为二元关系)
        equivalence_relation(指定 relation 施加等价关系)
        strict_weak_order(指定一个 relation 所强加的是严格弱序)
动态内存管理
<memory>
        uses_allocator_construction_args(准备匹配给定类型所要求的使用分配器构造的口味的参数列表)
        make_obj_using_allocator(以使用分配器构造的手段创建给类型的对象)
        uninitialized_construct_using_allocator(以使用分配器构造的手段在指定的内存位置创建给定类型的对象)
        construct_at(在给定地址创建对象)
        no-throw-input-iterator(指定迭代器、哨位和范围上的某些操作不抛出)
        no-throw-forward-iterator(指定迭代器、哨位和范围上的某些操作不抛出)
        no-throw-sentinel-for(指定迭代器、哨位和范围上的某些操作不抛出)
        no-throw-input-range(指定迭代器、哨位和范围上的某些操作不抛出)
        no-throw-forward-range(指定迭代器、哨位和范围上的某些操作不抛出)
        ranges::uninitialized_copy(复制元素范围到未初始化的内存区域)
        ranges::uninitialized_copy_n(复制一定量元素到未初始化的内存区域)
        ranges::uninitialized_fill(复制一个对象到范围所定义的未初始化的内存区域)
        ranges::uninitialized_fill_n(复制一个对象到起始与计数所定义的未初始化的内存区域)
        ranges::uninitialized_move(移动对象范围到未初始化的内存区域)
        ranges::uninitialized_move_n(移动一定量对象到未初始化的内存区域)
        ranges::uninitialized_default_construct(在范围所定义的未初始化的内存区域以默认初始化构造对象)
        ranges::uninitialized_default_construct_n(在起始与计数所定义的未初始化的内存区域以默认初始化构造对象)
        ranges::uninitialized_value_construct(在范围所定义的未初始化的内存区域以值初始化构造对象)
        ranges::uninitialized_value_construct_n(在起始与计数所定义的未初始化的内存区域以值初始化构造对象)
        ranges::destroy_at(销毁位于给定地址的元素)
        ranges::destroy(销毁范围中的元素)
        ranges::destroy_n(销毁范围中一定量的元素)
        ranges::construct_at(在给定地址创建对象)
        to_address(从指针式类型获得裸指针)
        assume_aligned(告知编译器指针已对齐)
日期和时间工具
<chrono>
        is_clock(确定类型是否为时钟 (Clock))
        is_clock_v(确定类型是否为时钟 (Clock))
        utc_clock(协调世界时 (UTC) 的时钟 (Clock))
        tai_clock(国际原子时 (TAI) 的时钟 (Clock))
        gps_clock(GPS 时间的时钟 (Clock))
        file_clock(用于文件时间的时钟 (Clock))
        local_t(表示本地时间的伪时钟)
        clock_time_conversion(定义如何转换一个时钟的时间点为另一个的特性类)
        clock_cast(转换一个时钟的时间点为另一个)
        time_of_day(表示一日中的时间)
        is_am(在 12 时和 24 时格式当天时刻之间翻译)
        is_pm(在 12 时和 24 时格式当天时刻之间翻译)
        make12(在 12 时和 24 时格式当天时刻之间翻译)
        make24(在 12 时和 24 时格式当天时刻之间翻译)
        last_spec(指示一个月中最后日期或星期的标签类)
        day(表示月之日期)
        month(表示年之月份)
        year(表示格里高利历中的年)
        weekday(表示格里高利历中星期之日)
        weekday_indexed(表示月份的第 n 个 weekday)
        weekday_last(表示月份的最后一个 weekday)
        month_day(表示特定 month 的特定 day)
        month_day_last(表示特定 month 的最后一日)
        month_weekday(表示特定 month 的第 n 个 weekday)
        month_weekday_last(表示特定 month 的最后一个 weekday)
        year_month(表示特定 year 的特定 month)
        year_month_day(表示特定的 year 、 month 和 day)
        year_month_day_last(表示特定 year 和 month 的最后一日)
        year_month_weekday(表示特定 year 和 month 的第 n 个 weekday)
        year_month_weekday_last(表示特定 year 和 month 的最后一个 weekday)
        operator/(创建格里高利历日期的约定语法)
        tzdb(描述 IANA 时区数据库的副本)
        tzdb_list(表示 tzdb 的链表)
        get_tzdb(访问和控制全球时区数据库信息)
        get_tzdb_list(访问和控制全球时区数据库信息)
        reload_tzdb(访问和控制全球时区数据库信息)
        remote_version(访问和控制全球时区数据库信息)
        locate_zone(定位基于其名称的 time_zone)
        current_zone(返回当前的 time_zone)
        time_zone(表示时区)
        sys_info(表示在特定时间点的关于时区的信息)
        local_info(表示关于从本地时间转换到 UNIX 时间的信息)
        choose(选择应如何解析歧义的本地时间)
        zoned_traits(zoned_time 所用的时区指针的特性类)
        zoned_time(表示时区和时间点)
        leap_second(含有关于插入闰秒的信息)
        time_zone_link(表示时区的替用名)
        nonexistent_local_time(抛出以报告本地时间不存在的异常)
        ambiguous_local_time(抛出以报告本地时间有歧义的异常)
        parse(从流分析 chrono 对象)
字符串
<string>
        starts_with(检查 string 是否始于给定前缀)
        ends_with(检查 string 是否终于给定后缀)
<string_view>
        starts_with(检查 string_view 是否始于给定前缀)
        ends_with(检查 string_view 是否终于给定后缀)
<cuchar>
        mbrtoc8(转换窄多字节字符为 UTF-8 编码)
        c8rtomb(转换 UTF-8 字符串为窄多字节编码)
容器库
<array>
        to_array(从内建数组创建 std::array 对象)
<vector>
        erase(std::vector)(擦除所有满足特定判别标准的元素)
        erase_if(std::vector)(擦除所有满足特定判别标准的元素)
<map>
        contains(检查容器是否含有带特定键的元素)
        erase_if(std::map)(擦除所有满足特定判别标准的元素)
<unordered_map>
        contains(检查容器是否含有带特定键的元素)
        erase_if(std::unordered_map)(擦除所有满足特定判别标准的元素)
<span>
        begin
        end
        rbegin
        rend
        front
        back
        dynamic_extent(size_t 类型常量，指明 span 拥有动态长度)
Defined in namespace std
        indirectly_readable(指定类型通过应用运算符 * 可读)
        indirectly_writable(指定可向迭代器所引用的对象写入值)
        weakly_incrementable(指定 semiregular 类型能以前后自增运算符自增)
        incrementable(指定 weakly_incrementable 类型上的自增操作保持相等性，而且该类型为 equality_comparable)
        input_or_output_iterator(指定该类型对象可以自增且可以解引用)
        sentinel_for(指定类型为某个 input_or_output_iterator 类型的哨位类型)
        sized_sentinel_for(指定可对一个迭代器和一个哨位应用 - 运算符，以在常数时间计算其距离)
        input_iterator(指定类型为输入迭代器，即可读取其所引用的值，且可前/后自增)
        output_iterator(指定类型为给定的值类型的输出迭代器，即可向其写入该类型的值，且可前/后自增)
        forward_iterator(指定 input_iterator 为向前迭代器，支持相等比较与多趟操作)
        bidirectional_iterator(指定 forward_iterator 为双向迭代器，支持向后移动)
        random_access_iterator(指定 bidirectional_iterator 为随机访问迭代器，支持常数时间内的前进和下标访问)
        contiguous_iterator(指定 random_access_iterator 为连续迭代器，指代内存中连续相接的元素)
        indirectly_readable_traits(计算 indirectly_readable 类型的值类型)
        iter_value_t(计算迭代器的关联类型)
        iter_reference_t(计算迭代器的关联类型)
        iter_difference_t(计算迭代器的关联类型)
        iter_rvalue_reference_t(计算迭代器的关联类型)
        iter_common_reference_t(计算迭代器的关联类型)
        iterator_traits(为迭代器各项性质提供统一接口)
        input_iterator_tag(用于指示迭代器类别的空类类型)
        output_iterator_tag(用于指示迭代器类别的空类类型)
        forward_iterator_tag(用于指示迭代器类别的空类类型)
        bidirectional_iterator_tag(用于指示迭代器类别的空类类型)
        random_access_iterator_tag(用于指示迭代器类别的空类类型)
        contiguous_iterator_tag(用于指示迭代器类别的空类类型)
                                       
        indirectly_unary_invocable(指定可调用类型能以解引用某个 indirectly_readable 类型的结果进行调用)
        indirectly_regular_unary_invocable(指定可调用类型能以解引用某个 indirectly_readable 类型的结果进行调用)
        indirect_unary_predicate(指定可调用类型，在以解引用一个 indirectly_readable 类型的结果进行调用时，满足 predicate)
        indirect_binary_predicate(指定可调用类型，在以解引用两个 indirectly_readable 类型的结果进行调用时，满足 predicate)
        indirect_equivalence_relation(指定可调用类型，在以解引用两个 indirectly_readable 类型的结果进行调用时，满足 equivalence_relation)
        indirect_strict_weak_order(指定可调用类型，在以解引用两个 indirectly_readable 类型的结果进行调用时，满足 strict_weak_order)
        indirectly_movable(指定可从 indirectly_readable 类型移动值给 indirectly_writable 类型)
        indirectly_movable_storable(指定可从 indirectly_readable 类型移动值给 indirectly_writable 类型，且该移动可以通过中间对象进行)
        indirectly_copyable(指定可从 indirectly_readable 类型复制值给 indirectly_writable 类型)
        indirectly_copyable_storable(指定可从 indirectly_readable 类型复制值给 indirectly_writable 类型，且该复制可以通过中间对象进行)
        indirectly_swappable(指定能交换两个 indirectly_readable 类型所引用的值)
        indirectly_comparable(指定能比较两个 indirectly_readable 类型所引用的值)
        permutable(指定在原位重排元素的算法的共用要求)
        mergeable(指定通过复制元素将已排序序列归并到输出序列中的算法的要求)
        sortable(指定重排序列为有序序列的算法的共用要求)
        indirect_result_t(计算在解引用某组 indirectly_readable 类型的结果上调用可调用对象的结果)
        projected(用于对接受投影的算法指定约束的辅助模板)
        move_sentinel(用于 std::move_iterator 的哨位适配器)
        common_iterator(适配一个迭代器类型及其哨位为一个公共迭代器类型)
        default_sentinel_t(用于知晓其边界的迭代器的默认哨位)
        counted_iterator(对到范围结尾距离进行跟踪的迭代器适配器)
        unreachable_sentinel_t(始终与任何 weakly_incrementable 类型比较都不相等的哨位) 
                                       
        ssize(返回容器或数组的大小)
Defined in namespace std::ranges
        iter_move(将解引用迭代器的结果转型为其关联的右值引用类型)
        iter_swap(交换两个可解引用对象所引用的值)
                                       
        ranges::advance(令迭代器前进给定的距离或到给定的边界)
        ranges::distance(返回迭代器与哨位间的距离，或范围起始与结尾间的距离)
        ranges::next(自增迭代器给定的距离或到边界)
        ranges::prev(自减迭代器给定的距离或到边界)
                                       
        ranges::begin(返回指向范围起始的迭代器)
        ranges::cbegin(返回指向只读范围起始的迭代器)
        ranges::end(返回指示范围结尾的哨位)
        ranges::cend(返回指示只读范围结尾的哨位)
        ranges::rbegin(返回指向范围的逆向迭代器)
        ranges::crbegin(返回指向只读范围的逆向迭代器)
        ranges::rend(返回指向范围的逆向尾迭代器)
        ranges::crend(返回指向只读范围的逆向尾迭代器)
        ranges::size(获得能在常数时间内计算大小的范围的大小)
        ranges::ssize(获得能在常数时间内计算大小的范围的大小，并将它转换成有符号整数)
        ranges::empty(检查范围是否为空)
        ranges::data(获得指向连续范围的起始的指针)
        ranges::cdata(获得指向只读连续范围的起始的指针)                               
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
                               
                               
                               
                               
