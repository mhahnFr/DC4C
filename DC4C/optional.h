/*
 * DC4C - Standard data containers for C
 *
 * Written in 2023 - 2026 by mhahnFr
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

#ifndef _dc4c_optional_h
#define _dc4c_optional_h

#include <stdbool.h>

#ifdef __cplusplus
# include "optional.hpp"
#else
# define _dc4c_optional_methods_cxx(type, name)
#endif

/**
 * Defines the optional structure.
 *
 * @param name the name of the optional
 * @param type the contained type
 */
#define _dc4c_optional_named(name, type) \
struct optional_##name {                 \
    bool has_value;                      \
    type value;                          \
}

/**
 * Defines the helper functions for the optional.
 *
 * @param type the contained type
 * @param name the name of the optional
 */
#define _dc4c_optional_methods(type, name) \
_dc4c_optional_methods_cxx(type, name)

/**
 * @brief Defines an optional containing the given type.
 *
 * The helper functions are defined here as well. If compiled with C++17 or
 * newer, the C++ helper functions are also defined here.
 *
 * @param name the name of the optional
 * @param type the contained type
 */
#define typedef_optional_named(name, type) \
_dc4c_optional_named(name, type);          \
_dc4c_optional_methods(type, name)         \
typedef struct optional_##name optional_##name##_t

/**
 * @brief Defines an optional containing the given type.
 *
 * The helper functions are defined here as well. If compiled with C++17 or
 * newer, the C++ helper functions are also defined here.
 *
 * @param type the type the optional should contain
 */
#define typedef_optional(type) typedef_optional_named(type, type)

#endif /* _dc4c_optional_h */
