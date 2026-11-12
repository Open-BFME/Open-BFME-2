// cl: /Od /Ob1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// RVA 0x0002AB40, 149 bytes: basic_string::insert(pos, source, count) procedure.
// Semantic guide: STLport 4.5.2 vendor/stlport/stl/_string.h and BFME 1
// STLport 4.6 at revision 92f6bbe8e1dcdb46b5d27da0674313efc822b790.
// Retail proves the unsigned checks, +0/+4 storage access and call targets;
// original class names and source constness remain source inferences.
// Retain the existing caller ABI and use the established string owner for
// the native 0x00028820 insertion. Its inline context is kept identical to
// Rva008314E0StringReplace.cpp; compiler inlining depth stays at its default.
// The shared mutable-copy provider's existing 68/41-byte link discrepancy
// is unchanged; this conversion claims only the caller's complete body.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

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
// Retail calls the shared empty destruction body at RVA 0x0069E440.
// Keep its existing neutral binding; the declaration does not claim its original name.
void Rva0069E440Destroy(char *, char *);

struct __true_type
{
};

// The POD-dispatch structure shared by the STLport sources. The four mutable
// buffer copies keep this analysis context and the existing neutral call binding.
// Their retail calls reach __copy_trivial at RVA 0x000179B0.
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
inline _OutputIter __copy_ptrs(_InputIter __first, _InputIter __last, _OutputIter __result, const __true_type &)
{
	return (_OutputIter)__copy_trivial(__first, __last, __result);
}

template <class _InputIter, class _OutputIter>
inline _OutputIter __copy_aux(_InputIter __first, _InputIter __last, _OutputIter __result, const __true_type &)
{
	return __copy_ptrs(__first, __last, __result, _IsOKToMemCpy((char *)0, (char *)0)._Ret());
}

template <class _InputIter, class _ForwardIter>
inline _ForwardIter __uninitialized_copy(_InputIter __first, _InputIter __last, _ForwardIter __result, const __true_type &)
{
	return __copy_aux(__first, __last, __result, _BothPtrType<_InputIter, _ForwardIter>::_Ret());
}

template <class _InputIter, class _ForwardIter>
inline _ForwardIter Rva000179B0UninitializedCopy(_InputIter __first, _InputIter __last, _ForwardIter __result)
{
	return __uninitialized_copy(__first, __last, __result, __true_type());
}
}

#pragma intrinsic(memcpy)

#include "../../Include/Common/BfmeRangeInputTag.h"

struct BfmeRangeTag : public BfmeRangeInputTag
{
};

#include "../../Include/Common/BfmeRangeFalseType.h"

template <class _RandomAccessIterator>
inline int __distance(const _RandomAccessIterator &__first,
	const _RandomAccessIterator &__last, const BfmeRangeTag &)
{
	return __last - __first;
}

template <class _InputIterator>
inline int distance(const _InputIterator &__first, const _InputIterator &__last)
{
	return __distance(__first, __last, BfmeRangeTag());
}

template <class _RandomAccessIterator, class _Distance>
inline void __advance(_RandomAccessIterator &__i, _Distance __n, const BfmeRangeTag &)
{
	__i += __n;
}

template <class _InputIterator, class _Distance>
inline void advance(_InputIterator &__i, _Distance __n)
{
	__advance(__i, __n, BfmeRangeTag());
}

class Rva008314E0String
{
public:
	Rva008314E0String &replaceRange(char *first, char *last,
		char *sourceFirst, char *sourceLast, const BfmeRangeTag &tag);

	// Erase at RVA 0x00012150; the body mirrors STLport's erase.
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

