/*
 * DC4C - Standard data containers for C
 *
 * Copyright (C) 2023  mhahnFr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef vector_h
 #warning Wrong inclusion of "vector.hpp" redirected to #include "vector.h"!
 #include "vector.h"
#else
 #ifndef vector_hpp
 #define vector_hpp

 #define vector_methods_cxx(type, name)                                      \
 namespace dc4c {                                                            \
 class vector_bridge_##name {                                                \
     vector_##name underlying;                                               \
                                                                             \
 public:                                                                     \
     vector_bridge_##name() {                                                \
         vector_##name##_create(&underlying);                                \
     }                                                                       \
                                                                             \
     vector_bridge_##name(const vector_bridge_##name & other) {              \
         vector_##name##_copy(&underlying, &other.underlying);               \
     }                                                                       \
                                                                             \
     vector_bridge_##name(vector_bridge_##name && other) {                   \
         vector_##name##_destroy(&underlying);                               \
         underlying = other.underlying;                                      \
         other.underlying = {};                                              \
     }                                                                       \
                                                                             \
     ~vector_bridge_##name() {                                               \
         vector_##name##_destroy(&underlying);                               \
     }                                                                       \
                                                                             \
     vector_bridge_##name & operator=(const vector_bridge_##name & other) {  \
         vector_##name##_destroy(&underlying);                               \
         vector_##name##_copy(&underlying, &other.underlying);               \
         return *this;                                                       \
     }                                                                       \
                                                                             \
     vector_bridge_##name & operator=(vector_bridge_##name && other) {       \
         vector_##name##_destroy(&underlying);                               \
         underlying = other.underlying;                                      \
         other.underlying = {};                                              \
         return *this;                                                       \
     }                                                                       \
                                                                             \
     vector_##name & data() {                                                \
         return underlying;                                                  \
     }                                                                       \
                                                                             \
     const vector_##name & data() const {                                    \
         return underlying;                                                  \
     }                                                                       \
                                                                             \
     operator vector_##name *() {                                            \
         return &underlying;                                                 \
     }                                                                       \
                                                                             \
     operator const vector_##name *() const {                                \
         return &underlying;                                                 \
     }                                                                       \
                                                                             \
     vector_##name * operator->() {                                          \
         return *this;                                                       \
     }                                                                       \
                                                                             \
     const vector_##name * operator->() const {                              \
         return *this;                                                       \
     }                                                                       \
                                                                             \
     type & operator[](const size_t position) const noexcept {               \
         return underlying.content[position];                                \
     }                                                                       \
 };                                                                          \
 }                                                                           \
 
 
 #endif /* vector_hpp */
#endif /* vector_h */
