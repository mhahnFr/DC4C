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

#ifndef optional_h
#define optional_h

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

#endif /* optional_h */
