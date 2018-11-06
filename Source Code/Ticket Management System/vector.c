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
		vector->data = malloc(sizeof(void*) * size);
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
