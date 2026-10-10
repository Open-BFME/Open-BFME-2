// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target object view; original type and member fields are unknown.
// Copy construction writes vptrs and cleanup dispatches a virtual destructor.
#define _STLP_NO_EXCEPTIONS 1
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

struct BfmeObject476
{
    virtual ~BfmeObject476();
    unsigned char opaque[472];
    BfmeObject476();
    BfmeObject476(const BfmeObject476&);
};

template class _STL::vector<BfmeObject476, _STL::allocator<BfmeObject476> >;
