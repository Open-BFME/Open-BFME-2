// cl: /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 wide signed 64-bit integer accumulator. The implementation
// is the upstream __get_integer body from vendor/stlport/stl/_num_get.c.

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
    typedef unsigned int size_type;

    __declspec(dllimport) __forceinline bool empty() const
    {
        return _M_start == _M_finish;
    }
    __declspec(dllimport) __forceinline const CharT *data() const
    {
        return _M_start;
    }
    __declspec(dllimport) __forceinline size_type size() const
    {
        return static_cast<size_type>(_M_finish - _M_start);
    }

private:
    CharT *_M_start;
    CharT *_M_finish;
    _STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > narrow_string;

template <class CharT, class Traits>
class basic_streambuf
{
public:
    wchar_t sbumpc();
};

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
    __declspec(dllimport) __forceinline bool equal(
            const istreambuf_iterator &other) const
    {
        if (_M_buf != 0)
            _M_getc();
        if (other._M_buf != 0)
            other._M_getc();
        return _M_eof == other._M_eof;
    }

    __declspec(dllimport) __forceinline CharT operator*() const
    {
        _M_getc();
        return _M_c;
    }

    __declspec(dllimport) __forceinline istreambuf_iterator &operator++()
    {
        _M_buf->sbumpc();
        _M_have_c = false;
        return *this;
    }

private:
    void _M_getc() const;

    basic_streambuf<CharT, Traits> *_M_buf;
    mutable CharT _M_c;
    mutable unsigned char _M_eof;
    mutable unsigned char _M_have_c;
};

typedef istreambuf_iterator<wchar_t, char_traits<wchar_t> > wide_iterator;

struct __true_type {};

extern const unsigned char __digit_val_table[];

__declspec(dllimport) __forceinline int __get_digit_from_table(unsigned index)
{
    return index > 127 ? 0xFF : __digit_val_table[index];
}

bool __cdecl __valid_grouping(
        const char *, const char *, const char *, const char *);

template <class InputIter, class Integer>
bool __cdecl __get_integer(
        InputIter &first, InputIter &last, int base, Integer &value,
        int got, bool negative, char separator,
        const narrow_string &grouping, const __true_type &)
{
    bool overflow = false;
    Integer result = 0;
    bool is_group = !grouping.empty();
    char group_sizes[64];
    int current_group_size = 0;
    char *group_sizes_end = group_sizes;

    Integer over_base = static_cast<Integer>(0x8000000000000000I64) /
            static_cast<Integer>(base);

    for (; !first.equal(last); ++first)
    {
        const char character = *first;

        if (is_group && character == separator)
        {
            *group_sizes_end++ = static_cast<char>(current_group_size);
            current_group_size = 0;
            continue;
        }

        int digit = __get_digit_from_table(character);
        if (digit >= base)
            break;

        ++got;
        ++current_group_size;
        if (result < over_base)
            overflow = true;
        else
        {
            Integer next = static_cast<Integer>(base * result - digit);
            if (result != 0)
                overflow = overflow || next >= result;
            result = next;
        }
    }

    if (is_group && group_sizes_end != group_sizes)
        *group_sizes_end++ = static_cast<char>(current_group_size);

    if (got > 0)
    {
        value = overflow
                ? negative ? static_cast<Integer>(0x8000000000000000I64)
                           : static_cast<Integer>(0x7FFFFFFFFFFFFFFFI64)
                : negative ? result : static_cast<Integer>(-result);
    }

    return got > 0 && !overflow &&
            (!is_group || __valid_grouping(
                    group_sizes, group_sizes_end,
                    grouping.data(), grouping.data() + grouping.size()));
}

template bool __cdecl __get_integer<wide_iterator, __int64>(
        wide_iterator &, wide_iterator &, int, __int64 &, int, bool, char,
        const narrow_string &, const __true_type &);

}
