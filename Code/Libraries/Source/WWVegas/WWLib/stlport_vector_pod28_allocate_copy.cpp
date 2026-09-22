// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 28-byte POD element.
// The allocator and the trivial-copy worker are both settled; the placeholder
// BfmePod28 names only the 28-byte stride, matching the pod-vector TU convention.
#include <vector>
struct BfmePod28 { int a[7]; };
template class _STL::vector<BfmePod28, _STL::allocator<BfmePod28> >;
