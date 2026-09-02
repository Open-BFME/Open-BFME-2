// cl: -GX- -MD -D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<char>::_M_allocate_block, the narrow twin of
// 0x0000BFD0. Its own unit for the same reason: beside a definition that calls
// it MSVC 7.1 folds it in and that body stops matching.
//
// BFME replaced STLport's allocator with a raw byte allocator, so the proxy
// does the sizeof multiply itself - for char that multiply is by one and
// disappears, which is the whole difference from the wide twin. The guard is
// the upstream `(count <= max_size() + 1) && (count > 0)`, and for char
// max_size() + 1 is 0xFFFFFFFF, the constant retail compares against.

namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator
{
public:
	typedef unsigned int size_type;

	static T *__cdecl allocate(size_type bytes, const void *hint = 0);
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	__declspec(dllimport) __forceinline Pointer allocate(unsigned int count)
	{
		return Alloc::allocate(count * sizeof(Value), 0);
	}

	Pointer _M_data;
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef unsigned int size_type;

private:
	void _M_allocate_block(size_type count);

	__declspec(dllimport) __forceinline size_type max_size() const
	{
		return (size_type(-1) / sizeof(CharT)) - 1;
	}

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
void basic_string<CharT, Traits, Alloc>::_M_allocate_block(size_type count)
{
	if (count <= max_size() + 1 && count > 0)
	{
		_M_start = _M_end_of_storage.allocate(count);
		_M_finish = _M_start;
		_M_end_of_storage._M_data = _M_start + count;
	}
}

template void
basic_string<char, char_traits<char>, allocator<char> >::_M_allocate_block(unsigned int);

}
