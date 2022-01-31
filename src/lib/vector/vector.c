#include "vector.h"

LOG_LEVEL_SET(LOG_LEVEL_INF);

//HAHAAAA ENCAPSULATION!!!! GOTEEEEMMMM
//TRY ACCESSING THIS!!!! MWAHAHAHAHAAHA
struct privatevector
{
    void* items;
    size_t item_size;
    size_t capacity;
    size_t num_items;
    size_t allocated_items;
};

void* vector_get(struct vector* v, int index)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    void* element;
    memcpy(element, vector_get_index_pointer(v, index), ptr->item_size);
    return element;
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

char* vector_get_index_pointer(struct vector* v, int index)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    return (char*)(ptr->items + (ptr->item_size * index));
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
    memmove((void*)vector_get_index_pointer(v, index+1), (void*)vector_get_index_pointer(v, index), ptr->item_size);
    memcpy(vector_get_index_pointer(v, index), element, ptr->item_size);
    ptr->num_items++;
    return 1;
}

//Lovely little getter methods for the struct properties!

int vector_deinit(struct vector* v)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    free(ptr->items);
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
size_t vector_length(struct vector* v)
{
    struct privatevector* ptr = (struct privatevector*) v->privatevector_ptr;
    return ptr->num_items;
}