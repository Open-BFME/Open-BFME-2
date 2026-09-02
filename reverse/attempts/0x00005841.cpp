// ?compareRange@@YAHPBDH0HUCharCompare@@@Z and ?compareRangeNoCase@...@Z
// partial score=0.98 date=2026-09-02
// cl: /O1 /G6
//
// The two narrow (const char *, int) comparison workers, split out of
// string_base.cpp so they can be built for the Pentium Pro. Both bodies pick
// the shorter of the two lengths with cmovge, and cl 13.10 will not emit a
// conditional move below /G6 - which is the whole reason these two sat
// unclaimed while the members that call them were already matched.

#define _DLL
#include <string.h>

// The four (const T *, int) comparison members hand five arguments to a shared
// worker: this string's data and length, the argument's data and length, and a
// one-byte trait object the callers zero with a lea/stosb pair. Neither narrow
// worker reads that object - only the wide pair takes its address - so it stays
// an opaque byte here.
struct CharCompare
{
    char m_unused;
};

int compareRange(const char *a, int alen, const char *b, int blen, CharCompare tag)
{
    const int len = alen < blen ? alen : blen;
    const int result = memcmp(a, b, len);
    if (result != 0)
        return result;
    return alen - blen;
}

int compareRangeNoCase(const char *a, int alen, const char *b, int blen, CharCompare tag)
{
    const int len = alen < blen ? alen : blen;
    const int result = _memicmp(a, b, len);
    if (result != 0)
        return result;
    return alen - blen;
}
