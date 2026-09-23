// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target object view; original type and member fields are unknown.
// Copy construction writes vptrs and cleanup dispatches a virtual destructor.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct BfmeObject476
{
    virtual ~BfmeObject476();
    unsigned char opaque[472];
    BfmeObject476();
    BfmeObject476(const BfmeObject476&);
};

template class _STL::vector<BfmeObject476, _STL::allocator<BfmeObject476> >;
