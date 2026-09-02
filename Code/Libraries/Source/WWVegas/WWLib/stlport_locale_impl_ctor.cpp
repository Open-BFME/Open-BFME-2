// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 _Locale_impl constructor from a locale name, 33 bytes: the
// vftable at 0x00BBBBB0 - the one whose slot 0 is the scalar deleting
// destructor at 0x0000B710 - and the name string at offset 0x0C, built by the
// two-argument constructor at 0x00009100.
//
// The allocator argument is the string constructor's own default, and the
// allocator needs a user-declared default constructor for it. Without one the
// temporary is VALUE-initialised: MSVC 7.1 allocates a fresh dword, clears a
// byte in it and pushes that, five bytes retail does not spend. Declared, the
// temporary costs nothing and lands in the dead `name` parameter slot - the
// `lea eax, [esp+8]` retail pushes.

namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator
{
public:
	allocator() {}
};

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
	typedef Alloc allocator_type;

	basic_string(const CharT *s, const allocator_type &a = allocator_type());
	~basic_string();

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

class locale
{
public:
	class facet {};
};

class _Locale_impl
{
public:
	_Locale_impl(const char *name);

	virtual ~_Locale_impl();
	virtual void _M_incr();
	virtual void _M_decr();

	locale::facet **_M_facets;
	unsigned int _M_count;
	string _M_name;
};

_Locale_impl::_Locale_impl(const char *name)
	: _M_name(name)
{
}

}
