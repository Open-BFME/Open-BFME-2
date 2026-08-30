// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<char>::push_back. These TU-scoped declarations
// retain the upstream class layout while leaving reserve as the external member
// used by the retail library body.

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
	typedef unsigned int size_type;
	void reserve(size_type amount);
	void push_back(CharT value);

private:
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
void basic_string<CharT, Traits, Alloc>::push_back(CharT value)
{
	if (_M_finish + 1 == _M_end_of_storage._M_data)
	{
		size_type one = 1;
		size_type currentSize = static_cast<size_type>(_M_finish - _M_start);
		const size_type &growth = currentSize < one ? one : currentSize;
		reserve(currentSize + growth);
	}
	*(_M_finish + 1) = CharT();
	*_M_finish = value;
	++_M_finish;
}

template void basic_string<char, char_traits<char>, allocator<char> >::push_back(char);

}
