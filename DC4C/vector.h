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

#ifndef _dc4c_vector_h
#define _dc4c_vector_h

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
# error The DC4C vector requires C23 or newer or C99 or newer with GNU extensions, both with expression statements extension.
#endif

#ifdef __cplusplus
# include <cstdlib>
# include <cstring>

#else
# if __STDC_VERSION__ < 202311L
#  include <stdbool.h>
# endif

# include <stdlib.h>
# include <string.h>
#endif

/**
 * Defines the vector structure.
 *
 * @param name the name of the vector
 * @param type the contained type
 */
#define _dc4c_vector_named(name, type) \
struct vector_##name {                 \
    size_t count;                      \
    size_t cap;                        \
    type*  content;                    \
}

#ifdef __cplusplus
# define _dc4c_typeof(expr) decltype(expr)
#else
# define _dc4c_typeof(expr) typeof(expr)
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
#define vector_reserve(vectorPtr, newSize) ({                                                \
    bool _dc4c_vr_result = false;                                                            \
    do {                                                                                     \
        _dc4c_typeof((vectorPtr)) _dc4c_v_vr = (vectorPtr);                                  \
        size_t _dc4c_s_vr = (size_t) (newSize);                                              \
                                                                                             \
        if (_dc4c_v_vr->cap >= _dc4c_s_vr) {                                                 \
            _dc4c_vr_result = true;                                                          \
            break;                                                                           \
        }                                                                                    \
                                                                                             \
        _dc4c_typeof(_dc4c_v_vr->content) _dc4c_vr_tmp = (_dc4c_typeof(_dc4c_v_vr->content)) \
            realloc(_dc4c_v_vr->content, sizeof(*_dc4c_v_vr->content) * _dc4c_s_vr);         \
        if (_dc4c_vr_tmp == NULL) {                                                          \
            break;                                                                           \
        }                                                                                    \
                                                                                             \
        _dc4c_v_vr->content = _dc4c_vr_tmp;                                                  \
        _dc4c_v_vr->cap     = _dc4c_s_vr;                                                    \
        _dc4c_vr_result = true;                                                              \
    } while (0);                                                                             \
    _dc4c_vr_result;                                                                         \
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
#define vector_push_back(vectorPtr, value) ({                             \
    bool _dc4c_vpb_result = false;                                        \
    do {                                                                  \
        _dc4c_typeof((vectorPtr)) _dc4c_v_vpb  = (vectorPtr);             \
        _dc4c_typeof((value))     _dc4c_vl_vpb = (value);                 \
                                                                          \
        if (_dc4c_v_vpb->cap < _dc4c_v_vpb->count + 1) {                  \
            if (!vector_reserve(_dc4c_v_vpb, _dc4c_v_vpb->cap == 0 ?      \
                                             1 : _dc4c_v_vpb->cap * 2)) { \
                break;                                                    \
            }                                                             \
        }                                                                 \
                                                                          \
        _dc4c_v_vpb->content[_dc4c_v_vpb->count++] = _dc4c_vl_vpb;        \
        _dc4c_vpb_result = true;                                          \
    } while (0);                                                          \
    _dc4c_vpb_result;                                                     \
})

/**
 * Removes the last element of the given vector.
 *
 * @param vectorPtr the pointer to the vector
 * @return the removed value
 */
#define vector_pop_back(vectorPtr) ({                          \
    _dc4c_typeof((vectorPtr)) _dc4c_v_vpopb = (vectorPtr);     \
    _dc4c_typeof(*_dc4c_v_vpopb->content) _dc4c_vpb_toReturn = \
        _dc4c_v_vpopb->content[_dc4c_v_vpopb->count - 1];      \
    --_dc4c_v_vpopb->count;                                    \
    _dc4c_vpb_toReturn;                                        \
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
#define vector_insert(vectorPtr, value, position) ({                              \
    bool _dc4c_vi_result = false;                                                 \
    do {                                                                          \
        _dc4c_typeof((vectorPtr)) _dc4c_v_vi  = (vectorPtr);                      \
        _dc4c_typeof((value))     _dc4c_vl_vi = (value);                          \
        _dc4c_typeof((position))  _dc4c_p_vi  = (position);                       \
                                                                                  \
        if (_dc4c_p_vi >= _dc4c_v_vi->count) {                                    \
            _dc4c_vi_result = vector_push_back(_dc4c_v_vi, _dc4c_vl_vi);          \
            break;                                                                \
        } else if (_dc4c_p_vi < 0) {                                              \
            _dc4c_p_vi = 0;                                                       \
        }                                                                         \
                                                                                  \
        if (_dc4c_v_vi->cap < _dc4c_v_vi->count + 1) {                            \
            if (!vector_reserve(_dc4c_v_vi, _dc4c_v_vi->cap * 2)) {               \
                break;                                                            \
            }                                                                     \
        }                                                                         \
        memmove(&_dc4c_v_vi->content[_dc4c_p_vi + 1],                             \
                &_dc4c_v_vi->content[_dc4c_p_vi],                                 \
                (_dc4c_v_vi->count - _dc4c_p_vi) * sizeof(*_dc4c_v_vi->content)); \
        _dc4c_v_vi->content[_dc4c_p_vi] = _dc4c_vl_vi;                            \
        ++_dc4c_v_vi->count;                                                      \
        _dc4c_vi_result = true;                                                   \
    } while (0);                                                                  \
    _dc4c_vi_result;                                                              \
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
#define vector_erase(vectorPtr, position) ({                                                \
    _dc4c_typeof((vectorPtr)) _dc4c_v_ve = (vectorPtr);                                     \
    _dc4c_typeof((position)) _dc4c_p_ve = (position);                                       \
                                                                                            \
    _dc4c_typeof(*_dc4c_v_ve->content) _dc4c_ve_toReturn = _dc4c_v_ve->content[_dc4c_p_ve]; \
    memmove(&_dc4c_v_ve->content[_dc4c_p_ve],                                               \
            &_dc4c_v_ve->content[_dc4c_p_ve + 1],                                           \
            (--_dc4c_v_ve->count - _dc4c_p_ve) * sizeof(*_dc4c_v_ve->content));             \
    _dc4c_ve_toReturn;                                                                      \
})

