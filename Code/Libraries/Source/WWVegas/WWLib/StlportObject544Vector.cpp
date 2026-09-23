// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target object view; original type and member fields are unknown.
// Target copy construction and nonvirtual destruction visit owned subobjects.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct BfmeObject544
{
    unsigned char opaque[544];
    ~BfmeObject544();
    BfmeObject544();
    BfmeObject544(const BfmeObject544&);
};

template class _STL::vector<BfmeObject544, _STL::allocator<BfmeObject544> >;
