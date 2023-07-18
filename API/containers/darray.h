#include "defines.h"

#define DEFAULT_CAPACITY 2
#define RESIZE_FACTOR 2

MAPI void* _darray_create(uint64 stride, uint64 initial_capacity);
MAPI void* _darray_destroy(void* darray);
MAPI void* _darray_resize(void** darray_reference);
MAPI void* _darray_push(void** darray_reference, const void* value);
MAPI void* _darray_pop(void** darray_reference);

MAPI uint64 darray_count(void* darray);

#define darray_create(type) _darray_create(sizeof(type), DEFAULT_CAPACITY)
#define darray_reserve(type, size) _darray_create(sizeof(type), size)
#define darray_destroy(darray) _darray_destroy(darray)
#define darray_push(darray, value) { typeof(value) temp = value; _darray_push((void**)&darray, &temp); }
#define darray_pop(darray) _darray_pop((void**) darray)
