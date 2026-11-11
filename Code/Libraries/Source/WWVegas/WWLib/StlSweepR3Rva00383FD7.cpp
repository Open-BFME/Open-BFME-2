// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#define _STLP_BFME_TREE_NODE_BASE_O2  // emit retail's _Rb_tree_node_base::_S_minimum/_S_maximum (vendor/stlport/stl/_tree.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <set>










#include "../../../../GameEngine/Include/Common/Rva00383B39Key.h"
// Instantiate the recovered member; retain only its required template dependencies.
template _STL::_Rb_tree<Rva00383B39Key, Rva00383B39Key, _STL::_Identity<Rva00383B39Key>, _STL::less<Rva00383B39Key>, _STL::allocator<Rva00383B39Key> > & _STL::_Rb_tree<Rva00383B39Key, Rva00383B39Key, _STL::_Identity<Rva00383B39Key>, _STL::less<Rva00383B39Key>, _STL::allocator<Rva00383B39Key> >::operator=(_STL::_Rb_tree<Rva00383B39Key, Rva00383B39Key, _STL::_Identity<Rva00383B39Key>, _STL::less<Rva00383B39Key>, _STL::allocator<Rva00383B39Key> > const &);
