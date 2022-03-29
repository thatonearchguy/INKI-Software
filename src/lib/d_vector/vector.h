/*
 * Copyright (c) 2022 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 * 
 */

/*
 __      __       _             
 \ \    / /      | |            
  \ \  / /__  ___| |_ ___  _ __ 
   \ \/ / _ \/ __| __/ _ \| '__|
    \  /  __/ (__| || (_) | |   
     \/ \___|\___|\__\___/|_|   

𝙘𝙪𝙨𝙩𝙤𝙢 𝙡𝙞𝙨𝙩 /𝙫𝙚𝙘𝙩𝙤𝙧 𝙞𝙢𝙥𝙡𝙚𝙢𝙚𝙣𝙩𝙖𝙩𝙞𝙤𝙣.

*/

#ifndef INKI_VECTOR
#define INKI_VECTOR

#include <stdlib.h>
#include <logging/log_instance.h>
#include <logging/log.h>
#include <logging/log_ctrl.h>

#define VECTOR_DEFAULT_SIZE 4
#define VECTOR_NAME iVector

struct vector
{
    LOG_INSTANCE_PTR_DECLARE(log);
    void* privatevector_ptr;
};

#define VECTOR_INIT(_name)  \
LOG_INSTANCE_REGISTER(VECTOR_NAME, _name, CONFIG_VECTOR_LOG_LEVEL);  \
struct vector _name = {  \
            LOG_INSTANCE_PTR_INIT(log, VECTOR_NAME, _name)  \
}

int vector_init(struct vector* v, size_t initial_length, size_t item_size);
int vector_resize(struct vector* v, size_t new_size);
int vector_push_back(struct vector* v, void* element);
int vector_remove_at(struct vector* v, int index);
int vector_insert_at(struct vector* v, int index, void* element);
int vector_deinit(struct vector* v);
int vector_log_init(struct vector* v);
int vector_set(struct vector* v, int index, void* data);
int vector_clear(struct vector* v);
void* vector_pop(struct vector* v);
void* vector_get(struct vector* v, int index);
size_t vector_size(struct vector* v);
size_t vector_length(struct vector* v);

  
   

#endif