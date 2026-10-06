// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// STLport copy_backward for 12-byte POD (BfmeE12 stand-in) at retail 0x0051C94D, 27 bytes.
// Pinned callee ??$__copy_backward_ptrs@PAUBfmeE12@@PAU1@@_STL@@YAPAUBfmeE12@@PAU1@00ABU__false_type@0@@Z 0x000B6813.
// Donor vendor/stlport/stl/_algobase.h copy_backward; callers 0x0051CDD0 0x00587B91 0x005D5DA5.
// Uses STOCK vendor headers (no bfmealloc shim): the shim marks aux/ptrs __forceinline
// which inlines to a 29B __copy_backward call; stock keeps the 27B ptrs call.
// Precedent Code/Libraries/Source/WWVegas/WWLib/stlport_deque_e12_copy_backward.cpp.
#include <vector>
struct BfmeE12 { float x, y, z; };
template BfmeE12* _STL::copy_backward<BfmeE12*, BfmeE12*>(BfmeE12*, BfmeE12*, BfmeE12*);
