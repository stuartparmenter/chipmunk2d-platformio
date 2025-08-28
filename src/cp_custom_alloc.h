#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void *cp_custom_calloc(size_t n, size_t size);
void *cp_custom_realloc(void *ptr, size_t size);
void  cp_custom_free(void *ptr);

#ifdef __cplusplus
}
#endif