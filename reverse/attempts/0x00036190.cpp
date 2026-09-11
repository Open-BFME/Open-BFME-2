// ?startsWith@?$StringBase@G@@QBE_NPBG@Z
// partial score=0.989 date=2026-09-11
// Partial attempt banked for ?startsWith@?$StringBase@G@@QBE_NPBG@Z
// (BFME2 0x00036190, 90 bytes). Score 0.989: 89/90 bytes identical; only the
// final inversion differs (retail `neg eax; sbb al,al; pop edi; inc al`,
// this body produces `neg eax; sbb eax,eax; pop edi; inc eax`).
//
// This is the SAME one-byte phenomenon as the banked narrow twin at
// 0x00036000 (reverse/attempts/0x00036000.cpp): both bodies end with the
// split 8-bit inversion (a pop interleaved between sbb and inc), while the
// (T*,int) trait workers in this TU end with plain neg/sbb/inc-eax. Two
// bodies, same mystery - the trigger is structural (wcslen-call prologue
// with two callee-saved regs changes the scheduler's lowering of `== 0`),
// not a typo. Do not retry the obvious `== 0` spellings; all were exhausted
// on the narrow twin.
//
// WHAT WAS TRIED (this body)
// - TU: Code/Libraries/Source/WWVegas/WWLib/string_base_inline.cpp (/O2).
// - `const int len = str ? (int)wcslen(str) : 0;` (wcslen stays a call;
//   strlen would inline-scan and miss), null guard, `*str == 0` early true,
//   length guard early false, then `tag.compare(&m_data->data[0], str, len)
//   == 0` with a deliberately uninitialized WideCharCompare (zeroing it
//   emits a stray stosb, proven on the endsWith worker).
// - Retail tail: F7 D8 1A C0 5F FE C0 (neg eax; sbb al,al; pop edi; inc al).
//   This body:   F7 D8 1B C0 5F 40    (neg eax; sbb eax,eax; pop edi; inc eax).
//
// LEADS FOR THE NEXT LANE
// - The 8-bit lowering needs the compared value byte-typed at the inversion
//   with no spill. Candidate nobody has tried: route the trait result through
//   an explicit `bool` lvalue that MSVC keeps in AL across the epilogue pops
//   (risky: likely spills). Or find which historical idiom (check BFME1's
//   narrow/wide C-string bodies and /O2 bool-lowering habits) selects sbb-al.
// - t=15min model=muse-spark (plus 20min on the narrow twin - same phenomenon)
//
// BODY AS TESTED:

template <>
bool StringBase<wchar_t>::startsWith(const wchar_t *str) const
{
    const int len = str ? (int)wcslen(str) : 0;

    if (*str == 0) {
        return true;
    }

    if ((m_data ? m_data->length : 0) < len) {
        return false;
    }

    WideCharCompare tag;

    return tag.compare(&m_data->data[0], str, len) == 0;
}
