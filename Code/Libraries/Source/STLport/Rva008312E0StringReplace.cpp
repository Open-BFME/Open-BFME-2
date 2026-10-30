// cl: /Od /Ob1 /DNDEBUG /MD
// STLport 4.5.3 string range replace at BFME 2 RVA 0x0002AE50, including aliased ranges.
// The inline helpers are defined so /Ob1 reserves retail's frame slots, including those of calls it declines to inline.

#include <string.h>

namespace _STL
{
template <class CharT>
class char_traits;

template <>
class char_traits<char>
{
public:
	static void assign(char &destination, const char &source);
};

template <class _Tp>
class allocator;

template <>
class allocator<char>
{
public:
	static char *allocate(unsigned int __n, const void *);
};

void *__copy_trivial(const void *__first, const void *__last, void *__result);
// STLport's empty inline _Destroy(char *, char *), declined by /Ob1; retail calls the
// shared empty ret it folded onto, so it carries that address's placeholder name.
void Rva0069E440Destroy(char *, char *);

struct __true_type
{
};

// STLport 4.5.3's POD dispatch behind uninitialized_copy; /Ob1 declines the outer
// layer, so each copy stays a call (retail's lands on the folded __copy_trivial at
// 0x000179B0, whose address the outer template's placeholder name carries).
template <class _Tp1, class _Tp2>
struct _BothPtrType;

template <class _Tp1, class _Tp2>
struct _BothPtrType<_Tp1 *, _Tp2 *>
{
	static __true_type _Ret() { return __true_type(); }
};

template <class _Tp1, class _Tp2>
struct _OKToMemCpy
{
	typedef __true_type _Type;
	static _Type _Ret() { return _Type(); }
};

template <class _Tp1, class _Tp2>
inline _OKToMemCpy<_Tp1, _Tp2> _IsOKToMemCpy(_Tp1 *, _Tp2 *)
{
	return _OKToMemCpy<_Tp1, _Tp2>();
}

template <class _InputIter, class _OutputIter>
__forceinline _OutputIter __copy_ptrs(_InputIter __first, _InputIter __last, _OutputIter __result, __true_type)
{
	return (_OutputIter)__copy_trivial(__first, __last, __result);
}

template <class _InputIter, class _OutputIter>
__forceinline _OutputIter __copy_aux(_InputIter __first, _InputIter __last, _OutputIter __result, __true_type)
{
	return __copy_ptrs(__first, __last, __result, _IsOKToMemCpy((char *)0, (char *)0)._Ret());
}

template <class _InputIter, class _ForwardIter>
__forceinline _ForwardIter __uninitialized_copy(_InputIter __first, _InputIter __last, _ForwardIter __result, const __true_type &)
{
	return __copy_aux(__first, __last, __result, _BothPtrType<_InputIter, _ForwardIter>::_Ret());
}

template <class _InputIter, class _ForwardIter>
inline _ForwardIter Rva000179B0UninitializedCopy(_InputIter __first, _InputIter __last, _ForwardIter __result)
{
	return __uninitialized_copy(__first, __last, __result, __true_type());
}
}

extern "C" void free(void *);

struct Rva008312E0InputTag
{
};

struct Rva008312E0Tag : public Rva008312E0InputTag
{
};

struct Rva008312E0FalseType
{
};

// STLport returns the first reference on equality; the global max owner
// has different tie semantics, so retain the donor namespace here.
namespace _STL
{
template <class _Tp>
inline const _Tp &(max)(const _Tp &__a, const _Tp &__b)
{
	return __a < __b ? __b : __a;
}
}

template <class _RandomAccessIterator>
inline int __distance(const _RandomAccessIterator &__first,
	const _RandomAccessIterator &__last, const Rva008312E0Tag &)
{
	return __last - __first;
}

template <class _InputIterator>
inline int distance(const _InputIterator &__first, const _InputIterator &__last)
{
	return __distance(__first, __last, Rva008312E0Tag());
}

template <class _RandomAccessIterator, class _Distance>
inline void __advance(_RandomAccessIterator &__i, _Distance __n, const Rva008312E0Tag &)
{
	__i += __n;
}

template <class _InputIterator, class _Distance>
inline void advance(_InputIterator &__i, _Distance __n)
{
	__advance(__i, __n, Rva008312E0Tag());
}

// A TU-local view of STLport 4.5.3 basic_string<char>. Sharing its erase owner
// binds the range view to the rowed retail body at 0x00012150. The visible
// inline body preserves /Ob1 analysis and the matched caller's stack slots.
namespace _STL
{
template <class _CharT, class _Traits, class _Alloc>
class basic_string;

template <>
class basic_string<char, char_traits<char>, allocator<char> >
{
public:
	char *erase(char *__first, char *__last)
	{
		if (__first != __last)
		{
			move(__first, __last, (m_finish - __last) + 1);
			char *__new_finish = m_finish - (__last - __first);
			m_finish = __new_finish;
		}
		return __first;
	}

	static char *move(char *s1, const char *s2, size_t n)
	{
		return n == 0 ? s1 : (char *)memmove(s1, s2, n);
	}

	char *m_start;
	char *m_finish;
	char *m_end;
};
}

class Rva008312E0String : public _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
{
public:
	Rva008312E0String &bfmeReplaceAliasedRange(char *first, char *last,
		char *sourceFirst, char *sourceLast, const Rva008312E0Tag &tag);

