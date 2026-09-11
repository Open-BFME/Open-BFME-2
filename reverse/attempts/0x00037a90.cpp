// ?compareNoCase@?$StringBase@G@@QBEHPBG@Z
// partial score=0.989 date=2026-09-11
// Partial attempt banked for ?compareNoCase@?$StringBase@G@@QBEHPBG@Z
// (BFME2 0x00037A90, 89 bytes). Score 0.989: 88/89 bytes identical; only the
// length-tiebreak instruction order differs (retail `sub esi,edi; mov eax,esi`,
// this body produces `mov eax,esi; sub eax,edi`).
//
// WHAT WAS TRIED
// - TU: Code/Libraries/Source/WWVegas/WWLib/string_base_inline.cpp (/O2).
// - wcslen CALL for the length (correct: this TU calls wcslen, strlen would
//   inline-scan and miss), null guard, empty check, length guard, then
//   `tag.compareNoCase(data, str, len < strLen ? len : strLen)` through a
//   deliberately uninitialized WideCharCompare (zeroing it emits a stray
//   stosb - proven on the endsWith worker), with
//   `if (result != 0) return result;` plus a length-difference tiebreak.
// - Tiebreak spellings tried: `return len - strLen;`, `len -= strLen; return
//   len;`, `return len -= strLen;` - all three compile to mov-eax-first.
// - Retail tail: ... 75 04 2B F7 8B C6 (jne, sub esi,edi, mov eax,esi).
//   This body:   ... 75 04 8B C6 2B C7 (jne, mov eax,esi, sub eax,edi).
//
// LEADS FOR THE NEXT LANE
// - For MSVC to emit sub-in-esi, the tiebreak value must already be at home
//   in esi with eax dead - i.e. some spelling where `len` is consumed from
//   esi rather than moved to eax first. Candidate nobody has tried: compute
//   the difference BEFORE the trait call into a separate local (reordering
//   constraints may force the in-place form), or express the tiebreak as an
//   assignment through a reference/pointer. Beware changing anything else:
//   all 85 preceding bytes are exact, including the branchy min-selection
//   (no cmov without /arch:SSE) and the uninitialized trait.
// - t=15min model=muse-spark
//
// BODY AS TESTED:

template <>
int StringBase<wchar_t>::compareNoCase(const wchar_t *str) const
{
    const int strLen = str ? (int)wcslen(str) : 0;
    int len = m_data ? m_data->length : 0;
    const wchar_t *data = m_data ? &m_data->data[0] : L"";

    WideCharCompare tag;

    int result = tag.compareNoCase(data, str, len < strLen ? len : strLen);
    if (result != 0) {
        return result;
    }
    return len -= strLen;
}
