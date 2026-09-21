// cl: /O2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 vector members for placeholder POD elements, as
// emitted at /O2. BfmePod36 stands for the real 36-byte element; the placed
// body's stride fixes the size. No retail caller is claimed.
#include <vector>
struct BfmePod36 { int a[9]; };
template class _STL::vector<BfmePod36, _STL::allocator<BfmePod36 > >;
