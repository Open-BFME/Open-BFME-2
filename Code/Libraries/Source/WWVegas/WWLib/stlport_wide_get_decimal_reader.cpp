// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 wide decimal integer reader. The upstream __get_decimal_integer
// body from vendor/stlport/stl/_num_get.c: it hands a default-constructed
// (empty) grouping string to the base-10 accumulator.

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

template <class CharT, class Traits>
class basic_streambuf;

template <class CharT, class Traits>
class istreambuf_iterator
{
private:
    basic_streambuf<CharT, Traits> *_M_buf;
    mutable CharT _M_c;
    mutable unsigned char _M_eof;
    mutable unsigned char _M_have_c;
};

typedef istreambuf_iterator<wchar_t, char_traits<wchar_t> > wide_iterator;

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

template bool __cdecl __get_decimal_integer<wide_iterator, long>(
        wide_iterator &, wide_iterator &, long &);

}
