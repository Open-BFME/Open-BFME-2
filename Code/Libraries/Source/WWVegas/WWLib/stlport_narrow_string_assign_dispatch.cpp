// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<char>::_M_assign_dispatch over a char* range:
// copy into the existing buffer while both ranges last, then erase the tail if
// the source ran out first or append the remainder if it did not.
//
// erase and the three-argument append are DECLARATIONS here. Beside their
// definitions MSVC 7.1 folds erase in and the body grows from 96 bytes to 105;
// retail calls both, erase at 0x00012150 and append at 0x0001B3E0.
//
// The iterator tag has to be a DEFAULT-initialised named local, not a
// value-initialised temporary: `forward_iterator_tag()` makes MSVC zero the
// empty object before the call, five bytes retail does not spend, while a
// plain `forward_iterator_tag tag;` leaves the scratch slot untouched exactly
// as retail does.

namespace _STL
{

template <class T>
class char_traits
{
public:
	static void assign(T &c1, const T &c2) { c1 = c2; }
};

template <class T>
class allocator {};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;
};

struct __false_type {};

struct forward_iterator_tag {};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef CharT *pointer;
	typedef CharT *iterator;

	iterator end() { return _M_finish; }
	iterator erase(iterator first, iterator last);

	// The public two-argument append folds in and the private three-argument
	// one is the call retail makes, with the iterator tag passed by reference
	// off the stack.
	template <class InputIter>
	basic_string<CharT, Traits, Alloc> &append(InputIter first, InputIter last)
	{
		forward_iterator_tag tag;
		return append(first, last, tag);
	}


	template <class InputIter>
	basic_string<CharT, Traits, Alloc> &_M_assign_dispatch(InputIter first, InputIter last,
			const __false_type &);

private:
	template <class InputIter>
	basic_string<CharT, Traits, Alloc> &append(InputIter first, InputIter last,
			const forward_iterator_tag &);

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
template <class InputIter>
basic_string<CharT, Traits, Alloc> &
basic_string<CharT, Traits, Alloc>::_M_assign_dispatch(InputIter __f, InputIter __l,
		const __false_type &)
{
	pointer __cur = _M_start;
	while (__f != __l && __cur != _M_finish) {
		Traits::assign(*__cur, *__f);
		++__f;
		++__cur;
	}
	if (__f == __l)
		erase(__cur, end());
	else
		append(__f, __l);
	return *this;
}

template basic_string<char, char_traits<char>, allocator<char> > &
basic_string<char, char_traits<char>, allocator<char> >::_M_assign_dispatch<char *>(
		char *, char *, const __false_type &);

}
