//
//  vector.h
//  C_STL
//
//  Created by Manuel Hahn on 28.06.23.
//

#ifndef vector_h
#define vector_h

#include <stdlib.h>

#define vector_named(type, name)    \
    struct vector_##name {          \
        size_t count;               \
        size_t capacity;            \
        type * content;             \
    }

#define vector(type) vector_named(type, type)

#define vector_methods(type, name)                                                                  \
static inline void vector_##name##_push_back(struct vector_##name * v, type value) {                \
                                                                                                    \
}                                                                                                   \
                                                                                                    \
static inline type vector_##name##_pop_back(struct vector_##name * v) {                             \
    return (type) NULL;                                                                             \
}                                                                                                   \
                                                                                                    \
static inline void vector_##name##_insert(struct vector_##name * v, type value, size_t position) {  \
                                                                                                    \
}                                                                                                   \
                                                                                                    \
static inline type vector_##name##_remove(struct vector_##name * v, size_t position) {              \
    return (type) NULL;                                                                             \
}                                                                                                   \
                                                                                                    \
static inline size_t vector_##name##_size(struct vector_##name * v) {                               \
    return 0;                                                                                       \
}                                                                                                   \
                                                                                                    \
static inline size_t vector_##name##_capacity(struct vector_##name * v) {                           \
    return 0;                                                                                       \
}                                                                                                   \
                                                                                                    \
static inline type * vector_##name##_data(struct vector_##name * v) {                               \
    return NULL;                                                                                    \
}                                                                                                   \
                                                                                                    \
static inline void vector_##name##_reserve(struct vector_##name * v) {                              \
                                                                                                    \
}                                                                                                   \


#define typedef_vector_named(type, name)        \
vector_named(type, name);                       \
vector_methods(type, name)                      \
typedef struct vector_##name vector_##name##_t

#define typedef_vector(type) typedef_vector_named(type, type)

#define vector_create_with_capacity(type, cap)                      \
    {                                                               \
        .count    = 0,                                              \
        .capacity = cap,                                            \
        .content  = cap == 0 ? NULL : malloc(cap * sizeof(type))    \
    }

#define vector_create(type) (struct vector_##type) vector_create_with_capacity(type, 0)

#endif /* vector_h */
