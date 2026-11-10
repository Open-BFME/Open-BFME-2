// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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



// The record is LadderPref under a long key: the node construct call goes to
// the rowed _Construct<pair<const long, LadderPref>> at 0x005DFBDE
// (stlport_map_long_ladderpref.cpp). Four units emit this member for that map.
#include "../../../../GameEngine/Include/GameNetwork/LadderPref.h"
// Declared only: the rowed copy serves the call.
namespace _STL { template <> void _Construct<pair<const long, LadderPref>, pair<const long, LadderPref> >(pair<const long, LadderPref> *, const pair<const long, LadderPref> &); }
// Instantiate the recovered member; retain only its required template dependencies.
template _STL::_Rb_tree_node<_STL::pair<long const, LadderPref> > * _STL::_Rb_tree<long, _STL::pair<long const, LadderPref>, _STL::_Select1st<_STL::pair<long const, LadderPref> >, _STL::less<long>, _STL::allocator<_STL::pair<long const, LadderPref> > >::_M_create_node(_STL::pair<long const, LadderPref> const &);
