// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 60-byte POD
// element at RVA 0xB975D. The allocator at 0x29B27B and the trivial-copy
// worker at 0xB651E are both rowed; the placeholder BfmePod60 names only the
// 60-byte stride, matching the pod-vector TU convention.
#include <vector>
struct BfmePod60 { int a[15]; };
template class _STL::vector<BfmePod60, _STL::allocator<BfmePod60> >;
