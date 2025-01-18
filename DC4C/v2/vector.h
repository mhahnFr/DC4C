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

#include <stdbool.h> // TODO: Only when __STDC_VERSION__ < C17
#include <stdlib.h>

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
    if ((vectorPtr)->cap >= (newSize)) {                                          \
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
    (vectorPtr)->cap     = (newSize);                                             \
    (vectorPtr)->result  = true;                                                  \
} while (0)

#define vector_push_back(vectorPtr, value)                                           \
do {                                                                                 \
    (vectorPtr)->result = false;                                                     \
    if ((vectorPtr)->cap < (vectorPtr)->count + 1) {                                 \
        vector_reserve(vectorPtr, (vectorPtr)->cap == 0 ? 1 : (vectorPtr)->cap * 2); \
        if (!(vectorPtr)->result) break;                                             \
    }                                                                                \
                                                                                     \
    (vectorPtr)->content[(vectorPtr)->count++] = (value);                            \
    (vectorPtr)->result = true;                                                      \
} while (0)

#define vector_pop_back(vectorPtr) (vectorPtr)->content[(vectorPtr)->count--]

#define vector_clear(vectorPtr) \
do {                            \
    (vectorPtr)->count = 0;     \
} while (0)

#define vector_insert(vectorPtr, value, position)                               \
do {                                                                            \
    (vectorPtr)->result = false;                                                \
    if ((position) >= (vectorPtr)->count) {                                     \
        vector_push_back(vectorPtr, value);                                     \
        break;                                                                  \
    }                                                                           \
                                                                                \
    if ((vectorPtr)->cap < (vectorPtr)->count + 1) {                            \
        vector_reserve(vectorPtr, (vectorPtr)->cap * 2);                        \
        if (!(vectorPtr)->result) break;                                        \
    }                                                                           \
    memmove(&(vectorPtr)->content[(position) + 1],                              \
            &(vectorPtr)->content[(position)],                                  \
            ((vectorPtr)->count - (position)) * sizeof(*(vectorPtr)->content)); \
    (vectorPtr)->content[(position)] = (value);                                 \
    ++(vectorPtr)->count;                                                       \
    (vectorPtr)->result = true;                                                 \
} while (0)

#define vector_erase(vectorPtr, position)                                       \
do {                                                                            \
    memmove(&(vectorPtr)->content[(position)],                                  \
            &(vectorPtr)->content[(position) + 1],                              \
            (--(vectorPtr)->count - position) * sizeof(*(vectorPtr)->content)); \
} while (0)

#define vector_forEach(vectorPtr, varname, block)                           \
for (size_t __dc4c_i = 0; __dc4c_i < (vectorPtr)->count; ++__dc4c_i) {      \
    typeof((vectorPtr)->content) varname = &(vectorPtr)->content[__dc4c_i]; \
    { block }                                                               \
}

#define vector_iterate(vectorPtr, block) vector_forEach(vectorPtr, element, block)

#define vector_destroy(vectorPtr) \
do {                              \
    free((vectorPtr)->content);   \
} while (0)

#define vector_destroyWith(vectorPtr, valueFunc)    \
do {                                                \
    vector_iterate(vectorPtr, valueFunc(*element);) \
    vector_destroy(vectorPtr);                      \
} while (0)

#define vector_destroyWithPtr(vectorPtr, ptrFunc) \
do {                                              \
    vector_iterate(vectorPtr, ptrFunc(element);)  \
    vector_destroy(vectorPtr);                    \
} while (0)

#define vector_init(vectorPtr)   \
do {                             \
    (vectorPtr)->cap     = 0;    \
    (vectorPtr)->count   = 0;    \
    (vectorPtr)->content = NULL; \
    (vectorPtr)->result  = true; \
} while (0)

#define vector_initializer { 0, 0, NULL, true }

#define vector_copy(lhsPtr, rhsPtr)                                \
do {                                                               \
    vector_init(lhsPtr);                                           \
    vector_reserve(lhsPtr, (rhsPtr)->cap);                         \
    memcpy((lhsPtr)->content, (rhsPtr)->content, (rhsPtr)->count); \
    (lhsPtr)->count = (rhsPtr)->count;                             \
} while (0)

#endif /* __DC4C_v2_vector_h */
