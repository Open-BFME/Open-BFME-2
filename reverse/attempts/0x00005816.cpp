// ?d_00005816@@YAXXZ
// partial score=0.9 date=2026-08-30
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
    int result = memcmp(left, right, leftLen < rightLen ? leftLen : rightLen);
    if (result != 0) {
        return result;
    }
    return leftLen - rightLen;
}
