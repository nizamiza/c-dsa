#pragma once
#include "multiarray.unity.h"

#define MULTIARRAY_MAX_FIELD_COUNT 32
#define SIZE_T_ERROR (size_t) - 1

typedef struct {
    size_t length;
    void **_field_arrays;
    size_t _struct_size;
    size_t _field_count;
    size_t _filed_offsets[MULTIARRAY_MAX_FIELD_COUNT];
    size_t _field_sizes[MULTIARRAY_MAX_FIELD_COUNT];
} Multiarray;

Multiarray *Multiarray_new(size_t field_count, ...) {
    Multiarray *ma = (Multiarray *)malloc(sizeof(Multiarray));

    if (!ma || field_count > MULTIARRAY_MAX_FIELD_COUNT) {
        return NULL;
    }

    ma->length = 0;

    ma->_struct_size = 0;
    ma->_field_count = field_count;
    ma->_field_arrays = malloc(sizeof(void *) * field_count);

    if (!ma->_field_arrays) {
        return NULL;
    }

    va_list field_sizes;
    va_start(field_sizes, field_count);

    for (size_t i = 0; i < field_count; i++) {
        size_t field_arr_size = va_arg(field_sizes, size_t);
        void *field_arr = malloc(field_arr_size);

        if (!field_arr) {
            for (size_t j = 0; j < i; j++) {
                free(ma->_field_arrays[j]);
            }

            free(ma);
            va_end(field_sizes);

            return NULL;
        }

        ma->_field_arrays[i] = field_arr;

        ma->_field_sizes[i] = field_arr_size;
        ma->_struct_size += field_arr_size;
    }

    va_end(field_sizes);

    return ma;
}

void Multiarray_free(Multiarray *ma) {
    if (!ma) {
        return;
    }
    
    for (size_t i = 0; i < ma->_field_count; i++) {
        free(ma->_field_arrays[i]);
    }

    free(ma->_field_arrays);
    free(ma);
}

size_t Multiarray_insert(Multiarray *ma, void *item) {
    if (!ma || !item) {
        return SIZE_T_ERROR;
    }

    void *field = item;

    for (size_t i = 0; i < ma->_field_count; i++) {
        size_t size = ma->_field_sizes[i];

        void *field_arr = ma->_field_arrays[i];
        void *field_arr_new = realloc(field_arr, (ma->length + 1) * size);

        if (!field_arr_new) {
            return SIZE_T_ERROR;
        }

        ma->_field_arrays[i] = field_arr_new;

        memcpy((char *)field_arr_new + ma->length * size, field, size);
        field = (char *)field + size;
    }

    ma->length++;
    return ma->length;
}

void *Multiarray_get(Multiarray *ma, size_t index) {
    if (!ma || index >= ma->length) {
        return NULL;
    }

    void *item = malloc(ma->_struct_size);

    if (!item) {
        return NULL;
    }

    void *curr_pos = item;

    for (size_t i = 0; i < ma->_field_count; i++) {
        size_t size = ma->_field_sizes[i];

        void *field_arr = ma->_field_arrays[i];
        void *field = (char *)field_arr + index * size;

        memcpy(curr_pos, field, size);

        curr_pos = (char *)curr_pos + size;
    }

    return item;
}

size_t Multiarray_find_index(Multiarray *ma, void *item) {
    if (!ma || !item) {
        return SIZE_T_ERROR;
    }

    for (size_t i = 0; i < ma->length; i++) {
        size_t match_count = 0;
        void *search_field = item;

        for (size_t j = 0; j < ma->_field_count; j++) {
            size_t size = ma->_field_sizes[j];

            void *field_arr = ma->_field_arrays[j];

            void *field = (char *)field_arr + i * size;

            if (memcmp(search_field, field, size) == 0) {
                match_count++;
            }

            search_field = (char *)search_field + size;
        }

        if (match_count == ma->_field_count) {
            return i;
        }
    }

    return SIZE_T_ERROR;
}

void *Multiarray_remove(Multiarray *ma, void *item) {
    if (!ma || !item) {
        return NULL;
    }

    size_t item_index = Multiarray_find_index(ma, item);

    if (item_index == SIZE_T_ERROR) {
        return NULL;
    }

    void *item_cpy = Multiarray_get(ma, item_index);

    if (!item_cpy) {
        return NULL;
    }

    for (size_t i = 0; i < ma->_field_count; i++) {
        size_t size = ma->_field_sizes[i];

        void *field_arr = ma->_field_arrays[i];

        for (size_t j = item_index; j < ma->length - 1; j++) {
            memcpy((char *)field_arr + j * size, (char *)field_arr + (j + 1) * size, size);
        }

        void *field_arr_new = realloc(field_arr, (ma->length - 1) * size);

        if (!field_arr_new) {
            free(item_cpy);
            return NULL;
        }

        ma->_field_arrays[i] = field_arr_new;
    }

    ma->length--;
    return item_cpy;
}

void *Multiarray_get_field_array(Multiarray *ma, size_t field_index) {
    if (!ma || field_index >= ma->_field_count) {
        return NULL;
    }

    return ma->_field_arrays[field_index];
}
