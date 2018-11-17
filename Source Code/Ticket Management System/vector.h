#pragma once

#include <stdbool.h>

struct Vector;

struct Vector* vector_create();
void vector_destroy(struct Vector*);
unsigned int vector_getSize(struct Vector*);
void vector_resize(struct Vector*, unsigned int size);
void* vector_getAt(struct Vector*, unsigned int index);
void vector_setAt(struct Vector*, unsigned int index, void* data);
void vector_push(struct Vector*, void* data);
struct Vector* vector_filter(struct Vector*, bool(*filterCondition)(void*, void*), void* filter_value);
struct Vector* vector_sort(struct Vector*, bool(*isBigger)(void*, void*));
