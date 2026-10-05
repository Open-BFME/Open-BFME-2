// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /EHsc
// stlport
// ?_M_fill_insert@?$vector@UBfmeStringRecord005ED5F3@@V?$allocator@UBfmeStringRecord005ED5F3@@@_STL@@@_STL@@QAEXPAUBfmeStringRecord005ED5F3@@IABU3@@Z retail 0x005EDEF3 258B. STLport vector _M_fill_insert for the 20-byte wide-string record (UnicodeString text plus 4 words) matching the 005ED5F3 copy. Evidence: in-place versus overflow shape with ret 0x0C and 0x14 stride; callees rowed copy 0x005ED5F3 fill 0x005ED63D copy_backward_ptrs 0x005ED620 uninitialized_copy 0x005ED886 uninitialized_fill_n 0x005ED98E overflow 0x005EDABD plus wide releaseBuffer 0x00036E70 for the temp dtor; callers unclaimed at 0x005EE0B6 and 0x005EE00F.
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
struct BfmeStringRecord005ED5F3 {
    UnicodeString text;
    unsigned int word0;
    unsigned int word1;
    unsigned int word2;
    unsigned int word3;
    BfmeStringRecord005ED5F3();
    BfmeStringRecord005ED5F3(const BfmeStringRecord005ED5F3 &);
    BfmeStringRecord005ED5F3 &operator=(const BfmeStringRecord005ED5F3 &);
};
namespace _STL {
template <> void _Construct<BfmeStringRecord005ED5F3, BfmeStringRecord005ED5F3>(BfmeStringRecord005ED5F3 *, const BfmeStringRecord005ED5F3 &);

// Retail calls the dispatch layers out of line. noinline forwarders keep them
// out of line as retail has them; bodies are verbatim generic.
// LINK-DUP: inline makes these copies select-any so the owners' plain
// definitions link (see packet).
template <>
inline BfmeStringRecord005ED5F3 *__copy_backward_ptrs<BfmeStringRecord005ED5F3 *, BfmeStringRecord005ED5F3 *>(BfmeStringRecord005ED5F3 *__first, BfmeStringRecord005ED5F3 *__last, BfmeStringRecord005ED5F3 *__result, const __false_type &)
{
	return __copy_backward(__first, __last, __result, random_access_iterator_tag(), (int *)0);
}

template <>
inline BfmeStringRecord005ED5F3 *uninitialized_fill_n<BfmeStringRecord005ED5F3 *, unsigned int, BfmeStringRecord005ED5F3>(BfmeStringRecord005ED5F3 *__first, unsigned int __n, const BfmeStringRecord005ED5F3 &__x)
{
	return __uninitialized_fill_n(__first, __n, __x, __false_type());
}

template <>
inline void vector<BfmeStringRecord005ED5F3, allocator<BfmeStringRecord005ED5F3> >::_M_fill_insert(
	BfmeStringRecord005ED5F3 *__position, size_type __n, const BfmeStringRecord005ED5F3 &__x)
{
	if (__n != 0) {
		if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
			BfmeStringRecord005ED5F3 __x_copy = __x;
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
// ?_bfmeStlportVectorStringRecord5ED5F3FillInsertAnchor@@YAXXZ absent-from-retail
void _bfmeStlportVectorStringRecord5ED5F3FillInsertAnchor()
{
    typedef _STL::vector<BfmeStringRecord005ED5F3, _STL::allocator<BfmeStringRecord005ED5F3> > StringRecordVector;
    StringRecordVector *vector = 0;
    BfmeStringRecord005ED5F3 *position = 0;
    const BfmeStringRecord005ED5F3 *value = 0;
    vector->_M_fill_insert(position, 0, *value);
}
#pragma inline_depth()
