// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /EHsc
// stlport
// ?_M_fill_insert@?$vector@UBfmeContainerRecord005FDEC7@@V?$allocator@UBfmeContainerRecord005FDEC7@@@_STL@@@_STL@@QAEXPAUBfmeContainerRecord005FDEC7@@IABU3@@Z retail 0x005FE835 258B. STLport vector _M_fill_insert for the 12-byte wide-string record (word word UnicodeString at +8) matching the 005FDEC7 assignment. Evidence: callers at 0x005FE9BE and 0x005FE96F; callees Container copy_backward 0x005FE089 fill 0x005FE0A6 fill_n 0x005FE3C1 overflow 0x005FE589 plus StringRecord copy 0x005F93E3 ICF twin of the Container copy and dup uninitialized_copy 0x005FE226 ICF twin and wide releaseBuffer 0x00036E70 for the temp dtor.
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

#include "unicode_string.h"
typedef unsigned short wchar_t;
#include <vector>
struct BfmeContainerRecord005FDEC7 {
    unsigned int word0;
    unsigned int word1;
    UnicodeString text;
    BfmeContainerRecord005FDEC7();
    BfmeContainerRecord005FDEC7(const BfmeContainerRecord005FDEC7 &);
    BfmeContainerRecord005FDEC7 &operator=(const BfmeContainerRecord005FDEC7 &);
};
namespace _STL {
template <> void _Construct<BfmeContainerRecord005FDEC7, BfmeContainerRecord005FDEC7>(BfmeContainerRecord005FDEC7 *, const BfmeContainerRecord005FDEC7 &);

// Retail calls the dispatch layers out of line. noinline forwarders keep them
// out of line as retail has them; bodies are verbatim generic.
// LINK-DUP: inline makes these copies select-any so the owners' plain
// definitions link (see packet).
template <>
inline BfmeContainerRecord005FDEC7 *__copy_backward_ptrs<BfmeContainerRecord005FDEC7 *, BfmeContainerRecord005FDEC7 *>(BfmeContainerRecord005FDEC7 *__first, BfmeContainerRecord005FDEC7 *__last, BfmeContainerRecord005FDEC7 *__result, const __false_type &)
{
	return __copy_backward(__first, __last, __result, random_access_iterator_tag(), (int *)0);
}

template <>
inline BfmeContainerRecord005FDEC7 *uninitialized_fill_n<BfmeContainerRecord005FDEC7 *, unsigned int, BfmeContainerRecord005FDEC7>(BfmeContainerRecord005FDEC7 *__first, unsigned int __n, const BfmeContainerRecord005FDEC7 &__x)
{
	return __uninitialized_fill_n(__first, __n, __x, __false_type());
}

template <>
inline void vector<BfmeContainerRecord005FDEC7, allocator<BfmeContainerRecord005FDEC7> >::_M_fill_insert(
	BfmeContainerRecord005FDEC7 *__position, size_type __n, const BfmeContainerRecord005FDEC7 &__x)
{
	if (__n != 0) {
		if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
			BfmeContainerRecord005FDEC7 __x_copy = __x;
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
			_M_insert_overflow(__position, __x, _IsPODType(), __n);
	}
}
}

// This method is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeStlportVectorContainerFillInsertAnchor@@YAXXZ absent-from-retail
void _bfmeStlportVectorContainerFillInsertAnchor()
{
    typedef _STL::vector<BfmeContainerRecord005FDEC7, _STL::allocator<BfmeContainerRecord005FDEC7> > ContainerVector;
    ContainerVector *vector = 0;
    BfmeContainerRecord005FDEC7 *position = 0;
    const BfmeContainerRecord005FDEC7 *value = 0;
    vector->_M_fill_insert(position, 0, *value);
}
#pragma inline_depth()
