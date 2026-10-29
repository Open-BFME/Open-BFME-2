// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// STLport 4.5.3 locale handle members. The class is a refcounted handle onto
// one _Locale_impl: every copy takes a reference through the impl's virtual
// _M_incr and every release drops one through _M_decr.

namespace _STL
{

class _Locale_impl;

// Reconstruction-only tag for the loader-initialized classic handle.
struct ClassicLocaleStorageTag {};
template <class T> union _Stl_aligned_buffer;
extern "C" _Stl_aligned_buffer<_Locale_impl> _S_classic_locale;

class locale
{
public:
    class facet {};

    class id
    {
    public:
        unsigned int _M_index;
    };

    // ?classicHandleStorageInitializer absent-from-retail
    locale(_Locale_impl *impl, ClassicLocaleStorageTag) : _M_impl(impl) {}

    locale();
    locale(const locale &that);
    ~locale();
    locale &operator=(const locale &that);
    facet *_M_get_facet(const id &index) const;
    facet *_M_use_facet(const id &index) const;
    static const locale &classic();

private:
    _Locale_impl *_M_impl;
};

class ios_base
{
public:
    typedef int fmtflags;
    typedef int iostate;
    typedef int openmode;
    typedef int seekdir;
    typedef int streamsize;

    virtual ~ios_base();
    locale getloc() const;

private:
    fmtflags _M_fmtflags;
    iostate _M_iostate;
    openmode _M_openmode;
    seekdir _M_seekdir;
    iostate _M_exception_mask;
    streamsize _M_precision;
    streamsize _M_width;
    locale _M_locale;
};

class _Locale_impl
{
public:
    virtual ~_Locale_impl();
    virtual void _M_incr();
    virtual void _M_decr();

    locale::facet **_M_facets;
    unsigned int _M_count;
};

extern _Locale_impl *_Stl_classic_locale_impl;
// Retail DA6214 contains DDE118 before initialization runs. No reference
// is acquired here: make_classic_locale later constructs that static storage.
locale _Stl_loc_classic_locale(
    reinterpret_cast<_Locale_impl *>(&_S_classic_locale), ClassicLocaleStorageTag());

__declspec(dllimport) __forceinline _Locale_impl *_M_add_ref(_Locale_impl *impl)
{
    impl->_M_incr();
    return impl;
}

inline locale::locale()
{
    _M_impl = 0;
    _M_impl = _M_add_ref(_Stl_classic_locale_impl);
}

inline locale::locale(const locale &that)
{
    _M_impl = 0;

    _Locale_impl *impl = that._M_impl;
    impl->_M_incr();
    _M_impl = impl;
}

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline locale::~locale()
{
    _M_impl->_M_decr();
}

// ?bfmeAnchorlocaleDtor absent-from-retail
void bfmeAnchorlocaleDtor(locale *p)
{
	p->locale::~locale();
}

locale &locale::operator=(const locale &that)
{
    _Locale_impl *impl = that._M_impl;
    if (_M_impl != impl)
    {
        _M_impl->_M_decr();
        impl = that._M_impl;
        impl->_M_incr();
        _M_impl = impl;
    }
    return *this;
}

// STLport 4.5.3 src/locale_impl.cpp: the non-throwing lookup. Built without
// exceptions, _M_use_facet's runtime_error path is gone and the two bodies are
// identical, so retail folds them at 0x00007190; basic_ios<char>::imbue at
// 0x00016110 calls it under this name.
locale::facet *locale::_M_get_facet(const id &index) const
{
    if (index._M_index < _M_impl->_M_count)
        return _M_impl->_M_facets[index._M_index];

    return 0;
}

locale::facet *locale::_M_use_facet(const id &index) const
{
    if (index._M_index < _M_impl->_M_count)
        return _M_impl->_M_facets[index._M_index];

    return 0;
}

// STLport 4.5.3 src/locale_impl.cpp: return the classic locale handle,
// distinct from the refcounted implementation pointer used by locale().
const locale &locale::classic()
{
    return _Stl_loc_classic_locale;
}


inline locale ios_base::getloc() const
{
    return _M_locale;
}

#pragma inline_depth(0)
// ?bfmeEmitStlportLocale@_STL@@YAXPAVlocale@1@PBV21@PBVios_base@1@@Z present-unmatched
void bfmeEmitStlportLocale(locale *p, const locale *q, const ios_base *b)
{
    p->locale::locale();
    p->locale::locale(*q);
    b->getloc();
}
#pragma inline_depth()

}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeLocaleCtor@BfmeLocaleShim@@SAXXZ=??0locale@_STL@@QAE@XZ")
