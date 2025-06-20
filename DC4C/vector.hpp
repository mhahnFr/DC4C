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
    t.count = static_cast<std::size_t>(0);
    t.cap   = static_cast<std::size_t>(0);

    static_cast<decltype(t.content)>(nullptr);
};
# endif

/**
 * This class acts as a RAII compatible wrapper class for the C vector of DC4C.
 *
 * @tparam T the C DC4C vector type to be managed by this wrapper class
 */
template<
# if __cplusplus >= 202002L
is_dc4c_vector
# else
typename
# endif
T>
class vector {
    /** The underlying C vector. */
    T underlying;

public:
    /** The type used for the size of the vector. */
    using size_type = typename std::decay<decltype(underlying.count)>::type;
    /** The type stored in the underlying vector. */
    using value_type = typename std::decay<decltype(*underlying.content)>::type;

    constexpr inline vector(): underlying(vector_initializer) {}

    __DC4C_CONSTEXPR_SINCE_CXX14 inline vector(const vector& other) {
        vector_copy(&underlying, &other.underlying);
    }

    __DC4C_CONSTEXPR_SINCE_CXX14 inline vector(vector&& other) noexcept: underlying(other.underlying) {
        vector_init(&other.underlying);
    }

    /**
     * Constructs a wrapper vector from the given C vector.
     *
     * @param cVector the C vector to be copied into this wrapper
     */
    __DC4C_CONSTEXPR_SINCE_CXX14 inline vector(const T* cVector) {
        vector_copy(&underlying, cVector);
    }

    /**
     * Constructs a wrapper from the given C vector.
     *
     * @param cVector the C vector to be copied into this wrapper
     */
    constexpr inline vector(const T& cVector): vector(&cVector) {}

    /**
     * Constructs a DC4C vector from the given C++ @c std::vector .
     *
     * @param other the C++ standard vector to be copied
     */
    __DC4C_CONSTEXPR_SINCE_CXX14 inline vector(const std::vector<value_type>& other): underlying(vector_initializer) {
        reserve(other.size());

        for (const auto& element : other) {
            push_back(element);
        }
    }

    /**
     * Constructs a DC4C wrapper vector from the given iterators.
     *
     * @tparam InputIt the type of the iterators
     * @param begin the beginning iterator of the range to be copied
     * @param end the past the end iterator of the range to be copied
     */
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

    /**
     * Assigns the given DC4C C vector to this instance.
     *
     * @param cVector the C vector to be copied
     * @return @c *this
     */
    __DC4C_CONSTEXPR_SINCE_CXX14 inline auto operator=(const T* cVector) -> vector& {
        vector_destroy(&underlying);
        vector_copy(&underlying, cVector);
        return *this;
    }

    /**
     * Assigns the given DC4C C vector to this instance.
     *
     * @param cVector the C vector to be copied
     * @return @c *this
     */
    __DC4C_CONSTEXPR_SINCE_CXX14 inline auto operator=(const T& cVector) -> vector& {
        return *this = &cVector;
    }

    /**
     * @brief Returns the underlying C vector.
     *
     * It is safe to manipulate the returned DC4C C vector.
     *
     * @return the underlying C vector
     */
    __DC4C_CONSTEXPR_SINCE_CXX14 inline auto data() -> T& {
        return underlying;
    }

    /**
     * @brief Returns the underlying C vector.
     *
     * @return the underlying C vector
     */
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

    /**
     * @brief Returns the element at the given position.
     *
     * The position is not range checked.
     *
     * @param position the position
     * @return the element at the given position
     */
    constexpr inline auto operator[](size_type position) const noexcept -> value_type& {
        return underlying.content[position];
    }

    /**
     * Returns an iterator to the first stored element.
     *
     * @return a pointer to the first stored element
     */
    constexpr inline auto begin() const noexcept -> value_type* {
        return underlying.content;
    }

    /**
     * Returns a past the end iterator.
     *
     * @return a pointer past the last stored element
     */
    constexpr inline auto end() const noexcept -> value_type* {
        return underlying.content + underlying.count;
    }

    /**
     * Adds the given value at the end of the vector.
     *
     * @param value the value to be stored
     * @throw std::bad_alloc if the memory allocation failed
     */
    __DC4C_CONSTEXPR_SINCE_CXX14 inline void push_back(const value_type& value) {
        if (!vector_push_back(&underlying, value)) {
            throw std::bad_alloc();
        }
    }

    /**
     * Removes the last element stored in this container.
     *
     * @return the removed element
     */
    __DC4C_CONSTEXPR_SINCE_CXX14 inline auto pop_back() -> value_type {
        return vector_pop_back(&underlying);
    }

    /**
     * @brief Erases the element at the given position.
     *
     * The given position is not range checked.
     *
     * @param index the index of the element to be erased
     * @return the erased element
     */
    __DC4C_CONSTEXPR_SINCE_CXX14 inline auto erase(size_type index) -> value_type {
        return vector_erase(&underlying, index);
    }

    /**
     * @brief Inserts the given value at the given position.
     *
     * If the position is invalid, the given value is added at the end of the vector.
     *
     * @param value the value to be inserted
     * @param index the position at which to insert the given value
     * @throw std::bad_alloc if the allocation failed
     */
    __DC4C_CONSTEXPR_SINCE_CXX14 inline void insert(const value_type& value, size_type index) {
        if (!vector_insert(&underlying, value, index)) {
            throw std::bad_alloc();
        }
    }

    /**
     * Reserves enough storage to hold the given amount of objects.
     *
     * @param newCap the amount of elements the vector should be able to store
     * @throw std::bad_alloc if the allocation failed
     */
    __DC4C_CONSTEXPR_SINCE_CXX14 inline void reserve(size_type newCap) {
        if (!vector_reserve(&underlying, newCap)) {
            throw std::bad_alloc();
        }
    }

    /**
     * Removes all elements stored in this vector.
     */
    __DC4C_CONSTEXPR_SINCE_CXX14 inline void clear() {
        vector_clear(&underlying);
    }

    /**
     * Returns the amount of objects currently held by this vector.
     *
     * @return the amount of objects currently held
     */
    constexpr inline auto size() const noexcept -> size_type {
        return vector_size(&underlying);
    }

    /**
     * Returns the amounf of objects this vector is currently capable to hold.
     *
     * @return the amount of objects this vector currently can hold
     */
    constexpr inline auto capacity() const noexcept -> size_type {
        return vector_capacity(&underlying);
    }

    /**
     * Returns the underlying storage of the C vector managed by this wrapper.
     *
     * @return the underlying storage of the managed C vector
     */
    __DC4C_CONSTEXPR_SINCE_CXX14 inline auto getUnderlyingData() noexcept -> value_type* {
        return underlying.content;
    }

    /**
     * Returns the underlying storage of the C vector managed by this wrapper.
     *
     * @return the underlying storage of the managed C vector
     */
    constexpr inline auto getUnderlyingData() const noexcept -> value_type* {
        return underlying.content;
    }

    /**
     * Sorts the vector using the given comparator.
     *
     * @tparam C the comparator type used to sort the vector
     * @param comp the comparator functor used to sort the vector
     */
    template<typename C = std::less<value_type>>
    __DC4C_CONSTEXPR_SINCE_CXX20 inline void sort(const C& comp = C()) {
        std::sort(begin(), end(), comp);
    }
};
}

#define __dc4c_vector_cxx_wrapper(name, actual) \
namespace dc4c {                         \
using vector_##name = vector<actual>;    \
}

# endif /* __DC4C_vector_hpp */
#endif /* !__DC4C_vector_h */
