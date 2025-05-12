
#include "heap.h"
#include <stddef.h>


typedef struct chunk_header {
  struct chunk_header* next;
  char in_use;
  int chunk_size;
} chunk_header_t;

#define HEAP_SIZE  (1024 * 1024)
static char heap[HEAP_SIZE];

static chunk_header_t *free_list = (chunk_header_t *)heap;
static char *heap_top = heap;

static void *new_alloc(int size)
{
  chunk_header_t *cur = (chunk_header_t *)heap_top;

  if ( ((char *)cur + sizeof(chunk_header_t) + size) > heap + HEAP_SIZE - 1 )
  {
    return NULL;
  }
  
  heap_top += sizeof(chunk_header_t) + size;
  
  cur->next = NULL;
  cur->chunk_size = size;
  cur->in_use = 1;
  
  return (void *)((char *)cur + sizeof(chunk_header_t));
}

static void heap_memset(void *addr, int init, int len)
{
  char *mem = (char *)addr;
  int total = len;
  
  while ( total > 0 )
  {
    *mem++ = init;
    total--;
  }
}

void heap_init(void)
{
  free_list = NULL;
  heap_top = heap;
  heap_memset(heap, 0, sizeof(heap));
}

void *heap_alloc(int size)
{
  chunk_header_t *cur = free_list;
  void *mem;
  
  if (!size) return NULL;
  
  // try to allocate new node
  if ( (mem = new_alloc(size)) ) 
  {
    if (!cur)
    {
      free_list = (chunk_header_t *)((char *)mem - sizeof(chunk_header_t));
    }
    else
    {
      while (cur->next) cur = cur->next;
      cur->next = (chunk_header_t *)((char *)mem - sizeof(chunk_header_t));
    }
    
    return mem;
  }
  else
  {
    if (cur)
    {
      while ( cur->next != NULL )
      {
        if ( cur->in_use == 0 && size <= cur->chunk_size )
        {
          cur->in_use = 1;
          return (void *)((char *)cur + sizeof(chunk_header_t));
        }
        cur = cur->next;
      }
    }
  }
  
  return NULL;
}

void *heap_calloc(int num, int size)
{
  int len = num * size;
  void *mem = heap_alloc(len);
  
  if (mem) heap_memset(mem, 0, len);
  
  return mem;
}

void *heap_realloc(void *ptr, int size)
{
  int len = size;
  char *src = (char *)ptr;
  char *mem = (char *)heap_alloc(len);
  char *temp = mem;
  
  if (!src) return mem;
  
  if (mem)
    while ( len-- ) *temp++ = *src++;

  return mem;
}

void heap_free(void *ptr)
{
  chunk_header_t *cur = free_list;
  chunk_header_t *node = (chunk_header_t *)(ptr - sizeof(chunk_header_t));
  char prev = 0, next = 0;
  node->in_use = 0;
  
  while ( cur->next && cur->next != node ) cur = cur->next;
  
  if (cur->in_use == 0 && node == (chunk_header_t *)((char *)cur + sizeof(chunk_header_t) + cur->chunk_size))
    prev = 1;
  
  if (node->next && node->next->in_use == 0 &&  node->next == (chunk_header_t *)((char *)node + sizeof(chunk_header_t) + node->chunk_size))
    next = 1;
  
  if (prev && next)
  {
    cur->next = node->next->next;
    cur->chunk_size = cur->chunk_size + node->chunk_size + node->next->chunk_size + sizeof(chunk_header_t)*2;
  }  
  else if (prev) 
  {
    cur->next = node->next;
    cur->chunk_size = cur->chunk_size + node->chunk_size + sizeof(chunk_header_t);
  }
  else if (next) 
  {
    node->chunk_size = node->chunk_size + node->next->chunk_size + sizeof(chunk_header_t);
    node->next = node->next->next;
  }
}

