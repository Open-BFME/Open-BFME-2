// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Record name remains neutral; the target key and payload evidence is below.
// cl: /O2 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

#include <map>



class Rva009EF0D0Element;
// Native refresh6227E0 compares the pair key with CMP/JAE (622A32/37), places
// the element pointer in pair+4 (622A28/2C), and reads it back for eviction.
// These are target ABI facts; the original mapped record name is unknown.
struct Rva00620A00Record { Rva009EF0D0Element *m_entry; };
// The owned cleanup below instantiates the tree destructor. Retail evidence
// does not require the rest of map's methods in this unit.

// Native620D90..620D95 tail JMP620A00 to the sole owned tree destructor.
// Unadjusted receiver only; original wrapper and enclosing type unknown.
struct Rva00620D90TreeRelease { void release(); };
void Rva00620D90TreeRelease::release() {
    typedef _STL::pair<const unsigned int,Rva00620A00Record> Value;
    typedef _STL::_Rb_tree<unsigned int,Value,_STL::_Select1st<Value>,_STL::less<unsigned int>,_STL::allocator<Value> > Tree;
    reinterpret_cast<Tree *>(this)->~_Rb_tree();
}
