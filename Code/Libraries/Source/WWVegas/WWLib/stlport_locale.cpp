// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 locale handle members. The class is a refcounted handle onto
// one _Locale_impl: every copy takes a reference through the impl's virtual
// _M_incr and every release drops one through _M_decr.

namespace _STL
{

class _Locale_impl;

class locale
{
public:
    class facet {};

    class id
    {
    public:
        unsigned int _M_index;
    };

    locale();
    locale(const locale &that);
    ~locale();
    locale &operator=(const locale &that);
    facet *_M_use_facet(const id &index) const;

private:
    _Locale_impl *_M_impl;
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

__declspec(dllimport) __forceinline _Locale_impl *_M_add_ref(_Locale_impl *impl)
{
    impl->_M_incr();
    return impl;
}

locale::locale()
{
    _M_impl = 0;
    _M_impl = _M_add_ref(_Stl_classic_locale_impl);
}

locale::locale(const locale &that)
{
    _M_impl = 0;

    _Locale_impl *impl = that._M_impl;
    impl->_M_incr();
    _M_impl = impl;
}

locale::~locale()
{
    _M_impl->_M_decr();
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

locale::facet *locale::_M_use_facet(const id &index) const
{
    if (index._M_index < _M_impl->_M_count)
        return _M_impl->_M_facets[index._M_index];

    return 0;
}

}