	// Forward-range insertion at RVA 0x00028820. The two source-range copies use
	// the const-char overload's direct __copy_trivial call; four buffer copies use POD dispatch.
	void insertRange(char *__position, char *__first, char *__last, const BfmeRangeTag &)
	{
		if (__first != __last)
		{
			int __n = distance(__first, __last);
			if (m_endOfStorage - m_finish >= __n + 1)
			{
				const int __elems_after = m_finish - __position;
				char *__old_finish = m_finish;
				if (__elems_after >= __n)
				{
					_STL::Rva000179B0UninitializedCopy((m_finish - __n) + 1, m_finish + 1, m_finish + 1);
					m_finish += __n;
					move(__position + __n, __position, (__elems_after - __n) + 1);
					copyIter(__first, __last, __position);
				}
				else
				{
					char *__mid = __first;
					advance(__mid, __elems_after + 1);
					_STL::__copy_trivial(__mid, __last, m_finish + 1);
					m_finish += __n - __elems_after;
					_STL::Rva000179B0UninitializedCopy(__position, __old_finish + 1, m_finish);
					m_finish += __elems_after;
					copyIter(__first, __mid, __position);
				}
			}
			else
			{
				const unsigned int __old_size = size();
				const unsigned int __len = __old_size + maxOf(__old_size, (unsigned int)__n) + 1;
				char *__new_start = allocate(__len);
				char *__new_finish = __new_start;
				__new_finish = _STL::Rva000179B0UninitializedCopy(m_start, __position, __new_start);
				__new_finish = (char *)_STL::__copy_trivial(__first, __last, __new_finish);
				__new_finish = _STL::Rva000179B0UninitializedCopy(__position, m_finish, __new_finish);
				constructNull(__new_finish);
				_STL::Rva0069E440Destroy(m_start, m_finish + 1);
				deallocateBlock();
				m_start = __new_start;
				m_finish = __new_finish;
				m_endOfStorage = __new_start + __len;
			}
		}
	}
	unsigned int size() const { return m_finish - m_start; }
	template <class _InputIter>
	static void copyIter(_InputIter __first, _InputIter __last, char *__result)
	{
		move(__result, __first, __last - __first);
	}
	char *allocate(unsigned int n) const { return n != 0 ? _STL::allocator<char>::allocate(n, 0) : 0; }
	static const unsigned int &maxOf(const unsigned int &a, const unsigned int &b)
	{
		return a < b ? b : a;
	}
	void constructNullAux(char *p, const _STL::__true_type &) { *p = 0; }
	void constructNull(char *p) { constructNullAux(p, _STL::__true_type()); }
	void deallocate(char *p, size_t) const { if (p != 0) free(p); }
	void deallocateBlock() { deallocate(m_start, m_endOfStorage - m_start); }

	// Plain forward-iterator replace at RVA 0x0002A730.
	Rva008314E0String &replaceBase(char *__first, char *__last, char *__f,
		char *__l, const BfmeRangeTag &)
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
	static void copyRange(const char *first, const char *last, char *result)
	{
		copy(result, first, last - first);
	}
	static void moveRange(const char *first, const char *last, char *result)
	{
		move(result, first, last - first);
	}
	void insertDispatch(char *position, char *first, char *last, const BfmeRangeFalseType &)
	{
		insertRange(position, first, last, BfmeRangeTag());
	}
	void insert(char *position, char *first, char *last)
	{
		insertDispatch(position, first, last, BfmeRangeFalseType());
	}
	static char *move(char *s1, const char *s2, size_t n)
	{
		return n == 0 ? s1 : (char *)memmove(s1, s2, n);
	}
	static char *copy(char *s1, const char *s2, size_t n)
	{
		return n == 0 ? s1 : (char *)memcpy(s1, s2, n);
	}

	char *m_start;
	char *m_finish;
	char *m_endOfStorage;
};

// Compatibility spelling for the pre-existing neutral caller ABI.
// The view adds no fields; all string operations use the existing owner.
class BfmeStrV21 : public Rva008314E0String
{
public:
	BfmeStrV21 *bfmeInsertV21(unsigned pos, char *s, unsigned n);
	void bfmeGrowV21();
	void bfmeLenErrV21();
	unsigned max_size() const { return unsigned(-1) / sizeof(char) - 1; }
};

BfmeStrV21 *BfmeStrV21::bfmeInsertV21(unsigned pos, char *s, unsigned n)
{
	if (pos > size())
	    bfmeGrowV21();
	if (size() > max_size() - n)
	    bfmeLenErrV21();
	insert(begin() + pos, s, s + n);
	return this;
}
