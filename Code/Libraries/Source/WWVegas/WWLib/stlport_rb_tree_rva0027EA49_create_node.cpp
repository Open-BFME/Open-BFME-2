// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHUTreeHintRef00217D4C@@@_STL@@U?$_Select1st@U?$pair@$$CBHUTreeHintRef00217D4C@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUTreeHintRef00217D4C@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHUTreeHintRef00217D4C@@@_STL@@@2@ABU?$pair@$$CBHUTreeHintRef00217D4C@@@2@@Z, retail 0x005C6728, 34 bytes.
// _M_create_node of map<int, TreeHintRef00217D4C>'s tree (8B value: int key
// at +0 plus the counted TargetRef at +4); its sole caller is that tree's
// _M_insert 0x005C6A75 (calls at 0x005C6A9D/0x005C6AB6), which
// Rva005C6CCC.cpp rows. Allocates the 0x18 node via rowed byte allocator
// 0x000307F0 then copies the value at +0x10 via rowed
// ?Rva0030CA53Set@@YAXPAVRva004733E0@@PBV1@@Z (0x0030CA53 wrapping
// Rva004733E0::set 0x0030BF66 with matching 8B layout and +4 refcount).
// Shape matches _M_create_node precedent 0x002D464E (34B, same flags without
// /I shim so allocator<char> specialization compiles). this is unused (static
// allocate plus free wrapper) so the body is identical to a free stdcall.
#include <map>
#include "../../Apt/AptRefTarget.h"
typedef _STL::pair<const int, TreeHintRef00217D4C> TreeHintPair;
typedef _STL::_Rb_tree<int, TreeHintPair, _STL::_Select1st<TreeHintPair>, _STL::less<int>, _STL::allocator<TreeHintPair> > TreeHintTree;
namespace _STL {
template <> class allocator<char> {
public:
	static char *allocate(unsigned int bytes, const void *hint);
};
}
#include "../../../../GameEngine/Include/Common/Rva004733E0Obj.h"
class Rva004733E0
{
	int m_00;
	Rva004733E0Obj *m_04;
public:
	Rva004733E0 *set(const Rva004733E0 *src);
};
void Rva0030CA53Set(Rva004733E0 *dst, const Rva004733E0 *src);
// ?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHUTreeHintRef00217D4C@@@_STL@@U?$_Select1st@U?$pair@$$CBHUTreeHintRef00217D4C@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUTreeHintRef00217D4C@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHUTreeHintRef00217D4C@@@_STL@@@2@ABU?$pair@$$CBHUTreeHintRef00217D4C@@@2@@Z
template <>
TreeHintTree::_Link_type TreeHintTree::_M_create_node(const TreeHintTree::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreeHintTree::value_type>), 0);
	Rva0030CA53Set((Rva004733E0 *)&node->_M_value_field, (const Rva004733E0 *)&value);
	return node;
}
template TreeHintTree::_Link_type TreeHintTree::_M_create_node(const TreeHintTree::value_type &);
