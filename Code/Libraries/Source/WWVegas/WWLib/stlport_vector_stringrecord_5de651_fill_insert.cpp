// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /EHsc
// stlport
//
// ?_M_fill_insert@?$vector@UBfmeStringRecord005DDD40@@V?$allocator@UBfmeStringRecord005DDD40@@@_STL@@@_STL@@QAEXPAUBfmeStringRecord005DDD40@@IABU3@@Z
// retail 0x005DE651 (260 bytes).
//
// Landed from the 0.95 banked stash. align_diff had the body at 260B/98
// instructions with exactly one differing byte -- the call at +0xD7. Retail's
// displacement reaches 0x00036E70, the body the export table names
// ?releaseBuffer@?$StringBase@G@@AAEXXZ; ours reached the record destructor's
// pin 0x005B804E, which is a 5-byte `jmp 0x36E70` thunk. Both spellings are the
// same two-instruction tail (`lea ecx,[ebp-0x14]` then a thiscall on the
// temporary), so retail INLINED that destructor and called the folded body.
// The byte-true call site is 0x005DE728 (`lea ecx,[ebp-0x14]` / `call 0x36E70`),
// which is why the record destructor's pin now names 0x36E70 instead of the
// UnicodeString thunk at 0x5B804E.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
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
struct BfmeStringRecord005DDD40 {
    UnicodeString text;
    unsigned int word;
    BfmeStringRecord005DDD40();
    BfmeStringRecord005DDD40(const BfmeStringRecord005DDD40 &);
    BfmeStringRecord005DDD40 &operator=(const BfmeStringRecord005DDD40 &);
};
namespace _STL {
template <> void _Construct<BfmeStringRecord005DDD40, BfmeStringRecord005DDD40>(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);

// Retail calls the dispatch layers out of line. noinline forwarders keep them
// out of line as retail has them; bodies are verbatim generic.
// LINK-DUP: inline makes these copies select-any so the owners' plain
// definitions link (see packet).
template <>
inline BfmeStringRecord005DDD40 *__copy_backward_ptrs<BfmeStringRecord005DDD40 *, BfmeStringRecord005DDD40 *>(BfmeStringRecord005DDD40 *__first, BfmeStringRecord005DDD40 *__last, BfmeStringRecord005DDD40 *__result, const __false_type &)
{
	return __copy_backward(__first, __last, __result, random_access_iterator_tag(), (int *)0);
}

template <>
inline BfmeStringRecord005DDD40 *uninitialized_fill_n<BfmeStringRecord005DDD40 *, unsigned int, BfmeStringRecord005DDD40>(BfmeStringRecord005DDD40 *__first, unsigned int __n, const BfmeStringRecord005DDD40 &__x)
{
	return __uninitialized_fill_n(__first, __n, __x, __false_type());
}

template <>
inline void vector<BfmeStringRecord005DDD40, allocator<BfmeStringRecord005DDD40> >::_M_fill_insert(
	BfmeStringRecord005DDD40 *__position, size_type __n, const BfmeStringRecord005DDD40 &__x)
{
	if (__n != 0) {
		if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
			BfmeStringRecord005DDD40 __x_copy = __x;
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
// ?_bfmeStlportVectorStringRecordFillInsertAnchor@@YAXXZ absent-from-retail
void _bfmeStlportVectorStringRecordFillInsertAnchor()
{
    typedef _STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> > StringRecordVector;
    StringRecordVector *vector = 0;
    BfmeStringRecord005DDD40 *position = 0;
    const BfmeStringRecord005DDD40 *value = 0;
    vector->_M_fill_insert(position, 0, *value);
}
#pragma inline_depth()
