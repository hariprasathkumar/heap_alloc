#include <stdio.h>
#include <string.h>
#include "heap.h"

// Helper to check memory content
int is_zeroed(void *ptr, size_t size) {
    unsigned char *bytes = (unsigned char *)ptr;
    for (size_t i = 0; i < size; i++) {
        if (bytes[i] != 0) return 0;
    }
    return 1;
}

int main() {
    void *d;
    
    heap_init();
    printf("=== Heap Allocator Tests ===\n");

    void *a = heap_alloc(100);
    if (!a) {
        printf("heap_alloc failed for 100 bytes\n");
        return 1;
    }
    printf("heap_alloc(100) OK\n");

    void *b = heap_calloc(50, sizeof(int));
    if (!b || !is_zeroed(b, 50 * sizeof(int))) {
        printf("heap_calloc failed or not zero-initialized\n");
        return 1;
    }
    printf("heap_calloc(50, sizeof(int)) OK and zero-initialized\n");

    strcpy(a, "hello heap");
    void *c = heap_realloc(a, 200);
    if (!c || strcmp(c, "hello heap") != 0) {
        printf("heap_realloc failed or data corrupted\n");
        return 1;
    }
    printf("heap_realloc OK and preserved content\n");

    heap_free(b);
    heap_free(c);  // This was originally 'a'

    heap_init();
    for (int i = 0; i < 100000; i++ )
    {
      d = heap_alloc(150);
      if (!d) {
          printf("heap_alloc failed %d round\n", i);
      }
      else
      {
          printf("heap_alloc success %d round\n", i);
          heap_free(d);
      }
    }
    
    // largest chunk
    heap_init();
    d = heap_alloc(1024*1024 - 8*3);
    if (!d)
    {
      printf("largest alloc failed\n");
      return 1;
    }
    else
    {
      printf("largest alloc successful\n");
      heap_free(d);
    }
      
    printf("All tests passed.\n");
    return 0;
}
