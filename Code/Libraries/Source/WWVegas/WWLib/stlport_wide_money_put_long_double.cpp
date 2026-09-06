// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 money_put<wchar_t>::do_put over long double (RVA 0xBE50).
// The upstream _monetary.h body leaves units unused and forwards its stack
// buffer through the string overload. Keep that behavior for byte matching.
//
// Retail's three-entry unwind map identifies a locale, an empty allocator
// temporary, and the string's base. The allocator cleanup at RVA 0x69E440 is
// a bare ret, but an empty C++ destructor is eliminated before MSVC 7.1
// assigns EH states. Disabled bookkeeping retains the state until optimization,
// as in stlport_narrow_string_base_dtor.cpp. The string destructor must remain
// out of line; the call at RVA 0xBEE9 reaches the ICF-folded body at 0x142D70.

void __cdecl free(void *);
namespace _STL
{
enum { _STLP_LEAKS_CHECK = 0 };

class _Locale_impl
{
public:
    virtual ~_Locale_impl();
    virtual void _M_incr();
    virtual void _M_decr();
};

class locale
{
public:
    class facet {
    public:
        virtual ~facet();
    };
    locale(const locale &) throw();
    ~locale() throw() { _M_impl->_M_decr(); }
private:
    _Locale_impl *_M_impl;
};

class ios_base
{
public:
    locale getloc() const;
};

template <class T> class char_traits {};

template <class T> class allocator {
public:
    allocator() {}
    ~allocator()
    {
        if (_STLP_LEAKS_CHECK)
            free(this);
    }
};

template <class CharT, class Traits, class Alloc> class basic_string {
public:
    basic_string(const CharT *, const Alloc & = Alloc());
    ~basic_string();
private:
    CharT *_M_start;
    CharT *_M_finish;
    CharT *_M_end_of_storage;
};

template <class CharT, class Traits> class basic_streambuf;
template <class CharT, class Traits> class ostreambuf_iterator {
private:
    basic_streambuf<CharT, Traits> *_M_buf;
    bool _M_ok;
};

template <class CharT, class OutputIter> class money_put : public locale::facet {
public:
    typedef basic_string<CharT, char_traits<CharT>, allocator<CharT> > string_type;
protected:
    virtual OutputIter do_put(OutputIter, bool, ios_base &, CharT, long double) const;
    virtual OutputIter do_put(OutputIter, bool, ios_base &, CharT, const string_type &) const;
};

template <class CharT, class OutputIter>
OutputIter money_put<CharT, OutputIter>::do_put(OutputIter s, bool intl,
        ios_base &str, CharT fill, long double) const
{
    locale loc = str.getloc();
    CharT buf[64];
    return do_put(s, intl, str, fill, buf + 0);
}
template ostreambuf_iterator<unsigned short, char_traits<unsigned short> >
money_put<unsigned short, ostreambuf_iterator<unsigned short, char_traits<unsigned short> > >::do_put(
    ostreambuf_iterator<unsigned short, char_traits<unsigned short> >,
    bool, ios_base &, unsigned short, long double) const;
}
