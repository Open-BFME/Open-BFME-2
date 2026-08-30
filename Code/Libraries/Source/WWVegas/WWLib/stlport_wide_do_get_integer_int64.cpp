// cl: /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 wide signed 64-bit integer scanner. The implementation is
// the upstream _M_do_get_integer body from vendor/stlport/stl/_num_get.c.

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

class locale
{
public:
    class facet
    {
    public:
        virtual ~facet();
    };
};

template <class CharT>
class numpunct;

template <>
class numpunct<char> : public locale::facet
{
public:
    __declspec(dllimport) __forceinline char thousands_sep() const
    {
        return do_thousands_sep();
    }

protected:
    virtual ~numpunct();
    virtual char do_decimal_point() const;
    virtual char do_thousands_sep() const;
};

class ios_base
{
public:
    typedef int fmtflags;
    typedef int iostate;
    typedef int openmode;
    typedef int seekdir;
    typedef int streamsize;

    enum
    {
        goodbit = 0,
        eofbit = 2,
        failbit = 4
    };

    virtual ~ios_base();
    __declspec(dllimport) __forceinline const void *_M_numpunct_facet() const
    {
        return _M_cached_numpunct;
    }
    __declspec(dllimport) __forceinline const narrow_string &_M_grouping() const
    {
        return _M_cached_grouping;
    }

private:
    fmtflags _M_fmtflags;
    iostate _M_iostate;
    openmode _M_openmode;
    seekdir _M_seekdir;
    iostate _M_exception_mask;
    streamsize _M_precision;
    streamsize _M_width;
    void *_M_locale;
    void *_M_callbacks;
    unsigned int _M_num_callbacks;
    unsigned int _M_callback_index;
    long *_M_iwords;
    unsigned int _M_num_iwords;
    void **_M_pwords;
    unsigned int _M_num_pwords;
    void *_M_cached_ctype;
    void *_M_cached_numpunct;
    narrow_string _M_cached_grouping;
};

template <class CharT, class Traits>
class basic_streambuf;

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

private:
    void _M_getc() const;

    basic_streambuf<CharT, Traits> *_M_buf;
    mutable CharT _M_c;
    mutable unsigned char _M_eof;
    mutable unsigned char _M_have_c;
};

typedef istreambuf_iterator<wchar_t, char_traits<wchar_t> > wide_iterator;

struct __true_type {};

template <class InputIter, class CharT>
int __cdecl _M_get_base_or_zero(
        InputIter &, InputIter &, ios_base &, CharT *);

template <class InputIter, class Integer>
bool __cdecl __get_integer(
        InputIter &, InputIter &, int, Integer &, int, bool, char,
        const narrow_string &, const __true_type &);

template <class InputIter, class Integer, class CharT>
InputIter __cdecl _M_do_get_integer(
        InputIter &in, InputIter &end, ios_base &stream,
        ios_base::iostate &error, Integer &value, CharT *character)
{
    const numpunct<CharT> &punctuation =
            *static_cast<const numpunct<CharT> *>(stream._M_numpunct_facet());
    const narrow_string &grouping = stream._M_grouping();

    const int base_or_zero =
            _M_get_base_or_zero(in, end, stream, character);
    int got = base_or_zero & 1;

    bool result;
    if (in.equal(end))
    {
        if (got > 0)
        {
            value = 0;
            result = true;
        }
        else
            result = false;
    }
    else
    {
        const bool negative = (base_or_zero & 2) != 0;
        const int base = base_or_zero >> 2;
        result = __get_integer(
                in, end, base, value, got, negative,
                punctuation.thousands_sep(), grouping, __true_type());
    }

    error = static_cast<ios_base::iostate>(
            result ? ios_base::goodbit : ios_base::failbit);
    if (in.equal(end))
        error |= ios_base::eofbit;
    return in;
}
template wide_iterator __cdecl _M_do_get_integer<
        wide_iterator, __int64, char>(
        wide_iterator &, wide_iterator &, ios_base &,
        ios_base::iostate &, __int64 &, char *);

}
