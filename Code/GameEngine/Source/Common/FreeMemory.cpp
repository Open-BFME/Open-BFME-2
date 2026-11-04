// cl: /MD
int __cdecl Rva008791E0Remove(void *key, void **out);
#include <stdlib.h>

// nbench sysspec.c FreeMemory: drop the block from mem_array, then free
// the true (unaligned) address the removal hands back.
void FreeMemory(void *mempointer, int *errorcode)
{
	if (Rva008791E0Remove(mempointer, &mempointer) != 0) {
		*errorcode = 3;
		return;
	}
	free(mempointer);
	*errorcode = 0;
}
