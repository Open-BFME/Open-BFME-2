// ?d_00005816@@YAXXZ
// partial score=0.95 date=2026-08-30
// cl: /O1 /Oy-
// Retail 0x00005816: the shared data comparison the StringBase<char> compare
// overloads tail into. The upstream name is not recoverable -- the body has
// internal linkage and no reloc, xref or vtable evidence names it -- so it
// carries its address as its name.

#define _DLL
#include <string.h>

__declspec(noinline) int Rva00005816(const char *left, int leftLen,
                                     const char *right, int rightLen,
                                     bool noCase)
{
    (void)noCase;
    int shortest = leftLen;
    if (shortest >= rightLen)
        shortest = rightLen;
    int result = memcmp(left, right, shortest);
    if (result != 0) {
        return result;
    }
    return leftLen - rightLen;
}
