/*
 * DC4C - Standard data containers for C
 *
 * Copyright (C) 2023 - 2024  mhahnFr
 *
 * This file is part DC4C.
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
