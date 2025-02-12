/*
 * DC4C - Standard data containers for C
 *
 * Copyright (C) 2025  mhahnFr
 *
 * This file is part of DC4C.
 *
 * DC4C is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DC4C is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * DC4C, see the file LICENSE.  If not, see <https://www.gnu.org/licenses/>.
 */

#if __cplusplus < 201103
# error This library requires C++11 or newer.
#endif

#ifndef __DC4C_v2_vector_h
# warning Wrong inclusion of "vector.hpp" redirected to #include "vector.h"!
# include "vector.h"
#else
# ifndef __DC4C_v2_vector_hpp
# define __DC4C_v2_vector_hpp

# if __cplusplus >= 202002
#  define __DC4C_CXX20_constexpr constexpr
# else
#  define __DC4C_CXX20_constexpr
# endif

# include <algorithm>
# include <functional>
# include <vector>

namespace dc4c {
# if __cplusplus >= 202002
template<typename T>
concept is_dc4c_vector = requires (T t) {
    t.count = std::size_t(0);
    t.cap   = std::size_t(0);

    (decltype(t.content)) nullptr;
};
# endif

template<
# if __cplusplus >= 202002
is_dc4c_vector
# else
typename
# endif
T>
class vector {
    T underlying;

public:
    using size_type = std::decay<decltype(underlying.count)>::type;
    using value_type = std::decay<decltype(*underlying.content)>::type;

    constexpr inline vector(): underlying(vector_initializer) {}

    constexpr inline vector(const vector& other) {
        vector_copy(&underlying, &other.underlying);
    }

    constexpr inline vector(vector&& other): underlying(other.underlying) {
        vector_create(&other.underlying);
    }

    constexpr inline vector(const T* cVector) {
        vector_copy(&underlying, cVector);
    }

    constexpr inline vector(const T& cVector): vector(&cVector) {}

    constexpr inline vector(const std::vector<value_type>& other): underlying(vector_initializer) {
        reserve(other.size());

        for (const auto& element : other) {
            push_back(element);
        }
    }

    template<typename InputIt>
    constexpr inline vector(InputIt begin, InputIt end): underlying(vector_initializer) {
        for (; begin != end; ++begin) {
            push_back(*begin);
        }
    }

    constexpr inline ~vector() {
        vector_destroy(&underlying);
    }

    constexpr inline auto operator=(const vector& other) -> vector& {
        vector_destroy(&underlying);
        vector_copy(&underlying, &other.underlying);
        return *this;
    }

    constexpr inline auto operator=(vector&& other) -> vector& {
        vector_destroy(&underlying);
        underlying = other.underlying;
        vector_create(&other.underlying);
        return *this;
    }

    constexpr inline auto operator=(const T* cVector) -> vector& {
        vector_destroy(&underlying);
        vector_copy(&underlying, cVector);
        return *this;
    }

    constexpr inline auto operator=(const T& cVector) -> vector& {
        return *this = &cVector;
    }

    constexpr inline auto data() -> T& {
        return underlying;
    }

    constexpr inline auto data() const -> const T& {
        return underlying;
    }

    constexpr inline operator std::vector<value_type>() const {
        auto toReturn = std::vector<value_type>();
        toReturn.reserve(size());
        for (const auto& element : *this) {
            toReturn.push_back(element);
        }
        return toReturn;
    }

    constexpr inline operator T*() {
        return &underlying;
    }

    constexpr inline operator const T*() const {
        return &underlying;
    }

    constexpr inline auto operator->() -> T* {
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

    constexpr inline void push_back(const value_type& value) {
        if (!vector_push_back(&underlying, value)) {
            throw std::bad_alloc();
        }
    }

    constexpr inline auto pop_back() -> value_type {
        return vector_pop_back(&underlying);
    }

    constexpr inline auto erase(size_type index) -> value_type {
        return vector_erase(&underlying, index);
    }

    constexpr inline void insert(const value_type& value, size_type index) {
        if (!vector_insert(&underlying, value, index)) {
            throw std::bad_alloc();
        }
    }

    constexpr inline void reserve(size_type newCap) {
        if (!vector_reserve(&underlying, newCap)) {
            throw std::bad_alloc();
        }
    }

    constexpr inline void clear() {
        vector_clear(&underlying);
    }

    constexpr inline auto size() const noexcept -> size_type {
        return vector_size(&underlying);
    }

    constexpr inline auto capacity() const noexcept -> size_type {
        return vector_capacity(&underlying);
    }

    constexpr inline auto getUnderlyingData() noexcept -> value_type* {
        return underlying.content;
    }

    constexpr inline auto getUnderlyingData() const noexcept -> value_type* {
        return underlying.content;
    }

    template<typename C = std::less<value_type>>
    __DC4C_CXX20_constexpr inline void sort(const C& comp = C()) {
        std::sort(begin(), end(), comp);
    }
};
}

#define vector_cxx_wrapper(name, actual) \
namespace dc4c {                         \
using vector_##name = vector<actual>;    \
}

# endif /* __DC4C_v2_vector_hpp */
#endif /* !__DC4C_v2_vector_h */
