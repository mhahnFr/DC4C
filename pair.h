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

#ifndef pair_h
#define pair_h

#ifdef __cplusplus
 #define pair_namespace_begin namespace dc4c {
 #define pair_namespace_end   ; }
 #define pair_namespace_name  dc4c::
#else
 #define pair_namespace_begin
 #define pair_namespace_end
 #define pair_namespace_name
#endif

#define pair_named(name, type1, type2) \
    pair_namespace_begin               \
        struct pair_##name {           \
            type1 first;               \
            type2 second;              \
        }                              \
    pair_namespace_end

#define dc4c_pair(type1, type2) pair_named(type1 ## _ ## type2, type1, type2)

#ifdef __cplusplus
 #include <utility>

 #define pair_cpp_conversions(type1, type2, name)                                                 \
 namespace dc4c {                                                                                 \
 constexpr static inline auto to_cpp(const dc4c::pair_##name & self) -> std::pair<type1, type2> { \
     return std::make_pair(self.first, self.second);                                              \
 }                                                                                                \
                                                                                                  \
 constexpr static inline auto to_dc4c(const std::pair<type1, type2> & p) -> dc4c::pair_##name {   \
     return make_pair_##name(p.first, p.second);                                                  \
 }                                                                                                \
 }
#else
#define pair_cpp_conversions(type1, type2, name)
#endif

#define pair_methods(type1, type2, name)                                                           \
static inline struct pair_namespace_name pair_##name make_pair_##name(type1 first, type2 second) { \
    struct pair_namespace_name pair_##name toReturn = { .first = first, .second = second };        \
    return toReturn;                                                                               \
}                                                                                                  \
                                                                                                   \
pair_cpp_conversions(type1, type2, name)

#define typedef_pair_named(name, type1, type2) \
pair_named(name, type1, type2);                \
pair_methods(type1, type2, name)               \
typedef struct pair_namespace_name pair_##name pair_##name##_t

#define typedef_pair(type1, type2) typedef_pair_named(type1 ## _ ## type2, type1, type2)

#endif /* pair_h */
