// cl: /O1 /G7 /arch:SSE
//
// WideCharCompare::compareNoCase at 0x00005344 (80B).
//
// The case-folded twin of WideCharCompare::compare (0x000052F8, already
// matched in string_base_compare_range.cpp). Both were named by the reloc
// sweep from the call sites in the wide compareRange workers (0x0000586D
// and 0x00005898), so the identity is the callers' rather than a guess.
//
// Donor: BFME1 StringBaseWideCompareNoCaseRaw.cpp (StringBase<WideChar>
// ::compareNoCaseRaw) — same loop with towlower, adapted from StringBase
// to the BFME2 WideCharCompare trait object (both ignore `this`, which
// arrives in ecx and is never read).
//
// towlower takes and returns unsigned short (16-bit, BFME1 donor spelling),
// not int: that is what lets retail keep the character in ax and push the
// full eax with a stale high half (the callee only reads the low 16).
// /G7 drops the redundant xor-before-mov-ax that /O1 emits for the two
// argument loads (QP-encoder precedent); everything else is identical
// under /O1 (frame, hoisted import load into esi, homes, tail movzx).

typedef unsigned short WideChar;

#define _DLL
#include <string.h>

extern "C" __declspec(dllimport) unsigned short __cdecl towlower(unsigned short value);

struct WideCharCompare
{
    char m_unused;

    int compareNoCase(const wchar_t *a, const wchar_t *b, int len) const;
};

int WideCharCompare::compareNoCase(const wchar_t *a, const wchar_t *b, int len) const
{
    while (len > 0) {
        const WideChar leftLower = (WideChar)towlower(*a);
        const WideChar rightLower = (WideChar)towlower(*b);
        if (leftLower != rightLower)
            return (int)leftLower - (int)rightLower;
        ++a;
        ++b;
        --len;
    }
    return 0;
}
