// cl: /DNDEBUG /MD /EHsc /Oi
// ?Rva003FCE11Compare@@YAHPAX0@Z @0x003FCE11 31B
// Forwards two pointers plus zero to Rva003FCD04Compare; third dword never read.
// Evidence: rowed callee Rva003FCD04Compare 0x003FCD04; caller 0x003FCFB5.
#include <string.h>
int __cdecl Rva003FCD04Compare(void *a, void *b, int c);

int __cdecl Rva003FCE11Compare(void *a, void *b)
{
    int c;
    memset(&c, 0, 1);
    return Rva003FCD04Compare(a, b, c);
}
