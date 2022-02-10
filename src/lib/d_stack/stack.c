/*
 * Copyright (c) 2021 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 */


#include "stack.h"

LOG_LEVEL_SET(LOG_LEVEL_INF);

struct privatevector
{
    struct vector stackvec;  
};


int stack_init(struct stack* s, size_t initial_length, size_t item_size)
{
    int rc;
    struct vector* vecptr = &((struct privatevector*) s->privatevector_ptr)->stackvec;
    
    rc = vector_init(vecptr, initial_length, item_size);

    return rc;
}
int stack_push(struct stack* s, void* element)
{
    int rc;
    struct vector* vecptr = &((struct privatevector*) s->privatevector_ptr)->stackvec;
    rc = vector_push_back(vecptr, element);
    return rc;
}
void* stack_pop(struct stack* s)
{
    void* element;
    struct vector* vecptr = &((struct privatevector*) s->privatevector_ptr)->stackvec;
    element = vector_pop(vecptr);
    return element;
}
int stack_destroy(struct stack* s)
{
    struct vector* vecptr = &((struct privatevector*) s->privatevector_ptr)->stackvec;
    int rc = vector_deinit(vecptr);
    return rc;
}
