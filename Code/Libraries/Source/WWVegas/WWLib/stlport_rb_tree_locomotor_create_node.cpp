// cl: /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
//
// LocomotorSetType to template-vector map node factory (AIUpdate parse cluster).
// Companion to LocomotorSetMapInstantiation.cpp: that TU carries the EH
// members (_M_insert, insert_unique); this TU carries the frameless
// _M_create_node 34B @0x1E7E7D under _STLP_NO_EXCEPTIONS, mirroring
// stlport_rb_tree_int_colormap.cpp. The pair _Construct folds to the rowed
// int-pair body at 0x1E7243 (same 16B layout, same vector copy 0x2CFAB9).

#include <map>
#include <vector>

class LocomotorTemplate;

enum LocomotorSetType
{
	LOCOMOTORSET_INVALID = -1,

	LOCOMOTORSET_NORMAL = 0,
	LOCOMOTORSET_NORMAL_UPGRADED,
	LOCOMOTORSET_FREEFALL,
	LOCOMOTORSET_WANDER,
	LOCOMOTORSET_PANIC,
	LOCOMOTORSET_TAXIING,
	LOCOMOTORSET_SUPERSONIC,
	LOCOMOTORSET_SLUGGISH,

	LOCOMOTORSET_COUNT
};

typedef _STL::vector<const LocomotorTemplate *> BfmeLocomotorTemplateVector;
typedef _STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> LocomotorMapValue;
typedef _STL::_Rb_tree<LocomotorSetType, LocomotorMapValue, _STL::_Select1st<LocomotorMapValue>, _STL::less<LocomotorSetType>, _STL::allocator<LocomotorMapValue> > LocomotorMapTree;
typedef _STL::map<LocomotorSetType, BfmeLocomotorTemplateVector, _STL::less<LocomotorSetType>, _STL::allocator<LocomotorMapValue> > LocomotorMap;

namespace _STL {
// Declared only; the gate resolves this reference to the ICF-folded body at
// 0x1E7243 (rowed as dup_001E7243, same 45B shape via rowed copy 0x795C1).
template <>
void _Construct<LocomotorMapValue, LocomotorMapValue>(LocomotorMapValue *, const LocomotorMapValue &);
}

// ?_M_create_node@?$_Rb_tree@W4LocomotorSetType@@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@U?$_Select1st@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@U?$less@W4LocomotorSetType@@@3@V?$allocator@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@2@ABU?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@2@@Z
template <>
LocomotorMapTree::_Link_type LocomotorMapTree::_M_create_node(const LocomotorMapValue &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<LocomotorMapValue>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}

template LocomotorMapTree::iterator LocomotorMapTree::insert_unique(LocomotorMapTree::iterator, const LocomotorMapValue &);
template void LocomotorMapTree::_M_erase(LocomotorMapTree::_Link_type);
template void LocomotorMapTree::clear();
template _STL::_Rb_tree_base<LocomotorMapValue, _STL::allocator<LocomotorMapValue> >::_Rb_tree_base(const _STL::allocator<LocomotorMapValue> &);
template LocomotorMapTree::_Rb_tree(const _STL::less<LocomotorSetType> &, const _STL::allocator<LocomotorMapValue> &);
template LocomotorMap::map();
