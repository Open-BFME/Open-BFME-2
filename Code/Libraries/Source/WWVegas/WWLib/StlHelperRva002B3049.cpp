// Reference: pristine STLport4.5.3. Address-derived opaque record ABI.
// Target boundary and literal pointer stride establish storage width only; no application identity inferred.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>



// Native2B3049 uses four-byte elements and calls the complete2B2F97 holder assignment.
class Rva002B2F97 { public: Rva002B2F97&operator=(const Rva002B2F97&); private: char bytes[4]; };
namespace _STL {template<> void _Construct<Rva002B2F97,Rva002B2F97>(Rva002B2F97*,const Rva002B2F97&);}
template Rva002B2F97 *_STL::__copy_backward(Rva002B2F97*,Rva002B2F97*,Rva002B2F97*,const _STL::random_access_iterator_tag&,int*);
template Rva002B2F97 *_STL::__copy_backward_ptrs(Rva002B2F97*,Rva002B2F97*,Rva002B2F97*,const _STL::__false_type&);
