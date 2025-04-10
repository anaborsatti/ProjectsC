#include <stdint.h>
#include <string.h>
// Override allocation functions
void *_malloc(size_t size, uint32_t line);
void *_calloc(size_t nitems, size_t size, uint32_t line);
void _free(void *ptr, uint32_t line);
char *__strdup(const char* s, uint32_t line);

void print_memory_leak_report();

// redefine allocator functions
#define malloc(size) _malloc(size, __LINE__)
#define calloc(nitems, size) _calloc(nitems, size, __LINE__)
#define strdup(s) __strdup(s, __LINE__) 
#define free(ptr) _free(ptr, __LINE__)