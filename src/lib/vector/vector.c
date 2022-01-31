#include "vector.h"

LOG_LEVEL_SET(LOG_LEVEL_INF);

//HAHAAAA ENCAPSULATION!!!! GOTEEEEMMMM
//TRY ACCESSING THIS!!!! MWAHAHAHAHAAHA
struct vector
{
    LOG_INSTANCE_PTR_DECLARE(log);
    void* items;
    size_t item_size;
    size_t capacity;
    size_t num_items;
    size_t allocated_items;
};

#define VECTOR_INIT(_name)  \
LOG_INSTANCE_REGISTER(VECTOR_NAME, _name, CONFIG_IFLASH_LOG_LEVEL);  \
struct vector _name = {  \
            LOG_INSTANCE_PTR_INIT(log, VECTOR_NAME, _name)  \
} 

vector* vector_init(char* name, size_t initial_length, size_t item_size)
{
    VECTOR_INIT(name);
    v->item_size = item_size;
    if(initial_length > 0)
    {
        v->allocated_items = initial_length;
    }
    else
    {
        v->allocated_items = DEFAULT_SIZE;
    }
    v->num_items = 0;
    v->items = malloc(item_size * v->allocated_items);
    if(v->items == NULL)
    {
        LOG_INST_ERR(v->log, "Memory not allocated!!");
        return -1;
    }
    LOG_INST_INF(v->log, "Success");
    return 1;
}

char* vector_get_index_pointer(struct vector* v, int index)
{
    return (char*)(v->items + (v->item_size * index));
}


int vector_resize(struct vector* v, size_t new_size)
{
    if(new_size > v->num_items)
    {
        v->allocated_items = new_size;
    }
    v->items = realloc(v->items, v->item_size * v->allocated_items);
    if(v->items == NULL)
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
    void* element;
    memcpy(element, vector_get_index_pointer(v, v->num_items-1), v->num_items);
    int retcode = vector_remove_at(v, v->num_items-1);
    if (retcode != 1)
    {
        LOG_INST_ERR(v->log, "Pop failed!");
        return NULL;
    }
    return element;
}

int vector_remove_at(struct vector* v, int index)
{
    if(index < 0 || index > v->num_items-1)
    {
        LOG_INST_ERR(v->log, "Invalid index: %i", index);
        return -EINVAL;
    }
    memmove((void*)vector_get_index_pointer(v, index), (void*)vector_get_index_pointer(v, index+1), v->item_size);
    v->num_items--;
    return 1;
}

int vector_insert_at(struct vector* v, int index, void* element)
{
    //Few cases - firstly the index is less than -1, in which case we exit because argument is invalid.
    if(index < -1)
    {
        LOG_INST_ERR(v->log, "Invalid index: %i", index);
        return -EINVAL;
    }
    //Secondly, the index is -1, meaning the item is to be appended to the back of the list.
    if (index == -1)
    {
        index = v->num_items;
    }
    //Thirdly, the index is greater than the allocated list. In this case
    //we resize by a factor of 2 until the index is within range to allow breathing room.
    //Of course people have to be nice and not like allocate the entire memory because of a factor of 10 error because that is seriously uncool. Lot of trust here!
    while(index > v->allocated_items)
    {
        vector_resize(v, v->allocated_items*2);
    }
    memmove((void*)vector_get_index_pointer(v, index+1), (void*)vector_get_index_pointer(v, index), v->item_size);
    memcpy(vector_get_index_pointer(v, index), element, v->item_size);
    v->num_items++;
    return 1;
}

//Lovely little getter methods for the struct properties!

int vector_deinit(struct vector* v)
{
    free(v->items);
}
size_t vector_size(struct vector* v)
{
    return v->item_size * v->num_items;
}
size_t vector_allocated_size(struct vector* v)
{
    return v->item_size * v->allocated_items;
}
size_t vector_length(struct vector* v)
{
    return v->num_items;
}