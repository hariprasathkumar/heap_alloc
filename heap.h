
#ifndef HEAP_H
#define HEAP_H

void heap_init(void);
void *heap_alloc(int size);
void *heap_calloc(int num, int size);
void *heap_realloc(void *ptr, int size);
void heap_free(void *ptr);

#endif
