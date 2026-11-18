// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Key identity: ObjectID, value int (map<ObjectID, int>; evidence in stlport_map_int_ptr_tree_dtor.cpp).
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <map>

#include "../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/ObjectID.h"

// Instantiate the recovered operation and its required template dependencies.
template void _STL::_Rb_tree<ObjectID, _STL::pair<ObjectID const, int>, _STL::_Select1st<_STL::pair<ObjectID const, int> >, _STL::less<ObjectID>, _STL::allocator<_STL::pair<ObjectID const, int> > >::clear(void);
