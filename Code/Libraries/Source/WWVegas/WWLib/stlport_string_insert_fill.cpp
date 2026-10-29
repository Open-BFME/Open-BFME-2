// cl: /O2 /Ob1 /DNDEBUG /MD
// stlport46
//
// STLport 4.5.3 basic_string<char>::insert(iterator, size_type n, char c), retail
// 0x00029530 (662 B; vendored _string.c body with _STLP_NO_EXCEPTIONS, so the
// _STLP_TRY/_STLP_UNWIND guards vanish). Retail compiled it unoptimized (/Od /Ob1
// frame) while the non-template inline fill(char*,char*,const char&) stays an
// out-of-line call to the /O2 copy at 0x000237C0; that inline's `__tmp` local
// still claims a cell (ebp-0x4C) in insert's frame. Compiling fill alone in an
// optimized region of an otherwise unoptimized unit reproduces both: the frame
// cell and fill's own 48-byte /O2 body. uninitialized_copy keeps its placeholder
// name (folded __copy_trivial at 0x000179B0) and _Destroy(char*,char*) is the
// shared empty RET at 0x0069E440, both pinned from the StringReplace unit.
#include <string.h>
// MSVC imported-inline ownership keeps these fully inlined helper views from
// emitting conflicting out-of-line copies. The COFF audit preserves every
// surviving body and relocation and confirms there are no helper import edges.
// The shared mutable-copy provider still has its separately tracked 68/41-byte debt.
#pragma optimize("", off)

namespace _STL
{
void *__copy_trivial(const void *__first, const void *__last, void *__result);
#pragma optimize("", on)
inline void fill(char *__first, char *__last, const char &__val)
{
	char __tmp = __val;
	memset(__first, (unsigned char)__tmp, __last - __first);
}
#pragma optimize("", off)
void free(void *);
void Rva0069E440Destroy(char *, char *);

template <class _Tp>
class allocator;

template <>
class allocator<char>
{
public:
	static char *allocate(unsigned int __n, const void *);
};

template <class CharT>
class char_traits;

template <>
class char_traits<char>
{
public:
	static char *assign(char *__s, unsigned int __n, char __c);
	static char *move(char *__s1, const char *__s2, unsigned int __n)
	{
		return __n == 0 ? __s1 : (char *)memmove(__s1, __s2, __n);
	}
};

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
__declspec(dllimport) __forceinline _OutputIter __copy_ptrs(_InputIter __first, _InputIter __last, _OutputIter __result, __true_type)
{
	return (_OutputIter)__copy_trivial(__first, __last, __result);
}

template <class _InputIter, class _OutputIter>
__declspec(dllimport) __forceinline _OutputIter __copy_aux(_InputIter __first, _InputIter __last, _OutputIter __result, __true_type)
{
	return __copy_ptrs(__first, __last, __result, _IsOKToMemCpy((char *)0, (char *)0)._Ret());
}

template <class _InputIter, class _ForwardIter>
__declspec(dllimport) __forceinline _ForwardIter __uninitialized_copy(_InputIter __first, _InputIter __last, _ForwardIter __result, const __true_type &)
{
	return __copy_aux(__first, __last, __result, _BothPtrType<_InputIter, _ForwardIter>::_Ret());
}

template <class _InputIter, class _ForwardIter>
inline _ForwardIter Rva000179B0UninitializedCopy(_InputIter __first, _InputIter __last, _ForwardIter __result)
{
	return __uninitialized_copy(__first, __last, __result, __true_type());
}

template <class _Size>
inline char *fill_n(char *__first, _Size __n, const char &__val)
{
	fill(__first, __first + __n, __val);
	return __first + __n;
}

template <class _ForwardIter, class _Size, class _Tp>
inline _ForwardIter __uninitialized_fill_n(_ForwardIter __first, _Size __n,
	const _Tp &__x, const __true_type &)
{
	return fill_n(__first, __n, __x);
}

template <class _ForwardIter, class _Size, class _Tp>
inline _ForwardIter uninitialized_fill_n(_ForwardIter __first, _Size __n, const _Tp &__x)
{
	return __uninitialized_fill_n(__first, __n, __x, __true_type());
}

template <class _Tp>
__declspec(dllimport) __forceinline const _Tp &(max)(const _Tp &__a, const _Tp &__b)
{
	return __a < __b ? __b : __a;
}
template <class _CharT, class _Traits, class _Alloc>
class basic_string
{
public:
	typedef _CharT *pointer;
	typedef _CharT *iterator;
	typedef unsigned int size_type;

	void insert(iterator __position, size_type __n, _CharT __c);

	__declspec(dllimport) __forceinline size_type size() const { return this->_M_finish - this->_M_start; }

private:
	pointer _M_allocate(size_type __n) { return __n != 0 ? _STL::allocator<char>::allocate(__n, 0) : 0; }
	void _M_deallocate(pointer __p, size_type) { if (__p != 0) _STL::free(__p); }
	void _M_deallocate_block() { _M_deallocate(this->_M_start, this->_M_end_of_storage - this->_M_start); }
	__declspec(dllimport) __forceinline void _M_construct_null_aux(pointer __p, const _STL::__true_type &) { *__p = 0; }
	__declspec(dllimport) __forceinline void _M_construct_null(pointer __p) { _M_construct_null_aux(__p, _STL::__true_type()); }

	pointer _M_start;
	pointer _M_finish;
	pointer _M_end_of_storage;
};
}

template <class _CharT, class _Traits, class _Alloc>
void _STL::basic_string<_CharT, _Traits, _Alloc>::insert(iterator __position, size_type __n, _CharT __c)
{
	if (__n != 0) {
		if ((size_type)(this->_M_end_of_storage - this->_M_finish) >= __n + 1) {
			const size_type __elems_after = this->_M_finish - __position;
			pointer __old_finish = this->_M_finish;
			if (__elems_after >= __n) {
				_STL::Rva000179B0UninitializedCopy((this->_M_finish - __n) + 1, this->_M_finish + 1, this->_M_finish + 1);
				this->_M_finish += __n;
				_Traits::move(__position + __n, __position, (__elems_after - __n) + 1);
				_Traits::assign(__position, __n, __c);
			}
			else {
				_STL::uninitialized_fill_n(this->_M_finish + 1, __n - __elems_after - 1, __c);
				this->_M_finish += __n - __elems_after;
				_STL::Rva000179B0UninitializedCopy(__position, __old_finish + 1, this->_M_finish);
				this->_M_finish += __elems_after;
				_Traits::assign(__position, __elems_after + 1, __c);
			}
		}
		else {
			const size_type __old_size = size();
			const size_type __len = __old_size + (_STL::max)(__old_size, __n) + 1;
			pointer __new_start = _M_allocate(__len);
			pointer __new_finish = __new_start;
			__new_finish = _STL::Rva000179B0UninitializedCopy(this->_M_start, __position, __new_start);
			__new_finish = _STL::uninitialized_fill_n(__new_finish, __n, __c);
			__new_finish = _STL::Rva000179B0UninitializedCopy(__position, this->_M_finish, __new_finish);
			_M_construct_null(__new_finish);
			_STL::Rva0069E440Destroy(this->_M_start, this->_M_finish + 1);
			_M_deallocate_block();
			this->_M_start = __new_start;
			this->_M_finish = __new_finish;
			this->_M_end_of_storage = __new_start + __len;
		}
	}
}

template void _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >::insert(char *, unsigned int, char);
