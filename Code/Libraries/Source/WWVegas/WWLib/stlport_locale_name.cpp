// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 locale::name, 34 bytes: the impl carries the name string at
// offset 0x0C, right behind the vptr, the facet table and the facet count
// locale::_M_use_facet reads, and name() hands the caller a copy of it through
// the string copy constructor at 0x00009170.
//
// The string needs its destructor DECLARED even though nothing here calls it:
// that is what makes MSVC 7.1 add the four-byte return-value flag retail
// clears with `mov [esp+8], 0` before the copy, and without it the body is six
// bytes short.

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
	basic_string(const basic_string<CharT, Traits, Alloc> &that);
	~basic_string();

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

class _Locale_impl;

class locale
{
public:
	class facet {};

	string name() const;

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
	string _M_name;
};

string locale::name() const
{
	return _M_impl->_M_name;
}

}
