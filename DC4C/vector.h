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

#ifndef __DC4C_vector_h
#define __DC4C_vector_h

// TODO: More version and compiler checks

#if __STDC_VERSION__ < 202311L
# include <stdbool.h>
#endif

#include <stdlib.h>
#include <string.h>

/**
 * Defines the vector structure.
 *
 * @param name the name of the vector
 * @param type the contained type
 */
#define __dc4c_vector_named(name, type) \
struct vector_##name {                  \
    size_t count;                       \
    size_t cap;                         \
    type*  content;                     \
}

#ifdef __cplusplus
# define __DC4C_TYPEOF(expr) decltype(expr)
#else
# define __DC4C_TYPEOF(expr) typeof(expr)
#endif

/**
 * @brief Allocates enough storage for the given vector to hold at least the given
 * amount of objects.
 *
 * If the allocation failed, the content of the given vector is left unchanged.
 *
 * @param vectorPtr the pointer to a DC4C vector
 * @param newSize the new amount of objects the vector should be able to hold
 * @return whether the vector holds enough memory
 */
#define vector_reserve(vectorPtr, newSize) ({                                      \
    bool __vr_result = false;                                                      \
    do {                                                                           \
        __DC4C_TYPEOF((vectorPtr)) __v_vr = (vectorPtr);                           \
        size_t __s_vr = (size_t) (newSize);                                        \
                                                                                   \
        if (__v_vr->cap >= __s_vr) {                                               \
            __vr_result = true;                                                    \
            break;                                                                 \
        }                                                                          \
                                                                                   \
        __DC4C_TYPEOF(__v_vr->content) __vr_tmp = (__DC4C_TYPEOF(__v_vr->content)) \
            realloc(__v_vr->content, sizeof(*__v_vr->content) * __s_vr);           \
        if (__vr_tmp == NULL) {                                                    \
            break;                                                                 \
        }                                                                          \
                                                                                   \
        __v_vr->content = __vr_tmp;                                                \
        __v_vr->cap     = __s_vr;                                                  \
        __vr_result = true;                                                        \
    } while (0);                                                                   \
    __vr_result;                                                                   \
})

/**
 * @brief Adds the given value at the end of the given vector.
 *
 * If the allocation failed, the content of the given vector is left unchanged.
 *
 * @param vectorPtr th pointer to the vector
 * @param value the value to be added
 * @return whether the value was added successfully
 */
#define vector_push_back(vectorPtr, value) ({                                         \
    bool __vpb_result = false;                                                        \
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
        __vpb_result = true;                                                          \
    } while (0);                                                                      \
    __vpb_result;                                                                     \
})

/**
 * Removes the last element of the given vector.
 *
 * @param vectorPtr the pointer to the vector
 * @return the removed value
 */
#define vector_pop_back(vectorPtr) ({                                                             \
    __DC4C_TYPEOF((vectorPtr)) __v_vpopb = (vectorPtr);                                           \
    __DC4C_TYPEOF(*__v_vpopb->content) __vpb_toReturn = __v_vpopb->content[__v_vpopb->count - 1]; \
    --__v_vpopb->count;                                                                           \
    __vpb_toReturn;                                                                               \
})

/**
 * Removes all content of the given vector.
 *
 * @param vectorPtr the pointer to the vector
 */
#define vector_clear(vectorPtr) \
do {                            \
    (vectorPtr)->count = 0;     \
} while (0)

/**
 * @brief Inserts the given value into the given vector at the given position.
 *
 * If the position is greater than the size of the vector, the value is added
 * at the end of the vector. If the position is smaller than zero, the value is
 * added at the beginning of the vector.<br>
 * In case that the allocation failed, the content of the vector is left
 * unchanged.
 *
 * @param vectorPtr the pointer to the vector
 * @param value the value to be inserted
 * @param position the position to insert the value at
 * @return whether the value was inserted successfully
 */
#define vector_insert(vectorPtr, value, position) ({                  \
    bool __vi_result = false;                                         \
    do {                                                              \
        __DC4C_TYPEOF((vectorPtr)) __v_vi  = (vectorPtr);             \
        __DC4C_TYPEOF((value))     __vl_vi = (value);                 \
        __DC4C_TYPEOF((position))  __p_vi  = (position);              \
                                                                      \
        if (__p_vi >= __v_vi->count) {                                \
            __vi_result = vector_push_back(__v_vi, __vl_vi);          \
            break;                                                    \
        } else if (__p_vi < 0) {                                      \
            __p_vi = 0;                                               \
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
        __vi_result = true;                                           \
    } while (0);                                                      \
    __vi_result;                                                      \
})

/**
 * @brief Erases the value at the given position.
 *
 * The given position must be in the range [0 ... size - 1].
 *
 * @param vectorPtr the pointer to the vector
 * @param position the position to be erased
 * @return the erased value
 */
#define vector_erase(vectorPtr, position) ({                                 \
    __DC4C_TYPEOF((vectorPtr)) __v_ve = (vectorPtr);                         \
    __DC4C_TYPEOF((position)) __p_ve = (position);                           \
                                                                             \
    __DC4C_TYPEOF(*__v_ve->content) __ve_toReturn = __v_ve->content[__p_ve]; \
    memmove(&__v_ve->content[__p_ve],                                        \
            &__v_ve->content[__p_ve + 1],                                    \
            (--__v_ve->count - __p_ve) * sizeof(*__v_ve->content));          \
    __ve_toReturn;                                                           \
})

/**
 * Iterates over the content of the given vector and executes the given block
 * of code for each of its elements.
 *
 * @param vectorPtr the pointer to the vector
 * @param varname the name of the iteration variable
 * @param block the code to execute for each element
 */
