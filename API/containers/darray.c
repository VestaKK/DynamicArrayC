#include "darray.h"

/**
 * @param uint64 capacity
 * @param uint64 count
 * @param uint64 stride
 * @param uint64 array
 **/

typedef enum darray_fields {
    DA_CAPACITY,
    DA_COUNT,
    DA_STRIDE,
    DA_MAX_FIELDS,
} darray_fields;

void* _darray_create(uint64 stride, uint64 initial_capacity) {
    uint64 field_size = DA_MAX_FIELDS * sizeof(uint64);
    uint64 array_size = stride * initial_capacity;
    uint64 total_allocation = field_size + array_size;

    uint64* new_darray = malloc(total_allocation);
    memset(new_darray, 0, total_allocation);

    new_darray[DA_CAPACITY] = initial_capacity;
    new_darray[DA_COUNT] = 0;
    new_darray[DA_STRIDE] = stride;

    printf("CAPACITY: %d\n", new_darray[DA_CAPACITY]);
    printf("COUNT: %d\n", new_darray[DA_COUNT]);
    printf("STRIDE: %d\n", new_darray[DA_STRIDE]);
    printf("TOTAL ALLOCATION: %d\n", total_allocation);

    printf("Array Struct Address: 0x%p\n", new_darray);
    printf("Array Address: 0x%p\n", new_darray + DA_MAX_FIELDS);

    return (void*)(new_darray + DA_MAX_FIELDS);
}

void* _darray_destroy(void* darray) {
    uint64* full_darray_struct = (uint64*)darray - DA_MAX_FIELDS;
    uint64 capacity = full_darray_struct[DA_CAPACITY];
    uint64 stride = full_darray_struct[DA_STRIDE];

    printf("FINAL ALLOCATION: %d\n", capacity*stride + sizeof(uint64)*DA_MAX_FIELDS );
    free(full_darray_struct);
}

void* _darray_resize(void** darray_reference) {
    uint64* curr_darray = *darray_reference;
    uint64* curr_darray_struct = curr_darray - DA_MAX_FIELDS;

    uint64 field_size = DA_MAX_FIELDS*sizeof(uint64);

    uint64 capacity = curr_darray_struct[DA_CAPACITY];
    uint64 count = curr_darray_struct[DA_COUNT];
    uint64 stride = curr_darray_struct[DA_STRIDE];

    curr_darray_struct[DA_CAPACITY] *= RESIZE_FACTOR;

    uint64 new_allocation = field_size + stride*(capacity*RESIZE_FACTOR);
    uint64* new_darray_struct = realloc(curr_darray_struct, new_allocation);

    *darray_reference = (void*)(new_darray_struct + DA_MAX_FIELDS);
}

void* _darray_push(void** darray_reference, const void* value) {
    uint64* curr_darray = *darray_reference;
    uint64* curr_darray_struct = curr_darray - DA_MAX_FIELDS;
    
    uint64 capacity = curr_darray_struct[DA_CAPACITY];
    uint64 count = curr_darray_struct[DA_COUNT];
    uint64 stride = curr_darray_struct[DA_STRIDE];

    if (count < capacity) {
        memcpy(*darray_reference + stride*count, (void*)value, stride);
        curr_darray_struct[DA_COUNT]++;
    } else {
        _darray_resize(darray_reference);
        memcpy(*darray_reference + stride*count, (void*)value, stride);
        curr_darray_struct = (uint64*)*darray_reference - DA_MAX_FIELDS;
        curr_darray_struct[DA_COUNT]++;
    }
}

uint64 darray_count(void* darray) {
    uint64* full_darray_struct = (uint64*)darray - DA_MAX_FIELDS;
    return full_darray_struct[DA_COUNT];
}