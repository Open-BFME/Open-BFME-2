// ?_M_insert_overflow@?$vector@UBfmePod172@@V?$allocator@UBfmePod172@@@_STL@@@_STL@@IAEXPAUBfmePod172@@ABU3@ABU__false_type@2@I_N@Z
// Landed from the banked 0.98 attempt; its two unresolved REL32 names are ICF
// aliases pinned in reverse/symbols.csv (0x1EBA30 non-const copy, 0x1EB9C8 clear).
// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@UBfmePod172@@V?$allocator@UBfmePod172@@@_STL@@@_STL@@IAEXPAUBfmePod172@@ABU3@ABU__false_type@2@I_N@Z,
// retail 0x001EBD3B 191B. Dedicated TU.
//
// STLport 4.5.3 vector<BfmePod172>::_M_insert_overflow (172-byte POD,
// 0xAC stride via idiv). Target evidence: pin names the overload; callees
// rowed allocate 0x001EAEBD plus __uninitialized_copy 0x001EBA30 plus
// __uninitialized_fill_n 0x001EBA5F plus _M_clear 0x001EB9C8 and pinned
// _Construct 0x001EB9E6; callers push_back 0x001EC086 plus 0x001EBFB3.
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

struct BfmePod172 {
	int a[43];
};

namespace _STL
{
template <> void _Construct<BfmePod172, BfmePod172>(BfmePod172 *, const BfmePod172 &);
template <> void vector<BfmePod172, allocator<BfmePod172> >::_M_clear();
}

template void _STL::vector<BfmePod172>::_M_insert_overflow(
	BfmePod172 *,
	const BfmePod172 &,
	const _STL::__false_type &,
	unsigned int,
	bool);
