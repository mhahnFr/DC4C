/*
 * DC4C - Standard data containers for C
 *
 * Written in 2023 - 2025 by mhahnFr
 *
 * This file is part of DC4C.
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along with DC4C,
 * see the file LICENSE. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#if __cplusplus < 201103L
# error This library requires C++11 or newer.
#endif

#ifndef __DC4C_vector_h
# warning Wrong inclusion of "vector.hpp" redirected to #include "vector.h"!
# include "vector.h"
#else
# ifndef __DC4C_vector_hpp
# define __DC4C_vector_hpp

# if __cplusplus >= 201402L
#  define __DC4C_CONSTEXPR_SINCE_CXX14 constexpr
# else
#  define __DC4C_CONSTEXPR_SINCE_CXX14
# endif

# if __cplusplus >= 201703L
#  define __DC4C_CONSTEXPR_SINCE_CXX17 constexpr
# else
#  define __DC4C_CONSTEXPR_SINCE_CXX17
# endif

# if __cplusplus >= 202002L
#  define __DC4C_CONSTEXPR_SINCE_CXX20 constexpr
# else
#  define __DC4C_CONSTEXPR_SINCE_CXX20
# endif

# include <algorithm>
# include <functional>
# include <vector>

namespace dc4c {
# if __cplusplus >= 202002L
template<typename T>
concept is_dc4c_vector = requires (T t) {
    t.count = std::size_t(0);
    t.cap   = std::size_t(0);

    (decltype(t.content)) nullptr;
};
# endif

template<
# if __cplusplus >= 202002L
is_dc4c_vector
# else
typename
# endif
T>
class vector {
    T underlying;

public:
    using size_type = typename std::decay<decltype(underlying.count)>::type;
    using value_type = typename std::decay<decltype(*underlying.content)>::type;

    constexpr inline vector(): underlying(vector_initializer) {}

    __DC4C_CONSTEXPR_SINCE_CXX14 inline vector(const vector& other) {
        vector_copy(&underlying, &other.underlying);
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline vector(vector&& other) noexcept: underlying(other.underlying) {
        vector_create(&other.underlying);
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline vector(const T* cVector) {
        vector_copy(&underlying, cVector);
    }

    constexpr inline vector(const T& cVector): vector(&cVector) {}

    __DC4C_CONSTEXPR_SINCE_CXX14 inline vector(const std::vector<value_type>& other): underlying(vector_initializer) {
        reserve(other.size());

        for (const auto& element : other) {
            push_back(element);
        }
    }

    template<typename InputIt>
    __DC4C_CONSTEXPR_SINCE_CXX14 inline vector(InputIt begin, InputIt end): underlying(vector_initializer) {
        for (; begin != end; ++begin) {
            push_back(*begin);
        }
    }

    __DC4C_CONSTEXPR_SINCE_CXX20 inline ~vector() {
        vector_destroy(&underlying);
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline auto operator=(const vector& other) -> vector& {
        vector_destroy(&underlying);
        vector_copy(&underlying, &other.underlying);
        return *this;
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline auto operator=(vector&& other) noexcept -> vector& {
        vector_destroy(&underlying);
        underlying = other.underlying;
        vector_create(&other.underlying);
        return *this;
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline auto operator=(const T* cVector) -> vector& {
        vector_destroy(&underlying);
        vector_copy(&underlying, cVector);
        return *this;
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline auto operator=(const T& cVector) -> vector& {
        return *this = &cVector;
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline auto data() -> T& {
        return underlying;
    }

    constexpr inline auto data() const -> const T& {
        return underlying;
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline operator std::vector<value_type>() const {
        auto toReturn = std::vector<value_type>();
        toReturn.reserve(size());
        for (const auto& element : *this) {
            toReturn.push_back(element);
        }
        return toReturn;
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline operator T*() {
        return &underlying;
    }

    constexpr inline operator const T*() const {
        return &underlying;
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline auto operator->() -> T* {
        return *this;
    }

    constexpr inline auto operator->() const -> const T* {
        return *this;
    }

    constexpr inline auto operator[](size_type position) const noexcept -> value_type& {
        return underlying.content[position];
    }

    constexpr inline auto begin() const noexcept -> value_type* {
        return underlying.content;
    }

    constexpr inline auto end() const noexcept -> value_type* {
        return underlying.content + underlying.count;
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline void push_back(const value_type& value) {
        if (!vector_push_back(&underlying, value)) {
            throw std::bad_alloc();
        }
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline auto pop_back() -> value_type {
        return vector_pop_back(&underlying);
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline auto erase(size_type index) -> value_type {
        return vector_erase(&underlying, index);
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline void insert(const value_type& value, size_type index) {
        if (!vector_insert(&underlying, value, index)) {
            throw std::bad_alloc();
        }
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline void reserve(size_type newCap) {
        if (!vector_reserve(&underlying, newCap)) {
            throw std::bad_alloc();
        }
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline void clear() {
        vector_clear(&underlying);
    }

    constexpr inline auto size() const noexcept -> size_type {
        return vector_size(&underlying);
    }

    constexpr inline auto capacity() const noexcept -> size_type {
        return vector_capacity(&underlying);
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline auto getUnderlyingData() noexcept -> value_type* {
        return underlying.content;
    }

    constexpr inline auto getUnderlyingData() const noexcept -> value_type* {
        return underlying.content;
    }

    template<typename C = std::less<value_type>>
    __DC4C_CONSTEXPR_SINCE_CXX20 inline void sort(const C& comp = C()) {
        std::sort(begin(), end(), comp);
    }
};
}

#define vector_cxx_wrapper(name, actual) \
namespace dc4c {                         \
using vector_##name = vector<actual>;    \
}

# endif /* __DC4C_vector_hpp */
#endif /* !__DC4C_vector_h */