	// Forward-iterator insert at retail 0x000284D0 (BFME 1 0x008300B0).
	void insertRange(char *position, char *first, char *last, const Rva008312E0Tag &tag);

	// Out of line in retail at 0x00830CC0: the plain forward-iterator replace.
	Rva008312E0String &replaceBase(char *__first, char *__last, char *__f,
		char *__l, const Rva008312E0Tag &)
	{
		int __n = distance(__f, __l);
		const int __len = __last - __first;
		if (__len >= __n)
		{
			copyRange(__f, __l, __first);
			erase(__first + __n, __last);
		}
		else
		{
			char *__m = __f;
			advance(__m, __len);
			copyRange(__f, __m, __first);
			insert(__last, __m, __l);
		}
		return *this;
	}

	char *begin() { return m_start; }
	bool inside(const char *s) const { const char *p = s; return p >= m_start && p < m_finish; }
	void copyRange(char *first, char *last, char *result)
	{
		for ( ; first != last; ++first, ++result)
			_STL::char_traits<char>::assign(*result, *first);
	}
	void insertDispatch(char *position, char *first, char *last, const Rva008312E0FalseType &)
	{
		insertRange(position, first, last, Rva008312E0Tag());
	}
	void insert(char *position, char *first, char *last)
	{
		insertDispatch(position, first, last, Rva008312E0FalseType());
	}
	size_t size() const { return m_finish - m_start; }
	char *allocate(size_t n) const { return n != 0 ? _STL::allocator<char>::allocate(n, 0) : 0; }
	void deallocate(char *p, size_t) const { if (p != 0) free(p); }
	void deallocateBlock() { deallocate(m_start, m_end - m_start); }
	void constructNullAux(char *p, const _STL::__true_type &) { *p = 0; }
	void constructNull(char *p) { constructNullAux(p, _STL::__true_type()); }
};

Rva008312E0String &Rva008312E0String::bfmeReplaceAliasedRange(char *first, char *last,
	char *sourceFirst, char *sourceLast, const Rva008312E0Tag &tag)
{
	if (inside(sourceFirst))
	{
		int __n = sourceLast - sourceFirst;
		const int __len = last - first;
		if (__len >= __n)
		{
			copyRange(sourceFirst, sourceLast, first);
			erase(first + __n, last);
		}
		else
		{
			char *__m = sourceFirst + __len;
			if (sourceLast <= first || sourceFirst >= last)
			{
				copyRange(sourceFirst, __m, first);
				insert(last, __m, sourceLast);
			}
			else
			{
				// Offsets survive a reallocation inside insert.
				const int __off_dest = first - begin();
				const int __off_src = sourceFirst - begin();
				insert(last, __m, sourceLast);
				move(begin() + __off_dest, begin() + __off_src, __n);
			}
		}
		return *this;
	}
	else
		return replaceBase(first, last, sourceFirst, sourceLast, Rva008312E0Tag());
}

// STLport 4.5.3 basic_string::insert(iterator, _ForwardIter, _ForwardIter, forward_iterator_tag)
// without exceptions; assign and _Destroy(char *, char *) stay calls as in retail.
__declspec(noinline) inline void Rva008312E0String::insertRange(char *__position, char *__first, char *__last, const Rva008312E0Tag &)
{
	if (__first != __last)
	{
		int __n = distance(__first, __last);
		if (m_end - m_finish >= __n + 1)
		{
			const int __elems_after = m_finish - __position;
			char *__old_finish = m_finish;
			if (__elems_after >= __n)
			{
				_STL::Rva000179B0UninitializedCopy((m_finish - __n) + 1, m_finish + 1, m_finish + 1);
				m_finish += __n;
				move(__position + __n, __position, (__elems_after - __n) + 1);
				copyRange(__first, __last, __position);
			}
			else
			{
				char *__mid = __first;
				advance(__mid, __elems_after + 1);
				_STL::Rva000179B0UninitializedCopy(__mid, __last, m_finish + 1);
				m_finish += __n - __elems_after;
				_STL::Rva000179B0UninitializedCopy(__position, __old_finish + 1, m_finish);
				m_finish += __elems_after;
				copyRange(__first, __mid, __position);
			}
		}
		else
		{
			const size_t __old_size = size();
			const size_t __len = __old_size + (_STL::max)(__old_size, (size_t)__n) + 1;
			char *__new_start = allocate(__len);
			char *__new_finish = __new_start;
			__new_finish = _STL::Rva000179B0UninitializedCopy(m_start, __position, __new_start);
			__new_finish = _STL::Rva000179B0UninitializedCopy(__first, __last, __new_finish);
			__new_finish = _STL::Rva000179B0UninitializedCopy(__position, m_finish, __new_finish);
			constructNull(__new_finish);
			_STL::Rva0069E440Destroy(m_start, m_finish + 1);
			deallocateBlock();
			m_start = __new_start;
			m_finish = __new_finish;
			m_end = __new_start + __len;
		}
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeInsertV54@BfmeStrV54@@QAEXPAD0000@Z=?bfmeReplaceAliasedRange@Rva008312E0String@@QAEAAV1@PAD000ABURva008312E0Tag@@@Z")
#pragma comment(linker, "/alternatename:?bfmeImplVMI@BfmeStrVMI@@QAEXHHHHPAD@Z=?bfmeReplaceAliasedRange@Rva008312E0String@@QAEAAV1@PAD000ABURva008312E0Tag@@@Z")
