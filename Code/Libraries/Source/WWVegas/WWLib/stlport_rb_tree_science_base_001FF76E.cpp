// cl: /DNDEBUG /MD /EHsc
//
// ??0?$_Rb_tree_base@U?$pair@$$CBW4ScienceType@@_N@_STL@@V?$allocator@U?$pair@$$CBW4ScienceType@@_N@_STL@@@2@@_STL@@QAE@ABV?$allocator@U?$pair@$$CBW4ScienceType@@_N@_STL@@@1@@Z @0x001FF76E 35B
// STLport _Rb_tree_base header-node ctor for ScienceStore map<ScienceType,bool>.
// Evidence: pin name; callees AllocProxy 0x0014F3C4 and pool 0x002EB448 at g_Va00DB9440;
// caller _Rb_tree ctor 0x001FF852; shape precedent Rva002F0C55Helper/Rva002F0C32Helper
// (proxy via rowed int ctor then pool pop to +0 returning this).
#include "../../../../GameEngine/Include/Common/Rva002E8548Pool.h"

// stlport
#include <map>

enum ScienceType
{
	SCIENCE_INVALID = -1
};

typedef _STL::pair<const ScienceType, bool> SciencePair;
typedef _STL::allocator<SciencePair> ScienceAlloc;

template <>
_STL::_Rb_tree_base<SciencePair, ScienceAlloc>::_Rb_tree_base(const ScienceAlloc &__a) :
    _M_header(_STLP_CONVERT_ALLOCATOR(__a, _Node), (_Node *)0)
{
    _M_header._M_data = (_Node *)g_Va00DB9440.rva002EB448();
}

template _STL::_Rb_tree_base<SciencePair, ScienceAlloc>::_Rb_tree_base(const ScienceAlloc &);
