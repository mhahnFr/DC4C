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

#include <stdio.h>

#include "try_catch.h"

jmp_buf* __tryCatch_lastJmpBuf = NULL;
void* __tryCatch_lastException = NULL;
bool __tryCatch_exceptionNeedsFree = false;

jmp_buf* tryCatch_setJmpBuf(jmp_buf* buf) {
    jmp_buf* toReturn = __tryCatch_lastJmpBuf;
    __tryCatch_lastJmpBuf = buf;
    return toReturn;
}

void* tryCatch_getException(void) {
    return __tryCatch_lastException;
}

void tryCatch_setException(void* ex) {
    __tryCatch_lastException = ex;
}

void tryCatch_setNeedsFree(bool f) {
    __tryCatch_exceptionNeedsFree = f;
}

bool tryCatch_getNeedsFree(void) {
    return __tryCatch_exceptionNeedsFree;
}

void tryCatch_freeException(bool force) {
    if (force || __tryCatch_exceptionNeedsFree) {
        free(__tryCatch_lastException);
    }
}

void tryCatch_throw(void* exception) {
    tryCatch_setException(exception);
    if (__tryCatch_lastJmpBuf == NULL) {
        fputs("mhahnFr's try_catch: Terminating due to uncaught exception!\n", stderr);
        abort();
    }
    longjmp(*__tryCatch_lastJmpBuf, 1);
}
