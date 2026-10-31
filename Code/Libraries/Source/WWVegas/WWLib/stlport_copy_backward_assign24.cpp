// cl: /EHs-c- /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport46
// ??$copy_backward@PAUBfmeAssignRecord24@@PAU1@@_STL@@YAPAUBfmeAssignRecord24@@PAU1@00@Z RVA 0x004286FB size 27
// Evidence: caller 0x0042875A in FUN_0082872d; callee rowed __copy_backward_ptrs at 0x00428421; shape matches E12 precedent 0x0051C94D.
// The 27B body is the out-of-line 0x00428421 call passing an uninitialized one-byte tag by reference;
// retail does not inline that forwarder here.
#include <vector>
#include "ascii_string.h"
// The rowed 33B assignment at 0x0042816E is the pinned operator= for this view.
struct BfmeAssignRecord24 { AsciiString s; int a[5]; BfmeAssignRecord24 &operator=(const BfmeAssignRecord24 &); };
namespace _STL { template <> BfmeAssignRecord24 *__copy_backward<BfmeAssignRecord24 *, BfmeAssignRecord24 *, int>(BfmeAssignRecord24 *, BfmeAssignRecord24 *, BfmeAssignRecord24 *, const random_access_iterator_tag &, int *); }
namespace _STL {
#pragma inline_depth(0)
template <>
BfmeAssignRecord24 *copy_backward<BfmeAssignRecord24 *, BfmeAssignRecord24 *>(BfmeAssignRecord24 *first, BfmeAssignRecord24 *last, BfmeAssignRecord24 *result)
{
	__false_type tag;
	return __copy_backward_ptrs(first, last, result, tag);
}
#pragma inline_depth()
}
