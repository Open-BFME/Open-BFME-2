// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 260-byte POD element.
// The allocator and the trivial-copy worker are both rowed; the placeholder
// BfmePod260 names only the 260-byte stride, matching the pod-vector TU convention.
#include <vector>
struct BfmePod260 { int a[65]; };
template class _STL::vector<BfmePod260, _STL::allocator<BfmePod260> >;
