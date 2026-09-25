// cl: -O2 -G6 -EHsc -MD -D_STLP_USE_STATIC_LIB
// stlport
//
// STLport unsigned decimal writer, the unsigned __int64 instantiation of
// __write_decimal_backward(__false_type). Retail divides with __aulldvrm,
// checks flags & showpos (0x0800) for the '+' prefix, and keeps the buffer
// pointer in esi across the zero-check (push before branch).

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

struct __false_type {};

template <class Integer>
char *__cdecl __write_decimal_backward(
        char *ptr, Integer value, ios_base::fmtflags flags, const __false_type &)
{
    for (; value != 0; value /= 10)
        *--ptr = static_cast<char>(static_cast<int>(value % 10) + '0');

    if (flags & ios_base::showpos)
        *--ptr = '+';

    return ptr;
}

template char *__cdecl __write_decimal_backward<unsigned __int64>(
        char *, unsigned __int64, ios_base::fmtflags, const __false_type &);

}