/**
 * Iterates over the content of the given vector and executes the given block
 * of code for each of its elements.
 *
 * @param vectorPtr the pointer to the vector
 * @param varname the name of the iteration variable
 * @param block the code to execute for each element
 */
#define vector_forEach(vectorPtr, varname, block)                                    \
do {                                                                                 \
    _dc4c_typeof((vectorPtr)) _dc4c_v_vfe = (vectorPtr);                             \
    for (size_t _dc4c_i = 0; _dc4c_i < _dc4c_v_vfe->count; ++_dc4c_i) {              \
        _dc4c_typeof(_dc4c_v_vfe->content) varname = &_dc4c_v_vfe->content[_dc4c_i]; \
        { block }                                                                    \
    }                                                                                \
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
    _dc4c_typeof((vectorPtr)) _dc4c_v_vs = (vectorPtr);    \
    if (_dc4c_v_vs->count > 0) {                           \
        qsort(_dc4c_v_vs->content,                         \
              _dc4c_v_vs->count,                           \
              sizeof(*_dc4c_v_vs->content),                \
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
#define vector_search(vectorPtr, keyPtr, comp) ({                          \
    _dc4c_typeof((vectorPtr)) _dc4c_v_vse = (vectorPtr);                   \
                                                                           \
    _dc4c_typeof(_dc4c_v_vse->content) _dc4c_vse_toReturn = NULL;          \
    if (_dc4c_v_vse->count > 0) {                                          \
        _dc4c_vse_toReturn = (_dc4c_typeof(_dc4c_v_vse->content)) bsearch( \
                             (const void*) (keyPtr),                       \
                             (const void*) _dc4c_v_vse->content,           \
                             _dc4c_v_vse->count,                           \
                             sizeof(*_dc4c_v_vse->content),                \
                             (int (*)(const void*, const void*)) (comp)    \
                         );                                                \
    }                                                                      \
    _dc4c_vse_toReturn;                                                    \
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
#define vector_destroyWith(vectorPtr, valueFunc)         \
do {                                                     \
    _dc4c_typeof((vectorPtr)) _dc4c_v_vdw = (vectorPtr); \
                                                         \
    vector_iterate(_dc4c_v_vdw, valueFunc(*element););   \
    vector_destroy(_dc4c_v_vdw);                         \
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
#define vector_destroyWithPtr(vectorPtr, ptrFunc)         \
do {                                                      \
    _dc4c_typeof((vectorPtr)) _dc4c_v_vdwp = (vectorPtr); \
                                                          \
    vector_iterate(_dc4c_v_vdwp, ptrFunc(element););      \
    vector_destroy(_dc4c_v_vdwp);                         \
} while (0)

/**
 * Initializes the given vector.
 *
 * @param vectorPtr the pointer to the vector
 */
#define vector_init(vectorPtr)                           \
do {                                                     \
    _dc4c_typeof((vectorPtr)) _dc4c_v_vin = (vectorPtr); \
                                                         \
    _dc4c_v_vin->cap     = 0;                            \
    _dc4c_v_vin->count   = 0;                            \
    _dc4c_v_vin->content = NULL;                         \
} while (0)

/** The initial values for a vector. */
#define vector_initializer { 0, 0, NULL }

/**
 * Copies the given vector into the given vector.
 *
 * @param lhsPtr the pointer to the target vector
 * @param rhsPtr the pointer to the vector to be copied
 */
#define vector_copy(lhsPtr, rhsPtr)                               \
do {                                                              \
    _dc4c_typeof((lhsPtr)) _dc4c_v_l_vc = (lhsPtr);               \
    _dc4c_typeof((rhsPtr)) _dc4c_v_r_vc = (rhsPtr);               \
                                                                  \
    vector_init(_dc4c_v_l_vc);                                    \
    vector_reserve(_dc4c_v_l_vc, _dc4c_v_r_vc->cap);              \
    memcpy(_dc4c_v_l_vc->content, _dc4c_v_r_vc->content,          \
           _dc4c_v_r_vc->count * sizeof(*_dc4c_v_l_vc->content)); \
    _dc4c_v_l_vc->count = _dc4c_v_r_vc->count;                    \
} while (0)

#ifdef __cplusplus
# include "vector.hpp"
#endif

#ifndef _dc4c_vector_cxx_wrapper
# define _dc4c_vector_cxx_wrapper(name, actual)
#endif

/**
 * Defines a vector of the given name and containing the given type.
 *
 * @param name the name of the vector
 * @param type the contained type
 */
#define typedef_vector_named(name, type)       \
_dc4c_vector_named(name, type);                \
_dc4c_vector_cxx_wrapper(name, vector_##name); \
typedef struct vector_##name vector_##name##_t

/**
 * Defines a vector containing the given type.
 *
 * @param type the contained type
 */
#define typedef_vector(type) typedef_vector_named(type, type)

#endif /* _dc4c_vector_h */