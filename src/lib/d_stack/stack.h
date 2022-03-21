/*
 * Copyright (c) 2022 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 * 
 */


#ifndef INKI_STACK
#define INKI_STACK

#include "../d_vector/vector.h"

#define STACK_NAME iStack

//Just a cheeky little wrapper around my vector class to emulate a stack (actually i bet this is extremely close to how a stack really works)
//Because of the implementation of the vector class, this stack has an UNBOUNDED SIZE.

struct stack
{
    LOG_INSTANCE_PTR_DECLARE(log);
    void* privatevector_ptr;
};

#define STACK_INIT(_name)  \
LOG_INSTANCE_REGISTER(VECTOR_NAME, _name, CONFIG_VECTOR_LOG_LEVEL);  \
struct stack _name = {  \
            LOG_INSTANCE_PTR_INIT(log, VECTOR_NAME, _name)  \
}

int stack_init(struct stack* s, size_t initial_length, size_t item_size);
int stack_push(struct stack* s, void* element);
void* stack_pop(struct stack* s);
size_t stack_length(struct stack* s);
int stack_destroy(struct stack* s);
int stack_clear(struct stack* s);



#endif

