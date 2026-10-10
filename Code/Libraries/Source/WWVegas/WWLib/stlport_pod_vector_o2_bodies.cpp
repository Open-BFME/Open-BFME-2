// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 vector members for placeholder POD elements, as
// emitted at /O2. BfmePod36 stands for the real 36-byte element; the placed
// body's stride fixes the size. No retail caller is claimed.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
struct BfmePod36 { int a[9]; };
template class _STL::vector<BfmePod36, _STL::allocator<BfmePod36 > >;
