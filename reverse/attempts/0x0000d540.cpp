// ??$__write_decimal_backward@J@_STL@@YAPADPADJHABU__true_type@0@@Z
// partial score=0.65 date=2026-09-21
// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 signed decimal writer: the out-of-line half of the
// __write_decimal_backward overload pair in vendor/stlport/stl/_num_put.c.
//
// Its own translation unit on purpose. stlport_write_integer_backward.cpp
// DECLARES this overload and never defines it, which is what makes its three
// matched bodies save esi/edi around the call the way retail does; defining
// it beside them would let MSVC see the callee and re-colour them.
//
// Retail widens to __max_int_t before the loop, so the digit step is one
// __alldvrm call returning quotient in eax:edx and remainder in ecx:ebx --
// `temp /= 10` and `temp % 10` fused. The sign flag is computed from the
// 32-bit argument before the widening cdq and spilled into the argument's
// own home slot.

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

typedef __int64 __max_int_t;

template <class Integer>
char *__cdecl __write_decimal_backward(char *ptr, Integer value,
        ios_base::fmtflags flags, const __true_type & /* is_signed */)
{
    __max_int_t temp = value;

    const bool negative = value < 0;

    if (negative)
        temp = -temp;

    for (; temp != 0; temp /= 10)
        *--ptr = static_cast<int>(temp % 10) + '0';

    // put sign if requested
    if (negative)
        *--ptr = '-';
    else if (flags & ios_base::showpos)
        *--ptr = '+';

    return ptr;
}

template char *__cdecl __write_decimal_backward<long>(
        char *, long, ios_base::fmtflags, const __true_type &);

}
