#include "vector.h"
#include <stdlib.h>

struct Vector
{
	void** data;
	unsigned int size;
};

struct Vector* vector_create()
{
	struct Vector* vector = malloc(sizeof(struct Vector));
	if (vector != NULL)
	{
		vector->data = NULL;
		vector->size = 0;
	}
	return vector;
}

void vector_destroy(struct Vector* vector)
{
	if (vector != NULL)
	{
		if (vector->data != NULL)
		{
			free(vector->data);
			vector->data = NULL;
			vector->size = 0;
		}
		free(vector);
	}
}

unsigned int vector_getSize(struct Vector* vector)
{
	if (vector != NULL)
	{
		return vector->size;
	}
	return 0;
}

void vector_resize(struct Vector* vector, unsigned int size)
{
	if (vector != NULL)
	{
		void** temp = vector->data;
		vector->data = malloc(sizeof(void*) * size); // TODO: rewrite with realloc?
		if (vector->data != NULL)
		{
			unsigned int i = 0;

			if (temp != NULL)
			{
				for (i = 0; i < size && i < vector->size; ++i)
				{
					vector->data[i] = temp[i];
				}
				free(temp);
			}

			for (; i < size; ++i)
			{
				vector->data[i] = NULL;
			}

			vector->size = size;
		}
	}
}

void* vector_getAt(struct Vector* vector, unsigned int index)
{
	if (vector != NULL && index < vector->size)
	{
		return vector->data[index];
	}
	return NULL;
}

void vector_setAt(struct Vector* vector, unsigned int index, void* data)
{
	if (vector != NULL && index < vector->size)
	{
		vector->data[index] = data;
	}
}

struct Vector* vector_copy(struct Vector* source_vector)
{
	struct Vector* result_vector = NULL;
	if (source_vector != NULL)
	{
		result_vector = vector_create();
		if (result_vector != NULL)
		{
			vector_resize(result_vector, source_vector->size);
			if (result_vector->data != NULL && source_vector->data != NULL)
			{
				for (unsigned int i = 0; i < source_vector->size; ++i)
				{
					result_vector->data[i] = source_vector->data[i];
				}
			}
		}
	}
	return result_vector;
}

void vector_push(struct Vector* vector, void* data)
{
	if (vector != NULL && data != NULL)
	{
		vector_resize(vector, vector->size + 1);
		vector->data[vector, vector->size - 1] = data;
	}
}

struct Vector* vector_filter(struct Vector* source_vector, bool(*filterCondition)(void*, void*), void* filter_value)
{
	struct Vector* result_vector = NULL;
	if (source_vector != NULL)
	{
		result_vector = vector_copy(source_vector);
		if (result_vector != NULL)
		{
			unsigned int j = 0;
			for (unsigned int i = 0; i < source_vector->size; ++i)
			{
				if (!filterCondition(source_vector->data[i], filter_value))
				{
					result_vector->data[j] = source_vector->data[i];
					++j;
				}
			}
			vector_resize(result_vector, j);
		}
	}
	return result_vector;
}

struct Vector* vector_sort(struct Vector* source_vector, bool(*isBigger)(void*, void*))
{
	struct Vector* result_vector = NULL;
	if (source_vector != NULL)
	{
		result_vector = vector_copy(source_vector);
		if (result_vector != NULL)
		{
			// TODO: Probably rewrite with something better than bubble sort
			bool swapped;
			do
			{
				swapped = false;
				for (unsigned int i = 1; i < result_vector->size; ++i)
				{
					if (isBigger(result_vector->data[i-1], result_vector->data[i]))
					{
						void* temp = result_vector->data[i-1];
						result_vector->data[i-1] = result_vector->data[i];
						result_vector->data[i] = temp;
						swapped = true;
					}
				}
			} while (swapped);
		}
	}
	return result_vector;
}
