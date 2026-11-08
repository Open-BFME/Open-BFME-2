// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@VEnableRegionRecord@@V?$allocator@VEnableRegionRecord@@@_STL@@@_STL@@IAEXPAVEnableRegionRecord@@ABV3@ABU__false_type@2@I_N@Z,
// retail 0x00565ACB. Dedicated TU.
//
// STLport 4.5.3 vector<EnableRegionRecord>::_M_insert_overflow. Target evidence: the
// retail body's calls read the matched _Construct<EnableRegionRecord> (0x0052C2F3, which
// calls the matched EnableRegionRecord copy ctor 0x0052BD3A) and the matched
// __uninitialized_fill_n<EnableRegionRecord *> (0x005655DC, stride 8). Recipe carried from
// the matched sibling ObjectCreationList_AnimSetInsertOverflow.cpp:
// /Ireference/shims/bfmealloc keeps allocator<EnableRegionRecord>::allocate a two-argument
// out-of-line call (push 0 / push len / call 0x00523D6C, the 8-byte ICF
// allocate), _Construct<EnableRegionRecord> is declared but not defined so the copies
// call its matched body, and explicit member instantiation keeps the other
// vector members out of this TU. EnableRegionRecord is reduced to its 8-byte footprint
// (vptr plus nugget list) with the out-of-line copy ctor and the virtual dtor
// GameClient/EnableRegionRecord.h declares: retail _M_clear 0x005659CA destroys each
// element through 0x0052BF33, a vtable slot 0 call with a zero flag.
//
// push_back (retail 0x0056625E) and the copy ctor (retail 0x0052CAC9) are
// instantiated here too: they are the only unowned callers of the
// _M_insert_overflow and __uninitialized_copy bodies this TU places.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class EnableRegionRecord
{
	char _m[4];

public:
	EnableRegionRecord(const EnableRegionRecord &that);
	virtual ~EnableRegionRecord();
};

namespace _STL
{
template <> void _Construct<EnableRegionRecord, EnableRegionRecord>(EnableRegionRecord *, const EnableRegionRecord &);
}

template void _STL::vector<EnableRegionRecord>::_M_insert_overflow(
	EnableRegionRecord *,
	const EnableRegionRecord &,
	const _STL::__false_type &,
	unsigned int,
	bool);

template void _STL::vector<EnableRegionRecord>::push_back(const EnableRegionRecord &);
template _STL::vector<EnableRegionRecord>::vector(const _STL::vector<EnableRegionRecord> &);
