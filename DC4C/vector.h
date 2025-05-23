/*
 * DC4C - Standard data containers for C
 *
 * Copyright (C) 2023 - 2025  mhahnFr
 *
 * This file is part of DC4C.
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

#ifndef __DC4C_vector_h
#define __DC4C_vector_h

#if !__STDC_VERSION__ && !__cplusplus
 #error This library requires C99 or newer.
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
 #include "vector.hpp"
#endif

#define vector_named(name, type)                                       \
    struct vector_##name {                                             \
        size_t count;                                                  \
        size_t cap;                                                    \
        type * content;                                                \
                                                                       \
        bool   (*push_back)     (struct vector_##name *, type);        \
        type   (*pop_back)      (struct vector_##name *);              \
        bool   (*insert)        (struct vector_##name *, type, size_t);\
        type   (*erase)         (struct vector_##name *, size_t);      \
        bool   (*reserve)       (struct vector_##name *, size_t);      \
        void   (*clear)         (struct vector_##name *);              \
        void   (*destroy)       (const struct vector_##name *);        \
        void   (*destroyWith)   (const struct vector_##name*,          \
                                 void (*)(type));                      \
        void   (*destroyWithPtr)(const struct vector_##name*,          \
                                 void (*)(type*));                     \
        size_t (*size)          (const struct vector_##name *);        \
        size_t (*capacity)      (const struct vector_##name *);        \
        type * (*data)          (const struct vector_##name *);        \
        void   (*sort)          (struct vector_##name*,                \
                                 int (*)(type*, type*));               \
        type*  (*search)        (struct vector_##name*, type*,         \
                                 int (*)(type*, type*));               \
    }

#define vector_light_named(name, type) \
    struct vector_##name {             \
        size_t count;                  \
        size_t cap;                    \
        type * content;                \
    }

#define dc4c_vector(type)  vector_named(type, type)
#define vector_light(type) vector_light_named(type, type)

#define vector_methods_c(type, name)                                                                \
static inline bool vector_##name##_reserve(struct vector_##name * v, size_t newSize) {              \
    if (v->cap >= newSize) {                                                                        \
        return true;                                                                                \
    }                                                                                               \
                                                                                                    \
    type * tmp = (type *) realloc(v->content, sizeof(type) * newSize);                              \
    if (tmp == NULL) {                                                                              \
        return false;                                                                               \
    }                                                                                               \
                                                                                                    \
    v->content = tmp;                                                                               \
    v->cap     = newSize;                                                                           \
                                                                                                    \
    return true;                                                                                    \
}                                                                                                   \
                                                                                                    \
static inline bool vector_##name##_push_back(struct vector_##name * v, type value) {                \
    if (v->cap < v->count + 1) {                                                                    \
        if (!vector_##name##_reserve(v, v->cap == 0 ? 1 : v->cap * 2)) {                            \
            return false;                                                                           \
        }                                                                                           \
    }                                                                                               \
                                                                                                    \
    v->content[v->count++] = value;                                                                 \
                                                                                                    \
    return true;                                                                                    \
}                                                                                                   \
                                                                                                    \
static inline type vector_##name##_pop_back(struct vector_##name * v) {                             \
    type toReturn = v->content[v->count - 1];                                                       \
    --v->count;                                                                                     \
    return toReturn;                                                                                \
}                                                                                                   \
                                                                                                    \
static inline bool vector_##name##_insert(struct vector_##name * v, type value, size_t position) {  \
    if (position >= v->count) {                                                                     \
        return vector_##name##_push_back(v, value);                                                 \
    }                                                                                               \
                                                                                                    \
    if (v->cap < v->count + 1) {                                                                    \
        if (!vector_##name##_reserve(v, v->cap * 2)) {                                              \
            return false;                                                                           \
        }                                                                                           \
    }                                                                                               \
    memmove(&v->content[position + 1], &v->content[position], (v->count - position) * sizeof(type));\
    v->content[position] = value;                                                                   \
    v->count++;                                                                                     \
                                                                                                    \
    return true;                                                                                    \
}                                                                                                   \
                                                                                                    \
static inline type vector_##name##_erase(struct vector_##name * v, size_t position) {               \
    type toReturn = v->content[position];                                                           \
    memmove(&v->content[position],                                                                  \
            &v->content[position + 1],                                                              \
            (--v->count - position) * sizeof(type));                                                \
    return toReturn;                                                                                \
}                                                                                                   \
                                                                                                    \
static inline size_t vector_##name##_size(const struct vector_##name * v) {                         \
    return v->count;                                                                                \
}                                                                                                   \
                                                                                                    \
static inline size_t vector_##name##_capacity(const struct vector_##name * v) {                     \
    return v->cap;                                                                                  \
}                                                                                                   \
                                                                                                    \
static inline type * vector_##name##_data(const struct vector_##name * v) {                         \
    return v->content;                                                                              \
}                                                                                                   \
                                                                                                    \
static inline void vector_##name##_destroy(const struct vector_##name * v) {                        \
    free(v->content);                                                                               \
}                                                                                                   \
                                                                                                    \
static inline void vector_##name##_destroyWith(const struct vector_##name* me,                      \
                                               void (*contentDestroy)(type)) {                      \
    if (contentDestroy != NULL) {                                                                   \
        for (size_t i = 0; i < me->count; ++i) {                                                    \
            contentDestroy(me->content[i]);                                                         \
        }                                                                                           \
    }                                                                                               \
    vector_##name##_destroy(me);                                                                    \
}                                                                                                   \
                                                                                                    \
static inline void vector_##name##_destroyWithPtr(const struct vector_##name* me,                   \
                                                  void (*contentDestroy)(type*)) {                  \
    if (contentDestroy != NULL) {                                                                   \
        vector_iterate(type, me, contentDestroy(element);)                                          \
    }                                                                                               \
    vector_##name##_destroy(me);                                                                    \
}                                                                                                   \
                                                                                                    \
static inline void vector_##name##_clear(struct vector_##name * v) {                                \
    v->count = 0;                                                                                   \
}                                                                                                   \
                                                                                                    \
static inline void vector_##name##_copy(      struct vector_##name * lhs,                           \
                                        const struct vector_##name * rhs) {                         \
    *lhs = (struct vector_##name) vector_initializer;                                               \
    vector_##name##_reserve(lhs, rhs->cap);                                                         \
    memcpy(lhs->content, rhs->content, rhs->count * sizeof(type));                                  \
    lhs->count = rhs->count;                                                                        \
}                                                                                                   \
                                                                                                    \
static inline void vector_##name##_sort(struct vector_##name* self, int (*comp)(type*, type*)) {    \
    if (self->count > 0) {                                                                          \
        qsort(self->content, self->count, sizeof(type), (int (*)(const void*, const void*)) comp);  \
    }                                                                                               \
}                                                                                                   \
                                                                                                    \
static inline type* vector_##name##_search(struct vector_##name* self,                              \
                                           type* key, int (*comp)(type*, type*)) {                  \
    type* toReturn = NULL;                                                                          \
    if (self->count > 0) {                                                                          \
        toReturn = (type*) bsearch((const void*) key, (const void*) self->content, self->count,     \
                                   sizeof(type), (int (*)(const void*, const void*)) comp);         \
    }                                                                                               \
    return toReturn;                                                                                \
}

#define vector_initer(name)                                     \
static inline struct vector_##name vector_##name##_init(void) { \
    struct vector_##name tmp;                                   \
    vector_##name##_create(&tmp);                               \
    return tmp;                                                 \
}

#define vector_create_named(name)                                    \
static inline void vector_##name##_create(struct vector_##name * v) {\
    v->count   = 0;                                                  \
    v->cap     = 0;                                                  \
    v->content = NULL;                                               \
                                                                     \
    v->push_back      = &vector_##name##_push_back;                  \
    v->pop_back       = &vector_##name##_pop_back;                   \
    v->insert         = &vector_##name##_insert;                     \
    v->erase          = &vector_##name##_erase;                      \
    v->size           = &vector_##name##_size;                       \
    v->capacity       = &vector_##name##_capacity;                   \
    v->data           = &vector_##name##_data;                       \
    v->reserve        = &vector_##name##_reserve;                    \
    v->destroy        = &vector_##name##_destroy;                    \
    v->destroyWith    = &vector_##name##_destroyWith;                \
    v->destroyWithPtr = &vector_##name##_destroyWithPtr;             \
    v->clear          = &vector_##name##_clear;                      \
    v->sort           = &vector_##name##_sort;                       \
    v->search         = &vector_##name##_search;                     \
}                                                                    \
                                                                     \
vector_initer(name)

#define vector_light_create_named(name)                               \
static inline void vector_##name##_create(struct vector_##name * v) { \
    v->count = 0;                                                     \
    v->cap   = 0;                                                     \
    v->content = NULL;                                                \
}                                                                     \
                                                                      \
vector_initer(name)

#ifdef __cplusplus
 #define vector_methods(type, name, create) vector_methods_c(type, name)   \
                                            create(name)                   \
                                            vector_methods_cxx(type, name)
#else
 #define vector_methods(type, name, create) vector_methods_c(type, name) \
                                            create(name)
#endif

#define typedef_vector_named(name, type) vector_named(name, type);                       \
                                         vector_methods(type, name, vector_create_named) \
                                         typedef struct vector_##name vector_##name##_t

#define typedef_vector(type) typedef_vector_named(type, type)

#define typedef_vector_light_named(name, type) vector_light_named(name, type);                       \
                                               vector_methods(type, name, vector_light_create_named) \
                                               typedef struct vector_##name vector_##name##_t

#define typedef_vector_light(type) typedef_vector_light_named(type, type)

#define vector_iterate(type, vectorPtr, block)    \
for (size_t i = 0; i < (vectorPtr)->count; ++i) { \
    type* element = &(vectorPtr)->content[i];     \
    { block }                                     \
}

#define vector_forEach(type, vectorPtr, varname, block) \
for (size_t i = 0; i < (vectorPtr)->count; ++i) {       \
    type* (varname) = &(vectorPtr)->content[i];         \
    { block }                                           \
}

#define vector_initializer { 0, 0, NULL }

#endif /* __DC4C_vector_h */
