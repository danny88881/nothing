#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "system/stacktrace.h"
#include "system/lt.h"
#include "system/nth_alloc.h"
#include "dynarray.h"

#define DYNARRAY_INIT_CAPACITY 8

struct Dynarray
{
    Lt *lt;
    size_t element_size;
    size_t capacity;
    size_t count;
    void *data;
};

Dynarray *create_dynarray(size_t element_size)
{
    Lt *lt = create_lt();
    if (lt == NULL) {
        return NULL;
    }

    Dynarray *dynarray = PUSH_LT(lt, nth_alloc(sizeof(Dynarray)), free);
    if (dynarray == NULL) {
        RETURN_LT(lt, NULL);
    }
    dynarray->lt = lt;

    dynarray->element_size = element_size;
    dynarray->capacity = DYNARRAY_INIT_CAPACITY;
    dynarray->count = 0;

    dynarray->data = PUSH_LT(lt, nth_calloc(DYNARRAY_INIT_CAPACITY, element_size), free);
    if (dynarray->data == NULL) {
        RETURN_LT(lt, NULL);
    }

    return dynarray;
}

void destroy_dynarray(Dynarray *dynarray)
{
    trace_assert(dynarray);
    RETURN_LT0(dynarray->lt);
}

size_t dynarray_count(const Dynarray *dynarray)
{
    trace_assert(dynarray);
    return dynarray->count;
}

void *dynarray_data(Dynarray *dynarray)
{
    trace_assert(dynarray);
    return dynarray->data;
}

void dynarray_clear(Dynarray *dynarray)
{
    trace_assert(dynarray);
    dynarray->count = 0;
}

int dynarray_push(Dynarray *dynarray, void *element)
{
    trace_assert(dynarray);
    trace_assert(element);

    if (dynarray->count >= dynarray->capacity) {
        void *new_data = nth_realloc(
            dynarray->data,
            dynarray->capacity * dynarray->element_size * 2);
        if (new_data == NULL) {
            return -1;
        }

        dynarray->data = REPLACE_LT(dynarray->lt, dynarray->data, new_data);
        if (dynarray->data == NULL) {
            return -1;
        }

        dynarray->capacity *= 2;
    }

    memcpy(
        (char*) dynarray->data + dynarray->count * dynarray->element_size,
        element,
        dynarray->element_size);

    dynarray->count++;

    return 0;
}

void dynarray_inspect(Dynarray *dynarray)
{
    trace_assert(dynarray);

    printf("count:    %ld\n", dynarray->count);
    printf("capacity: %ld\n", dynarray->capacity);
}
