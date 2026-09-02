// ??$append@PBD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAEAAV01@PBD0ABUforward_iterator_tag@1@@Z
// partial score=0.95 date=2026-09-02
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<char>::append over a forward-iterator range -
// the narrow twin of 0x00013160. The upstream shape from
// vendor/stlport/stl/_string.c: an empty range returns straight away, a range
// that fits copies all but the first element past the terminator, writes the
// new terminator and only then assigns the first element over the old one, and
// a range that does not fit reallocates through two __copy_trivial calls.
//
// __copy_trivial is DEFINED here, the opposite of the wide unit: retail folds
// the memmove into all three sites rather than calling 0x000179B0.
//
// max returns a REFERENCE, which is what the pair of `lea ecx, [esp+...]` and
// the load through ecx are - the growth term is selected by address, not by
// value.
//
// Two shapes in the test itself, both worth eight bytes each:
//
//   * the REALLOCATING arm is the `if` and the in-place arm the `else`.
//     Written the upstream way round MSVC 7.1 lays the in-place code inline
//     and jumps away to the reallocation, which is the opposite of retail.
//   * the element count is HOISTED above the test here - the opposite of the
//     wide twin, which needs it scoped inside each arm. Scoped, this body
//     comes out with 235 of its 254 bytes differing; hoisted, 108. Same
//     template, same two arms, opposite preference.
//
// STILL OPEN: register allocation. The length is exactly right and so is the
// instruction sequence, but retail keeps `first` in ebp and `last` in ecx,
// pushing ebp before esi, where MSVC 7.1 puts `first` in edx and `last` in
// edi. /G6, /G7, /Ox and reversing the emptiness test change nothing.

extern "C" __declspec(dllimport) void *__cdecl memmove(void *destination,
		const void *source, unsigned int count);
extern "C" void __cdecl free(void *block);

namespace _STL
{

typedef unsigned int size_t;

template <class T>
inline const T &(max)(const T &a, const T &b)
{
	return a < b ? b : a;
}

__declspec(dllimport) __forceinline void *__copy_trivial(
		const void *first, const void *last, void *result)
{
	return last == first
			? result
			: (void *)((char *)memmove(result, first,
					(unsigned int)((const char *)last - (const char *)first)) +
					((const char *)last - (const char *)first));
}

inline char *uninitialized_copy(const char *first, const char *last, char *result)
{
	return (char *)__copy_trivial(first, last, result);
}

struct forward_iterator_tag {};

template <class T>
class char_traits {};

template <>
class char_traits<char>
{
public:
	static void assign(char &c1, const char &c2) { c1 = c2; }
};

template <class T>
class allocator
{
public:
	static T *__cdecl allocate(size_t bytes, const void *hint);
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

	template <class ForwardIter>
	basic_string<CharT, Traits, Alloc> &append(ForwardIter first, ForwardIter last)
	{
		forward_iterator_tag tag;
		return append(first, last, tag);
	}

private:
	template <class ForwardIter>
	basic_string<CharT, Traits, Alloc> &append(ForwardIter first, ForwardIter last,
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
basic_string<CharT, Traits, Alloc>::append(ForwardIter __first, ForwardIter __last,
		const forward_iterator_tag &)
{
	if (__first != __last) {
		const size_type __old_size = size();
		const size_type __n = (size_type)(__last - __first);
		if (__n + __old_size > capacity()) {
			const size_type __len = __old_size + (max)(__old_size, __n) + 1;
			pointer __new_start = _M_end_of_storage.allocate(__len);
			pointer __new_finish = uninitialized_copy(_M_start, _M_finish, __new_start);

			__new_finish = uninitialized_copy(__first, __last, __new_finish);
			_M_construct_null(__new_finish);
			_M_deallocate_block();
			_M_start = __new_start;
			_M_finish = __new_finish;
			_M_end_of_storage._M_data = __new_start + __len;
		}
		else {
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

template basic_string<char, char_traits<char>, allocator<char> > &
basic_string<char, char_traits<char>, allocator<char> >::append<const char *>(
		const char *, const char *);

}
