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

#ifndef __DC4C_pair_h
#define __DC4C_pair_h

#ifdef __cplusplus
 #include "pair.hpp"
#else
 #define __dc4c_pair_namespace_begin
 #define __dc4c_pair_namespace_end
 #define __dc4c_pair_namespace_name
 #define __dc4c_pair_methods_cxx(type1, type2, name)
#endif

/**
 * Defines the pair structure using the given name and the given types.
 *
 * @param name the name of the pair
 * @param type1 the first contained type
 * @param type2 the second contained type
 */
#define __dc4c_pair_named(name, type1, type2) \
    __dc4c_pair_namespace_begin               \
        struct pair_##name {                  \
            type1 first;                      \
            type2 second;                     \
        }                                     \
    __dc4c_pair_namespace_end

/**
 * Defines the helper functions for the pair.
 *
 * @param type1 the first contained type
 * @param type2 the second contained type
 * @param name the name of the pair
 */
#define __dc4c_pair_methods(type1, type2, name)                                                           \
static inline struct __dc4c_pair_namespace_name pair_##name make_pair_##name(type1 first, type2 second) { \
    struct __dc4c_pair_namespace_name pair_##name toReturn = { first, second };                           \
    return toReturn;                                                                                      \
}                                                                                                         \
__dc4c_pair_methods_cxx(type1, type2, name)

/**
 * @brief Defines a pair containing the two given types.
 *
 * The helper functions are also defined here. If compiled in C++ mode, the C++
 * helper functions are defined here as well.
 *
 * @param name the name of the optional
 * @param type1 the first contained type
 * @param type2 the second contained type
 */
#define typedef_pair_named(name, type1, type2) \
__dc4c_pair_named(name, type1, type2);         \
__dc4c_pair_methods(type1, type2, name)        \
typedef struct __dc4c_pair_namespace_name pair_##name pair_##name##_t

/**
 * @brief Defines a pair containing the two given types.
 *
 * The helper functions are also defined here. If compiled in C++ mode, the C++
 * helper functions are defined here as well.
 *
 * @param type1 the first contained type
 * @param type2 the second contained type
 */
#define typedef_pair(type1, type2) typedef_pair_named(type1 ## _ ## type2, type1, type2)

#endif /* __DC4C_pair_h */