#define vector_forEach(vectorPtr, varname, block)                              \
do {                                                                           \
    __DC4C_TYPEOF((vectorPtr)) __v_vfe = (vectorPtr);                          \
    for (size_t __dc4c_i = 0; __dc4c_i < __v_vfe->count; ++__dc4c_i) {         \
        __DC4C_TYPEOF(__v_vfe->content) varname = &__v_vfe->content[__dc4c_i]; \
        { block }                                                              \
    }                                                                          \
} while (0)

/**
 * Returns the amount of elements held by the given vector.
 *
 * @param vectorPtr the pointer to the vector
 * @return the amount of elements in the given vector
 */
#define vector_size(vectorPtr) ({ (vectorPtr)->count; })

/**
 * Returns the amount of objects the given vector is currently capable to hold.
 *
 * @param vectorPtr the pointer to the vector
 * @return the amount of elements the given vector can hold
 */
#define vector_capacity(vectorPtr) ({ (vectorPtr)->cap; })

/**
 * Returns the underlying content of the given vector.
 *
 * @param vectorPtr the pointer to the vector
 * @return the underlying content of the given vector
 */
#define vector_data(vectorPtr) ({ (vectorPtr)->content; })

/**
 * @brief Calls the given block of code for each of the elements in the given vector.
 *
 * The iteration variable is called @c element .
 *
 * @param vectorPtr the pointer to the vector
 * @param block the code to be executed for each element in the given vector
 */
#define vector_iterate(vectorPtr, block) vector_forEach(vectorPtr, element, block)

/**
 * Sorts the given vector using the given comparison function.
 *
 * @param vectorPtr the pointer to the vector
 * @param comp the comparison function
 */
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

/**
 * @brief Searches the given vector for the given element.
 *
 * The vector is searched using @c bsearch and should be sorted.
 *
 * @param vectorPtr the pointer to the vector
 * @param keyPtr the pointer to the searched element
 * @param comp the comparison function used to sort the vector
 * @return the pointer to the searched element in the vector or @c NULL if not found
 */
#define vector_search(vectorPtr, keyPtr, comp) ({                       \
    __DC4C_TYPEOF((vectorPtr)) __v_vse = (vectorPtr);                   \
                                                                        \
    __DC4C_TYPEOF(__v_vse->content) __vse_toReturn = NULL;              \
    if (__v_vse->count > 0) {                                           \
        __vse_toReturn = (__DC4C_TYPEOF(__v_vse->content)) bsearch(     \
                             (const void*) (keyPtr),                    \
                             (const void*) __v_vse->content,            \
                             __v_vse->count,                            \
                             sizeof(*__v_vse->content),                 \
                             (int (*)(const void*, const void*)) (comp) \
                         );                                             \
    }                                                                   \
    __vse_toReturn;                                                     \
})

/**
 * @brief Destroys the given vector.
 *
 * The destroyed vector must be reconstructed before being used again. If the
 * contained objects need to be destroyed as well, consider using
 * @c vector_destroyWith or @c vector_destroyWithPtr .
 *
 * @param vectorPtr the pointer to the vector
 */
#define vector_destroy(vectorPtr) \
do {                              \
    free((vectorPtr)->content);   \
} while (0)

/**
 * @brief Destroys the given vector and its contents.
 *
 * Calls the given function for each object contained in the given vector. The
 * vector must be reconstructed before being used again.
 *
 * @param vectorPtr the pointer to the given vector
 * @param valueFunc the function to destroy the contained objects
 */
#define vector_destroyWith(vectorPtr, valueFunc)      \
do {                                                  \
    __DC4C_TYPEOF((vectorPtr)) __v_vdw = (vectorPtr); \
                                                      \
    vector_iterate(__v_vdw, valueFunc(*element););    \
    vector_destroy(__v_vdw);                          \
} while (0)

/**
 * @brief Destroys the given vector and its contents.
 *
 * Calls the given function for each object contained in the given vector. The
 * vector must be reconstructed before being used again.
 *
 * @param vectorPtr the pointer to the vector
 * @param ptrFunc the function to destroy the contained objects
 */
#define vector_destroyWithPtr(vectorPtr, ptrFunc)      \
do {                                                   \
    __DC4C_TYPEOF((vectorPtr)) __v_vdwp = (vectorPtr); \
                                                       \
    vector_iterate(__v_vdwp, ptrFunc(element););       \
    vector_destroy(__v_vdwp);                          \
} while (0)

/**
 * Initializes the given vector.
 *
 * @param vectorPtr the pointer to the vector
 */
#define vector_init(vectorPtr)                        \
do {                                                  \
    __DC4C_TYPEOF((vectorPtr)) __v_vin = (vectorPtr); \
                                                      \
    __v_vin->cap     = 0;                             \
    __v_vin->count   = 0;                             \
    __v_vin->content = NULL;                          \
} while (0)

/** The initial values for a vector. */
#define vector_initializer { 0, 0, NULL }

/**
 * Copies the given vector into the given vector.
 *
 * @param lhsPtr the pointer to the target vector
 * @param rhsPtr the pointer to the vector to be copied
 */
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

#ifndef __dc4c_vector_cxx_wrapper
# define __dc4c_vector_cxx_wrapper(name, actual)
#endif

/**
 * Defines a vector of the given name and containing the given type.
 *
 * @param name the name of the vector
 * @param type the contained type
 */
#define typedef_vector_named(name, type)        \
__dc4c_vector_named(name, type);                \
__dc4c_vector_cxx_wrapper(name, vector_##name); \
typedef struct vector_##name vector_##name##_t

/**
 * Defines a vector containing the given type.
 *
 * @param type the contained type
 */
#define typedef_vector(type) typedef_vector_named(type, type)

#endif /* __DC4C_vector_h */
