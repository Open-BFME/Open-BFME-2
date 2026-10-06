// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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



struct Rva00501E22Record {  char bytes[1]; };


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::_Rb_tree_iterator<_STL::pair<int const, Rva00501E22Record>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00501E22Record> > > _STL::map<int, Rva00501E22Record, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00501E22Record> > >::insert(_STL::_Rb_tree_iterator<_STL::pair<int const, Rva00501E22Record>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00501E22Record> > >, _STL::pair<int const, Rva00501E22Record> const &);
