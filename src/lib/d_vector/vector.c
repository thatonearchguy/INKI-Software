/*
 * Copyright (c) 2022 INKI-Systems Inc.
 *
 * Licensed under GPL 3
 * 
 */

#include "vector.h"

LOG_LEVEL_SET(LOG_LEVEL_INF);

//HAHAAAA ENCAPSULATION!!!! GOTEEEEMMMM
//TRY ACCESSING THIS!!!! MWAHAHAHAHAAHA
struct privatevector
{
    void* items;
    size_t item_size;
    size_t capacity;
    unsigned int num_items;
    size_t allocated_items;
};

uint8_t* vector_get_index_pointer(struct vector* v, int index);


//It is your responsibility to properly dispose of the generated item by using free!
void* vector_get(struct vector* v, int index)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    void* element = k_malloc(ptr->item_size);
    memcpy(&element, (void*)vector_get_index_pointer(v, index), ptr->item_size);
    return element; 
}


int vector_set(struct vector* v, int index, void* data)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    memcpy(vector_get_index_pointer(v, index), (void*)data, ptr->item_size);
    return 1;
}

int vector_init(struct vector* v, size_t initial_length, size_t item_size)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    ptr->item_size = item_size;
    if(initial_length > 0)
    {
        ptr->allocated_items = initial_length;
    }
    else
    {
        ptr->allocated_items = VECTOR_DEFAULT_SIZE;
    }
    ptr->num_items = 0;
    ptr->items = malloc(item_size * ptr->allocated_items);
    if(ptr->items == NULL)
    {
        LOG_INST_ERR(v->log, "Memory not allocated!!");
        return -1;
    }
    LOG_INST_INF(v->log, "Success");
    return 1;
}

int vector_clear(struct vector* v)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    int rc;
    for (int i = 0; i < ptr->num_items; i++)
    {
        rc = vector_set(v, i, NULL);
        if(rc < 0)
        {
            return rc;
        }
    }
    return 1;
}




uint8_t* vector_get_index_pointer(struct vector* v, int index)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    return (uint8_t*)((uint8_t*)ptr->items + (ptr->item_size * index));
}


int vector_resize(struct vector* v, size_t new_size)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    if(new_size > ptr->num_items)
    {
        ptr->allocated_items = new_size;
    }
    ptr->items = realloc(ptr->items, ptr->item_size * ptr->allocated_items);
    if(ptr->items == NULL)
    {
        LOG_INST_ERR(v->log, "Data lost during realloc");
        return -1;
    }
    LOG_INST_INF(v->log, "Success");
    return 1;
}

int vector_push_back(struct vector* v, void* element)
{
    return vector_insert_at(v, -1, element);
}

//You must dispose of the return value with free() when you are done!
void* vector_pop(struct vector* v)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    void* element = vector_get(v, ptr->num_items-1);
    int retcode = vector_remove_at(v, ptr->num_items-1);
    if (retcode != 1)
    {
        LOG_INST_ERR(v->log, "Pop failed!");
        return NULL;
    }
    return element;
}

int vector_remove_at(struct vector* v, int index)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    if(index < 0 || index > ptr->num_items-1)
    {
        LOG_INST_ERR(v->log, "Invalid index: %i", index);
        return -EINVAL;
    }
    memmove((void*)vector_get_index_pointer(v, index), (void*)vector_get_index_pointer(v, index+1), ptr->item_size);
    ptr->num_items--;
    return 1;
}

int vector_insert_at(struct vector* v, int index, void* element)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    //Few cases - firstly the index is less than -1, in which case we exit because argument is invalid.
    if(index < -1)
    {
        LOG_INST_ERR(v->log, "Invalid index: %i", index);
        return -EINVAL;
    }
    char* testing_str = "hello world this is some important binary code";

    //Secondly, the index is -1, meaning the item is to be appended to the back of the list.
    if (index == -1)
    {
        index = ptr->num_items;
    }
    //Thirdly, the index is greater than the allocated list. In this case
    //we resize by a factor of 2 until the index is within range to allow breathing room.
    //Of course people have to be nice and not like allocate the entire memory because of a factor of 10 error because that is seriously uncool. Lot of trust here!
    while(index > ptr->allocated_items)
    {
        vector_resize(v, ptr->allocated_items*2);
    }
    if(index < ptr->num_items) memmove((void*)vector_get_index_pointer(v, index+1), (void*)vector_get_index_pointer(v, index), (ptr->num_items - index) * ptr->item_size);
    memcpy((void*)vector_get_index_pointer(v, index), element, ptr->item_size);
    ptr->num_items++;
    return 1;
}

//Lovely little getter methods for the struct properties!

int vector_deinit(struct vector* v)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    free(ptr->items);
    return 1;
}
size_t vector_size(struct vector* v)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    return ptr->item_size * ptr->num_items;
}
size_t vector_allocated_size(struct vector* v)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    return ptr->item_size * ptr->allocated_items;
}
unsigned int vector_length(struct vector* v)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    return ptr->num_items;
}
// A utility function to swap two elements
void swap(struct vector* v, int* a, int* b)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    int t = *a;
    *a = *b;
    *b = t;
}
 
/*
int partition(int arr[], int l, int h)
{
    int x = arr[h];
    int i = (l - 1);
 
    for (int j = l; j <= h - 1; j++) {
        if (arr[j] <= x) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[h]);
    return (i + 1);
}
 

void quickSortIterative(int arr[], int l, int h)
{
    // Create an auxiliary stack
    int stack[h - l + 1];
 
    // initialize top of stack
    int top = -1;
 
    // push initial values of l and h to stack
    stack[++top] = l;
    stack[++top] = h;
 
    // Keep popping from stack while is not empty
    while (top >= 0) {
        // Pop h and l
        h = stack[top--];
        l = stack[top--];
 
        // Set pivot element at its correct position
        // in sorted array
        int p = partition(arr, l, h);
 
        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }
 
        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}
*/