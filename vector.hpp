/*
 * DC4C - Standard data containers for C
 *
 * Copyright (C) 2023 - 2024  mhahnFr
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
 #error This library requires C++11 or newer.
#endif

#ifndef __DC4C_vector_h
 #warning Wrong inclusion of "vector.hpp" redirected to #include "vector.h"!
 #include "vector.h"
#else
 #ifndef __DC4C_vector_hpp
 #define __DC4C_vector_hpp

 #include <vector>

 #define vector_methods_cxx(type, name)                                                    \
 namespace dc4c {                                                                          \
 class vector_bridge_##name {                                                              \
     vector_##name underlying;                                                             \
                                                                                           \
 public:                                                                                   \
     inline vector_bridge_##name() {                                                       \
         vector_##name##_create(&underlying);                                              \
     }                                                                                     \
                                                                                           \
     inline vector_bridge_##name(const vector_bridge_##name & other) {                     \
         vector_##name##_copy(&underlying, &other.underlying);                             \
     }                                                                                     \
                                                                                           \
     inline vector_bridge_##name(vector_bridge_##name && other) {                          \
         vector_##name##_destroy(&underlying);                                             \
         underlying = other.underlying;                                                    \
         vector_##name##_create(&other.underlying);                                        \
     }                                                                                     \
                                                                                           \
     inline vector_bridge_##name(const std::vector<type> & other) {                        \
         vector_##name##_create(&underlying);                                              \
         vector_##name##_reserve(&underlying, other.capacity());                           \
                                                                                           \
         for (const auto & element : other) {                                              \
             vector_##name##_push_back(&underlying, element);                              \
         }                                                                                 \
     }                                                                                     \
                                                                                           \
     template<typename InputIt>                                                            \
     inline vector_bridge_##name(InputIt begin, InputIt end) {                             \
         vector_##name##_create(&underlying);                                              \
         for (; begin != end; ++begin) {                                                   \
             vector_##name##_push_back(&underlying, *begin);                               \
         }                                                                                 \
     }                                                                                     \
                                                                                           \
     inline ~vector_bridge_##name() {                                                      \
         vector_##name##_destroy(&underlying);                                             \
     }                                                                                     \
                                                                                           \
     inline auto operator=(const vector_bridge_##name & other) -> vector_bridge_##name & { \
         vector_##name##_destroy(&underlying);                                             \
         vector_##name##_copy(&underlying, &other.underlying);                             \
         return *this;                                                                     \
     }                                                                                     \
                                                                                           \
     inline auto operator=(vector_bridge_##name && other) -> vector_bridge_##name & {      \
         vector_##name##_destroy(&underlying);                                             \
         underlying = other.underlying;                                                    \
         vector_##name##_create(&other.underlying);                                        \
         return *this;                                                                     \
     }                                                                                     \
                                                                                           \
     inline auto data() -> vector_##name & {                                               \
         return underlying;                                                                \
     }                                                                                     \
                                                                                           \
     constexpr auto data() const -> const vector_##name & {                                \
         return underlying;                                                                \
     }                                                                                     \
                                                                                           \
     inline operator vector_##name *() {                                                   \
         return &underlying;                                                               \
     }                                                                                     \
                                                                                           \
     constexpr inline operator const vector_##name *() const {                             \
         return &underlying;                                                               \
     }                                                                                     \
                                                                                           \
     inline operator std::vector<type>() const {                                           \
         auto toReturn = std::vector<type>();                                              \
         toReturn.reserve(underlying.cap);                                                 \
         for (size_t i = 0; i < underlying.count; ++i) {                                   \
             toReturn.push_back(underlying.content[i]);                                    \
         }                                                                                 \
         return toReturn;                                                                  \
     }                                                                                     \
                                                                                           \
     inline auto operator->() -> vector_##name * {                                         \
         return *this;                                                                     \
     }                                                                                     \
                                                                                           \
     constexpr inline auto operator->() const -> const vector_##name * {                   \
         return *this;                                                                     \
     }                                                                                     \
                                                                                           \
     constexpr inline auto operator[](const size_t position) const noexcept -> type & {    \
         return underlying.content[position];                                              \
     }                                                                                     \
                                                                                           \
     constexpr inline auto begin() const noexcept -> type * {                              \
         return underlying.content;                                                        \
     }                                                                                     \
                                                                                           \
     constexpr inline auto end() const noexcept -> type * {                                \
         return underlying.content + underlying.count;                                     \
     }                                                                                     \
                                                                                           \
     inline void push_back(const type& value) {                                            \
         if (!vector_##name##_push_back(*this, value)) {                                   \
             throw std::bad_alloc();                                                       \
         }                                                                                 \
     }                                                                                     \
                                                                                           \
     inline void push_back(type&& value) {                                                 \
         if (!vector_##name##_push_back(*this, value)) {                                   \
             throw std::bad_alloc();                                                       \
         }                                                                                 \
     }                                                                                     \
                                                                                           \
     inline auto pop_back() -> type {                                                      \
         return vector_##name##_pop_back(*this);                                           \
     }                                                                                     \
                                                                                           \
     inline auto erase(std::size_t index) -> type {                                        \
         return vector_##name##_erase(*this, index);                                       \
     }                                                                                     \
                                                                                           \
     inline void insert(const type& value, std::size_t index) {                            \
         if (!vector_##name##_insert(*this, value, index)) {                               \
             throw std::bad_alloc();                                                       \
         }                                                                                 \
     }                                                                                     \
                                                                                           \
     inline void insert(type&& value, std::size_t index) {                                 \
         if (!vector_##name##_insert(*this, value, index)) {                               \
             throw std::bad_alloc();                                                       \
         }                                                                                 \
     }                                                                                     \
                                                                                           \
     inline void reserve(std::size_t newCap) {                                             \
         if (!vector_##name##_reserve(*this, newCap)) {                                    \
             throw std::bad_alloc();                                                       \
         }                                                                                 \
     }                                                                                     \
                                                                                           \
     inline void clear() {                                                                 \
         vector_##name##_clear(*this);                                                     \
     }                                                                                     \
                                                                                           \
     constexpr inline auto size() const noexcept -> std::size_t {                          \
         return underlying.count;                                                          \
     }                                                                                     \
                                                                                           \
     constexpr inline auto capacity() const noexcept -> std::size_t {                      \
         return underlying.cap;                                                            \
     }                                                                                     \
                                                                                           \
     inline auto getUnderlyingData() noexcept -> type* {                                   \
         return underlying.content;                                                        \
     }                                                                                     \
                                                                                           \
     constexpr inline auto getUnderlyingData() const noexcept -> const type* {             \
         return underlying.content;                                                        \
     }                                                                                     \
 };                                                                                        \
 }                                                                                         \
 
 
 #endif /* __DC4C_vector_hpp */
#endif /* __DC4C_vector_h */
