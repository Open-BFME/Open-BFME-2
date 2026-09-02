// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 integer writer, the unsigned __int64 instantiation. Its own
// unit because of one line: the 32-bit instantiations widen through a mask
// that clears the high word, and at 64 bits there is nothing to clear - the
// octal and hex arms shift the whole value with shrd. Sharing the template
// would force one shape on both.

namespace _STL
{

class ios_base
{
public:
    typedef int fmtflags;

    enum
    {
        hex = 0x0010,
        oct = 0x0020,
        basefield = 0x0038,
        showbase = 0x0200,
        showpos = 0x0800,
        uppercase = 0x4000
    };
};

struct __true_type {};
struct __false_type {};

template <class Integer>
struct __integer_is_signed
{
    typedef __true_type _Ret;
};

template <>
struct __integer_is_signed<unsigned __int64>
{
    typedef __false_type _Ret;
};

typedef unsigned __int64 __umax_int_t;

extern const char __hex_char_table_lo[];
extern const char __hex_char_table_hi[];

template <class Integer>
char *__cdecl __write_decimal_backward(
        char *, Integer, ios_base::fmtflags, const __true_type &);

template <class Integer>
__declspec(dllimport) __forceinline char *__cdecl __write_decimal_backward(
        char *ptr, Integer value, ios_base::fmtflags flags,
        const __false_type &)
{
    for (; value != 0; value /= 10)
        *--ptr = static_cast<int>(value % 10) + '0';

    if (flags & ios_base::showpos)
        *--ptr = '+';

    return ptr;
}

template <class Integer>
char *__cdecl __write_integer_backward(
        char *buffer, ios_base::fmtflags flags, Integer value)
{
    char *ptr = buffer;
    __umax_int_t temp;

    if (value == 0)
    {
        *--ptr = '0';
        if ((flags & ios_base::showpos) &&
                ((flags & (ios_base::hex | ios_base::oct)) == 0))
            *--ptr = '+';
    }
    else
    {
        switch (flags & ios_base::basefield)
        {
        case ios_base::oct:
            temp = value;

            for (; temp != 0; temp >>= 3)
                *--ptr = (static_cast<unsigned>(temp) & 0x7) + '0';

            if (flags & ios_base::showbase)
                *--ptr = '0';
            break;

        case ios_base::hex:
            {
                const char *table = (flags & ios_base::uppercase)
                        ? __hex_char_table_hi
                        : __hex_char_table_lo;
                temp = value;

                for (; temp != 0; temp >>= 4)
                    *--ptr = table[static_cast<unsigned>(temp) & 0xF];

                if (flags & ios_base::showbase)
                {
                    *--ptr = table[16];
                    *--ptr = '0';
                }
            }
            break;

        default:
            ptr = __write_decimal_backward(ptr, value, flags,
                    typename __integer_is_signed<Integer>::_Ret());
            break;
        }
    }

    return ptr;
}

template char *__cdecl __write_integer_backward<unsigned __int64>(
        char *, ios_base::fmtflags, unsigned __int64);

}
