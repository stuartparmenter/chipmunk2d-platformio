#include <stddef.h>
#include <string.h>

#ifdef ESP_PLATFORM
  #include "esp_heap_caps.h"
  #define TRY_CAPS   (MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT)
  #define FALLBACK   (MALLOC_CAP_8BIT)
#endif

// calloc-like
void *cp_custom_calloc(size_t n, size_t size) {
  size_t bytes = n * size;
#ifndef ESP_PLATFORM
  // Non-IDF builds (desktop tests, etc.)
  void *p = calloc(n, size);
  return p;
#else
  void *p = heap_caps_calloc(1, bytes, TRY_CAPS);
  if (!p) p = heap_caps_calloc(1, bytes, FALLBACK);
  return p;
#endif
}

// realloc-like
void *cp_custom_realloc(void *ptr, size_t size) {
#ifndef ESP_PLATFORM
  return realloc(ptr, size);
#else
  // try keep/ move into PSRAM first, then fall back to internal RAM
  void *p = heap_caps_realloc(ptr, size, TRY_CAPS);
  if (!p && size) p = heap_caps_realloc(ptr, size, FALLBACK);
  return p;
#endif
}

// free-like
void cp_custom_free(void *p) {
#ifndef ESP_PLATFORM
  free(p);
#else
  // In ESP-IDF, memory from heap_caps_* may be freed with standard free()
  // or heap_caps_free(). Either is OK; use free() for simplicity.
  free(p);
#endif
}
