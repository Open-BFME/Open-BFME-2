// cl: /G7 /DNDEBUG /MD
//
// nstrdup, retail 0x00619880, 68 bytes. Tagged array new at 0x6C4C30, then
// an inlined strcpy. Dedicated TU so ini.cpp cannot inline this helper.

void *__cdecl operator new[](unsigned int, unsigned int);
#include <string.h>

char *nstrdup(const char *str)
{
	if (!str)
		return 0;
	char *copy = new (0x737472u) char[strlen(str) + 1];
	strcpy(copy, str);
	return copy;
}
