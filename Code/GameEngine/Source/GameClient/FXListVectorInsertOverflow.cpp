// cl: /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@VFXList@@V?$allocator@VFXList@@@_STL@@@_STL@@IAEXPAVFXList@@ABV3@ABU__false_type@2@I_N@Z,
// retail 0x00565ACB. Dedicated TU.
//
// STLport 4.5.3 vector<FXList>::_M_insert_overflow. Target evidence: the
// retail body's calls read the matched _Construct<FXList> (0x0052C2F3, which
// calls the matched FXList copy ctor 0x0052BD3A) and the matched
// __uninitialized_fill_n<FXList *> (0x005655DC, stride 8). Recipe carried from
// the matched sibling ObjectCreationList_AnimSetInsertOverflow.cpp:
// /Ireference/shims/bfmealloc keeps allocator<FXList>::allocate a two-argument
// out-of-line call (push 0 / push len / call 0x00523D6C, the 8-byte ICF
// allocate), _Construct<FXList> is declared but not defined so the copies
// call its matched body, and explicit member instantiation keeps the other
// vector members out of this TU. FXList is reduced to its 8-byte footprint
// with the out-of-line copy ctor and dtor.
//
// push_back (retail 0x0056625E) and the copy ctor (retail 0x0052CAC9) are
// instantiated here too: they are the only unowned callers of the
// _M_insert_overflow and __uninitialized_copy bodies this TU places.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class FXList
{
	char _m[8];

public:
	FXList(const FXList &that);
	~FXList();
};

namespace _STL
{
template <> void _Construct<FXList, FXList>(FXList *, const FXList &);
}

template void _STL::vector<FXList>::_M_insert_overflow(
	FXList *,
	const FXList &,
	const _STL::__false_type &,
	unsigned int,
	bool);

template void _STL::vector<FXList>::push_back(const FXList &);
template _STL::vector<FXList>::vector(const _STL::vector<FXList> &);
