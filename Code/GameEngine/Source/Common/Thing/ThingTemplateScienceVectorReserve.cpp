// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?reserve@?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@QAEXI@Z retail 0x002A1410 110B
// Evidence: capacity check sar-2 for 4-byte elements; _M_allocate_and_copy via ScienceType pin at 0x0031B9EB
// allocator<ScienceType> via pin at 0x00068E15 and _free at 0x00030830; callers 0x002E0298 and 0x00398280
// both operate on vector<ScienceType> via rowed erase 0x00532803 and push_back 0x002E01C6; same 110B
// reserve shape as BfmeE8 reserve at 0x0030B876 with sar-3 and x8 scaled for 8-byte elements.
#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};

template void _STL::vector<ScienceType, _STL::allocator<ScienceType> >::reserve(unsigned int);
