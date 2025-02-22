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

#ifndef try_catch_h
#define try_catch_h

#include <setjmp.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

jmp_buf* tryCatch_setJmpBuf(jmp_buf* buf);

void tryCatch_setException(void* exception);
void* tryCatch_getException(void);

void tryCatch_setNeedsFree(bool needsFree);
bool tryCatch_getNeedsFree(void);

void tryCatch_freeException(bool force);

void tryCatch_throw(void* exception);

#define TRY(block, catchBlock) {                  \
    jmp_buf __env;                                \
    jmp_buf* __prev = tryCatch_setJmpBuf(&__env); \
    void* __lastExc = tryCatch_getException();    \
    int __result = setjmp(__env);                 \
    if (__result == 0) {                          \
        { block }                                 \
    } else {                                      \
        tryCatch_setJmpBuf(__prev);               \
        tryCatch_setNeedsFree(true);              \
        { catchBlock }                            \
        tryCatch_setNeedsFree(false);             \
    }                                             \
    tryCatch_setJmpBuf(__prev);                   \
    tryCatch_freeException(true);                 \
    tryCatch_setException(__lastExc);             \
}

#define RETHROW do {                         \
    tryCatch_setNeedsFree(false);            \
    tryCatch_throw(tryCatch_getException()); \
} while (0)

#define THROW(value) do {                        \
    tryCatch_freeException(false);               \
    void* __exception = malloc(sizeof((value))); \
    typeof((value)) __vl = (value);              \
    memcpy(__exception, &__vl, sizeof((value))); \
    tryCatch_throw(__exception);                 \
} while (0)

#define CATCH(type, name, block) \
type name = *(type*) tryCatch_getException(); { block }

#endif /* try_catch_h */
