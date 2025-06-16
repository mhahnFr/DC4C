/*
 * DC4C - Standard data containers for C
 *
 * Written in 2023 - 2024 by mhahnFr
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

#ifndef __DC4C_pair_h
#define __DC4C_pair_h

#ifdef __cplusplus
 #include "pair.hpp"
#else
 #define pair_namespace_begin
 #define pair_namespace_end
 #define pair_namespace_name
 #define pair_methods_cxx(type1, type2, name)
#endif

#define pair_named(name, type1, type2) \
    pair_namespace_begin               \
        struct pair_##name {           \
            type1 first;               \
            type2 second;              \
        }                              \
    pair_namespace_end

#define dc4c_pair(type1, type2) pair_named(type1 ## _ ## type2, type1, type2)

#define pair_methods(type1, type2, name)                                                           \
static inline struct pair_namespace_name pair_##name make_pair_##name(type1 first, type2 second) { \
    struct pair_namespace_name pair_##name toReturn = { first, second };                           \
    return toReturn;                                                                               \
}                                                                                                  \
                                                                                                   \
pair_methods_cxx(type1, type2, name)

#define typedef_pair_named(name, type1, type2) \
pair_named(name, type1, type2);                \
pair_methods(type1, type2, name)               \
typedef struct pair_namespace_name pair_##name pair_##name##_t

#define typedef_pair(type1, type2) typedef_pair_named(type1 ## _ ## type2, type1, type2)

#endif /* __DC4C_pair_h */
