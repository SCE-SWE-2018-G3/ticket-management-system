#pragma once

#include <stdbool.h>

struct Vector;

// Creates a new, empty vector.
// If fails, returns NULL.
struct Vector* vector_create();

// Destroys an existing vector.
// The contents of the vector are not destroyed.
void vector_destroy(struct Vector*);

// Gets the size of the vector.
unsigned int vector_getSize(struct Vector*);

// Changes the size of a vector, reallocating if neccesary.
void vector_resize(struct Vector*, unsigned int size);

// Gets the element at `index` in vector. NULL if `index` is out of bounds.
void* vector_getAt(struct Vector*, unsigned int index);

// Sets `data` of vector at `index`.
// Does not perform deallocation of the previous data.
void vector_setAt(struct Vector*, unsigned int index, void* data);

// Adds an element to the end of the vector, reallocating.
void vector_push(struct Vector*, void* data);

// Returns a new vector that contains the members of the passed vector that do not answer the `filterCondition`.
// filterCondition receives as parameters an element of the vector, and `filter_value`.
struct Vector* vector_filter(struct Vector*, bool(*filterCondition)(void*, void*), void* filter_value);

// Returns a new vector that contains all the members of the passed vector, sorted.
// The `isBigger` function is used to sort the elements. It receives as parameters two members of the passed vector.
struct Vector* vector_sort(struct Vector*, bool(*isBigger)(void*, void*));
