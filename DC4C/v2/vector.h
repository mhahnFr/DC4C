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

#ifdef __cplusplus
# define __DC4C_TYPEOF(expr) decltype(expr)
#else
# define __DC4C_TYPEOF(expr) typeof(expr)
#endif

#define vector_reserve(vectorPtr, newSize) ({                                 \
    bool result = false;                                                      \
    do {                                                                      \
        __DC4C_TYPEOF((vectorPtr)) __v_vr = (vectorPtr);                      \
        size_t __s_vr = (size_t) (newSize);                                   \
                                                                              \
        if (__v_vr->cap >= __s_vr) {                                          \
            break;                                                            \
        }                                                                     \
                                                                              \
        __DC4C_TYPEOF(__v_vr->content) tmp = (__DC4C_TYPEOF(__v_vr->content)) \
            realloc(__v_vr->content, sizeof(*__v_vr->content) * __s_vr);      \
        if (tmp == NULL) {                                                    \
            break;                                                            \
        }                                                                     \
                                                                              \
        __v_vr->content = tmp;                                                \
        __v_vr->cap     = __s_vr;                                             \
        result = true;                                                        \
    } while (0);                                                              \
    result;                                                                   \
})

#define vector_push_back(vectorPtr, value) ({                                         \
    bool result = false;                                                              \
    do {                                                                              \
        __DC4C_TYPEOF((vectorPtr)) __v_vpb  = (vectorPtr);                            \
        __DC4C_TYPEOF((value))     __vl_vpb = (value);                                \
                                                                                      \
        if (__v_vpb->cap < __v_vpb->count + 1) {                                      \
            if (!vector_reserve(__v_vpb, __v_vpb->cap == 0 ? 1 : __v_vpb->cap * 2)) { \
                break;                                                                \
            }                                                                         \
        }                                                                             \
                                                                                      \
        __v_vpb->content[__v_vpb->count++] = __vl_vpb;                                \
        result = true;                                                                \
    } while (0);                                                                      \
    result;                                                                           \
})

#define vector_pop_back(vectorPtr) ({                                                       \
    __DC4C_TYPEOF((vectorPtr)) __v_vpopb = (vectorPtr);                                     \
    __DC4C_TYPEOF(*__v_vpopb->content) toReturn = __v_vpopb->content[__v_vpopb->count - 1]; \
    --__v_vpopb->count;                                                                     \
    toReturn;                                                                               \
})

#define vector_clear(vectorPtr) \
do {                            \
    (vectorPtr)->count = 0;     \
} while (0)

#define vector_insert(vectorPtr, value, position) ({                  \
    bool result = false;                                              \
    do {                                                              \
        __DC4C_TYPEOF((vectorPtr)) __v_vi  = (vectorPtr);             \
        __DC4C_TYPEOF((value))     __vl_vi = (value);                 \
        __DC4C_TYPEOF((position))  __p_vi  = (position);              \
                                                                      \
        if (__p_vi >= __v_vi->count) {                                \
            result = vector_push_back(__v_vi, __vl_vi);               \
            break;                                                    \
        }                                                             \
                                                                      \
        if (__v_vi->cap < __v_vi->count + 1) {                        \
            if (!vector_reserve(__v_vi, __v_vi->cap * 2)) {           \
                break;                                                \
            }                                                         \
        }                                                             \
        memmove(&__v_vi->content[__p_vi + 1],                         \
                &__v_vi->content[__p_vi],                             \
                (__v_vi->count - __p_vi) * sizeof(*__v_vi->content)); \
        __v_vi->content[__p_vi] = __vl_vi;                            \
        ++__v_vi->count;                                              \
        result = true;                                                \
    } while (0);                                                      \
    result;                                                           \
})

#define vector_erase(vectorPtr, position) ({                            \
    __DC4C_TYPEOF((vectorPtr)) __v_ve = (vectorPtr);                    \
    __DC4C_TYPEOF((position)) __p_ve = (position);                      \
                                                                        \
    __DC4C_TYPEOF(*__v_ve->content) toReturn = __v_ve->content[__p_ve]; \
    do {                                                                \
        memmove(&__v_ve->content[__p_ve],                               \
                &__v_ve->content[__p_ve + 1],                           \
                (--__v_ve->count - __p_ve) * sizeof(*__v_ve->content)); \
    } while (0);                                                        \
    toReturn;                                                           \
})

