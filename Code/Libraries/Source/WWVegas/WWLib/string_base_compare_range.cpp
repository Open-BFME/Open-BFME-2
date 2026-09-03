// cl: /O1 /arch:SSE
//
// The two narrow (const char *, int) comparison workers, split out of
// string_base.cpp for one flag: /arch:SSE. Both bodies pick the shorter of the
// two lengths with cmovge, and cl 13.10 will not emit a conditional move
// without /arch - not at /G5, /G6, /G7, /GB, /Ot, /Os, /O1, /O2 or /Ox, which
// is what kept these two unclaimed while the members calling them were
// already matched. /O2 loses it again by dropping the ebp frame.
//
// The ternary is not cosmetic either: written as an if statement cl also
// picks the other length for esi and three more bytes move.
//
// The trait object is a one-byte struct the callers zero with a lea/stosb
// pair. Neither narrow worker reads it - only the wide pair takes its address
// - so it stays opaque here.

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

// The wide pair at 0x0000586D and 0x00005898 is the same shape, except that
// both of them DO read the trait object: each takes its address and calls
// through it, which is why the narrow pair can leave it opaque and these
// cannot. ecx holds &tag at the call, so the worker is a member of the trait.
struct WideCharCompare
{
    char m_unused;

    int compare(const wchar_t *a, const wchar_t *b, int len) const;
    int compareNoCase(const wchar_t *a, const wchar_t *b, int len) const;
};

int compareRange(const wchar_t *a, int alen, const wchar_t *b, int blen, WideCharCompare tag)
{
    const int len = alen < blen ? alen : blen;
    const int result = tag.compare(a, b, len);
    if (result != 0)
        return result;
    return alen - blen;
}

int compareRangeNoCase(const wchar_t *a, int alen, const wchar_t *b, int blen, WideCharCompare tag)
{
    const int len = alen < blen ? alen : blen;
    const int result = tag.compareNoCase(a, b, len);
    if (result != 0)
        return result;
    return alen - blen;
}
