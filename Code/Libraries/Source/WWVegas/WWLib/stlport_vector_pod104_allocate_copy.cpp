// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 104-byte POD element.
// The allocator and the trivial-copy worker are both settled; the placeholder
// BfmePod104 names only the 104-byte stride, matching the pod-vector TU convention.
#include <vector>
struct BfmePod104 { int a[26]; };
template class _STL::vector<BfmePod104, _STL::allocator<BfmePod104> >;
