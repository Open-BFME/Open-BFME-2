// cl: -GX- -MD -D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<wchar_t>::_M_range_initialize for a
// forward-iterator range - the wide twin of the narrow body at 0x000078C0.
// It is 53 bytes against the narrow one's 84 because retail keeps both
// _M_allocate_block and __copy_trivial out of line here, so they are
// declarations only; uninitialized_copy and _M_terminate_string still fold in,
// which is the `mov [esi+4],eax` / `mov word ptr [eax],0` pair at the end.

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
	void _M_allocate_block(size_type count);

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
basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::
		_M_range_initialize<const unsigned short *>(
				const unsigned short *, const unsigned short *, const forward_iterator_tag &);

}
