// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 12-byte BfmeE12
// element. The allocator at 0x395928 and the trivial-copy worker at 0x766F5
// are both rowed under the BfmeE12 spelling; this shard reuses it.
#include <vector>
struct BfmeE12 { int a[3]; };
template class _STL::vector<BfmeE12, _STL::allocator<BfmeE12> >;
