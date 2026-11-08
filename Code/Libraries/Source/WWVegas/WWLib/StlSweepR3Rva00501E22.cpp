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

// Preserve the native inline comparison and the verified external owner at 0x00626F90.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &left, const int &right) const
{ return left < right; }
}



// The mapped value is retail's 0x18-byte Rva0050055D: node 0x0050116B allocates 0x2C bytes and 0x00500839 copies through 0x0050055D.
class Rva0050055D { public: Rva0050055D(const Rva0050055D &); private: char m_trees[0x18]; };
struct Rva00501E22Record { Rva0050055D value; };


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::_Rb_tree_iterator<_STL::pair<int const, Rva00501E22Record>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00501E22Record> > > _STL::map<int, Rva00501E22Record, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00501E22Record> > >::insert(_STL::_Rb_tree_iterator<_STL::pair<int const, Rva00501E22Record>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00501E22Record> > >, _STL::pair<int const, Rva00501E22Record> const &);
