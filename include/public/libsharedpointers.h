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
 * @brief Creates a new shared memory pointer. A newly created shared memory
 * is already referenced once and shared_unref must be called on it later.
 * 
 * @param size : Size in bytes of the allocated shared memory.
 * @param unalloc_cb : Callback to unallock resources when the shared memory.
 * will be free'd.
 * @return void* : A pointer to the allocated shared memory. On failure NULL
 * is returned.
 * 
 * @warning The unalloc_cb MUST NOT free the shared memory, but only unalloc
 * ressources that could be stored inside it (pointer inside a shared struct).
 * If there is nothing to do on unalloc, unalloc_cb must be set to NULL.
 */
void *shared_alloc(const size_t size, void (*unalloc_cb)(void *));

/**
 * @brief Resizes a previously allocated shared memory.
 * 
 * @param ptr : Pointer to the shared memory.
 * @param size : New size of the shared memory.
 * @return void* : Pointer to the new shared memory, this can be different than
 * ptr. In case of failure NULL is returned.
 * 
 * @note Unlike realloc, setting a size of 0 will not free the shared memory.
 */
void *shared_realloc(void *ptr, const size_t size);

/**
 * @brief References the shared memory, incrementing its references count.
 * 
 * @param ptr : Pointer to the shared memory to reference.
 * @return void* : ptr itself for convenience
 */
void *shared_ref(void *ptr);

/**
 * @brief Unreferences the shared memory, decrementing its references count.
 * If the references count reach 0, the unalloc_cb specified at creation is
 * called on ptr, then the shared memory is free'd.
 * 
 * @param ptr : Pointer to the shared memory to unreference.
 * @return void* : If this call results in freeing the shared memory, NULL is
 * returned, otherwise ptr is returned.
 */
void *shared_unref(void *ptr);

/**
 * @brief Returns the number of current references on the given shared memory
 * pointer.
 * 
 * @param ptr : Pointer to the shared memory for which to get the references
 * count. 
 * @return int : Number of references on the given shared memory. On failure a
 * negative errno is returned.
 */
int shared_count(const void *ptr);

#endif /* LIB_SHARED_POINTERS_H */
