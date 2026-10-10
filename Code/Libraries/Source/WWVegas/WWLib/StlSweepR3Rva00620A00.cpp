// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O2 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <map>



struct Rva00620A00Record {  char bytes[1]; };
template class _STL::map<int,Rva00620A00Record>;

// Native620D90..620D95 tail JMP620A00 to the sole owned tree destructor.
// Unadjusted receiver only; original wrapper and enclosing type unknown.
struct Rva00620D90TreeRelease { void release(); };
void Rva00620D90TreeRelease::release() {
    typedef _STL::pair<const int,Rva00620A00Record> Value;
    typedef _STL::_Rb_tree<int,Value,_STL::_Select1st<Value>,_STL::less<int>,_STL::allocator<Value> > Tree;
    reinterpret_cast<Tree *>(this)->~_Rb_tree();
}
