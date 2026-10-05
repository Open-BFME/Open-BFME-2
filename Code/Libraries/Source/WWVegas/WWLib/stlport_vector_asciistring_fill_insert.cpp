// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /EHsc
// stlport
// ?_M_fill_insert@?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAEXPAVAsciiString@@IABV3@@Z @0x000C0697 258B: vector AsciiString _M_fill_insert via StringBase copy 0x365F0 plus uninitialized_copy 0x2C4B2 plus copy_backward 0xB6631 plus fill 0xB4300 plus Rva000B9596Fill 0xB9596 plus overflow 0x2D1CF plus releaseBuffer 0x36410. Evidence: same 258B shape as StringRecord fill_insert 0x005EDEF3; ret 0x0C with sar 2 stride 4; callers at 0x000C331A and 0x000C1CA9.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "ascii_string.h"
#include <vector>
namespace _STL
{
template <class InputIter, class OutputIter>
OutputIter __uninitialized_copy(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
// Retail calls the dispatch layer out of line. Forwarders keep it out of line.
template <>
inline AsciiString *__copy_backward_ptrs<AsciiString *, AsciiString *>(AsciiString *__first, AsciiString *__last, AsciiString *__result, const __false_type &)
{
	return __copy_backward(__first, __last, __result, random_access_iterator_tag(), (int *)0);
}
template <class ForwardIter, class T>
void fill(ForwardIter first, ForwardIter last, const T &value);
}
AsciiString *Rva000B9596Fill(AsciiString *first, unsigned int n, const AsciiString &x);
namespace _STL
{
template <>
inline void vector<AsciiString, allocator<AsciiString> >::_M_fill_insert(
	AsciiString *__position, size_type __n, const AsciiString &__x)
{
	if (__n != 0) {
		if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
			AsciiString __x_copy = __x;
			const size_type __elems_after = this->_M_finish - __position;
			pointer __old_finish = this->_M_finish;
			if (__elems_after > __n) {
				__uninitialized_copy(this->_M_finish - __n, this->_M_finish, this->_M_finish, _IsPODType());
				this->_M_finish += __n;
				__copy_backward_ptrs(__position, __old_finish - __n, __old_finish, _TrivialAss());
				_STLP_STD::fill(__position, __position + __n, __x_copy);
			}
			else {
				Rva000B9596Fill(this->_M_finish, __n - __elems_after, __x_copy);
				this->_M_finish += __n - __elems_after;
				__uninitialized_copy(__position, __old_finish, this->_M_finish, _IsPODType());
				this->_M_finish += __elems_after;
				_STLP_STD::fill(__position, __old_finish, __x_copy);
			}
		}
		else
			_M_insert_overflow(__position, __x, _IsPODType(), __n, false);
	}
}
}
// This method is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeStlportVectorAsciiStringFillInsertAnchor@@YAXXZ absent-from-retail
void _bfmeStlportVectorAsciiStringFillInsertAnchor()
{
	typedef _STL::vector<AsciiString, _STL::allocator<AsciiString> > AsciiStringVector;
	AsciiStringVector *vector = 0;
	AsciiString *position = 0;
	const AsciiString *value = 0;
	vector->_M_fill_insert(position, 0, *value);
}
#pragma inline_depth()
