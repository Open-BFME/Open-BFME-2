// ?compareNoCase@WideCharCompare@@QBEHPBG0H@Z
// partial score=0.95 date=2026-09-03
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

extern "C" __declspec(dllimport) int __cdecl towlower(int c);

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

// The two trait members themselves, at 0x000052F8 and 0x00005344. Both were
// named by the reloc sweep from the call sites in the wide workers below, so
// the identity is the callers' rather than a guess.
//
// Neither touches the trait, which is why both callers can pass it by value
// and the struct can stay a single opaque byte: `this` arrives in ecx and is
// never read. Both count down the length parameter in its own home slot
// rather than in a register, and both take the difference through movzx, so
// the comparison is on the unsigned value.
int WideCharCompare::compare(const wchar_t *a, const wchar_t *b, int len) const
{
    while (len > 0) {
        if (*a != *b)
            return *a - *b;
        ++a;
        ++b;
        --len;
    }
    return 0;
}

// The case-folded twin loads towlower's import thunk once and calls it twice
// per character, keeping the folded left-hand character in the length's
// neighbouring home slot between the two calls.
int WideCharCompare::compareNoCase(const wchar_t *a, const wchar_t *b, int len) const
{
    while (len > 0) {
        const wchar_t la = (wchar_t)towlower(*a);
        const wchar_t lb = (wchar_t)towlower(*b);
        if (la != lb)
            return la - lb;
        ++a;
        ++b;
        --len;
    }
    return 0;
}

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
