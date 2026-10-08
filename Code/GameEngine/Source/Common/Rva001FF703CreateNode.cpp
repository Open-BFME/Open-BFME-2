// cl: /O1 /D_STLP_NO_EXCEPTIONS /MD
// stlport
//
// ?_M_create_node@?$_Rb_tree@W4ScienceType@@U?$pair@$$CBW4ScienceType@@_N@_STL@@U?$_Select1st@U?$pair@$$CBW4ScienceType@@_N@_STL@@@3@U?$less@W4ScienceType@@@3@V?$allocator@U?$pair@$$CBW4ScienceType@@_N@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBW4ScienceType@@_N@_STL@@@2@ABU?$pair@$$CBW4ScienceType@@_N@2@@Z @0x001FF703 34B
// Named lane: _Rb_tree<ScienceType,pair<const ScienceType,bool>>::_M_create_node.
// Allocates 0x18-byte node via pool 0x002EB448 at g_Va00DB9440 then constructs
// pair at +0x10 via rowed _Construct 0x001FF5AC. Evidence: callee REL32s in
// _M_insert 0x001FF791 (StlportIntMapInsertFamily.cpp); callers at 0x001FF7B9
// 0x001FF7D2 link bonus.
#include <map>

enum ScienceType
{
	SCIENCE_INVALID = -1
};

#include "../../Include/Common/Rva002E8548Pool.h"

typedef _STL::pair<const ScienceType, bool> SciencePair;
typedef _STL::pair<const unsigned int, bool> UIntPair;
typedef _STL::_Rb_tree<ScienceType, SciencePair, _STL::_Select1st<SciencePair>, _STL::less<ScienceType>, _STL::allocator<SciencePair> > ScienceTree;

// ?_M_create_node@?$_Rb_tree@W4ScienceType@@U?$pair@$$CBW4ScienceType@@_N@_STL@@U?$_Select1st@U?$pair@$$CBW4ScienceType@@_N@_STL@@@3@U?$less@W4ScienceType@@@3@V?$allocator@U?$pair@$$CBW4ScienceType@@_N@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBW4ScienceType@@_N@_STL@@@2@ABU?$pair@$$CBW4ScienceType@@_N@2@@Z @0x001FF703
template <>
_STL::_Rb_tree_node<SciencePair> *
_STL::_Rb_tree<ScienceType, SciencePair, _STL::_Select1st<SciencePair>, _STL::less<ScienceType>, _STL::allocator<SciencePair> >::_M_create_node(const SciencePair &value)
{
	void *raw = g_Va00DB9440.rva002EB448();
	_Link_type node = (_Link_type)raw;
	_STL::_Construct(reinterpret_cast<UIntPair *>(&node->_M_value_field), reinterpret_cast<const UIntPair &>(value));
	return node;
}

struct ScienceTreeExposer : public ScienceTree
{
	static _Link_type callCreate(ScienceTreeExposer &t, const value_type &v);
};

// ?callCreate@ScienceTreeExposer@@SAPAU?$_Rb_tree_node@U?$pair@$$CBW4ScienceType@@_N@_STL@@@_STL@@AAU1@ABU?$pair@$$CBW4ScienceType@@_N@3@@Z present-unmatched
ScienceTree::_Link_type ScienceTreeExposer::callCreate(ScienceTreeExposer &t, const ScienceTree::value_type &v)
{
	return t._M_create_node(v);
}
