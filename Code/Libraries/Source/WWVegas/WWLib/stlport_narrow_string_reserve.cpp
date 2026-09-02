// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<char>::reserve. The capacity test is against
// _M_end_of_storage._M_data - _M_start - 1, the null terminator's slot is
// written by hand after the copy, and the old block is released through the
// inlined _M_deallocate_block rather than a call.
//
// The proxy's allocate keeps its `count != 0` guard: that is the `je` retail
// takes to a zero pointer when the requested size wraps, and without it the
// allocation is unconditional and the body is four bytes short.

extern "C" __declspec(dllimport) void *__cdecl memmove(void *destination,
		const void *source, unsigned int count);
extern "C" void __cdecl free(void *block);

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
		return count != 0 ? Alloc::allocate(count * sizeof(Value), 0) : 0;
	}

	void deallocate(Pointer block, unsigned int)
	{
		if (block != 0)
			free(block);
	}

	Pointer _M_data;
};

__declspec(dllimport) __forceinline void *__copy_trivial(
		const void *first, const void *last, void *result)
{
	return last == first
			? result
			: static_cast<char *>(memmove(result, first,
					static_cast<unsigned int>(static_cast<const char *>(last) -
							static_cast<const char *>(first)))) +
					(static_cast<const char *>(last) -
							static_cast<const char *>(first));
}

__declspec(dllimport) __forceinline char *uninitialized_copy(
		char *first, char *last, char *result)
{
	return static_cast<char *>(__copy_trivial(first, last, result));
}

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef unsigned int size_type;
	typedef CharT *pointer;

	void reserve(size_type count);

private:
	__declspec(dllimport) __forceinline size_type capacity() const
	{
		return static_cast<size_type>(_M_end_of_storage._M_data - _M_start) - 1;
	}

	__declspec(dllimport) __forceinline void _M_construct_null(pointer p)
	{
		*p = CharT();
	}

	__declspec(dllimport) __forceinline void _M_deallocate_block()
	{
		_M_end_of_storage.deallocate(_M_start,
				static_cast<size_type>(_M_end_of_storage._M_data - _M_start));
	}

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
void basic_string<CharT, Traits, Alloc>::reserve(size_type count)
{
	if (count >= capacity())
	{
		size_type n = count + 1;
		pointer new_start = _M_end_of_storage.allocate(n);
		pointer new_finish = uninitialized_copy(_M_start, _M_finish, new_start);

		_M_construct_null(new_finish);
		_M_deallocate_block();
		_M_start = new_start;
		_M_end_of_storage._M_data = new_start + n;
		_M_finish = new_finish;
	}
}

template void
basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int);

}
