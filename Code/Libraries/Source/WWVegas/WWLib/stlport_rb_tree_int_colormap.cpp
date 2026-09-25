// cl: /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// Tree mapping int keys to MultiplayerColorDefinition values (the
// multiplayer color table). The node allocator and the pair _Construct are
// already rowed (0x307F0 and 0x380E07), so the custom _M_create_node below
// calls them directly, mirroring stlport_rb_tree_hint_asciistring_set.cpp.
// NOTE (MSVC 7.1): an explicit member specialization is silently dropped
// unless the TU also explicitly instantiates other members of the same
// class; the three instantiation lines at the bottom exist for that reason.
#include <map>

class MultiplayerColorDefinition
{
public:
	MultiplayerColorDefinition(const MultiplayerColorDefinition &other);

private:
	char m_pad[64];
};

typedef _STL::pair<const int, MultiplayerColorDefinition> ColorMapValue;
typedef _STL::_Rb_tree<int, ColorMapValue, _STL::_Select1st<ColorMapValue>, _STL::less<int>, _STL::allocator<ColorMapValue> > ColorMapTree;

namespace _STL {
// Declared only; the gate resolves this reference to the rowed body at
// 0x380E07 (same mechanism as the fill_n cascade).
template <>
void _Construct<ColorMapValue, ColorMapValue>(ColorMapValue *, const ColorMapValue &);
}

// ?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHVMultiplayerColorDefinition@@@_STL@@U?$_Select1st@U?$pair@$$CBHVMultiplayerColorDefinition@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHVMultiplayerColorDefinition@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBHVMultiplayerColorDefinition@@@_STL@@@2@ABU?$pair@$$CBHVMultiplayerColorDefinition@@@2@@Z
template <>
ColorMapTree::_Link_type ColorMapTree::_M_create_node(const ColorMapValue &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<ColorMapValue>), 0);
	_STL::_Construct(&node->_M_value_field, value);
	return node;
}

template ColorMapTree::iterator ColorMapTree::insert_unique(ColorMapTree::iterator, const ColorMapValue &);
template void ColorMapTree::_M_erase(ColorMapTree::_Link_type);
template void ColorMapTree::clear();
template _STL::_Rb_tree_base<ColorMapValue, _STL::allocator<ColorMapValue> >::_Rb_tree_base(const _STL::allocator<ColorMapValue> &);
template _STL::_Rb_tree<int, ColorMapValue, _STL::_Select1st<ColorMapValue>, _STL::less<int>, _STL::allocator<ColorMapValue> >::_Rb_tree(const _STL::less<int> &, const _STL::allocator<ColorMapValue> &);
