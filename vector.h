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

#ifndef vector_h
#define vector_h

#include <stdlib.h>
#include <string.h>

#define vector_named(name, type)                                   \
    struct vector_##name {                                         \
        size_t count;                                              \
        size_t cap;                                                \
        type * content;                                            \
                                                                   \
        void   (*push_back)(struct vector_##name *, type);         \
        type   (*pop_back) (struct vector_##name *);               \
        void   (*insert)   (struct vector_##name *, type, size_t); \
        type   (*remove)   (struct vector_##name *, size_t);       \
        size_t (*size)     (struct vector_##name *);               \
        size_t (*capacity) (struct vector_##name *);               \
        type * (*data)     (struct vector_##name *);               \
        void   (*reserve)  (struct vector_##name *, size_t);       \
        void   (*destroy)  (struct vector_##name *);               \
    }

#define vector(type) vector_named(type, type)

#define vector_methods(type, name)                                                                  \
static inline void vector_##name##_push_back(struct vector_##name * v, type value) {                \
    if (v->cap < v->count + 1) {                                                                    \
        v->reserve(v, v->cap == 0 ? 1 : v->cap * 2);                                                \
    }                                                                                               \
                                                                                                    \
    v->content[v->count++] = value;                                                                 \
}                                                                                                   \
                                                                                                    \
static inline type vector_##name##_pop_back(struct vector_##name * v) {                             \
    return v->content[v->count--];                                                                  \
}                                                                                                   \
                                                                                                    \
static inline void vector_##name##_insert(struct vector_##name * v, type value, size_t position) {  \
    if (position >= v->count) {                                                                     \
        v->push_back(v, value);                                                                     \
        return;                                                                                     \
    }                                                                                               \
                                                                                                    \
    if (v->cap < v->count) {                                                                        \
        v->reserve(v, v->cap * 2);                                                                  \
    }                                                                                               \
    memmove(&v->content[position + 1], &v->content[position], (v->count - position) * sizeof(type));\
    v->content[position] = value;                                                                   \
    v->count++;                                                                                     \
}                                                                                                   \
                                                                                                    \
static inline type vector_##name##_remove(struct vector_##name * v, size_t position) {              \
    return (type) NULL;                                                                             \
}                                                                                                   \
                                                                                                    \
static inline size_t vector_##name##_size(struct vector_##name * v) {                               \
    return v->count;                                                                                \
}                                                                                                   \
                                                                                                    \
static inline size_t vector_##name##_capacity(struct vector_##name * v) {                           \
    return v->cap;                                                                                  \
}                                                                                                   \
                                                                                                    \
static inline type * vector_##name##_data(struct vector_##name * v) {                               \
    return v->content;                                                                              \
}                                                                                                   \
                                                                                                    \
static inline void vector_##name##_reserve(struct vector_##name * v, size_t newSize) {              \
    if (v->cap >= newSize) {                                                                        \
        return;                                                                                     \
    }                                                                                               \
                                                                                                    \
    type * tmp = malloc(sizeof(type) * newSize);                                                    \
    if (tmp == NULL) {                                                                              \
        return;                                                                                     \
    }                                                                                               \
                                                                                                    \
    memcpy(tmp, v->content, v->count * sizeof(type));                                               \
    free(v->content);                                                                               \
    v->content = tmp;                                                                               \
    v->cap = newSize;                                                                               \
}                                                                                                   \
                                                                                                    \
static inline void vector_##name##_destroy(struct vector_##name * v) {                              \
    free(v->content);                                                                               \
}                                                                                                   \
                                                                                                    \
static inline void vector_##name##_create(struct vector_##name * v) {                               \
    v->count     = 0;                                                                               \
    v->cap       = 0;                                                                               \
    v->content   = NULL;                                                                            \
                                                                                                    \
    v->push_back = &vector_##name##_push_back;                                                      \
    v->pop_back  = &vector_##name##_pop_back;                                                       \
    v->insert    = &vector_##name##_insert;                                                         \
    v->remove    = &vector_##name##_remove;                                                         \
    v->size      = &vector_##name##_size;                                                           \
    v->capacity  = &vector_##name##_capacity;                                                       \
    v->data      = &vector_##name##_data;                                                           \
    v->reserve   = &vector_##name##_reserve;                                                        \
    v->destroy   = &vector_##name##_destroy;                                                        \
}                                                                                                   \


#define typedef_vector_named(name, type)        \
vector_named(name, type);                       \
vector_methods(type, name)                      \
typedef struct vector_##name vector_##name##_t

#define typedef_vector(type) typedef_vector_named(type, type)

#endif /* vector_h */
