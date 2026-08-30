// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 integer writer. The upstream __write_integer_backward body
// from vendor/stlport/stl/_num_put.c: the octal and hex arms build their
// digits here and the decimal arm tails into __write_decimal_backward.

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

typedef unsigned __int64 __umax_int_t;

extern const char __hex_char_table_lo[];
extern const char __hex_char_table_hi[];

template <class Integer>
char *__cdecl __write_decimal_backward(
        char *, Integer, ios_base::fmtflags, const __true_type &);

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
            temp &= 0xFFFFFFFF;

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
                temp &= 0xFFFFFFFF;

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
            ptr = __write_decimal_backward(ptr, value, flags, __true_type());
            break;
        }
    }

    return ptr;
}

template char *__cdecl __write_integer_backward<long>(
        char *, ios_base::fmtflags, long);

}
