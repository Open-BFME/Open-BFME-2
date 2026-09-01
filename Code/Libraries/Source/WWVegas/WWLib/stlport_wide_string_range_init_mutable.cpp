// cl: -GX- -MD -D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<wchar_t>::_M_range_initialize over a MUTABLE
// wchar_t* range. The const-iterator instantiation is the 53-byte body at
// 0x0000BF90; this one is 84 bytes because its unit inlined _M_allocate_block -
// the 0x7FFFFFFF guard and the `lea edi,[eax+eax]` are folded straight in -
// while still calling __copy_trivial out of line.

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

struct forward_iterator_tag {};

void *__cdecl __copy_trivial(const void *first, const void *last, void *result);

__declspec(dllimport) __forceinline unsigned short *uninitialized_copy(
		const unsigned short *first, const unsigned short *last, unsigned short *result)
{
	return static_cast<unsigned short *>(__copy_trivial(first, last, result));
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
	__declspec(dllimport) __forceinline void _M_terminate_string()
	{
		*_M_finish = CharT();
	}

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
basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::
		_M_range_initialize<unsigned short *>(
				unsigned short *, unsigned short *, const forward_iterator_tag &);

}
