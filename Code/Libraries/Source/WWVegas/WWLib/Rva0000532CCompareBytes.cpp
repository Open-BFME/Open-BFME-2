// cl: /MD
// Target 24B at 532C..5344 forwards three 32-bit stack arguments to
// MSVCR71.dll!_memicmp, target PE IAT VA BBA690 (DIR32 offset 14).
// Boundary: verified WideCharCompare at 52F8+52 ends exactly here;
// next verified compareNoCase starts at 5344. No E8/E9 or VA callers found.
// A BFME1 xsurface.cpp BlitBackward masked match supplied the lead, but
// its memmove identity is refuted by the target import, not carried over.
// This address-labelled stdcall view preserves the 12B callee stack pop
// and comparison result in EAX; ECX is unused. Original name, member/free
// distinction, return contract and reachability remain unknown.
#include <string.h>
int __stdcall rva0000532CCompareBytes(const void *left, const void *right, unsigned count)
{
 return _memicmp(left, right, count);
}
