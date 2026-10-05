// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 basic_string<char>::append over a forward-iterator range -
// the narrow twin of the wide append at 0x00013160. Upstream shape from
// vendor/stlport/stl/_string.c, following reference/open-bfme-1's
// stlport_wide_string_append.cpp donor (f/l local copies, hoisted
// difference_type count, max selected by address): an empty range returns
// straight away, a range that fits copies all but the first element past the
// terminator, writes the new terminator and only then assigns the first
// element over the old one, and a range that does not fit reallocates through
// two __copy_trivial calls.
//
// __copy_trivial is DEFINED here, the opposite of the wide unit: retail folds
// the memmove into all three sites rather than calling 0x000179B0.
//
// max returns a REFERENCE, which is what the pair of `lea ecx, [esp+...]` and
// the load through ecx are - the growth term is selected by address, not by
// value.
//
// The REALLOCATING arm is the `if` and the in-place arm the `else`. Written
// the upstream way round MSVC 7.1 lays the in-place code inline and jumps away
// to the reallocation, which is the opposite of retail. The element count is
// HOISTED above the test here - the opposite of the wide twin, which needs it
// scoped inside each arm.

extern "C" __declspec(dllimport) void *__cdecl memmove(void *destination,
		const void *source, unsigned int count);
extern "C" void __cdecl free(void *block);

namespace _STL
{

typedef unsigned int size_t;
typedef int difference_type;

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

inline void *__copy_trivial(const void *first, const void *last, void *result)
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
	const CharT *__f = __first;
	const CharT *__l = __last;
	if (__f != __l) {
		const size_type __old_size = size();
		difference_type __n = __l - __f;
		if ((size_type)__n + __old_size > capacity()) {
			size_type __n_sz = (size_type)__n;
			size_type __mx = *(__old_size < __n_sz ? &__n_sz : &__old_size);
			const size_type __len = __old_size + __mx + 1;
			pointer __new_start = _M_end_of_storage.allocate(__len);
			pointer __new_finish = uninitialized_copy(_M_start, _M_finish, __new_start);

			__new_finish = uninitialized_copy(__f, __l, __new_finish);
			_M_construct_null(__new_finish);
			_M_deallocate_block();
			_M_start = __new_start;
			_M_finish = __new_finish;
			_M_end_of_storage._M_data = __new_start + __len;
		}
		else {
			ForwardIter __f1 = __f;
			++__f1;
			uninitialized_copy(__f1, __l, _M_finish + 1);
			_M_construct_null(_M_finish + __n);
			Traits::assign(*end(), *__f);
			_M_finish += __n;
		}
	}

	return *this;
}

template basic_string<char, char_traits<char>, allocator<char> > &
basic_string<char, char_traits<char>, allocator<char> >::append<const char *>(
		const char *, const char *);

}
