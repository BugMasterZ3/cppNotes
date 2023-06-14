
/************************************************ C++ 23 ***************************************************/
类型支持（基本类型、RTTI、类型特性）
<type_traits>
        is_scoped_enum(检查类型是否为有作用域枚举类型)
<utility>
        to_underlying(转换枚举到其底层类型)
<stacktrace>
        stacktrace_entry(栈踪中求值的表示)
        basic_stacktrace(由栈踪条目组成的调用序列的近似表示)
动态内存管理
<memory>
        out_ptr_t(与外来指针设置器交互，并在析构时重设智能指针)
        out_ptr(以关联的智能指针和重设参数创建 out_ptr_t)
        inout_ptr_t(与外来指针设置器交互，从智能指针获得初始指针值，并在析构时重设它)
        inout_ptr(以关联的智能指针和重设参数创建 inout_ptr_t)
        allocation_result(记录由 allocate_at_least 分配的存储的地址与实际大小)
        allocate_at_least(经由分配器分配至少与请求的大小一样大的存储)
字符串
<string>
        contains(检查字符串是否含有给定的子串或字符)
<string_view>
        contains(检查字符串视图是否含有给定的子串或字符)
