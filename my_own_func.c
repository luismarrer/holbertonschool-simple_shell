#include "simple_shell.h"

/**
 * _realloc - Reallocate memory block
 *
 * @ptr: Pointer to the previously allocated memory
 *
 * @old_size: Size of the previously allocated memory
 *
 * @new_size: New size of the memory block
 *
 * Return: Pointer to the newly allocated memory, or NULL on failure
 */

void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr = malloc(new_size);

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		return (malloc(new_size));
	}
	if (new_size <= old_size)
	{
		return (ptr);
	}

	if (new_ptr == NULL)
	{
		return (NULL);
	}
	memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

