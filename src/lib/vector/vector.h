#include <stdlib.h>

struct vector
{
    int* data;
    size_t capacity;
    size_t size;
};