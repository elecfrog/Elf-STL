#pragma once

#include <iostream>
#include <string>
#include <cassert>

namespace elf::stl
{
#define _ELF_STL_THROW_OUT_OF_RANGE(__idx, __n) throw std::out_of_range("Out of range! i = " + std::to_string(__idx) + "\n" + ", size " + std::to_string(__n) + "\n");

template<typename _Tp, std::size_t _N>
struct FixedArray {

    using value_type = _Tp;
    using size_type = std::size_t;
    using iterator = _Tp *;
    using const_iterator = const _Tp *;

    explicit FixedArray(const _Tp &value) {
        fill(value);
    }


    // 默认构造函数：不进行任何初始化
    FixedArray() = default;

    // 构造函数：通过大括号列表初始化
    FixedArray(std::initializer_list<_Tp> initList) {
        if (initList.size() != _N) {
            throw std::out_of_range("Initializer list size does not match array size.");
        }
        std::copy(initList.begin(), initList.end(), _M_elements);
    }

    static constexpr size_type size() {
        return _N;
    }

    static constexpr size_type max_size() {
        return size();
    }

    _Tp *data() {
        return _M_elements;
    }

    void fill(const _Tp &__val) noexcept(std::is_nothrow_copy_assignable_v<_Tp>) {
        for (auto &&idx = begin(); idx < end(); ++idx) {
            _M_elements[idx] = __val;
        }
    }

    void swap(FixedArray &__ohs) noexcept(std::is_nothrow_copy_assignable_v<_Tp>) {
        for (auto &&idx = begin(); idx < end(); ++idx) {
            _M_elements[idx] = __ohs[idx];
        }
    }

    const _Tp *data() const {
        return _M_elements;
    }

    const _Tp *cdata() const {
        return _M_elements;
    }

    _Tp &operator[](size_type __idx) noexcept {
        return _M_elements[__idx];
    }

    const _Tp &operator[](size_type __idx) const noexcept {
        return _M_elements[__idx];
    }

    _Tp &at(size_type __idx) {
        check_index(__idx);
        return _M_elements[__idx];
    }

    const _Tp &at(size_type __idx) const {
        check_index(__idx);
        return _M_elements[__idx];
    }

    iterator begin() {
        return _M_elements;
    }

    iterator end() {
        return _M_elements + _N;
    }

    const_iterator begin() const {
        return _M_elements;
    }

    const_iterator end() const {
        return _M_elements + _N;
    }

    const_iterator cbegin() {
        return _M_elements;
    }

    const_iterator cend() {
        return _M_elements + _N;
    }

    iterator rbegin() {
        return _M_elements + _N;
    }

    iterator rend() {
        return _M_elements;
    }

    const_iterator rbegin() const {
        return _M_elements + _N;
    }

    const_iterator rend() const {
        return _M_elements;
    }

    const_iterator crbegin() const {
        return _M_elements + _N - 1;
    }

    const_iterator crend() const {
        return _M_elements - 1;
    }

    _Tp &front() {
        return _M_elements[0];
    }

    _Tp &back() {
        return _M_elements[_N - 1];
    }

    // 打印所有成员
    void print() const {
        for (const auto &element: _M_elements) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    // 打印所有成员
    void rprint() const {
        for (auto it = crbegin(); it > crend(); --it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

private:
    constexpr void check_index(size_type __idx) {
        if (__idx >= size()) [[unlikely]] {
            _ELF_STL_THROW_OUT_OF_RANGE(__idx, _N);
        }
    }

private:
    _Tp _M_elements[_N];
};

template<class T, class ...Ts>
FixedArray(T, Ts...) -> FixedArray<T, 1 + sizeof...(Ts)>;

template<class T, size_t N>
FixedArray<std::decay_t<T>, N> to_fixed_array(T (&a)[N]) {
    FixedArray<std::decay_t<T>, N> fa;
    for (size_t i = 0; i < N; ++i) {
        fa[i] = a[i];
    }
    return fa;
}

#if defined(_MSC_VER)
#define _ELF_STL_UNREACHABLE() __assume(0)
#elif defined(__GNUC__)
#define _ELF_STL_UNREACHABLE() __builtin_unreachable()
#else
#define _ELF_STL_UNREACHABLE() do {} while (1)
#endif


template<typename _Tp>
struct FixedArray<_Tp, 0> {

    using value_type = _Tp;
    using size_type = std::size_t;
    using iterator = _Tp *;
    using const_iterator = const _Tp *;

    explicit FixedArray(const _Tp &value) {
        _ELF_STL_UNREACHABLE();
    }


    // 默认构造函数：不进行任何初始化
    FixedArray() = default;

    // 构造函数：通过大括号列表初始化
    FixedArray(std::initializer_list<_Tp> initList) {
        _ELF_STL_UNREACHABLE();
    }

    static constexpr size_type size() {
        return 0;
    }

    static constexpr size_type max_size() {
        return 0;
    }

    _Tp *data() {
        _ELF_STL_UNREACHABLE();
    }

    void fill(const _Tp &__val) noexcept(std::is_nothrow_copy_assignable_v<_Tp>) {
        _ELF_STL_UNREACHABLE();
    }

    void swap(FixedArray &__ohs) noexcept(std::is_nothrow_copy_assignable_v<_Tp>) {
        _ELF_STL_UNREACHABLE();
    }

    const _Tp *data() const {
        _ELF_STL_UNREACHABLE();
    }

    const _Tp *cdata() const {
        _ELF_STL_UNREACHABLE();
    }

    _Tp &operator[](size_type __idx) noexcept {
        _ELF_STL_UNREACHABLE();
    }

    const _Tp &operator[](size_type __idx) const noexcept {
        _ELF_STL_UNREACHABLE();
    }

    _Tp &at(size_type __idx) {
        _ELF_STL_UNREACHABLE();
    }

    const _Tp &at(size_type __idx) const {
        _ELF_STL_UNREACHABLE();
    }

    iterator begin() {
        _ELF_STL_UNREACHABLE();
    }

    iterator end() {
        _ELF_STL_UNREACHABLE();
    }

    const_iterator begin() const {
        _ELF_STL_UNREACHABLE();
    }

    const_iterator end() const {
        _ELF_STL_UNREACHABLE();
    }

    const_iterator cbegin() {
        _ELF_STL_UNREACHABLE();
    }

    const_iterator cend() {
        _ELF_STL_UNREACHABLE();
    }

    iterator rbegin() {
        _ELF_STL_UNREACHABLE();
    }

    iterator rend() {
        _ELF_STL_UNREACHABLE();
    }

    const_iterator rbegin() const {
        _ELF_STL_UNREACHABLE();
    }

    const_iterator rend() const {
        _ELF_STL_UNREACHABLE();
    }

    const_iterator crbegin() const {
        _ELF_STL_UNREACHABLE();
    }

    const_iterator crend() const {
        _ELF_STL_UNREACHABLE();
    }

    _Tp &front() {
        _ELF_STL_UNREACHABLE();
    }

    _Tp &back() {
        _ELF_STL_UNREACHABLE();
    }

    void print() const {
        _ELF_STL_UNREACHABLE();
    }

    void rprint() const {
        _ELF_STL_UNREACHABLE();
    }

private:
    constexpr void check_index(size_type __idx) {
        _ELF_STL_UNREACHABLE();
    }

private:
    _Tp _M_elements[0];
};
}
