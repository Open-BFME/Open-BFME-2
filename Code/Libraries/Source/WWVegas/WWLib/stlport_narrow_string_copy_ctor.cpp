// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<char> copy constructor. The _String_base
// constructor zeroes the three members, then the two-argument
// _M_range_initialize landed at 0x00008D00 does the allocation and copy - which
// is why the body is only 81 bytes despite the SEH frame the half-built string
// needs.

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
	__declspec(dllimport) __forceinline _STLP_alloc_proxy(const Alloc &, Pointer data)
		: _M_data(data)
	{
	}

	Pointer _M_data;
};

struct forward_iterator_tag {};

template <class CharT, class Alloc>
class _String_base
{
public:
	__declspec(dllimport) __forceinline _String_base(const Alloc &alloc)
		: _M_start(0), _M_finish(0), _M_end_of_storage(alloc, 0)
	{
	}

	__declspec(dllimport) __forceinline ~_String_base()
	{
		_M_deallocate_block();
	}

	void _M_deallocate_block();

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : public _String_base<CharT, Alloc>
{
public:
	basic_string(const basic_string<CharT, Traits, Alloc> &that);

	template <class InputIter>
	void _M_range_initialize(InputIter first, InputIter last);
};

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc>::basic_string(
		const basic_string<CharT, Traits, Alloc> &that)
	: _String_base<CharT, Alloc>(Alloc())
{
	_M_range_initialize(that._M_start, that._M_finish);
}

template class basic_string<char, char_traits<char>, allocator<char> >;

}
