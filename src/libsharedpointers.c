#include "libsharedpointers.h"

/* Includes ------------------------------------------------------------------*/

#include <errno.h>
#include <stdatomic.h>
#include <stdlib.h>

/* Definitions ---------------------------------------------------------------*/

struct meta {
        _Atomic unsigned int count;
        void (*unalloc_cb)(void *ptr);
};

/* Static functions ----------------------------------------------------------*/

struct meta *ptr_to_meta(const void *ptr)
{
        return (struct meta *)ptr - 1;
}

void *meta_to_ptr(const struct meta *meta)
{
        return (void *)(meta + 1);
}

/* API -----------------------------------------------------------------------*/

void *shared_alloc(const size_t size, void (*unalloc_cb)(void *))
{
        struct meta *meta = NULL;

        meta = malloc(sizeof(*meta) + size);
        if (!meta)
                return NULL;

        meta->count = 1;
        meta->unalloc_cb = unalloc_cb;
        return meta_to_ptr(meta);
}

void *shared_realloc(void *ptr, const size_t size)
{
        struct meta *meta = NULL;

        if (!ptr)
                return NULL;

        meta = ptr_to_meta(ptr);
        meta = realloc(meta, sizeof(*meta) + size);
        if (!meta)
                return NULL;

        return meta_to_ptr(meta);
}

void *shared_ref(void *ptr)
{
        if (!ptr)
                return NULL;

        ptr_to_meta(ptr)->count++;
        return ptr;
}

void *shared_unref(void *ptr)
{
        struct meta *meta = NULL;

        if (!ptr)
                return NULL;

        meta = ptr_to_meta(ptr);
        if (atomic_fetch_sub(&meta->count, 1) == 1) {
                if (meta->unalloc_cb)
                        meta->unalloc_cb(ptr);

                free(meta);
                ptr = NULL;
        }

        return ptr;
}

int shared_count(const void *ptr)
{
        if (!ptr)
                return -EINVAL;

        return ptr_to_meta(ptr)->count;
}
