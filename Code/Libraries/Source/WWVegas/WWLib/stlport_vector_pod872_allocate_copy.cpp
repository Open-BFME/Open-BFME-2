// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 872-byte POD element.
// The allocator and the trivial-copy worker are both rowed; the placeholder
// BfmePod872 names only the 872-byte stride, matching the pod-vector TU convention.
#include <vector>
struct BfmePod872 { int a[218]; };
template class _STL::vector<BfmePod872, _STL::allocator<BfmePod872> >;
