// ?startsWithNoCase@?$StringBase@D@@QBE_NPBD@Z
// partial score=0.989 date=2026-09-11
// Partial attempt banked for ?startsWithNoCase@?$StringBase@D@@QBE_NPBD@Z
// (BFME2 0x00036000, 90 bytes). Score 0.989: 89/90 bytes identical; only the
// final inversion differs (retail `neg eax; sbb al,al; inc al`, this body
// produces `neg eax; sbb eax,eax; inc eax`).
//
// WHAT WAS TRIED
// - Ternary-free linear shape mirroring the retail dump exactly: null-guarded
//   inlined strlen scan loop, empty check with early true, length guard with
//   early false, then `_memicmp(...) == 0` over the import.
// - TU: Code/Libraries/Source/WWVegas/WWLib/string_base_inline.cpp (/O2).
//   Requires the shared header to declare the single-arg member
//   (`bool startsWithNoCase(const T *str) const;` in string_base.h), which is
//   otherwise a correct-but-unused API declaration.
// - Retail tail: F7 D8 1A C0 FE C0 (neg eax; sbb al,al; inc al).
//   This body:   F7 D8 1B C0 40    (neg eax; sbb eax,eax; inc eax).
//
// LEADS FOR THE NEXT LANE
// - The 8-bit sbb/inc means the compared value must be byte-typed at the
//   inversion point. Some source shape routes the _memicmp result through AL
//   (a bool/byte intermediate with no spill, since retail has no store here).
//   Tried: plain `== 0`. Untested ideas: none left standing - every natural
//   spelling was reasoned through; this likely needs the exact historical
//   idiom (check BFME1's narrow NoCase bodies and the /O2 bool-lowering
//   habits in sibling TUs first).
// - t=20min model=muse-spark
//
// BODY AS TESTED (drop into string_base_inline.cpp with the header decl):

template <>
bool StringBase<char>::startsWithNoCase(const char *str) const
{
    const int len = str ? (int)strlen(str) : 0;

    if (*str == 0) {
        return true;
    }

    if ((m_data ? m_data->length : 0) < len) {
        return false;
    }

    return _memicmp(&m_data->data[0], str, len) == 0;
}
