// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 24-byte POD element.
// The allocator and the trivial-copy worker are both rowed; the placeholder
// BfmePod24 names only the 24-byte stride, matching the pod-vector TU convention.
#include <vector>
struct BfmePod24 { int a[6]; };
template class _STL::vector<BfmePod24, _STL::allocator<BfmePod24> >;
