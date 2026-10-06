// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??$rva001EF83A@PBG@?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@AAEAAV01@PBG0ABUforward_iterator_tag@1@@Z @0x001EF83A 212B.
// Wide-string 3-arg append (forward_iterator_tag) for /O1 TUs (PeerThread).
// Model is stlport_wide_string_append.cpp (0x00013160 241B, /EHsc, byte allocator
// via proxy); retail here uses /O1 (EBP frame) and calls the const-thiscall wide
// allocator directly with count (no proxy multiply, no null check), matching the
// push-0/push-len/mov-ecx shape at 0x001EF885.
// Callers 0x001EFC42/0x001EFC58/0x001EFC6E (assign family) all reach here;
// callees 0x00017710 (wide allocate), 0x000179B0 (__copy_trivial x3), 0x00030830
// (free) are rowed. Honest Rva method name (real class + real PBG signature)
// because the real append name already rows a different 241B body at 0x00013160
// and pin_consistency forbids same name different bodies; follow retail.

extern "C" void __cdecl free(void *block);

namespace _STL
{

typedef unsigned int size_t;

template <class T>
inline const T &(max)(const T &a, const T &b)
{
	return a < b ? b : a;
}

void *__cdecl __copy_trivial(const void *first, const void *last, void *result);

inline unsigned short *uninitialized_copy(const unsigned short *first,
		const unsigned short *last, unsigned short *result)
{
	return (unsigned short *)__copy_trivial(first, last, result);
}

struct forward_iterator_tag {};

template <class _Tp1, class _Tp2>
struct __char_traits_base
{
	static _Tp1 *copy(_Tp1 *dst, const _Tp2 *src, unsigned int n);
};

template <class T>
class char_traits {};

template <>
class char_traits<unsigned short>
{
public:
	static void assign(unsigned short &c1, const unsigned short &c2) { c1 = c2; }
};

template <class T>
class allocator
{
public:
	T *allocate(size_t count, const void *hint) const;
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Value *allocate(size_t count)
	{
		return count != 0 ? Alloc::allocate(count * sizeof(Value), 0) : 0;
	}

	void deallocate(Value *block, size_t)
	{
		if (block != 0)
			free(block);
	}

	Pointer _M_data;
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	typedef CharT *pointer;
	typedef CharT *iterator;
	typedef unsigned int size_type;

	size_type size() const { return (size_type)(_M_finish - _M_start); }
	size_type capacity() const
	{
		return (size_type)(_M_end_of_storage._M_data - _M_start) - 1;
	}
	iterator end() { return _M_finish; }

	iterator erase(iterator first, iterator last);

	template <class ForwardIter>
	basic_string<CharT, Traits, Alloc> &append(ForwardIter first, ForwardIter last)
	{
		forward_iterator_tag tag;
		return append(first, last, tag);
	}

	template <class ForwardIter>
	basic_string<CharT, Traits, Alloc> &rva001EF83A(ForwardIter first, ForwardIter last)
	{
		forward_iterator_tag tag;
		return rva001EF83A(first, last, tag);
	}

	basic_string<CharT, Traits, Alloc> &assign(const CharT *first, const CharT *last);

private:
	template <class ForwardIter>
	basic_string<CharT, Traits, Alloc> &append(ForwardIter first, ForwardIter last,
			const forward_iterator_tag &);

	template <class ForwardIter>
	basic_string<CharT, Traits, Alloc> &rva001EF83A(ForwardIter first, ForwardIter last,
			const forward_iterator_tag &);

	void _M_construct_null(pointer p) { *p = CharT(); }
	void _M_deallocate_block()
	{
		_M_end_of_storage.deallocate(_M_start,
				(size_type)(_M_end_of_storage._M_data - _M_start));
	}

	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};

template <class CharT, class Traits, class Alloc>
template <class ForwardIter>
basic_string<CharT, Traits, Alloc> &
basic_string<CharT, Traits, Alloc>::rva001EF83A(ForwardIter __first, ForwardIter __last,
		const forward_iterator_tag &)
{
	if (__first != __last) {
		const size_type __old_size = size();
		if ((size_type)(__last - __first) + __old_size > capacity()) {
			const size_type __n = (size_type)(__last - __first);
			const size_type __len = __old_size + (max)(__old_size, __n) + 1;
			pointer __new_start = ((const Alloc &)_M_end_of_storage).allocate(__len, 0);
			pointer __new_finish = uninitialized_copy(_M_start, _M_finish, __new_start);

			__new_finish = uninitialized_copy(__first, __last, __new_finish);
			_M_construct_null(__new_finish);
			_M_deallocate_block();
			_M_start = __new_start;
			_M_finish = __new_finish;
			_M_end_of_storage._M_data = __new_start + __len;
		}
		else {
			const size_type __n = (size_type)(__last - __first);
			ForwardIter __f1 = __first;
			++__f1;
			uninitialized_copy(__f1, __last, _M_finish + 1);
			_M_construct_null(_M_finish + __n);
			Traits::assign(*end(), *__first);
			_M_finish += __n;
		}
	}

	return *this;
}

template <class CharT, class Traits, class Alloc>
basic_string<CharT, Traits, Alloc> &
basic_string<CharT, Traits, Alloc>::assign(const CharT *__f, const CharT *__l)
{
	int __n = (int)(__l - __f);
	if ((size_type)__n <= size()) {
		__char_traits_base<CharT, CharT>::copy(_M_start, __f, (size_type)__n);
		erase(_M_start + __n, _M_finish);
	}
	else {
		__char_traits_base<CharT, CharT>::copy(_M_start, __f, size());
		forward_iterator_tag tag;
		rva001EF83A(__f + size(), __l, tag);
	}
	return *this;
}

template basic_string<unsigned short, char_traits<unsigned short>,
		allocator<unsigned short> > &
basic_string<unsigned short, char_traits<unsigned short>,
		allocator<unsigned short> >::rva001EF83A<const unsigned short *>(
		const unsigned short *, const unsigned short *);

template basic_string<unsigned short, char_traits<unsigned short>,
		allocator<unsigned short> > &
basic_string<unsigned short, char_traits<unsigned short>,
		allocator<unsigned short> >::assign(
		const unsigned short *, const unsigned short *);

}
