// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 172-byte POD element.
// The allocator and the trivial-copy worker are both rowed; the placeholder
// BfmePod172 names only the 172-byte stride, matching the pod-vector TU convention.
#include <vector>
struct BfmePod172 { int a[43]; };
template class _STL::vector<BfmePod172, _STL::allocator<BfmePod172> >;
