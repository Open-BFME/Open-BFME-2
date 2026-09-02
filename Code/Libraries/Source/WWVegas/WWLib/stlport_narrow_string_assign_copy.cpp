// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<char>::assign over another string, 41 bytes:
// self-assignment is the early out, and everything else is handed to the
// _M_assign_dispatch at 0x000120F0 as a raw pointer range.
//
// The dispatch tag has to be a VALUE-initialised temporary here, the opposite
// of what the iterator tag inside _M_assign_dispatch needs: `__false_type()`
// is what makes MSVC 7.1 clear the scratch byte at [esp+0x14] before the call,
// and a plain named local leaves the body five bytes short.

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

struct __false_type {};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	basic_string<CharT, Traits, Alloc> &assign(
			const basic_string<CharT, Traits, Alloc> &that);

	template <class InputIter>
	basic_string<CharT, Traits, Alloc> &_M_assign_dispatch(InputIter first,
			InputIter last, const __false_type &);

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc> &
basic_string<CharT, Traits, Alloc>::assign(
		const basic_string<CharT, Traits, Alloc> &that)
{
	if (&that != this)
	{
		_M_assign_dispatch(that._M_start, that._M_finish, __false_type());
	}
	return *this;
}

template basic_string<char, char_traits<char>, allocator<char> > &
basic_string<char, char_traits<char>, allocator<char> >::assign(
		const basic_string<char, char_traits<char>, allocator<char> > &);

}
