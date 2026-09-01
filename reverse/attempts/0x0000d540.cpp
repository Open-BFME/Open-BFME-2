// ??$__write_decimal_backward@J@_STL@@YAPADPADJHABU__true_type@0@@Z
// partial score=0.93 date=2026-09-02
// ??$__write_decimal_backward@J@_STL@@YAPADPADJHABU__true_type@0@@Z
// partial score=0.93 date=2026-09-02
//
// 2026-09-02: the NAME is now confirmed. reverse/reloc_names.csv, regenerated
// by the full gate, derives ??$__write_decimal_backward@J@... at 0x0000D540
// from its call sites, so this is no longer an anonymous dump row.
//
// Two things fixed since the last bank. __max_int_t is UNSIGNED __int64, not
// signed: retail divides through __aulldvrm at 0x006296E0, and a signed
// __int64 asks for __alldvrm instead. That helper is now pinned, so the body
// resolves cleanly and the only remaining difference is the one already
// recorded.
//
// Still open: retail keeps the negative flag in bl, pushing ebx for it, and
// spills it to [esp+0x18]; MSVC 7.1 keeps it in cl and spills to [esp+0x10].
// 115 bytes against 118. Flags re-swept with LEADING DASHES (Git Bash rewrites
// a slash-leading argument into a path before cl sees it): -O2, -Ox and
// -O2 -Ob0 all give 115, -O1 and -O1 -G7 give 94, and -O2 -G7 gives 119 - the
// only one on the far side, and worth a closer look than it got here. Computing
// the flag before the widening rather than after gives 111.

// cl: -O2 -EHsc -MD -D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 signed decimal writer. The upstream __write_decimal_backward
// body from vendor/stlport/stl/_num_put.c, widened to the library's
// __max_int_t before the digit loop so the division is the 64-bit helper.

namespace _STL
{

class ios_base
{
public:
    typedef int fmtflags;

    enum
    {
        showpos = 0x0800
    };
};

struct __true_type {};

typedef unsigned __int64 __max_int_t;

template <class Integer>
char *__cdecl __write_decimal_backward(
        char *ptr, Integer value, ios_base::fmtflags flags, const __true_type &)
{
    __max_int_t temp = value;

    const bool negative = value < 0;

    if (negative)
        temp = -temp;

    for (; temp != 0; temp /= 10)
        *--ptr = static_cast<int>(temp % 10) + '0';

    if (negative)
        *--ptr = '-';
    else if (flags & ios_base::showpos)
        *--ptr = '+';

    return ptr;
}

template char *__cdecl __write_decimal_backward<long>(
        char *, long, ios_base::fmtflags, const __true_type &);

}
