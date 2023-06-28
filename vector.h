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

#define vector(type)        \
vector_named(type, type)

#define typedef_vector_named(type, name) \
typedef vector_named(type, name) vector_##name##_t

#define typedef_vector(type) \
typedef_vector_named(type, type)

#define vector_create_with_capacity(type, cap)                      \
    {                                                               \
        .count    = 0,                                              \
        .capacity = cap,                                            \
        .content  = cap == 0 ? NULL : malloc(cap * sizeof(type))    \
    }

#define vector_create(type) (struct vector_##type) vector_create_with_capacity(type, 0)

#endif /* vector_h */
