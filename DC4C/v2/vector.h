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

// TODO: More version and compiler checks

#if __STDC_VERSION__ < 202311L
# include <stdbool.h>
#endif

#include <stdlib.h>
#include <string.h>

#define vector_named(name, type) \
struct vector_##name {           \
    size_t count;                \
    size_t cap;                  \
    type*  content;              \
}

#define dc4c_vector(type) vector_named(type, type)

#define vector_reserve(vectorPtr, newSize) ({                                         \
    bool result = false;                                                              \
    do {                                                                              \
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
        result = true;                                                                \
    } while (0);                                                                      \
    result;                                                                           \
})

#define vector_push_back(vectorPtr, value) ({                                                   \
    bool result = false;                                                                        \
    do {                                                                                        \
        if ((vectorPtr)->cap < (vectorPtr)->count + 1) {                                        \
            if (!vector_reserve(vectorPtr, (vectorPtr)->cap == 0 ? 1 : (vectorPtr)->cap * 2)) { \
                break;                                                                          \
            }                                                                                   \
        }                                                                                       \
                                                                                                \
        (vectorPtr)->content[(vectorPtr)->count++] = (value);                                   \
        result = true;                                                                          \
    } while (0);                                                                                \
    result;                                                                                     \
})

#define vector_pop_back(vectorPtr) ({                                                      \
    typeof(*(vectorPtr)->content) toReturn = (vectorPtr)->content[(vectorPtr)->count - 1]; \
    --(vectorPtr)->count;                                                                  \
    toReturn;                                                                              \
})

#define vector_clear(vectorPtr) \
do {                            \
    (vectorPtr)->count = 0;     \
} while (0)

#define vector_insert(vectorPtr, value, position) ({                                \
    bool result = false;                                                            \
    do {                                                                            \
        if ((position) >= (vectorPtr)->count) {                                     \
            result = vector_push_back(vectorPtr, value);                            \
            break;                                                                  \
        }                                                                           \
                                                                                    \
        if ((vectorPtr)->cap < (vectorPtr)->count + 1) {                            \
            if (!vector_reserve(vectorPtr, (vectorPtr)->cap * 2)) {                 \
                break;                                                              \
            }                                                                       \
        }                                                                           \
        memmove(&(vectorPtr)->content[(position) + 1],                              \
                &(vectorPtr)->content[(position)],                                  \
                ((vectorPtr)->count - (position)) * sizeof(*(vectorPtr)->content)); \
        (vectorPtr)->content[(position)] = (value);                                 \
        ++(vectorPtr)->count;                                                       \
        result = true;                                                              \
    } while (0);                                                                    \
    result;                                                                         \
})

#define vector_erase(vectorPtr, position) ({                                        \
    typeof(*(vectorPtr)->content) toReturn = (vectorPtr)->content[position];        \
    do {                                                                            \
        memmove(&(vectorPtr)->content[(position)],                                  \
                &(vectorPtr)->content[(position) + 1],                              \
                (--(vectorPtr)->count - position) * sizeof(*(vectorPtr)->content)); \
    } while (0);                                                                    \
    toReturn;                                                                       \
})

#define vector_forEach(vectorPtr, varname, block)                           \
for (size_t __dc4c_i = 0; __dc4c_i < (vectorPtr)->count; ++__dc4c_i) {      \
    typeof((vectorPtr)->content) varname = &(vectorPtr)->content[__dc4c_i]; \
    { block }                                                               \
}

#define vector_size(vectorPtr) ({ (vectorPtr)->count; })

#define vector_capacity(vectorPtr) ({ (vectorPtr)->cap; })

#define vector_data(vectorPtr) ({ (vectorPtr)->content; })

#define vector_iterate(vectorPtr, block) vector_forEach(vectorPtr, element, block)

#define vector_sort(vectorPtr, comp)                       \
do {                                                       \
    if ((vectorPtr)->count > 0) {                          \
        qsort((vectorPtr)->content,                        \
              (vectorPtr)->count,                          \
              (int (*)(const void*, const void*)) (comp)); \
    }                                                      \
} while (0)

#define vector_search(vectorPtr, keyPtr, comp) ({                 \
    typeof((vectorPtr)->content) toReturn = NULL;                 \
    if ((vectorPtr)->count > 0) {                                 \
        toReturn = (typeof((vectorPtr)->content)) bsearch(        \
                       (const void*) (keyPtr),                    \
                       (const void*) (vectorPtr)->content,        \
                       (vectorPtr)->count,                        \
                       sizeof(*(vectorPtr)->content),             \
                       (int (*)(const void*, const void*)) (comp) \
                   );                                             \
    }                                                             \
    toReturn;                                                     \
})

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
} while (0)

#define vector_initializer { 0, 0, NULL }

#define vector_copy(lhsPtr, rhsPtr)                                \
do {                                                               \
    vector_init(lhsPtr);                                           \
    vector_reserve(lhsPtr, (rhsPtr)->cap);                         \
    memcpy((lhsPtr)->content, (rhsPtr)->content, (rhsPtr)->count); \
    (lhsPtr)->count = (rhsPtr)->count;                             \
} while (0)

#define typedef_vector_named(name, type)       \
vector_named(name, type);                      \
typedef struct vector_##name vector_##name##_t

#define typedef_vector(type) typedef_vector_named(type, type)

#endif /* __DC4C_v2_vector_h */
