# Lib_shared_pointers

Simple C lib for shared memory pointers.

This lib provides a malloc/realloc/free like interface but manages shared pointers with reference counting.
The machanism is tranparent for the user and returned pointers can be manipulated like normal ones.

## Example

```C
#include "lib_shared_pointers.h"

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

void unalloc(void *ptr)
{
        printf("The memory has been free'd\n");
}

int run(void *arg)
{
        int *value = arg;
        int i = 0;

        printf("Count = %d\n", shared_count(value));

        for (i = 0; i < 10; ++i)
                printf("i = %d\n", i);

        shared_unref(value);
        printf("Thread end\n");
        return 0;
}

int main()
{
        int *value = NULL;
        thrd_t thread;
        int status = EXIT_FAILURE;
        int res = -1;

        value = shared_alloc(sizeof(*value), unalloc);
        if (!value)
                goto out;

        res = thrd_create(&thread, run, shared_ref(value));
        if (res != thrd_success)
                goto error_create_thread;

        printf("Count main = %d\n", shared_count(value));
        thrd_join(thread, NULL);

        status = EXIT_SUCCESS;
error_create_thread:
        shared_unref(value);
out:
        return status;
}
```

Possible output :
```
Count main = 2
Count = 2
i = 0
i = 1
i = 2
i = 3
i = 4
i = 5
i = 6
i = 7
i = 8
i = 9
Thread end
The memory has been free'd
```
