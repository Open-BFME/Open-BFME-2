// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?reserve@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@QAEXI@Z retail 0x002B712E 110B
// Evidence: capacity check sar-2 for 4-byte elements; _M_allocate_and_copy via int row at 0x0053BD39 ICF-folded
// allocator<PBVModuleData> via pin at 0x00068E15 and _free at 0x00030830; callers 0x0040E269 and 0x0026F8D6
// both operate on vector<const ModuleData*> via rowed push_back 0x004DFCB0 on same receiver; same 110B
// reserve shape as BfmeE8 reserve at 0x0030B876 with sar-3 and x8 scaled for 8-byte elements
// and ScienceType reserve at 0x002A1410 with sar-2 and x4 for 4-byte elements.
#include <vector>

class ModuleData;

template void _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> >::reserve(unsigned int);
