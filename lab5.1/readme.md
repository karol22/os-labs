
To run the program type ``make`` or type make + the specific name of the program (without .c).
To clean the generated files, type ``make clean``
-----------------------------------------------------------------------------------------------------------------------
Memory Allocation

-Simple memory allocation
You allocate memory using the malloc call in the standard C library:
``#include <stdlib.h>
void *malloc(size_t size);``

-Allocating Lots of Memory

-Freeing memory
Programs that use memory on a dynamic basis should always release unused memory back to the
malloc memory manager using the free call. This enables separate blocks to be remerged and enables
the malloc library to look after memory, rather than have the application manage it.

``#include <stdlib.h>
void free(void *ptr_to memory);``

A call to free should be made only with a pointer to memory allocated by a call to malloc, calloc, or
realloc.

-Other memory allocation functions
``#include <stdlib.h>
void *calloc(size_t number_of_elements, size_t element_size);
void *realloc(void *existing_memory, size_t new_size);``

Although calloc allocates memory that can be freed with free, it has somewhat different parameters
from malloc: It allocates memory for an array of structures and requires the number of elements and the
size of each element as its parameters. The allocated memory is filled with zeros; and if calloc is successful,
a pointer to the first element is returned. Like malloc, subsequent calls are not guaranteed to return
contiguous space, so you can’t enlarge an array created by calloc by simply calling calloc again and
expecting the second call to return memory appended to that returned by the first call.
The realloc function changes the size of a block of memory that has been previously allocated. It’s
passed a pointer to some memory previously allocated by malloc, calloc, or realloc and resizes it
up or down as requested. The realloc function may have to move data around to achieve this, so it’s
important to ensure that once memory has been realloced, you always use the new pointer and never
try to access the memory using pointers set up before realloc was called.
