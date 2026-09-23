// cl: -O2 -G6 -EHsc -MD -D_STLP_USE_STATIC_LIB
// stlport
//
// STLport signed decimal writer, the long instantiation of
// __write_decimal_backward(__true_type).
//
// Target evidence: retail divides with __aulldvrm and keeps the sign flag in
// bl, spilled to the argument's home slot across the helper call. The
// vendored 4.5.3 body (signed __max_int_t negated in place) cannot produce
// that: it calls __alldvrm, or with an unsigned __max_int_t puts the flag in
// cl. The body below is the later STLport shape -- flag first, then an
// unsigned __umax_int_t copy selected by the flag -- which is a structural
// inference from the bytes, not a claim about the shipped STLport release.
//
// Its own translation unit: stlport_write_integer_backward.cpp declares this
// overload without defining it, which keeps its callers saving esi/edi around
// the call the way retail does.

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
typedef unsigned __int64 __umax_int_t;

template <class Integer>
char *__cdecl __write_decimal_backward(
        char *ptr, Integer value, ios_base::fmtflags flags, const __true_type &)
{
    const bool negative = value < 0;
    __max_int_t temp = value;
    __umax_int_t utemp = negative ? -temp : temp;

    for (; utemp != 0; utemp /= 10)
        *--ptr = static_cast<char>(static_cast<int>(utemp % 10) + '0');

    if (negative)
        *--ptr = '-';
    else if (flags & ios_base::showpos)
        *--ptr = '+';

    return ptr;
}

template char *__cdecl __write_decimal_backward<long>(
        char *, long, ios_base::fmtflags, const __true_type &);

}
