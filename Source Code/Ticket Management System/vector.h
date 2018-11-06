#pragma once

struct Vector;

struct Vector* vector_create();
void vector_destroy(struct Vector*);
unsigned int vector_getSize(struct Vector*);
void vector_resize(struct Vector*, unsigned int size);
void* vector_getAt(struct Vector*, unsigned int index);
void vector_setAt(struct Vector*, unsigned int index, void* data);
