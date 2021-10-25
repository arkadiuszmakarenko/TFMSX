#include <stdio.h>
#include <sys/errno.h>


void *_sbrk(int incr)
{
	extern char s_heap asm("s_heap");
	extern char e_heap asm("e_heap");
	static char *heap_end;
	char *prev_heap_end;

	if (heap_end == 0)
		heap_end = &s_heap;

	prev_heap_end = heap_end;

	if (heap_end + incr > &e_heap)
	{
		errno = ENOMEM;
		return (void *) -1;
	}

	heap_end += incr;

	return (void *) prev_heap_end;
}