#define vector_forEach(vectorPtr, varname, block)                              \
do {                                                                           \
    __DC4C_TYPEOF((vectorPtr)) __v_vfe = (vectorPtr);                          \
    for (size_t __dc4c_i = 0; __dc4c_i < __v_vfe->count; ++__dc4c_i) {         \
        __DC4C_TYPEOF(__v_vfe->content) varname = &__v_vfe->content[__dc4c_i]; \
        { block }                                                              \
    }                                                                          \
} while (0)

#define vector_size(vectorPtr) ({ (vectorPtr)->count; })

#define vector_capacity(vectorPtr) ({ (vectorPtr)->cap; })

#define vector_data(vectorPtr) ({ (vectorPtr)->content; })

#define vector_iterate(vectorPtr, block) vector_forEach(vectorPtr, element, block)

#define vector_sort(vectorPtr, comp)                       \
do {                                                       \
    __DC4C_TYPEOF((vectorPtr)) __v_vs = (vectorPtr);       \
    if (__v_vs->count > 0) {                               \
        qsort(__v_vs->content,                             \
              __v_vs->count,                               \
              sizeof(*__v_vs->content),                    \
              (int (*)(const void*, const void*)) (comp)); \
    }                                                      \
} while (0)

#define vector_search(vectorPtr, keyPtr, comp) ({                 \
    __DC4C_TYPEOF((vectorPtr)) __v_vse = (vectorPtr);             \
                                                                  \
    __DC4C_TYPEOF(__v_vse->content) toReturn = NULL;              \
    if (__v_vse->count > 0) {                                     \
        toReturn = (__DC4C_TYPEOF(__v_vse->content)) bsearch(     \
                       (const void*) (keyPtr),                    \
                       (const void*) __v_vse->content,            \
                       __v_vse->count,                            \
                       sizeof(*__v_vse->content),                 \
                       (int (*)(const void*, const void*)) (comp) \
                   );                                             \
    }                                                             \
    toReturn;                                                     \
})

#define vector_destroy(vectorPtr) \
do {                              \
    free((vectorPtr)->content);   \
} while (0)

#define vector_destroyWith(vectorPtr, valueFunc)      \
do {                                                  \
    __DC4C_TYPEOF((vectorPtr)) __v_vdw = (vectorPtr); \
                                                      \
    vector_iterate(__v_vdw, valueFunc(*element););    \
    vector_destroy(__v_vdw);                          \
} while (0)

#define vector_destroyWithPtr(vectorPtr, ptrFunc)      \
do {                                                   \
    __DC4C_TYPEOF((vectorPtr)) __v_vdwp = (vectorPtr); \
                                                       \
    vector_iterate(__v_vdwp, ptrFunc(element););       \
    vector_destroy(__v_vdwp);                          \
} while (0)

#define vector_init(vectorPtr)                        \
do {                                                  \
    __DC4C_TYPEOF((vectorPtr)) __v_vin = (vectorPtr); \
                                                      \
    __v_vin->cap     = 0;                             \
    __v_vin->count   = 0;                             \
    __v_vin->content = NULL;                          \
} while (0)

#define vector_initializer { 0, 0, NULL }

#define vector_copy(lhsPtr, rhsPtr)                                \
do {                                                               \
    __DC4C_TYPEOF((lhsPtr)) __v_l_vc = (lhsPtr);                   \
    __DC4C_TYPEOF((rhsPtr)) __v_r_vc = (rhsPtr);                   \
                                                                   \
    vector_init(__v_l_vc);                                         \
    vector_reserve(__v_l_vc, __v_r_vc->cap);                       \
    memcpy(__v_l_vc->content, __v_r_vc->content, __v_r_vc->count); \
    __v_l_vc->count = __v_r_vc->count;                             \
} while (0)

#ifdef __cplusplus
# include "vector.hpp"
#endif

#ifndef vector_cxx_wrapper
# define vector_cxx_wrapper(name, actual)
#endif

#define typedef_vector_named(name, type)       \
vector_named(name, type);                      \
vector_cxx_wrapper(name, vector_##name);       \
typedef struct vector_##name vector_##name##_t

#define typedef_vector(type) typedef_vector_named(type, type)

#endif /* __DC4C_v2_vector_h */
