// cl: /GX- /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<char>::_M_range_initialize for a forward-iterator
// range, the body every string built from a (first, last) pair runs. The
// constructor that calls it zeroes the three members first, so this body only
// allocates, copies and terminates. _M_allocate_block is inlined here with the
// upstream `(n <= max_size() + 1) && (n > 0)` guard; its length-error else arm
// leaves no code because the retail library is built without exceptions.

extern "C" __declspec(dllimport) void *__cdecl memmove(void *destination,
		const void *source, unsigned int count);

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
	__declspec(dllimport) __forceinline Pointer allocate(unsigned int count)
	{
		return Alloc::allocate(count, 0);
	}

	Pointer _M_data;
};

struct forward_iterator_tag {};

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
		const char *first, const char *last, char *result)
{
	return static_cast<char *>(__copy_trivial(first, last, result));
}

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef unsigned int size_type;

	template <class ForwardIter>
	void _M_range_initialize(ForwardIter first, ForwardIter last,
			const forward_iterator_tag &);

private:
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

	__declspec(dllimport) __forceinline void _M_terminate_string()
	{
		*_M_finish = CharT();
	}

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
template <class ForwardIter>
void basic_string<CharT, Traits, Alloc>::_M_range_initialize(
		ForwardIter first, ForwardIter last, const forward_iterator_tag &)
{
	int count = static_cast<int>(last - first);

	_M_allocate_block(count + 1);
	_M_finish = uninitialized_copy(first, last, _M_start);
	_M_terminate_string();
}

template void
basic_string<char, char_traits<char>, allocator<char> >::_M_range_initialize<
		const char *>(const char *, const char *, const forward_iterator_tag &);

}
