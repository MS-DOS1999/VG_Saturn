#include <stdlib.h>
#include <stddef.h>

void *
operator new(size_t size)
{
    void *ptr = malloc(size == 0 ? 1 : size);
    if (ptr == 0) {
        abort();
    }
    return ptr;
}

void *
operator new[](size_t size)
{
    void *ptr = malloc(size == 0 ? 1 : size);
    if (ptr == 0) {
        abort();
    }
    return ptr;
}

void
operator delete(void *ptr) noexcept
{
    free(ptr);
}

void
operator delete[](void *ptr) noexcept
{
    free(ptr);
}

void
operator delete(void *ptr, size_t) noexcept
{
    free(ptr);
}

void
operator delete[](void *ptr, size_t) noexcept
{
    free(ptr);
}
