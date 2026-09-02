// cl: -O2 -G6 -EHsc -MD -D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 signed decimal writer, the __int64 instantiation. The
// upstream __write_decimal_backward body from vendor/stlport/stl/_num_put.c,
// widened to the library's __max_int_t before the digit loop so the division
// is __aulldvrm.
//
// The 32-bit instantiation of this same template is banked rather than landed:
// at `long` the compiler puts the negative flag in cl where retail uses bl,
// and the body comes out three bytes short. At __int64 there is no such
// choice to make - the value already occupies edx:eax - and the same source
// matches on the first build.

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

template char *__cdecl __write_decimal_backward<__int64>(
        char *, __int64, ios_base::fmtflags, const __true_type &);

}
