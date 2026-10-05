// ?_M_fill_insert@?$vector@UBfmeAssignRecord32@@V?$allocator@UBfmeAssignRecord32@@@_STL@@@_STL@@QAEXPAUBfmeAssignRecord32@@IABU3@@Z
// partial score=0.9 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /EHsc
// stlport
// ?_M_fill_insert@?$vector@UBfmeAssignRecord32@@V?$allocator@UBfmeAssignRecord32@@@_STL@@@_STL@@QAEXPAU3@IABU3@@Z @0x0017422D 264B: vector BfmeAssignRecord32 _M_fill_insert.
// Evidence: same fill_insert shape as AsciiString 0x000C0697 with sar 5 stride 32;
// callees rowed copy 0x00173731 uninit_copy 0x0017398C copy_backward 0x00173786
// fill 0x001737A3 uninit_fill_n 0x001739B2 overflow 0x00173FE9 dtor 0x0017330A;
// prev clear next partial_sort same flags.
#include "ascii_string.h"
#include <vector>
struct BfmeAssignRecord32 {
	AsciiString s;
	int a[7];
	BfmeAssignRecord32(const BfmeAssignRecord32 &o);
	BfmeAssignRecord32 &operator=(const BfmeAssignRecord32 &o);
	~BfmeAssignRecord32();
};
namespace _STL
{
template <class InputIter, class OutputIter>
OutputIter __uninitialized_copy(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
template <>
inline BfmeAssignRecord32 *__copy_backward_ptrs<BfmeAssignRecord32 *, BfmeAssignRecord32 *>(BfmeAssignRecord32 *__first, BfmeAssignRecord32 *__last, BfmeAssignRecord32 *__result, const __false_type &)
{
	return __copy_backward(__first, __last, __result, random_access_iterator_tag(), (int *)0);
}
template <class ForwardIter, class T>
void fill(ForwardIter first, ForwardIter last, const T &value);
template <class ForwardIter, class Size, class T>
ForwardIter uninitialized_fill_n(ForwardIter first, Size n, const T &x);
}
namespace _STL
{
template <>
inline void vector<BfmeAssignRecord32, allocator<BfmeAssignRecord32> >::_M_fill_insert(
	BfmeAssignRecord32 *__position, size_type __n, const BfmeAssignRecord32 &__x)
{
	if (__n != 0) {
		if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
			BfmeAssignRecord32 __x_copy = __x;
			const size_type __elems_after = this->_M_finish - __position;
			pointer __old_finish = this->_M_finish;
			if (__elems_after > __n) {
				__uninitialized_copy(this->_M_finish - __n, this->_M_finish, this->_M_finish, _IsPODType());
				this->_M_finish += __n;
				__copy_backward_ptrs(__position, __old_finish - __n, __old_finish, _TrivialAss());
				_STLP_STD::fill(__position, __position + __n, __x_copy);
			}
			else {
				uninitialized_fill_n(this->_M_finish, __n - __elems_after, __x_copy);
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
#pragma inline_depth(0)
// ?_bfmeStlportVectorAssignRecord32FillInsertAnchor@@YAXXZ absent-from-retail
void _bfmeStlportVectorAssignRecord32FillInsertAnchor()
{
	typedef _STL::vector<BfmeAssignRecord32, _STL::allocator<BfmeAssignRecord32> > AssignRecord32Vector;
	AssignRecord32Vector *vec = 0;
	BfmeAssignRecord32 *pos = 0;
	const BfmeAssignRecord32 *val = 0;
	vec->_M_fill_insert(pos, 0, *val);
}
#pragma inline_depth()
