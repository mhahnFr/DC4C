/*
 * DC4C - Standard data containers for C
 *
 * Copyright (C) 2025  mhahnFr
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

#ifndef __DC4C_v2_vector_h
#define __DC4C_v2_vector_h

#define vector_named(name, type) \
struct vector_##name {           \
    size_t count;                \
    size_t cap;                  \
    type*  content;              \
                                 \
    bool result;                 \
}

#define dc4c_vector(type) vector_named(type, type)

#define vector_reserve(vectorPtr, newSize)                                        \
do {                                                                              \
    (vectorPtr)->result = false;                                                  \
    if ((vectorPtr)->cap >= newSize) {                                            \
        break;                                                                    \
    }                                                                             \
                                                                                  \
    typeof((vectorPtr)->content) tmp = (typeof((vectorPtr)->content))             \
        realloc((vectorPtr)->content, sizeof(*(vectorPtr)->content) * (newSize)); \
    if (tmp == NULL) {                                                            \
        break;                                                                    \
    }                                                                             \
                                                                                  \
    (vectorPtr)->content = tmp;                                                   \
    (vectorPtr)->cap     = newSize;                                               \
    (vectorPtr)->result  = true;                                                  \
} while (0)

#endif /* __DC4C_v2_vector_h */
