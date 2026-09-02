// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<char>::basic_string(const char *, const
// allocator &) - the two-argument constructor, hence `ret 8`. The base zeroes
// the three pointers, char_traits::length is the inline scan retail carries
// rather than a call, and the range initialiser at 0x00008D00 does the rest.

namespace _STL
{

typedef unsigned int size_t;

}

extern "C" size_t __cdecl strlen(const char *s);
#pragma intrinsic(strlen)

namespace _STL
{

template <class T>
class char_traits {};

template <>
class char_traits<char>
{
public:
	static size_t __cdecl length(const char *s) { return strlen(s); }
};

template <class T>
class allocator {};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	_STLP_alloc_proxy(const Alloc &a, Pointer data) : Alloc(a), _M_data(data) {}

	Pointer _M_data;
};

template <class CharT, class Alloc>
class _String_base
{
public:
	_String_base(const Alloc &a) : _M_start(0), _M_finish(0), _M_end_of_storage(a, 0) {}
	~_String_base();

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : public _String_base<CharT, Alloc>
{
public:
	typedef Alloc allocator_type;

	basic_string(const CharT *s, const allocator_type &a = allocator_type());

	template <class InputIter>
	void _M_range_initialize(InputIter first, InputIter last);
};

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc>::basic_string(const CharT *s,
		const allocator_type &a)
	: _String_base<CharT, Alloc>(a)
{
	_M_range_initialize(s, s + Traits::length(s));
}

template basic_string<char, char_traits<char>, allocator<char> >::basic_string(
		const char *, const allocator<char> &);

}
