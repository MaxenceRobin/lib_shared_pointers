/**
 * @author Maxence ROBIN
 * @brief Provides a malloc like interface for shared memory pointers with
 * reference counting.
 */

#ifndef LIB_SHARED_POINTERS_H
#define LIB_SHARED_POINTERS_H

/* Includes ------------------------------------------------------------------*/

#include <stddef.h>

/* API -----------------------------------------------------------------------*/

/**
 * @brief Creates a new pointer on a shared memory of 'size' bytes, that will be
 * free()'d with 'unalloc_cb' at end of life.
 * 
 * @return Pointer to the shared memory on success.
 * @return NULL on failure.
 * 
 * @warning 'unalloc_cb' MUST NOT free the shared memory itself, but only
 * unalloc ressources that could be stored inside it (pointer inside a shared
 * struct). If there is nothing to do, 'unalloc_cb' must be set to NULL. 
 */
void *shared_alloc(const size_t size, void (*unalloc_cb)(void *));

/**
 * @brief Resizes the shared memory pointer 'ptr' to 'size' bytes.
 * 
 * @return Pointer to the reallocated shared memory on success.
 * @return NULL if 'ptr' is invalid, or on failure.
 * 
 * @note Unlike realloc, setting a size of 0 will not free the shared memory.
 */
void *shared_realloc(void *ptr, const size_t size);

/**
 * @brief References the shared memory pointer 'ptr', incrementing its
 * references count.
 * 
 * @return 'ptr' itself for convenience.
 */
void *shared_ref(void *ptr);

/**
 * @brief Unreferences the shared memory pointer 'ptr', decrementing its
 * references count. If the references count reach 0, the 'unalloc_cb'
 * specified at creation is called on 'ptr', then the shared memory is free()'d.
 * 
 * @return 'ptr' itself if its reference count is greater than 0 after the call.
 * @return NULL if the reference count reaches 0 upon the call.
 */
void *shared_unref(void *ptr);

/**
 * @brief Returns the reference count of 'ptr'.
 * 
 * @return The reference count of 'ptr' on success.
 * @return -EINVAL if 'ptr' is invalid.
 */
int shared_count(const void *ptr);

#endif /* LIB_SHARED_POINTERS_H */
