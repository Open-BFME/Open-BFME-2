// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<wchar_t> default constructor, the wide twin of
// 0x00007850. Same body, two bytes longer: BFME's allocator takes bytes rather
// than elements, so the proxy has to double the count and that is the
// `lea eax,[eax+eax]` retail runs before the call.

namespace _STL
{

template <class T>
class char_traits {};

template <class T>
class allocator
{
public:
	typedef unsigned int size_type;

	static T *__cdecl allocate(size_type count, const void *hint = 0);
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	__declspec(dllimport) __forceinline _STLP_alloc_proxy(const Alloc &,
			Pointer data)
		: _M_data(data)
	{
	}

	__declspec(dllimport) __forceinline Pointer allocate(unsigned int count)
	{
		return Alloc::allocate(count * sizeof(Value), 0);
	}

	Pointer _M_data;
};

template <class CharT, class Alloc>
class _String_base
{
public:
	typedef unsigned int size_type;

	__declspec(dllimport) __forceinline _String_base(const Alloc &alloc)
		: _M_start(0), _M_finish(0), _M_end_of_storage(alloc, 0)
	{
	}

	__declspec(dllimport) __forceinline ~_String_base()
	{
		_M_deallocate_block();
	}

	void _M_deallocate_block();

	__declspec(dllimport) __forceinline size_type max_size() const
	{
		return (size_type(-1) / sizeof(CharT)) - 1;
	}

	__declspec(dllimport) __forceinline void _M_allocate_block(size_type count)
	{
		if (count <= max_size() + 1 && count > 0)
		{
			_M_start = _M_end_of_storage.allocate(count);
			_M_finish = _M_start;
			_M_end_of_storage._M_data = _M_start + count;
		}
	}

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
class basic_string : public _String_base<CharT, Alloc>
{
public:
	typedef unsigned int size_type;

	basic_string();

private:
	__declspec(dllimport) __forceinline void _M_terminate_string()
	{
		*this->_M_finish = CharT();
	}
};

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc>::basic_string()
	: _String_base<CharT, Alloc>(Alloc())
{
	this->_M_allocate_block(8);
	_M_terminate_string();
}

template class basic_string<unsigned short, char_traits<unsigned short>,
		allocator<unsigned short> >;

}
