// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 128-byte POD element.
// The allocator and the trivial-copy worker are both rowed; the placeholder
// BfmePod128 names only the 128-byte stride, matching the pod-vector TU convention.
#include <vector>
struct BfmePod128 { int a[32]; };
template class _STL::vector<BfmePod128, _STL::allocator<BfmePod128> >;
