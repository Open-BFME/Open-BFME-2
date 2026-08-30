// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<char>::insert(iterator, char). Appending at the
// end is the cheap path the retail body inlines around push_back; everything
// else defers to the external _M_insert_aux.

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
	typedef CharT *iterator;

	iterator end() { return _M_finish; }
	void push_back(CharT value);
	iterator insert(iterator position, CharT value);

private:
	iterator _M_insert_aux(iterator position, CharT value);

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
typename basic_string<CharT, Traits, Alloc>::iterator
basic_string<CharT, Traits, Alloc>::insert(iterator position, CharT value)
{
	if (position == end())
	{
		push_back(value);
		return end() - 1;
	}
	else
		return _M_insert_aux(position, value);
}

template basic_string<char, char_traits<char>, allocator<char> >::iterator
basic_string<char, char_traits<char>, allocator<char> >::insert(char *, char);

}
