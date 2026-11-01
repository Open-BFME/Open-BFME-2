// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Retail 0x004F6FE1 (27B) is _STL::copy_backward<TreeHintRef00217D4C *> (the
// name reverse/symbols.csv already pinned there): its three callers in
// __merge_backward 0x004F792B push three arguments, and the body builds the
// _IsOKToMemCpy tag on its own stack and calls the rowed __false_type
// dispatcher 0x004F6D2E (Rva004F6D2ECopyBackward.cpp). The element is the
// owning handle of PAUTreeHintRef00217D4CRva004F9565.cpp; only a user-declared
// assignment matters here (it makes the copy non-trivial).
#include <algorithm>

#include "../../Apt/AptRefTarget.h"

// The dispatcher is rowed in Rva004F6D2ECopyBackward.cpp; declare it so this
// TU calls that body instead of emitting its own copy.
namespace _STL {
template <> TreeHintRef00217D4C *__copy_backward_ptrs<TreeHintRef00217D4C *, TreeHintRef00217D4C *>(
	TreeHintRef00217D4C *, TreeHintRef00217D4C *, TreeHintRef00217D4C *, const __false_type &);
}

// copy_backward with __copy_backward_aux inlined: the tag lives in the
// frame uninitialised (retail never stores to [ebp-1]); STLport's
// _IsOKToMemCpy(...)._Ret() temporary would zero it first.
namespace _STL {
template <> TreeHintRef00217D4C *copy_backward<TreeHintRef00217D4C *, TreeHintRef00217D4C *>(
	TreeHintRef00217D4C *first, TreeHintRef00217D4C *last, TreeHintRef00217D4C *result)
{
	__false_type tag;
	return __copy_backward_ptrs(first, last, result, tag);
}
}
