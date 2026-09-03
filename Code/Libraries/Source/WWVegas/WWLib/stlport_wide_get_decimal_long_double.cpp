// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 __get_decimal_integer over a wide string, accumulating into a
// long double. This is the instantiation money_get<wchar_t>::do_get reaches
// for the long double overload - _monetary.c pushes a terminating zero onto
// its string_type buffer and then hands begin()/end() to this reader, so the
// iterator is a raw wchar_t* rather than the istreambuf_iterator the num_get
// twins at 0x00009CD0 and 0x0000B4C0 use, and the accumulator is long double
// rather than long.
//
// Both of those show in the accumulator at 0x0000DCC0: it reads the character
// with a byte load but advances the iterator by two, which is a wchar_t*
// narrowed to char by `const char __c = *__first`, and it computes
// numeric_limits<_Integer>::max() / __base on the x87 stack, which no
// integral _Integer would need.
//
// The body itself is unchanged from the twins - a default-constructed empty
// grouping string handed to the base-10 accumulator.
void __cdecl free(void *);

typedef unsigned short wchar_t;

namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator {};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
    Pointer _M_data;
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
    basic_string();
    __declspec(dllimport) __forceinline ~basic_string()
    {
        if (_M_start != 0)
            free(_M_start);
    }

private:
    CharT *_M_start;
    CharT *_M_finish;
    _STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > narrow_string;

struct __false_type {};

template <class InputIter, class Integer>
bool __cdecl __get_integer(
        InputIter &, InputIter &, int, Integer &, int, bool, char,
        const narrow_string &, const __false_type &);

template <class InputIter, class Integer>
bool __cdecl __get_decimal_integer(
        InputIter &first, InputIter &last, Integer &value)
{
    narrow_string grouping;
    return __get_integer(
            first, last, 10, value, 0, false, ' ', grouping, __false_type());
}

template bool __cdecl __get_decimal_integer<wchar_t *, long double>(
        wchar_t *&, wchar_t *&, long double &);

}
