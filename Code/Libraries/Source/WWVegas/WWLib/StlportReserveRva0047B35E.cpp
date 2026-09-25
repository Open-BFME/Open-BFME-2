// Target boundary 0x0047B35E/125: the body reserves storage for a vector
// (start/finish/end at +0/+4/+8) with 24-byte elements. The target calls the
// matched allocate/copy helper at 0x0047A6C0 and the shared 24-byte allocator
// at 0x00395944. The element's application type and payload are not established.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_MEMBER_TEMPLATES /Ireference/shims/bfmealloc
// stlport
#include <vector>

// Address-derived codegen view; only the 24-byte stride is witnessed.
struct Rva0047B35EElement { int opaque[6]; };

template void _STL::vector<Rva0047B35EElement,
                            _STL::allocator<Rva0047B35EElement> >::reserve(unsigned int);
