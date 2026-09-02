// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<wchar_t>::basic_string(const wchar_t *, const
// allocator &) - the wide twin of 0x00009100, and ten bytes shorter for two
// reasons. There is no wcslen intrinsic, so char_traits::length stays the
// inline scan `while (s[n]) ++n` retail carries; and the range initialiser it
// reaches is the THREE-argument overload at 0x0000BF90, with the iterator tag
// passed as a named local so MSVC 7.1 hands over the address of the dead `s`
// parameter slot rather than zeroing a fresh temporary.

namespace _STL
{

typedef unsigned int size_t;


template <class T>
class char_traits {};

template <>
class char_traits<unsigned short>
{
public:
	static size_t __cdecl length(const unsigned short *s)
	{
		size_t n = 0;
		while (s[n] != 0)
		{
			++n;
		}
		return n;
	}
};

struct forward_iterator_tag {};

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
	void _M_range_initialize(InputIter first, InputIter last, const forward_iterator_tag &);

	template <class InputIter>
	void _M_range_initialize(InputIter first, InputIter last)
	{
		forward_iterator_tag tag;
		_M_range_initialize(first, last, tag);
	}
};

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc>::basic_string(const CharT *s,
		const allocator_type &a)
	: _String_base<CharT, Alloc>(a)
{
	_M_range_initialize(s, s + Traits::length(s));
}

template basic_string<unsigned short, char_traits<unsigned short>,
		allocator<unsigned short> >::basic_string(
		const unsigned short *, const allocator<unsigned short> &);

}
