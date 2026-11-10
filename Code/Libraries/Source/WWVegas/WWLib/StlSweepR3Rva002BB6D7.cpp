// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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



// 52-byte record: retail's range destroy 0x002BB6A5 steps by 0x34 and calls the
// rowed BfmeAssignRecord52 destructor 0x002B707E, reached here by a qualified call.
struct BfmeAssignRecord52 { ~BfmeAssignRecord52(); };
struct Rva002BB6D7Record
{
	__forceinline ~Rva002BB6D7Record() { ((BfmeAssignRecord52 *)this)->BfmeAssignRecord52::~BfmeAssignRecord52(); }
	char bytes[52];
};


// Instantiate the recovered member; retain only its required template dependencies.
template void _STL::vector<Rva002BB6D7Record, _STL::allocator<Rva002BB6D7Record> >::_M_clear(void);
