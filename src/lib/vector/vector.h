/*
 * Copyright (c) 2021 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 */

#ifndef INKI_VECTOR
#define INKI_VECTOR

#include <stdlib.h>
#include <logging/log_instance.h>
#include <logging/log.h>

#define DEFAULT_SIZE 4
#define VECTOR_NAME iVector

struct vector;

int vector_init(struct vector* v, size_t initial_length, size_t item_size);
int vector_resize(struct vector* v, size_t new_size);
int vector_push_back(struct vector* v, void* element);
int vector_remove_at(struct vector* v, int index);
int vector_insert_at(struct vector* v, int index, void* element);
int vector_deinit(struct vector* v);
void* vector_get(struct vector* v, int index);
char* vector_get_index_pointer(struct vector* v, int index);
size_t vector_size(struct vector* v);
size_t vector_length(struct vector* v);

  
   

#endif