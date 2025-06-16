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

#ifndef __DC4C_optional_h
#define __DC4C_optional_h

#include <stdbool.h>

#ifdef __cplusplus
 #include "optional.hpp"
#else
 #define optional_namespace_begin
 #define optional_namespace_end
 #define optional_namespace_name
 #define optional_methods_cxx(type, name)
#endif

#define optional_named(name, type) \
    optional_namespace_begin       \
        struct optional_##name {   \
            bool has_value;        \
            type value;            \
        };                         \
    optional_namespace_end

#define dc4c_optional(type) optional_named(type, type)

#define optional_methods(type, name) \
optional_methods_cxx(type, name)

#define typedef_optional_named(name, type) \
optional_named(name, type)                 \
optional_methods(type, name)               \
typedef struct optional_namespace_name optional_##name optional_##name##_t

#define typedef_optional(type) typedef_optional_named(type, type)

#endif /* __DC4C_optional_h */
